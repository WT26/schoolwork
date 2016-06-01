#ifndef FUNKTIOT_H
#define FUNKTIOT_H

/**
  * @file
  * @brief Moduuli, jossa hyödyllisiä funktioita.
  */

#include "sijainti.hh"

namespace OmaPuoli {


/**
 * @brief Tarkistaa onko koordinaatit pelialueen sisällä.
 * @pre -
 * @param Tarkistettavat koordinaatit int x, y ja pelialueen int korkeus, leveys
 * @return boolean arvon true, jos koordinaatit olivat pelialueen sisällä, muuten false.
 * @post -
 */
bool onkoKuvassa(int x, int y, int korkeus, int leveys);

/**
 * @brief Tarkistaa onko parametrina saatu luku parillinen.
 * @pre -
 * @param int tarkistettava numero.
 * @return boolean arvot true jos numero on parillinen tai nolla, muuten false.
 * @post -
 */
bool onkoParillinen(int numero);

/**
 * @brief Tarkistaa onko parametrina saadut sijainnit lähellä toisiaan.
 * samanlainen kuin Sijainnin omat metodit, mutta alue hitusen isompi.
 * @pre -
 * @param Kaksi Sijainti oliota.
 * @return boolean arvot true jos Sijainnit lähellä toisiaan.
 * @post -
 */
bool onkoMelkoLahella(Rajapinta::Sijainti sij, Rajapinta::Sijainti sij2);

}

#endif // FUNKTIOT_H
