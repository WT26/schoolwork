#ifndef DROONI_H
#define DROONI_H

/**
  * @file
  * @brief Määrittelee pelitilassa tapahtuvia virheitä ilmaisevan poikkeusluokan.
  */

#include "kulkuneuvorp.hh"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QLabel>

namespace OmaPuoli {


/**
 * @brief Drooni jolla lennetaan kaupungin ylla. Perii ToimijaRP, jotta voi
 * kayttaa hyodyllisia Sijainti ja muita Rajapinta funktioita.
 * Perii myos QGraphicsPixmapItemin, jotta helppo asettaa kuva
 * ja sijoittaa QGraphicsSceneen.
 */
class Drooni : public Rajapinta::ToimijaRP, public QGraphicsPixmapItem {

public:
    Drooni();
    ~Drooni();

    /**
     * @brief Ottaa signaaleja käyttäjän painikkeiden painamisesta.
     * @pre -
     * @post Jonkin painikkeen "pohjassa" arvo on tosi.
     */
    void keyPressEvent(QKeyEvent * event);

    /**
     * @brief Ottaa signaaleja jos painike ei enää ole pohjassa.
     * @pre Painike on ollut painettuna.
     * @post -
     */
    void keyReleaseEvent(QKeyEvent * event);

    /**
     * @brief Hidastaa Kaupungin PAIVITYS_VALI aika valein droonin nykyinen_nopeus_ arvoa.
     * @pre -
     * @post -
     */
    void hidastaVauhtia();

    /**
     * @brief Vaihdetaan droonin_kuva_ parametrina saaduksi kuvaksi.
     * @param QPixmap kuva on droonille vaihdettava kuva.
     * @pre -
     * @post Kuva on vaihdettu.
     */
    void paivitaDrooninKuva(QPixmap kuva);

    /**
     * @brief Vaihdetaan droonin_kuva_ parametrina saaduksi kuvaksi.
     * @pre -
     * @post Sijainti on muutettu
     */
    void paivitaDrooninSijainti();

    /**
     * @brief Palautetaan droonin valilyonti_pohjassa_ boolean arvo.
     * @pre -
     * @return valilyonti_pohjassa_
     * @post -
     */
    bool palautaValilyonninTila();

    /**
     * @brief Resetoidaan valilyonti_pohjassa_ arvo arvoksi false.
     * @pre -
     * @post valilyonti_pohjassa_ on false
     */
    void resetoiValilyonninTila(); // Valilyonnin tila muutetaan false

    /**
     * @brief Liikutaan pixeli kerrallaan suunta_kulma_:n osoittamaan suuntaan
     * kunnes ollaan kuvan rajalla.
     * @param int dx ja dy ovat suuntakertoimet, joilla kerrotaan nopeutta suunta_kulma_:n osoittamaan
     * suuntaan. Mahdollisia arvoja vain -1, 0 ja 1
     * @pre -
     * @post Droonin sijainti ei voi olla yhtään pixeliä reunemmassa.
     */
    void liikuPixeliKerrallaan(int dx, int dy);

    /**
     * @brief Palauttaa nykyisen droonin_kuva_ arvon.
     * @pre -
     * @return QPixmap droonin_kuva_
     * @post -
     */
    QPixmap palautaKuva();

    /**
     * @brief Palautetaan sen hetken suunta_kulma_:n arvo.
     * @pre -
     * @return int suunta_kulma_
     * @post -
     */
    int palautaSuuntakulma();


    Rajapinta::Sijainti annaSijainti() const;

    void liiku(Rajapinta::Sijainti sij);
    void tuhoa();

    bool onkoTuhottu() const;


public slots:
    /**
     * @brief Liikuttaa droonia suunta_kulma_:n ja nykyinen_nopeus_:n avulla.
     * @pre -
     * @post Droonin paikka tarvittaessa vaihtunut.
     */
    void drooninLiike();


private:

    Rajapinta::Sijainti sijainti_;
    QPixmap droonin_kuva_;

    int suunta_kulma_;
    double nykyinen_nopeus_;

    const double MAX_NOPEUS_ = 20;

    bool kaasupohjassa_ = false;
    bool kaannospohjassa_ = false;
    bool valilyonti_pohjassa_ = false;

    bool onko_tuhottu_ = false;
};

}
#endif // DROONI_H
