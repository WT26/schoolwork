#include "drooni.hh"
#include <QKeyEvent>
#include <QThread>
#include <QMovie>
#include "funktiot.hh"
#include <QObject>

// Drooni jolla lennetaan kaupungin ylla. Perii ToimijaRP, jotta voi
// kayttaa hyodyllisia Sijainti ja muita Rajapinta funktioita.
// Perii myos QGraphicsPixmapItemin jotta helppo asettaa kuva
// ja sijoittaa QGraphicsSceneen.

namespace OmaPuoli {

Drooni::Drooni() {
    suunta_kulma_ = 0;
    nykyinen_nopeus_ = 0;
    valilyonti_pohjassa_ = false;
}

Drooni::~Drooni()
{

}

// Metodi, joka odottaa kayttajan nappaimisto toimintoja.
// Metodi vaihtaa droonin lentonopeutta, kaantaa suuntaa
// tai tiputtaa pommeja. Mahdollisia nappaimia ovat
// nuolinappaimet seka spacebar.
void Drooni::keyPressEvent(QKeyEvent * event){
    if  (event->key() == Qt::Key_Left) {

        // Suuntakulma vaihtuu yhden pykalan vasemmalle.
        // Kaannopohjassa boolean vaihtaa myos arvoaan.
        // Talla estetaan se ettei kaannoksia tapahdu miljoonaa
        // perakkain.
        if(!kaannospohjassa_){
            suunta_kulma_ -= 1;
            if(suunta_kulma_ < 0){
                suunta_kulma_ = 7;
            }
            kaannospohjassa_ = true;
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(!kaannospohjassa_){
            suunta_kulma_ += 1;
            if(suunta_kulma_ > 7){

                suunta_kulma_ = 0;
            }
            kaannospohjassa_ = true;
        }

    }
    else if (event->key() == Qt::Key_Up){
        // Kaasupohjassa boolean vaihtuu todeksi, jottei
        // hidastaVauhtia funktio ala hidastaa droonin
        // vauhtia. Lisaa myos nykyista nopeutta sopivilla
        // arvoilla. Arvot valittu ja viilattu sopiviksi,
        // mahdotonta kayttaa vakioita.
        kaasupohjassa_ = true;
        if(nykyinen_nopeus_ <= 2){
             nykyinen_nopeus_ += 3;
        }
        nykyinen_nopeus_ *= 1.5;
    }
    else if (event->key() == Qt::Key_Down){
        // Jarrupohjassa eli hidastetaan droonin vauhtia.
        nykyinen_nopeus_ -= 1;

    }
}


// Kutsutaan paivitysvalein, ja hidastetaan
// Droonin vauhtia, jollei kaasu ole pohjassa.
void Drooni::hidastaVauhtia(){
    if(!kaasupohjassa_){
        nykyinen_nopeus_ *= 0.8;
        if(nykyinen_nopeus_ <= 0){
            nykyinen_nopeus_ = 0;
        }
    }
}


void Drooni::keyReleaseEvent(QKeyEvent * event){
    // Kun nappain ei ole enaa pohjassa, asetetaan kaannospohjassa_
    // tai kaasupohjassa_ tai valilyonti_pohjassa_ epatodeksi.
    // Naita arvoja hyodynnetaan kaantamisessa, jarrutuksessa seka
    // siina ettei pommeja tiputeta miljoonaa sekunnissa.
    if  (event->key() == Qt::Key_Left) {
        if(!event->isAutoRepeat()){
            kaannospohjassa_ = false;
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(!event->isAutoRepeat()){
            kaannospohjassa_ = false;
        }
    }
    else if (event->key() == Qt::Key_Up){
        if(!event->isAutoRepeat()){
            kaasupohjassa_ = false;
        }
    }
    else if (event->key() == Qt::Key_Space){
        if(!event->isAutoRepeat()){
            valilyonti_pohjassa_ = true;
        }
    }
}


// Tama metodi paivittaa nykyisen Droonin Gifin vaiheen.
// Koska kaupunki on QObject, pystyy se kasittelemaan connecteja.
// Kaupungilla on siis connect, joka saa signaaleja aina kun gifin
// framen on aika vaihtua. Sen slottina on metodi joka kutsuu tata metodia,
// paivittaen droonin_kuvan. Taman jalkeen useammin kutsuttava
// pelinakyman piirtometodi piirtaa uuden kuvan naytolle.
// Hankala prosessi, mutten saanut tallaista gifia toimimaan paremmin.
//__LISAOSA?__: animoitu droonikuva.
void Drooni::paivitaDrooninKuva(QPixmap kuva) {
    droonin_kuva_ = kuva;
}


// Kutsutaan paivitysvalein, liikutetaan Droonia ja muutetaan
// sen Sijaiti oliota.
void Drooni::paivitaDrooninSijainti() {
    drooninLiike();
    sijainti_.asetaXY(x(), y());
}


// Palauttaa valilyonnin tilan, varsinkin pomminpudotus metodille
// pelinakymassa.
bool Drooni::palautaValilyonninTila()
{
    return valilyonti_pohjassa_;
}


// Resetoidaan valilyonnin tila. Ilman tata, pommeja tippuisi
// taukoamatta monta perakkain.
void Drooni::resetoiValilyonninTila() {
    valilyonti_pohjassa_ = false;
}


// Droonin paikkaa vaihtava metodi.
// __LISAOSA?__: Liike on tasaista ja sulavaa ja vauhti hidastuu jollei
// kaasu ole pohjassa. Lisaksi reunoissa jarkeva collision detection
// metodi liikuPixeliKerrallaan estaa ettei pelaaja koskaan jaa
// reunoihin jumiin tai paase niista lavitse.
// Droonia ohjataan nuolinappaimilla. Eteenpain on kaasu,
// taaksepain on jarru. Ohjaus tapahtuu painamalla oikealle tai
// vasemmalle, kaantaen Droonin suuntaa 45 astetta. Eli liikkuminen
// voi tapahtua vain kahdeksaan eri suuntaan. Tallainen ohjaus
// pelin pienen koon vuoksi, seka se tuntui sopivalle lennokkimaisen
// Droonin ohjaamiseen.
void Drooni::drooninLiike() {

    // Varmistetaan ettei nopeus kasva liikaa sekä se ettei se
    // voi olla negatiivista.
    if (nykyinen_nopeus_ >= MAX_NOPEUS_) {
        nykyinen_nopeus_ = MAX_NOPEUS_;
    }
    else if(nykyinen_nopeus_ <= 0) {
        nykyinen_nopeus_ = 0;
    }

    // Drooni voi liikkua kahdeksaan eri suuntaan. Tein samasta osiosta
    // for-loopin, muttei se ollut yhtaan lyhyempi ja se oli paljon
    // vaikealukuisempi. Suuntakulmat ovat siis:
    //
    //                 7    0    1
    //                      |
    //               6-------------2
    //                      |
    //                 5    4    3
    //
    // 0 ylos, 1 Koillinen, 2 oikea jne. Kulmittain liikutaan 75% liikkeen
    // maarasta.
    //
    // Jottei tarvita pitkaa listaa if:feja, valitaan dx ja dy
    // suunnan mukaan. Jos esimerkiksi suunta on Ylos, on dx = 0
    // ja dy = -1. Nain liikesuunta on oikea.
    int dx = 0;
    int dy = 0;

    if(suunta_kulma_ == 0)         { dx = 0; dy = -1; }
    else if( (suunta_kulma_ == 1) ){ dx = 1; dy = -1; }
    else if( (suunta_kulma_ == 2) ){ dx = 1; dy = 0; }
    else if( (suunta_kulma_ == 3) ){ dx = 1; dy = 1; }
    else if( (suunta_kulma_ == 4) ){ dx = 0; dy = 1; }
    else if( (suunta_kulma_ == 5) ){ dx = -1; dy = 1; }
    else if( (suunta_kulma_ == 6) ){ dx = -1; dy = 0; }
    else if( (suunta_kulma_ == 7) ){ dx = -1; dy = -1; }

    if(onkoParillinen(suunta_kulma_)){
        if(onkoKuvassa(x() + (dx * nykyinen_nopeus_), y() + (dy * nykyinen_nopeus_), 500, 500)){
            setPos(x() + (dx * nykyinen_nopeus_), y() + (dy * nykyinen_nopeus_));
        }
        else{
            // Jollei liikuttava kohta ole enaa kuvassa, siirrytaan metodiin
            // liikuPixeliKerrallaan.
            liikuPixeliKerrallaan(dx, dy);
            nykyinen_nopeus_ -= 5;
        }
    }
    else{
        if(onkoKuvassa(x() + ((dx * nykyinen_nopeus_) * 0.75), y() + ((dy * nykyinen_nopeus_) * 0.75), 500, 500)){
            setPos(x() + ((dx * nykyinen_nopeus_) * 0.75), y() + ((dy * nykyinen_nopeus_) * 0.75));
        }
        else{
            liikuPixeliKerrallaan(dx, dy);
            nykyinen_nopeus_ -= 5;
        }
    }
}


Rajapinta::Sijainti OmaPuoli::Drooni::annaSijainti() const {
    return sijainti_;
}


// Metodia kutsutaan, kun liikuttava kohta ei ole enaa kuvassa.
// Koska kuitenkin halutaan paasta ihan rajaan asti, liikutaan
// viimeiset pikselit yksitellen, ja tarkastellaan olisiko
// viela seuraava pikseli kuvassa. Lopetetaan kun seuraava
// pixeli ei enaa olisi kuvassa. Melko hyva collision-detection
// menetelma, lopussa tapahtuvaa hidasta liikkumista ei silmilla
// huomaa ja suurella varmuudella Drooni ei voi paatya kuvan
// ulkopuolelle eika jaada jumiin rajojen valiin.
void Drooni::liikuPixeliKerrallaan(int dx, int dy) {

    // Natin loopin luomisen takia, kaytetaan drooninLiike metodissa
    // laskettuja dx ja dy arvoja.
    // Esimerkiksi jos suunta on ylos(0) niin muutos tapahtuu
    // -y suuntaan yksi pikseli. Eli dx = 0 ja dy = -1.

    // Askelletaan pikseleittain eteenpain.
    bool askellus_kaynnissa = true;

    while(askellus_kaynnissa){
        if(onkoKuvassa(x() + dx, y() + dy, 500, 500)){
            setPos(x() + dx, y() + dy);
        }
        else {
            askellus_kaynnissa = false;
        }
    }
}


// Muutetaan Droonin sijainti_ olion arvoa parametrina saatuun
// sijaintiin.
void OmaPuoli::Drooni::liiku(Rajapinta::Sijainti sij)
{
    sijainti_ = sij;
}


// Palauttaa kutsujalleen sen hetken Droonin kuvan.
QPixmap Drooni::palautaKuva() {
    QPixmap palautettava_kuva;
    palautettava_kuva = droonin_kuva_;
    return palautettava_kuva;
}


int Drooni::palautaSuuntakulma() {
    return suunta_kulma_;
}


bool Drooni::onkoTuhottu() const {
    if(onko_tuhottu_){
       return true;
    }
    else {
        return false;
    }
}


void Drooni::tuhoa() {
    // Droonia ei voi tassa pelissa tuhota mikaan.
    // Toteutetaan kuitenkin kantaluokan virtuaalifunktio
    onko_tuhottu_ = true;
}

}

