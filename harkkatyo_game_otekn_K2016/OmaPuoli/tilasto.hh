#ifndef TILASTO_HH
#define TILASTO_HH

/**
  * @file
  * @brief Luokka joka pitää kirjaa erinäisistä arvoista.
  */

#include "tilastorp.hh"



namespace OmaPuoli{


/**
  * @file
  * @brief Luokka sisältää tilastoa pelistä. Kaupunki päivittelee tilastoa,
  * ja pelinäkymä käyttää sitä hyödykseen esimerkiksi piirtäessaan
  * kokonaispisteiden määrää kuvaan.
  */
class Tilasto : public Rajapinta::TilastoRP
{
public:
    Tilasto();

    /**
     * @brief lisaaPisteita Lisaa int lkm:män verran pisteitä muuttujaan int pisteet_.
     * @pre -
     * @post Pisteet lisätty.
     */
    void lisaaPisteita(int lkm);

    // Speksattu TilastoRP luokassa.
    int annaPisteet() const;

    /**
     * @brief Palauttaa matkustajien lkm.
     * @pre -
     * @post -
     */
    int annaMatkustijienLkm() const;

    /**
     * @brief Palauttaa nyssejen lkm.
     * @pre -
     * @post -
     */
    int annaNyssejenLkm() const;

    /**
     * @brief Palauttaa tuhoutuneiden nyssejen lkm.
     * @pre -
     * @post -
     */
    int annaTuhoutuneidenNyssejenLkm() const;


    void matkustajiaKuoli(int lkm);
    void lisaaMatkustajia(int lkm);
    void nysseTuhoutui();
    void uusiNysse();
    void nyssePoistui();

private:
    int pisteet_;
    int matkustajien_kokonais_lkm_;
    int nyssejen_kokonais_lkm_;
    int tuhoutuneet_nysset_lkm_;
};

}

#endif // TILASTO_HH
