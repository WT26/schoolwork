#include "funktiot.hh"

namespace OmaPuoli {

// Funktio tarkistaa onko parametrina saadut koordinaatit pelin kuvassa.
// Jalkimmaiset parametrit melko turhia, koska tuskin lisataan peliin
// liukuvaa nayttoa.
bool onkoKuvassa(int x, int y, int leveys, int korkeus)
{
    // Tarkoin valitut ja hiotut reunat. Nailla mitoilla QGraphicsScene ei tee temppuja
    // jos drooni menee reunoille.
    const int REUNAVALI_VASEN = 27;
    const int REUNAVALI_YLA = 35;
    const int REUNAVALI_OIKEA = 25;
    const int REUNAVALI_ALA = 45;

    // Tarkistetaan onko koordinaatit kuvassa +- reunavalit.
    if ((x > 0 + REUNAVALI_VASEN) && (x < leveys - REUNAVALI_OIKEA) &&
            (y > 0 + REUNAVALI_YLA) && (y < korkeus - REUNAVALI_ALA)){
        return true;
    }
    else {
        return false;
    }
}


// Funktio tarkistaa onko numero parillinen vai ei.
bool onkoParillinen(int numero) {
    if ( numero % 2 == 0 || numero == 0){ return true; }
    else { return false; }
}

// Funktio on samanlainen kuin Sijainti luokan onkoLahella metodi,
// mutta havaitsee sijainteja kauvempaa.
bool onkoMelkoLahella(Rajapinta::Sijainti sij, Rajapinta::Sijainti sij2) {
    int raja = 14;
    int dx = sij.annaX() - sij2.annaX();
    int dy = sij.annaY() - sij2.annaY();

    return dx*dx + dy*dy <= raja*raja;
}


}
