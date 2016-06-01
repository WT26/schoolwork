#ifndef KAUPUNKI_HH
#define KAUPUNKI_HH

/**
  * @file
  * @brief Luokka joka toteuttaa KaupunkiRP:n ja toimii pääasiallisena logiikan
  * pyörittämisenä OmaPuoli:lla.
  */

#include <vector>
#include <memory>
#include <pysakki.hh>
#include <QTime>
#include <QTimer>
#include <QObject>
#include "pelinakyma.hh"
#include "drooni.hh"
#include "tilasto.hh"



namespace OmaPuoli {

/**
  * @file
  * @brief Luokka pitaa kirjaa tilastoista, pelinakymasta, droonista, seka
  * kaikista toimijoista. Luokka myos toimii rajapintana KurssinPuolen
  * koodien kanssa.
  */
class Kaupunki :  public QObject, public Rajapinta::KaupunkiRP

{
    Q_OBJECT
public:

    Kaupunki(QObject *parent = 0);
    ~Kaupunki();

    // Nama metodit speksattu jo KaupunkiRP:ssä.
    void asetaTausta(QImage& perustaustakuva, QImage& isotaustakuva);
    void asetaKello(QTime kello);
    void lisaaPysakki(std::shared_ptr<Rajapinta::PysakkiRP> pysakki);
    void peliAlkaa();
    void lisaaToimija(std::shared_ptr<Rajapinta::ToimijaRP> uusitoimija);
    void poistaToimija(std::shared_ptr<Rajapinta::ToimijaRP> toimija);
    void toimijaTuhottu(std::shared_ptr<Rajapinta::ToimijaRP> toimija);
    void toimijaLiikkunut(std::shared_ptr<Rajapinta::ToimijaRP> toimija);

    bool loytyykoToimija(std::shared_ptr<Rajapinta::ToimijaRP> toimija) const;
    bool peliLoppunut() const;

    std::vector<std::shared_ptr<Rajapinta::ToimijaRP>>
                          annaToimijatLahella(Rajapinta::Sijainti paikka) const;


    /**
     * @brief Pelin päämäärä on tuhota busseista matkustajia. Tämä metodi tuhoaa
     * pommitettjen bussien matkustajat.
     * @pre -
     * @param Lista busseista joihin on osunut std::list<std::shared_ptr<Rajapinta::ToimijaRP>>
     * @post Bussi tyhja, ja sen matkustajat ovat tuhottu.
     */
    void tuhoaBussienMatkustajat(std::list<std::shared_ptr<Rajapinta::ToimijaRP>>
                                 lista_lahella_olevista_nysseista);

    /**
     * @brief Tarkistaa Tilaston pistemäärän ja katsoo onko se ylittanyt PISTEET_VOITTOON
     * arvon.
     * @pre -
     * @return Boolean arvo, onko peli läpäisty.
     * @post -
     */
    bool tarkistaVoitto();

    /**
     * @brief Näytetään pelaajalle tieto siitä, että peli on voitettu.
     * @pre peliVoitettu() metodi antaa arvon tosi.
     * @post -
     */
    void peliVoitettu();



public slots:

    /**
     * @brief Metodi käydään läpi PAIVITYSVALI_MS:n valein. Piirretaan
     * ja paivitetaan olioiden sijainteja ja pisteita.
     * @pre -
     * @post -
     */
    void paivitaPelinakyma();

    /**
     * @brief Metodi paivittaa Droonille uuden QPixmap kuvan jos gifin kuva
     * on vaihtunut.
     * @pre -
     * @post Droonin kuva muutettu.
     */
    void drooninKuvaMuuttunut();



private:
    QTime kello_;
    QTimer ajastin_;
    QTime peli_ollut_kaynnissa_;
    QImage taustakuva_;
    QMovie *movie_;
    pelinakyma pelinakyma_;
    Tilasto tilasto_;

    std::shared_ptr<OmaPuoli::Drooni> drooni_;
    std::list< std::shared_ptr<Rajapinta::ToimijaRP> > toimijat_;
    std::vector< std::shared_ptr<Rajapinta::PysakkiRP> > pysakit_;

    bool kaupunki_alustus_tilassa_;
    bool peli_kaynnissa_ = false;

    // Noin 13-14fps~. Toimi hyvin myos 30fps(eli PAIVITYSVALI_MS = 33),
    // mutta tuntui turhalta, koska bussit kuitenkin vaihtavat paikkaa
    // kymmenen kertaa sekunnissa(logiikka.cc:n paivitysvali = 100).
    // Myoskaan droonin liike ei ole mitenkaan yhteydessa PAIVITYSVALI_MS
    // suuruuteen, joten droonin nopeus kasvaa tiheampaan.
    const int PAIVITYSVALI_MS = 75;
    const int PISTEET_VOITTOON = 200;

};


}

#endif // KAUPUNKI_HH
