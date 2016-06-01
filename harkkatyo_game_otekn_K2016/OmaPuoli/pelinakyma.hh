#ifndef PELINAKYMA_H
#define PELINAKYMA_H

/**
  * @file
  * @brief Luokka joka toteuttaa pelialueen ja sillä sijaitsevien asioiden
  * piirtämisen.
  */

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTime>
#include <memory>
#include <vector>
#include <map>
#include "toimijarp.hh"
#include "pysakki.hh"
#include "drooni.hh"


namespace Ui {
class pelinakyma;
}

/**
  * @file
  * @brief Kayttoliittyma luokka. Kayttoliittymaan luodaan QGraphicsScene ja se
  * sijoitetaan QGraphicsViewiin. Sceneen piirretaan tasaisin valiajoin
  * kaikki kuvassa silla hetkella tapahtuvat asiat, kuten toimijat
  * oikeille sijainneilleen, kokonaispisteet, tiputetut pommit seka
  * Drooni.
  */
class pelinakyma : public QMainWindow
{

Q_OBJECT
public:
    explicit pelinakyma(QWidget *parent = 0);
    ~pelinakyma();


    /**
     * @brief Asetetaan valikon QAction:eille Connectit tarvittaviin SLOT:teihin.
     * @pre -
     * @post Connectit asetettu.
     */
    void valikkoConnect();

    /**
     * @brief Asetetaan scene_:lle taustakuva.
     * @pre -
     * @param QImage taustakuva.
     * @post Taustakuva asetettu.
     */
    void asetaTaustakuva(QImage taustakuva);


    /**
     * @brief Ensimmainen piirtaminen, toimijoille oikeat kuvat ja sijainnit.
     * @pre -
     * @param std::list< std::shared_ptr<Rajapinta::ToimijaRP> > kaikki_toimijat.
     * @post Toimijat ovat nyt alustettu scene_:lle ja piirretyt_kuvat_
     * sekä nyssejen_tekstit_ luotu.
     */
    void piirraToimijat(std::list< std::shared_ptr<Rajapinta::ToimijaRP> > kaikki_toimijat);

    /**
     * @brief Piirretään peliin pysäkit.
     * @pre -
     * @param std::vector< std::shared_ptr<Rajapinta::PysakkiRP> > kaikki_pysakit.
     * @post Pysäkit piirretty scene_:een.
     */
    void piirraPysakit(std::vector< std::shared_ptr<Rajapinta::PysakkiRP> > kaikki_pysakit);

    /**
     * @brief Piirretään sceneen 'PISTEET X / PISTEET_VOITTOON'.
     * @pre -
     * @post Pisteet alustettu ja scene_:ssä.
     */
    void piirraPisteet();

    /**
     * @brief Keraa std::list<std::shared_ptr<Rajapinta::ToimijaRP> > liikkuneet_toimijat_
     * listaan aina toimijan liikahtaessa se listaan.
     * @pre -
     * @param std::shared_ptr<Rajapinta::ToimijaRP> toimija joka on liikahtanut.
     * @post -
     */
    void keraaLiikkuneetToimijat(std::shared_ptr<Rajapinta::ToimijaRP> toimija);

    /**
     * @brief Asetetaan valikon QAction:eille Connectit tarvittaviin SLOT:teihin.
     * @pre -
     * @post Connectit asetettu.
     */
    void luoShaderi();

    /**
     * @brief Tyhjennetaan pommi listat 150 framen valein. Vapautetaan muisti.
     * @pre -
     * @post Listat tyhjia.
     */
    void tyhjennaPommiListat();

    /**
     * @brief Kun pommi pudotetaan, Tama metodi nayttaa gif kuvan pommin
     * räjähdyksestä.
     * @pre -
     * @post -
     */
    void naytaPommiGif();

    /**
     * @brief Kun pommi pudotetaan ja se osuu nysseen,
     * tämä metodi väläyttaa kuvaa.
     * @pre Pommi osuu nysseen.
     * @post -
     */
    void valaytaKuva();

    // Paivita-metodit ovat metodeita, jotka paivittavat tietyn osa-alueen
    // sijainnin, kuvan, pistemaaran jne mika on muuttunut. Paivitys vaihtaa
    // siis vain jotain mika on jo scenessa.
    void paivitaToimijoidenSijainnit();
    void paivitaPisteet(int pisteet);
    void paivitaDrooninKuva(QPixmap droonin_kuva);
    void paivitaToimijoidenPaallekkyys();
    void paivitaNyssejenTeksti();
    void paivitaKursori();
    void paivitaShaderi();
    void paivitaValahdys();
    void paivitaKello(QTime peli_ollut_kaynnissa);
    void paivitaPelitilanne(bool onko_peli_voitettu);

    /**
     * @brief paivitaPelinakyma päivittää koko pelialueen kuvan kaikkine uusine
     * tietoineen, joita muut paivita-metodit ovat keränneet. Kaupunki kutsuu
     * tätä metodia PAIVITYSVALI_MS:n välein.
     * @pre -
     * @post -
     */
    void paivitaPelinakyma();

    /**
     * @brief Luo Drooni:n pelinäkymään ja palauttaa shared_ptr:n siihen Drooniin.
     * @pre -
     * @return std::shared_ptr<OmaPuoli::Drooni> drooni.
     * @post Drooni luotu.
     */
    std::shared_ptr<OmaPuoli::Drooni> luoDrooni();

    /**
     * @brief Metodi tiputtaa pommin tarvittaessa. Tämä tarkoittaa tilannetta
     * että valilyonti_pohjassa_ arvo on tosi. Tätä metodia kutsutaan useasti sekunnissa.
     * @pre -
     * @param bool droonin_ampuminen_kaynnissa, ja
     * std::vector<std::shared_ptr<Rajapinta::ToimijaRP>> lahella_olevat_toimijat
     * @return std::list<std::shared_ptr<Rajapinta::ToimijaRP>> lista nysseistä,
     * joihin pommi osui.
     * @post Pommi tiputettu.
     */
    std::list<std::shared_ptr<Rajapinta::ToimijaRP>> tiputaPommiTarvittaessa(
            std::vector<std::shared_ptr<Rajapinta::ToimijaRP>>
                                            lahella_olevat_toimijat);

    /**
     * @brief Tarkistaa std::shared_ptr<Rajapinta::ToimijaRP> toimijan laadun.
     * @pre -
     * @return stringi toimijasta('drooni', 'matkustaja' tai 'kulkuneuvo')
     * @post -
     */
    std::string toimijanLaatu(std::shared_ptr<Rajapinta::ToimijaRP> toimija);

    /**
     * @brief Palauttaa Rajapinta::Sijainti: joka on kursorin kohdassa.
     * @pre -
     * @return Rajapinta::Sijainti kursorin sijainti
     * @post -
     */
    Rajapinta::Sijainti palautaKursorinSijainti();


public Q_SLOTS:
    /**
     * @brief action_ohjeet QActionia klikatessa ohjeet tulevat nakyviin.
     * @pre -
     * @post -
     */
    void naytaOhjeet();

    /**
     * @brief action_ohjeet QActionia klikatessa peli lopetetaan.
     * @pre -
     * @post -
     */
    void lopetaPeli();


private:
    Ui::pelinakyma *ui;


    int shaderin_nayttaja_ = 0;
    int shaderin_odottaja_ = 60;
    QGraphicsProxyWidget *shaderi_;
    bool shaderi_scenessa_ = true;

    std::list<QMovie *>pommi_moviet_;
    std::list<QLabel *>pommilabelit_;
    std::list<QGraphicsProxyWidget *>pommigifit_;
    int pommien_poistaja_laskuri_ = 0;

    int valahdyksen_nayttaja_ = 0;
    QGraphicsPixmapItem* valahdys_;

    const int PELINAKYMA_KORKEUS_ = 500;
    const int PELINAKYMA_LEVEYS_ = 500;

    QGraphicsScene* scene_;
    OmaPuoli::Drooni* drooni_;
    QGraphicsTextItem pisteet_teksti_;
    QGraphicsTextItem kello_teksti_;
    QGraphicsPixmapItem* kursori_;

    int voitto_aika_ = 0;

    int pisteet_;
    bool peli_voitettu_;

    // liikkuneet_toimijat_ on lista niista toimijoista, jotka ovat juuri
    // liikahtaneet viime piirtamisen jalkeen.
    std::list<std::shared_ptr<Rajapinta::ToimijaRP> > liikkuneet_toimijat_;

    // Mappi kuvista jotka ovat piirretty. Avaimena shared_ptr toimijaan
    // joka ollaan piirretty, ja arvona QGraphicsPixmapItem kuvake siitä
    // toimijasta.
    std::map<std::shared_ptr<Rajapinta::ToimijaRP>, QGraphicsPixmapItem*>
                                                            piirretyt_kuvat_;

    // Samanlainen mappi kuin ylempi, mutta tassa sailotaan Nyssejen
    // ylapuolella olevien tekstikenttien kuvakkeet.
    std::map<std::shared_ptr<Rajapinta::ToimijaRP>, QGraphicsTextItem*>
                                                            nyssejen_tekstit_;

};



#endif // PELINAKYMA_H
