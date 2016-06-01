#include "pelinakyma.hh"
#include "ui_pelinakyma.h"
#include "sijainti.hh"
#include "kulkuneuvorp.hh"
#include "matkustajarp.hh"
#include "drooni.hh"
#include "funktiot.hh"
#include "random"
#include "alkukuva.hh"
#include <memory>
#include <list>
#include <QImage>
#include <QMovie>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFont>
#include <QBitmap>
#include <QGraphicsProxyWidget>


pelinakyma::pelinakyma(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pelinakyma)
{
    ui->setupUi(this);

    // Asetetaan widgetin title.
    setWindowTitle(QString("NysseOsu 1.02.7b"));

    peli_voitettu_ = false;

    // Lukitaan pelinakyman leveys ja korkeus (500x500).
    QWidget::setFixedSize(PELINAKYMA_LEVEYS_, PELINAKYMA_KORKEUS_);

    // Luodaan QGraphicsScene ja tallennetaan se scene_
    scene_ = new QGraphicsScene();


    // Kuvasta scrollbarit pois kaytosta.
    ui->graphicsView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    ui->graphicsView->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    // Yhdistetaan valikon Actionit.
    valikkoConnect();

    // Naytetaan luotu scene_ graphicsViewissa
    ui->graphicsView->setScene(scene_);

}


// Yhdistetaan QActionit naytaOhjeet seka lopetaPeli metodeihin.
void pelinakyma::valikkoConnect() {
    QObject::connect(ui->action_ohjeet, SIGNAL(triggered()), this, SLOT(naytaOhjeet()));
    QObject::connect(ui->action_lopeta, SIGNAL(triggered()), this, SLOT(lopetaPeli()));
}


void pelinakyma::asetaTaustakuva(QImage taustakuva) {
    // Tehdaan taustakuvasta QGraphicsPixmapItem ja lisataan se sceneen.
    QGraphicsPixmapItem * taustakuva_item = new QGraphicsPixmapItem(QPixmap::fromImage(taustakuva));
    scene_->addItem(taustakuva_item);
    //luoShaderi();
}


// Kaynnistetaan alkukuva dialog.
void pelinakyma::naytaOhjeet() {
    Alkukuva *alku = new Alkukuva();
    alku->scrollaaYlos();
    alku->setModal(true);
    alku->exec();
}


void pelinakyma::lopetaPeli() {
    QApplication::exit();
}


// Metodi piirtaa parametrinaan saamat toimijat ensimmaista kertaa sceneen
// alustaen ne. Alustaa myos gifit ja valahdyksen seka muut tarvittavat kuvat.
void pelinakyma::piirraToimijat(std::list<std::shared_ptr<Rajapinta::ToimijaRP> > kaikki_toimijat) {

    // Kaydaan kaikki toimijat lapi ja otetaan koordinaatit niiden sijaintiin.
    for(auto toimija : kaikki_toimijat){
        QPixmap toimijan_kuva;
        Rajapinta::Sijainti sij = (*toimija).annaSijainti();
        int x = sij.annaX();
        int y = sij.annaY();

        // Jos toimija on kulkuneuvo, ladataan sille nysse kuva ja lisataan
        // teksti.
        if(toimijanLaatu(toimija) == "kulkuneuvo"){
            toimijan_kuva = QPixmap(":/kuvat/nysse.png");

            // Alustetaan teksti.
            QGraphicsTextItem * nyssen_teksti = new QGraphicsTextItem;
            nyssen_teksti->setPlainText(QString("0"));
            QFont fontti("Helvetica",10);
            fontti.setBold(true);
            nyssen_teksti->setFont(fontti);

            // Sijoitetaan aluksi pois kuvasta. Paivittyy oikeaan kohtaan
            // paivitys metodilla.
            nyssen_teksti->setPos(1000, 1000);
            nyssen_teksti->setDefaultTextColor(Qt::black);

            // Jos tekstin koordinaatit ovat kuvassa, piirretaan ne sceneen.
            if(OmaPuoli::onkoKuvassa(x, y, PELINAKYMA_LEVEYS_, PELINAKYMA_KORKEUS_)){
                scene_->addItem(nyssen_teksti);
            }

            // Asetetaan toimija-teksti pari myos nyssejen_tekstit_ mappiin.
            nyssejen_tekstit_.insert(std::make_pair(toimija, nyssen_teksti));

        }

        // Jos toimija on matkustaja, ladataan sen kuva, seka valitaan
        // randomilla sille vari.
        else if(toimijanLaatu(toimija) == "matkustaja"){
            toimijan_kuva = QPixmap(":/kuvat/matkustaja.png");
            int varin_valitsin = 1 + rand() % 5;

            // Luodaan tyhja/variton QPixmap, joka on matkustaja.png
            // kokonen ja muotoinen.
            QPixmap pxr( toimijan_kuva.size() );

            // Varjataan tama QPixmap randomilla varilla.
            if(varin_valitsin == 1){ pxr.fill( Qt::red ); }
            else if(varin_valitsin == 2){ pxr.fill( Qt::cyan ); }
            else if(varin_valitsin == 3){ pxr.fill( Qt::black ); }
            else if(varin_valitsin == 4){ pxr.fill( Qt::green ); }
            else if(varin_valitsin == 5){ pxr.fill( Qt::yellow ); }

            pxr.setMask( toimijan_kuva.createMaskFromColor( Qt::transparent ) );
            toimijan_kuva = pxr;
        }

        // Luodaan QPixmap toimijan kuvalla QGraphicsPixmapItem olio.
        QGraphicsPixmapItem * toimija_kuva_item = new QGraphicsPixmapItem(toimijan_kuva);

        // Jos toimija_kuva_item on kuvassa, lisataan se sceneen.
        if(OmaPuoli::onkoKuvassa(x, y, PELINAKYMA_LEVEYS_, PELINAKYMA_KORKEUS_)){
            toimija_kuva_item->setPos(x, y);
            piirretyt_kuvat_.insert(std::make_pair(toimija, toimija_kuva_item));
            scene_->addItem(toimija_kuva_item);
        }
    }

    // Lisaksi alustetaan kursorin kuva, tehdaan siita QGraphicsPixmapItem
    // ja lisataan se sceneen. 50% opacity nayttaa sopivalta.
    kursori_ = new QGraphicsPixmapItem(QPixmap(":/kuvat/kursori.png"));
    kursori_->setOpacity(0.5);
    scene_->addItem(kursori_);

    // Ja alustetaan valahdys.
    valahdys_ = new QGraphicsPixmapItem(QPixmap(":/kuvat/valahdys.png"));
    valahdys_->setOpacity(0);
    scene_->addItem(valahdys_);

    // Seka kello teksti.
    QFont fontti("Helvetica",20);
    fontti.setBold(true);
    kello_teksti_.setFont(fontti);
    kello_teksti_.setDefaultTextColor(Qt::blue);
    kello_teksti_.setPos(325, 0);
    kello_teksti_.setOpacity(0.55);
    kello_teksti_.setZValue(10000);
    scene_->addItem(&kello_teksti_);

    // Luodaan myos shaderi valmiiksi.
    luoShaderi();
}


// Piirtaa kaikki pysakit pelikentalle, jotka ovat scenen alueella.
void pelinakyma::piirraPysakit(std::vector<std::shared_ptr<Rajapinta::PysakkiRP> > kaikki_pysakit){

    // Kaydaan pysakit lapi, ladataan kuva, sijoitetaan sceneen sen sijainnista
    // saataviin koordinaatteihin.
    for (auto pysakki : kaikki_pysakit){
        QPixmap toimijan_kuva;
        toimijan_kuva = QPixmap(":/kuvat/pysakki.png");
        QGraphicsPixmapItem * pysakki_item = new QGraphicsPixmapItem(toimijan_kuva);

        Rajapinta::Sijainti sij = (*pysakki).annaSijainti();

        int x = sij.annaX();
        int y = sij.annaY();

        if(OmaPuoli::onkoKuvassa(x, y, PELINAKYMA_LEVEYS_, PELINAKYMA_KORKEUS_)){
            pysakki_item->setPos(x, y);
            scene_->addItem(pysakki_item);
        }
    }
}

// Alustetaan pisteet teksti peliin. Valitaan sopiva vari, koko, opacity,
// fontti yms ja lisataan sceneen.
//__LISAOSA?__: Pelin tilan seuranta.
void pelinakyma::piirraPisteet() {
    QFont fontti("Helvetica",20);
    fontti.setBold(true);
    pisteet_teksti_.setFont(fontti);
    pisteet_teksti_.setPos(10, 0);
    pisteet_teksti_.setOpacity(0.55);
    pisteet_teksti_.setDefaultTextColor(Qt::blue);
    scene_->addItem(&pisteet_teksti_);
}

// Aina kun toimijan paikka on muuttunut, tama metodi keraa muuttuneet
// toimijat listaan liikkuneet_toimijat_.
void pelinakyma::keraaLiikkuneetToimijat(std::shared_ptr<Rajapinta::ToimijaRP> toimija) {
    liikkuneet_toimijat_.push_back(toimija);
}


// Luodaan feikki shaderi, koska oikeiden laittaminen QGraphicsScenelle ei
// taida olla mahdollista? Gif kuva joka toimii "vanhan tv staattisena efektina".
// Gif animaatio joka lisataan kuvan paalle.
//__LISAOSA?__: Animoitu tausta.
void pelinakyma::luoShaderi() {
    QLabel *gif_anim = new QLabel();
    QMovie *movie = new QMovie(":/kuvat/shaderi.gif");
    gif_anim->setMovie(movie);
    movie->start();

    // gifin taustan muokkaaminen nakymattomaksi.
    gif_anim->setStyleSheet("background-color: rgba(0,0,0,0%)");
    // Gifista Widget, jonka voi lisata sceneen.
    shaderi_ = scene_->addWidget(gif_anim);
    // Asetetaan sopivaan kohtaan kursoriin nahden.
    shaderi_->setPos(0, 0);

    // Hitusen nakymattomyytta itse gifille, koska gifi ei ole haavi.
    shaderi_->setOpacity(0.05);

    // Mahdollistetaan gifin taustan nakymattomyys.
    shaderi_->setAttribute( Qt::WA_NoSystemBackground );

    // Z-korkeus bussin ylapuolelle, mutta kursorin ja droonin alapuolelle.
    shaderi_->setZValue(11000);
}


// Tyhjennetaan kaikki pommilistat. Labelit ja moviet iteraattorien avulla,
// jotta muisti saadaan vapautettua. Tama tapahtuu noin 10s valein.
void pelinakyma::tyhjennaPommiListat() {
    pommien_poistaja_laskuri_ ++;

    if(pommien_poistaja_laskuri_ >= 150){

        for(std::list<QLabel*>::iterator it = pommilabelit_.begin(); it != pommilabelit_.end(); it++) {
            delete *it;
        }
        pommilabelit_.clear();

        for(std::list<QMovie*>::iterator it = pommi_moviet_.begin(); it != pommi_moviet_.end(); it++) {
            delete *it;
        }
        pommi_moviet_.clear();

        pommigifit_.clear();
        pommien_poistaja_laskuri_ = 0;

    }
}

void pelinakyma::naytaPommiGif() {

    QLabel * pommilabel = new QLabel();
    QMovie * pommi_movie = new QMovie(":/kuvat/lemp.gif");
    pommilabel->setMovie(pommi_movie);
    pommi_movie->start();

    // gifin taustan muokkaaminen nakymattomaksi.
    pommilabel->setStyleSheet("background-color: rgba(0,0,0,0%)");

    // Gifista Widget, jonka voi lisata sceneen.
    QGraphicsProxyWidget *pommigif;
    pommigif = scene_->addWidget(pommilabel);

    // Asetetaan sopivaan kohtaan kursoriin nahden.
    pommigif->setPos(kursori_->x() + 8, kursori_->y() + 8);

    // Hitusen nakymattomyytta itse gifille, koska gifi ei ole haavi.
    pommigif->setOpacity(0.7);

    // Mahdollistetaan gifin taustan nakymattomyys.
    pommigif->setAttribute( Qt::WA_NoSystemBackground );

    // Z-korkeus bussin ylapuolelle, mutta kursorin ja droonin alapuolelle.
    pommigif->setZValue(7000);

    pommilabelit_.push_back(pommilabel);
    pommi_moviet_.push_back(pommi_movie);
    pommigifit_.push_back(pommigif);
}


// Valaytetaan kuva. Eli lyodaan kuvan paalle valkoinen kuva
// joka katoaa 3 framen kuluessa.
// __LISAOSA?__: interaktiivinen ja responsiivinen elementti, joka korostaa
// kohteeseen osumista paljon.
void pelinakyma::valaytaKuva() {
    valahdys_->setOpacity(0.7);
    valahdyksen_nayttaja_ = 3;
}



// Paivitetaan Toimijan sijainta monta kertaa sekunnissa. Jossei sijainti ole
// enaa kuvassa, poistetaan se scenesta. Hyvin samanlainen kuin piirraToimijat
// metodi.
// __LISAOSA?__: Minimaalinen ruudunpaivitys. Ruutua ei paiviteta muualla kuin
// tassa. Muualla tehdyt laskutoimitukset tulevat kuvaan vasta tassa metodissa.
void pelinakyma::paivitaToimijoidenSijainnit(){
    for(auto toimija : liikkuneet_toimijat_){
        Rajapinta::Sijainti sij = (*toimija).annaSijainti();

        if(OmaPuoli::onkoKuvassa(sij.annaX(), sij.annaY(), PELINAKYMA_LEVEYS_, PELINAKYMA_KORKEUS_)){
            std::map<std::shared_ptr<Rajapinta::ToimijaRP>, QGraphicsPixmapItem*>::iterator it;

            // Tarkistetaan onko kyseinen toimija jo piirretty kuvaan.
            // Jos on vaihdetaan vain sen sijainti.
            bool on_jo_piirretty = false;
            for(it = piirretyt_kuvat_.begin(); it!=piirretyt_kuvat_.end(); it++){
                if(it->first == toimija){
                    it->second->setPos( sij.annaX(), sij.annaY() );
                    on_jo_piirretty = true;
                    break;
                }
            }

            // Toimijaa ei oltu piirretty, joten ladataan toimijalle kuva ja
            // lisataan se sceneen.
            if(on_jo_piirretty == false){
                QPixmap toimijan_kuva;

                if(toimijanLaatu(toimija) == "kulkuneuvo"){
                    toimijan_kuva = QPixmap(":/kuvat/nysse.png");

                    // Alustetaan uudelle bussille tekstit.
                    QGraphicsTextItem * nyssen_teksti = new QGraphicsTextItem;
                    nyssen_teksti->setPlainText(QString("0"));
                    QFont fontti("Helvetica",10);
                    fontti.setBold(true);
                    nyssen_teksti->setFont(fontti);
                    nyssen_teksti->setPos(1000, 1000);
                    nyssen_teksti->setDefaultTextColor(Qt::black);
                    scene_->addItem(nyssen_teksti);
                    nyssejen_tekstit_.insert(std::make_pair(toimija, nyssen_teksti));
                }
                // Samanlainen kuin piirraToimijat metodissa. Alustetaan
                // matkustajat.
                else if(toimijanLaatu(toimija) == "matkustaja"){
                    toimijan_kuva = QPixmap(":/kuvat/matkustaja.png");
                    int varin_valitsin = 1 + rand() % 5;
                    QPixmap pxr( toimijan_kuva.size() );

                    if(varin_valitsin == 1){ pxr.fill( Qt::red ); }
                    else if(varin_valitsin == 2){ pxr.fill( Qt::cyan ); }
                    else if(varin_valitsin == 3){ pxr.fill( Qt::black ); }
                    else if(varin_valitsin == 4){ pxr.fill( Qt::green ); }
                    else if(varin_valitsin == 5){ pxr.fill( Qt::yellow ); }

                    pxr.setMask( toimijan_kuva.createMaskFromColor( Qt::transparent ) );

                    toimijan_kuva = pxr;
                }

                // Kuvasta item ja item sceneen.
                QGraphicsPixmapItem * toimija_kuva_item = new QGraphicsPixmapItem(toimijan_kuva);

                toimija_kuva_item->setPos(sij.annaX(), sij.annaY());
                piirretyt_kuvat_.insert(std::make_pair(toimija, toimija_kuva_item));
                scene_->addItem(toimija_kuva_item);
            }
        }
        // Tanne paatyy toimija, jonka sijainti on paivitetty,
        // mutta ei sijaitse kuvassa. Poistetaan tallainen toimija.
        else{
            std::map<std::shared_ptr<Rajapinta::ToimijaRP>, QGraphicsPixmapItem*>::iterator it;
            for(it = piirretyt_kuvat_.begin(); it!=piirretyt_kuvat_.end(); it++){

                // Jos kuva loytyy piirretyt_kuvat_ mapista, poistetaan se
                // scenesta ja mapista.
                if(it->first == toimija){
                    scene_->removeItem(it->second);
                    piirretyt_kuvat_.erase(it);
                }
            }
        }
    }

    // Kaikki liikkuneet toimijat paivitelty, tyhjennetaan lista.
    liikkuneet_toimijat_.clear();

    // Nysset nayttavat hyvilta kun ne ovat matkustajien, pysakkien seka
    // taustakuvan ylapuolella.
    for(auto nysse : piirretyt_kuvat_){
        if(toimijanLaatu(nysse.first) == "kulkuneuvo"){
            nysse.second->setZValue(5000);
        }
    }

    // Drooni lahes paalimmaiseksi, vain pisteet ovat korkeammalla.
    drooni_->setZValue(9999);
    pisteet_teksti_.setZValue(10000);
}


// Metodi paivittaa pisteet_teksti_:n pisteet parametrinaan saaneiden
// pisteiden mukaiseksi.
// __LISAOSA?__: Pelin tilan seuranta. Nykyiset pisteet nakyvat aina pelaajalle.
void pelinakyma::paivitaPisteet(int pisteet) {

    // Jos peli on voitettu, teksti on erilainen kun jos sita ei ole voitettu.
    if(peli_voitettu_){
        pisteet_teksti_.setPlainText(QString("PISTEET: ")
                            + QString::number(pisteet)
                            + QString(" / 200\n        WAPPU ON PELASTETTU !\n")
                            + QString("\n\n\n\n\n\n\n\n\n")
                            + QString("                    AJASSA: ")
                            + QString::number(voitto_aika_)
                            + QString("s"));

        pisteet_teksti_.setOpacity(100);
        QFont fontti("Helvetica",22);
        fontti.setBold(true);
        pisteet_teksti_.setFont(fontti);

    }
    else{
        pisteet_teksti_.setPlainText(QString("PISTEET: ")
                            + QString::number(pisteet) + QString(" / 200"));
    }
}


// Metodi paivittaa droonin kuvan.
void pelinakyma::paivitaDrooninKuva(QPixmap droonin_kuva) {

    // Asetetaan kuva droonille.
    drooni_->paivitaDrooninKuva(droonin_kuva);
    droonin_kuva = drooni_->palautaKuva();
    drooni_->setPixmap(droonin_kuva);

    // Vaihdetaan droonin offset kuvan keskelle.
    drooni_->setOffset(-25, -25);

    // Pyydetaan droonilta sen suuntakulma, ja sen avulla
    // edetaan 45 asteittain suuntakulman verran oikealle tai vasemmalle
    int suuntakulma = drooni_->palautaSuuntakulma();
    int kulma = 0;
    for(int i=0;i!=suuntakulma;i++){
        kulma += 45;
        if(kulma >= 360){
            kulma = 0;
        }
    }

    // Asetetaan laskettu kulma droonin rotaatioksi.
    drooni_->setRotation(kulma);
}

// Metodi siirtelee matkustajia kartalla, jos ne ovat paallekkain.
// ja poistavat nakyvista, jos ne on nyssen sisalla.
// __LISAOSA?__: Jarkevasti kuvaan asetellut matkustajat. Muuten ei matkustajien
// suurella maaralla ole mitaan hyotya, jollei ne ole kuvassa nakyvissa
// pelaajalle.
void pelinakyma::paivitaToimijoidenPaallekkyys() {

    std::pair<int, int> koordinaatti;
    std::list<std::pair<int, int>> koordinaatit;

    // Kerataan koordinaatit, joissa on matkustajia jotka ovat
    // piirretty kuvaan.
    for(auto toimija : piirretyt_kuvat_){
        if(toimijanLaatu(toimija.first) == "matkustaja"){
            koordinaatti = std::make_pair(toimija.second->x(), toimija.second->y());
            koordinaatit.push_back(koordinaatti);
        }
    }

    // Nyt kaydaan matkustajat taas lavitse, ja jos koordinaatti, jossa
    // matkustaja on, on yli kaksi matkustajaa, siirretaan sen matkustajan
    // offset arvoa randomilla muutamia pixeleita.
    for(auto toimija : piirretyt_kuvat_){
        if(toimijanLaatu(toimija.first) == "matkustaja"){

            // Otetaan matkustajan koordinaatit.
            koordinaatti = std::make_pair(toimija.second->x(), toimija.second->y());

            // Lasketaan montako kertaa koordinaatti esiintyy
            // keratyissa koordinaateissa.
            int koordinaattien_lukumaara = std::count(koordinaatit.begin(),
                                                      koordinaatit.end(),
                                                      koordinaatti);

            // Jos koordinaatit esiintyy yli kaksi kertaa ja toimijan offset arvoa
            // ei ole muutettu, muutetaan sita randomilla hitusen.
            if(koordinaattien_lukumaara > 2 && toimija.second->offset().isNull()){
                int random_x = -15 + rand() % 30;
                int random_y = 15 + rand() % 5;
                toimija.second->setOffset(random_x, random_y);
                toimija.second->setOpacity(0.7);
            }

            // Nyt tutkitaan etta jos matkustaja on kulkuneuvossa,
            // piilotetaan se kayttamalla metodia (QGraphicsItem::hide()),
            // muulloin show().
            Rajapinta::MatkustajaRP* matkustaja = dynamic_cast<Rajapinta::MatkustajaRP*>(toimija.first.get());
            if(matkustaja->onkoKulkuneuvossa()){
                toimija.second->hide();
            }
            else {
                toimija.second->show();
            }
        }
    }

}


// Metodi paivittaa Nyssejen ylapuolella olevan tekstin, eli numeron
// nyssessa olevien matkustajien maarasta. Mita isompi maara, sita isompi
// on teksti. Jos teksti yli 14, niin teksti muuttuu punaiseksi.
// __LISAOSA?__: Matkustaja maarat. Pelaajalle esitetaan reaaliajassa
// matkustajien lukumaaran jokaisessa nyssessa.
void pelinakyma::paivitaNyssejenTeksti() {
    for(auto nyssen_teksti : nyssejen_tekstit_){

        // Varmistetaan viela etta kyseessa nysse.
        if(toimijanLaatu(nyssen_teksti.first) == "kulkuneuvo"){

            // Castataan ToimijaRP->KulkuneuvoRP
            Rajapinta::KulkuneuvoRP* kulkuneuvo =
                    dynamic_cast<Rajapinta::KulkuneuvoRP*>(nyssen_teksti.first.get());

            // Lasketaan matkustajat.
            std::vector<std::shared_ptr<Rajapinta::MatkustajaRP>> vektori
                    = kulkuneuvo->annaMatkustajat();

            int matkustajien_lkm = vektori.size();

            // Teksti matkustajien lukumaaraksi.
            nyssen_teksti.second->setPlainText(QString::number(matkustajien_lkm));

            // Etsitaan nyssen sijainti ja sen avulla sijoitetaan teksti
            // sen paalle.
            Rajapinta::Sijainti sij = nyssen_teksti.first->annaSijainti();
            if(matkustajien_lkm < 4){

                // Matkustajia alle nelja eli pienin fontti.
                QFont fontti("Helvetica",11);

                // Boldataan fontti.
                fontti.setBold(true);

                // Asetetaan tekstinfontiksi fontti.
                nyssen_teksti.second->setFont(fontti);

                // Koska alle nelja matkustajaa on vahan, tekstin vari on musta
                // ja sijainti sopivasti nyssen ylapuolella ja sen keskella.
                nyssen_teksti.second->setDefaultTextColor(Qt::black);
                nyssen_teksti.second->setPos(sij.annaX() + 5, sij.annaY() - 20);
            }
            else if(matkustajien_lkm >= 4 && matkustajien_lkm < 10){
                QFont fontti("Helvetica",14);
                fontti.setBold(true);
                nyssen_teksti.second->setFont(fontti);
                Rajapinta::Sijainti sij = nyssen_teksti.first->annaSijainti();
                nyssen_teksti.second->setDefaultTextColor(Qt::black);
                nyssen_teksti.second->setPos(sij.annaX() + 5, sij.annaY() - 23);
            }
            else if(matkustajien_lkm >= 10 && matkustajien_lkm < 14){
                QFont fontti("Helvetica",16);
                fontti.setBold(true);
                nyssen_teksti.second->setFont(fontti);
                Rajapinta::Sijainti sij = nyssen_teksti.first->annaSijainti();
                nyssen_teksti.second->setDefaultTextColor(Qt::black);
                nyssen_teksti.second->setPos(sij.annaX() - 3, sij.annaY() - 25);
            }
            else{
                QFont fontti("Helvetica",20);
                fontti.setBold(true);
                nyssen_teksti.second->setFont(fontti);
                Rajapinta::Sijainti sij = nyssen_teksti.first->annaSijainti();
                nyssen_teksti.second->setDefaultTextColor(Qt::red);
                nyssen_teksti.second->setPos(sij.annaX() - 7, sij.annaY() - 32);
            }

            // Jos teksti on scenessa, poistetaan se scenesta.
            for( auto item : scene_->items() ){
                if (nyssen_teksti.second == item){
                    scene_->removeItem(nyssen_teksti.second);
                }
            }

            // Ja jos se on kuvassa lisataan takaisin sceneen.
            if(OmaPuoli::onkoKuvassa(sij.annaX(), sij.annaY(), 500, 500)){
                scene_->addItem(nyssen_teksti.second);
            }
        }
    }
}


// Metodi paivittaa kursorin paikan. Kursorin paikka on viimeisenpaalle
// viilattu, melko mahdotonta tehda tasta metodista looppia.
void pelinakyma::paivitaKursori() {
    if(drooni_->palautaSuuntakulma() == 0){
        kursori_->setPos(drooni_->annaSijainti().annaX() - 20,
                         drooni_->annaSijainti().annaY() - 60);
    }
    else if(drooni_->palautaSuuntakulma() == 1){
        kursori_->setPos(drooni_->annaSijainti().annaX() + 10,
                         drooni_->annaSijainti().annaY() - 50);
    }
    else if(drooni_->palautaSuuntakulma() == 2){
        kursori_->setPos(drooni_->annaSijainti().annaX() + 20,
                         drooni_->annaSijainti().annaY() - 20);
    }
    else if(drooni_->palautaSuuntakulma() == 3){
        kursori_->setPos(drooni_->annaSijainti().annaX() + 10,
                         drooni_->annaSijainti().annaY() + 10);
    }
    else if(drooni_->palautaSuuntakulma() == 4){
        kursori_->setPos(drooni_->annaSijainti().annaX() - 20,
                         drooni_->annaSijainti().annaY() + 20);
    }
    else if(drooni_->palautaSuuntakulma() == 5){
        kursori_->setPos(drooni_->annaSijainti().annaX() - 50,
                         drooni_->annaSijainti().annaY() + 10);
    }
    else if(drooni_->palautaSuuntakulma() == 6){
        kursori_->setPos(drooni_->annaSijainti().annaX() - 60,
                         drooni_->annaSijainti().annaY() - 20);
    }
    else{
        kursori_->setPos(drooni_->annaSijainti().annaX() - 50,
                         drooni_->annaSijainti().annaY() - 50);
    }
}


// Paivittaa 'shaderia'. Randomilla sijoittaa shaderin ja ottaa sen pois.
// Joka kutsumiskerta(frame) lisaa shaderin_nayttaja_ arvoa yhdella.
// Kun se saavuttaa arvon shaderin_odottaja_ niin se lisaa uuden shaderin.
// Se poistetaan kuvasta kun 30% seuraavan shaderin_odottajan_ arvosta
// on kulunut.
// Esimerkki:
// Luodaan shaderi, nayttaja = 0 ja odottaja 100.
// Joka freimi nayttajaan lisaantyy 1 ja shaderi on kuvassa.
// 30 framea myohemmin shaderi poistetaan koska 30% on taynna.
// Siita 70 framea myohemmin luodaan uusi shaderi, nayttaja taas 0 ja
// odottaja 60 + rand()%80. Jne.
void pelinakyma::paivitaShaderi() {
    shaderin_nayttaja_ ++;

    // Jos shaderi on scenessa, katsotaan onko se ollut jo 30% ajasta.
    // Jos on, poistetaan se nakyvista.
    if(shaderi_scenessa_){
        if(shaderin_nayttaja_ >= (shaderin_odottaja_* 0.3 )){
            for( auto item : scene_->items() ){
                if (item == shaderi_){
                    scene_->removeItem(shaderi_);
                    shaderi_scenessa_ = false;
                }
            }
        }
    }

    // Luodaan uusi shaderi ja lasketaan uusi odottajan arvo.
    if(shaderin_nayttaja_ >= shaderin_odottaja_){
        scene_->addItem(shaderi_);
        shaderi_scenessa_ = true;
        shaderin_nayttaja_ = 0;
        shaderin_odottaja_ = 60 + rand() % 80;
    }
}


// Paivittaa valahdyksen tilaa, jos se on juuri asetettu,
// vahentaa sen opacity arvoa joka frame 33% kunnes se on
// nolla.
void pelinakyma::paivitaValahdys() {
    if(valahdyksen_nayttaja_ >= 3){
        valahdys_->setOpacity(0.66);
        valahdyksen_nayttaja_--;
    }
    else if(valahdyksen_nayttaja_ = 2){
        valahdys_->setOpacity(0.33);
        valahdyksen_nayttaja_--;
    }
    else if(valahdyksen_nayttaja_ = 1){
        valahdys_->setOpacity(0);
        valahdyksen_nayttaja_--;
    }
    else{
        valahdyksen_nayttaja_ <= 0;
        valahdys_->setOpacity(0);
    }
}


// Paivitetaan kellon aika sceneen.
void pelinakyma::paivitaKello(QTime peli_ollut_kaynnissa) {
    if(peli_voitettu_ && voitto_aika_ == 0){
        voitto_aika_ = peli_ollut_kaynnissa.elapsed() / 1000;
    }
    kello_teksti_.setPlainText(QString("AIKA: ") +
                       QString::number(peli_ollut_kaynnissa.elapsed() / 1000) +
                       QString(" s"));
}


void pelinakyma::paivitaPelitilanne(bool onko_peli_voitettu) {
    peli_voitettu_ = onko_peli_voitettu;
}


// Luodaan drooni, piirretaan se sceneen ja palautetaan shared_ptr
// Kaupungille.
std::shared_ptr<OmaPuoli::Drooni> pelinakyma::luoDrooni(){
    // Luodaan drooni ja ptr siihen.
    auto drooni_ptr = std::make_shared<OmaPuoli::Drooni>();
    drooni_ = drooni_ptr.get();

    Rajapinta::Sijainti sij;

    // Aloitus sijainti.
    sij.asetaXY(250, 375);
    drooni_->liiku(sij);
    drooni_->setPos(drooni_->annaSijainti().annaX(),
                    drooni_->annaSijainti().annaY());

    // Focus drooniin.
    drooni_->setFlag(QGraphicsItem::ItemIsFocusable);
    drooni_->setFocus();

    // Lisataan drooni sceneen.
    scene_->addItem(drooni_);

    return drooni_ptr;
}


// Tiputetaan pommi jos spacebar on painettuna.
std::list<std::shared_ptr<Rajapinta::ToimijaRP>> pelinakyma::tiputaPommiTarvittaessa(
            std::vector<std::shared_ptr<Rajapinta::ToimijaRP>> lahella_olevat_toimijat) {
    std::list<std::shared_ptr<Rajapinta::ToimijaRP>> lista_lahella_olevista_nysseista;

    // Kaydaan lapi lahella olevat toimijat, jos toimija on nysse lisataan
    // se listaan.
    for(auto toimija : lahella_olevat_toimijat){
        if(toimijanLaatu(toimija) == "kulkuneuvo"){
            lista_lahella_olevista_nysseista.push_back(toimija);
        }
    }    

    // Naytetaan pommigifi.
    naytaPommiGif();

    // Jos osuttiin nysseen, valaytetaan myos kuvaa.
    if(lista_lahella_olevista_nysseista.size() >= 1){
        valaytaKuva();
    }

    // Resetoidaan valilyonti, nyt ollan valmiita jos kayttaja haluaa tiputtaa
    // lisaa pommeja.
    drooni_->resetoiValilyonninTila();

    // Matkustajien poistaja ja pisteiden laskija tarvitsee listaa
    // busseista johon pommi osui.
    return lista_lahella_olevista_nysseista;
}

// Metodi paivittaa pelinakyma, piirtaa kaikki tarvittavat asiat siihen.
void pelinakyma::paivitaPelinakyma() {

    // Focus aina takaisin drooniin.
    drooni_->setFlag(QGraphicsItem::ItemIsFocusable);
    drooni_->setFocus();

    //Jollei Droonilla ole kaasu pohjassa, hidastetaan sen vauhtia.
    drooni_->hidastaVauhtia();

    // Liikutetaan Droonia.
    drooni_->paivitaDrooninSijainti();

    // Paivitetaan kaikki kuvassa olevat asiat.
    paivitaToimijoidenSijainnit();
    paivitaKursori();
    paivitaToimijoidenPaallekkyys();
    paivitaNyssejenTeksti();
    paivitaShaderi();
    paivitaValahdys();

    // Tyhjennetaan gifien kuvat muistista ja vapautetaan se muisti.
    tyhjennaPommiListat();

}


// Metodi palauttaa sijainnin kursoriin.
Rajapinta::Sijainti pelinakyma::palautaKursorinSijainti() {
    Rajapinta::Sijainti kursorin_sijainti;
    kursorin_sijainti.asetaXY(kursori_->x() + 6, kursori_->y() + 13);
    return kursorin_sijainti;
}


// Tarkistaa onko toimija kulkuneuvo vai matkustaja ja palauttaa
// stringing sen laadusta.
std::string pelinakyma::toimijanLaatu(std::shared_ptr<Rajapinta::ToimijaRP> toimija){
    std::string toimijan_laatu = "drooni";

    Rajapinta::KulkuneuvoRP* kulkuneuvo = dynamic_cast<Rajapinta::KulkuneuvoRP*>(toimija.get());
    if(kulkuneuvo != 0){
        toimijan_laatu = "kulkuneuvo";
    }

    Rajapinta::MatkustajaRP* matkustaja = dynamic_cast<Rajapinta::MatkustajaRP*>(toimija.get());
    if(matkustaja != 0){
        toimijan_laatu = "matkustaja";
    }
    return toimijan_laatu;
}


pelinakyma::~pelinakyma()
{
    delete ui;
}



