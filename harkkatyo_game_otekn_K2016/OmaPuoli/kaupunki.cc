#include "kaupunki.hh"
#include "pelinakyma.hh"
#include <QImage>
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QMovie>
#include <exception>
#include "alustusvirhe.hh"
#include "funktiot.hh"


namespace OmaPuoli
{

// Luokka pitaa kirjaa tilastoista, pelinakymasta, droonista, seka
// kaikista toimijoista. Luokka myos toimii rajapintana KurssinPuolen
// koodien kanssa.

Kaupunki::Kaupunki(QObject *parent)
    : QObject(parent)
{
    kaupunki_alustus_tilassa_ = true;
}


Kaupunki::~Kaupunki()
{

}

// Asettaa taustakuvan pelinakymaan. Isoa taustakuvaa ei kayteta lainkaan.
void Kaupunki::asetaTausta(QImage& perustaustakuva, QImage& isotaustakuva){
    try{
        taustakuva_ = perustaustakuva;
        pelinakyma_.asetaTaustakuva(taustakuva_);
    }
    catch (std::exception e){
        throw Rajapinta::AlustusVirhe("Kuvan asettaminen epaonnistui tai kuva on epakelpo.");
    }

}

void Kaupunki::asetaKello(QTime kello){
    kello_ = kello;
}


// Lisataan pysakki shared_ptr pysakit_ vektoriin.
void Kaupunki::lisaaPysakki(std::shared_ptr<Rajapinta::PysakkiRP> pysakki){
    pysakit_.push_back(pysakki);
}


// Metodi piirtaa kaikki kuvassa nakyvat asiat Pelinakymalla, luo droonin
// seka asettaa connecteilla toimivat ominaisuudet.
void Kaupunki::peliAlkaa(){

    // Piirretaan kuvassa nakyvat oliot.
    pelinakyma_.piirraToimijat(toimijat_);
    pelinakyma_.piirraPysakit(pysakit_);
    pelinakyma_.piirraPisteet();

    // Luodaan drooni ja naytetaan pelinakyma.
    drooni_ = pelinakyma_.luoDrooni();
    pelinakyma_.show();

    peli_ollut_kaynnissa_.start();

    // Kaynnistetaan droonin gif ja paivitetaan droonin kuva aina kun gifin
    // kuva paivittyy.
    movie_ = new QMovie(":/kuvat/drooni.gif");
    movie_->start();
    connect(movie_, SIGNAL(updated(const QRect &)), this, SLOT(drooninKuvaMuuttunut()));

    // Paivitetaan pelinakyma PAIVITYSVALI_MS valein.
    connect(&ajastin_, SIGNAL(timeout()), this, SLOT(paivitaPelinakyma()));
    ajastin_.start(PAIVITYSVALI_MS);

    peli_kaynnissa_ = true;
}


// Lisataan uusi toimija toimijat_ listaan.
void Kaupunki::lisaaToimija(std::shared_ptr<Rajapinta::ToimijaRP> uusitoimija){
    toimijat_.push_back(uusitoimija);
}


// Poistetaan toimija toimijat_ listasta.
void Kaupunki::poistaToimija(std::shared_ptr<Rajapinta::ToimijaRP> toimija){

    // Etsitaan poistettava toimija Kaupungin toimijoista iteraattorin avulla.
    std::list< std::shared_ptr<Rajapinta::ToimijaRP>>::iterator it = toimijat_.begin();

    while(it != toimijat_.end()){

        // Poistetaan loydetty toimija
        if (*it  == toimija){
            toimijat_.erase(it);
            break;
        }
        it++;
    }
}


// Tuhotaan parametrina saatu toimia.
void Kaupunki::toimijaTuhottu(std::shared_ptr<Rajapinta::ToimijaRP> toimija){
    for (auto etsittava_toimija : toimijat_) {
        if (etsittava_toimija == toimija){
            etsittava_toimija->tuhoa();
        }
    }
}


// Tarkistetaan loytyyko parametrina saatu toimija toimijat_ listasta.
bool Kaupunki::loytyykoToimija(std::shared_ptr<Rajapinta::ToimijaRP> toimija) const {
    for (auto etsittava_toimija : toimijat_) {
        if (etsittava_toimija == toimija){
            return true;
        }
    }
    return false;
}


// Jos toimija on liikahtanut, kerataan se pelinakyman metodilla
// keraaLiikkuneetToimijat talteen.
void Kaupunki::toimijaLiikkunut(std::shared_ptr<Rajapinta::ToimijaRP> toimija){
    pelinakyma_.keraaLiikkuneetToimijat(toimija);
}


// Tuhotaan busseissa olevat matkustajat.
void Kaupunki::tuhoaBussienMatkustajat(std::list<std::shared_ptr<Rajapinta::ToimijaRP>>
                                       lista_lahella_olevista_nysseista) {

    // Kaydaan kaikki bussit lapi, tuhotaan niiden matkustajat
    // ja kerrytetaan pisteita.
    for(auto nysse : lista_lahella_olevista_nysseista){
        Rajapinta::KulkuneuvoRP* kulkuneuvo =
                dynamic_cast<Rajapinta::KulkuneuvoRP*>(nysse.get());

        std::vector<std::shared_ptr<Rajapinta::MatkustajaRP> >
                vektori_nyssen_matkustajista = kulkuneuvo->annaMatkustajat();

        int lisattavat_pisteet = 0;
        for(auto matkustaja : vektori_nyssen_matkustajista){
            toimijaTuhottu(matkustaja);
            lisattavat_pisteet += 1;
        }
        tilasto_.lisaaPisteita(lisattavat_pisteet);
    }
}


// Paivitetaan pelinakyma PAIVITYSVALI_MS paivitys valein.
//__LISAOSA?__: Tasainen ruudunpaivitys.
void Kaupunki::paivitaPelinakyma() {

    // Etsitaan kursorin sijainti ja tiputetaan siihen pommi, jo droonilla
    // on valilyonti pohjassa.
    if(drooni_->palautaValilyonninTila()){
        Rajapinta::Sijainti kursorin_sij = pelinakyma_.palautaKursorinSijainti();

        // Kerataan lista niista busseista, jotka ovat pommin tiputuskohdan
        // lahella.
        std::list<std::shared_ptr<Rajapinta::ToimijaRP>>
                lista_lahella_olevista_nysseista =
                pelinakyma_.tiputaPommiTarvittaessa( annaToimijatLahella(kursorin_sij));

        // Jos tallaisia busseja loytyi, tuhotaan niiden matkustajat.
        if(lista_lahella_olevista_nysseista.size() > 0){
            tuhoaBussienMatkustajat(lista_lahella_olevista_nysseista);
        }
    }

    // Paivitetaan pisteet, ja lopulta piirretaan kaikki tapahtumat kuvaan.
    pelinakyma_.paivitaPisteet(tilasto_.annaPisteet());
    pelinakyma_.paivitaPelinakyma();
    pelinakyma_.paivitaKello(peli_ollut_kaynnissa_);

    // Jos peli on voitettu, kaynnistetaan peliVoitettu metodi.
    if(tarkistaVoitto()){
        peliVoitettu();
    }

}


// Jos droonin kuva muuttuu, paivitetaan se.
void Kaupunki::drooninKuvaMuuttunut() {
    pelinakyma_.paivitaDrooninKuva(movie_->currentPixmap());
}


// Palauttaa vektorin lahella olevista toimijoista.
std::vector<std::shared_ptr<Rajapinta::ToimijaRP>>
            Kaupunki::annaToimijatLahella(Rajapinta::Sijainti paikka) const {

    std::vector<std::shared_ptr<Rajapinta::ToimijaRP>> lahella_olevat_toimijat;

    // Kaydaan toimijat lapi ja jos ne ovat melko lahella, kerataan ne
    // lahella_olevat_toimijat vectoriin.
    for(auto toimija : toimijat_){
        if(OmaPuoli::onkoMelkoLahella(toimija->annaSijainti(),paikka)){
            lahella_olevat_toimijat.push_back(toimija);
        }
    }
    return lahella_olevat_toimijat;
}


// Tarkistaa onko peli voitettu.
bool Kaupunki::tarkistaVoitto() {
    if(tilasto_.annaPisteet() >= PISTEET_VOITTOON){
        return true;
    }
    else{
        return false;
    }
}


// Peli on voitettu, paivitetaan pelitilanne.
void Kaupunki::peliVoitettu() {
    pelinakyma_.paivitaPelitilanne(true);   
}

// Peli loppunut, palautetaan tosi.
bool Kaupunki::peliLoppunut() const{
    if(peli_kaynnissa_ == false){
        return true;
    }
    else{
        return false;
    }
}


}
