#include "tilasto.hh"

namespace OmaPuoli{


Tilasto::Tilasto() {
    pisteet_ = 0;
    matkustajien_kokonais_lkm_ = 0;
    nyssejen_kokonais_lkm_ = 0;
    tuhoutuneet_nysset_lkm_ = 0;
}

void Tilasto::lisaaPisteita(int lkm) {
    pisteet_ += lkm;
}

int Tilasto::annaPisteet() const {
    return pisteet_;
}

int Tilasto::annaMatkustijienLkm() const {
    return matkustajien_kokonais_lkm_;
}

int Tilasto::annaNyssejenLkm() const {
    return nyssejen_kokonais_lkm_;
}

int Tilasto::annaTuhoutuneidenNyssejenLkm() const {
    return tuhoutuneet_nysset_lkm_;
}

void Tilasto::matkustajiaKuoli(int lkm) {
    matkustajien_kokonais_lkm_ -= lkm;
}

void Tilasto::lisaaMatkustajia(int lkm) {
    matkustajien_kokonais_lkm_ += lkm;
}

void Tilasto::nysseTuhoutui() {
    nyssejen_kokonais_lkm_ -= 1;
    tuhoutuneet_nysset_lkm_ += 1;
}

void Tilasto::uusiNysse() {
    nyssejen_kokonais_lkm_ += 1;
}

void Tilasto::nyssePoistui() {
    nyssejen_kokonais_lkm_ -= 1;
}


}
