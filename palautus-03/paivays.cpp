#include "paivays.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>  // invalid_argument-poikkeustyyppi.

using namespace std;


namespace {

    // Funktio palauttaa true, jos parametrien kuvaama päiväys
    // on olemassa.  Muussa tapauksessa paluuarvo on false.
    bool onko_paivays_olemassa(unsigned int pp, unsigned int kk,
                              unsigned int vv) {
        bool karkausvuosi;
        karkausvuosi = ((vv % 4 == 0 and vv % 100 != 0) or vv % 400 == 0);

        if ( pp < 1 or pp > 31 ) {
            return false;

        } else if ( kk < 1 or kk > 12 ) {
            return false;

        } else if ( karkausvuosi and kk == 2 and pp > 29 ) {
            return false;

        } else if ( not karkausvuosi and kk == 2 and pp > 28 ) {
           return false;

        } else if ((kk == 4 or kk == 6 or kk == 9 or kk == 11) and pp > 30) {
            return false;

        } else {

            return true;
        }
    }
}


Paivays::Paivays(): paiva_{0}, kuu_{0}, vuosi_{0} {
}


Paivays::Paivays(unsigned int paiva, unsigned int kuu, unsigned int vuosi) {
    // Koska rakentaja ei voi palauttaa arvoa virhetilanteessa,
    // on tässä toimittu siten, että lähtöarvojen edustaessa
    // virheellistä päivämäärää, rakentaja aiheuttaa (heittää, throw)
    // poikkeuksen.  Tämä on jonkin verran ylikurssiainesta, eikä
    // sitä ole tarpeen ymmärtää.

    if ( not aseta(paiva, kuu, vuosi) ) {
        throw invalid_argument("virheellinen paivamaara");
    }
}


Paivays::Paivays(const string& paivays) {
    if ( not aseta(paivays) ) {
        throw invalid_argument("virheellinen paivamaara");
    }
}


// Asettaa päiväyksen arvon parametrien mukaiseksi. Paluuarvo
// true, jos paiväys on virheetön, muutoin paluuarvo on false.
bool Paivays::aseta(unsigned int paiva, unsigned int kuu, unsigned int vuosi) {
    if ( not onko_paivays_olemassa(paiva, kuu, vuosi) ) {
        return false;
    }

    paiva_ = paiva;
    kuu_ = kuu;
    vuosi_ = vuosi;

    return true;
}


// Asettaa päiväyksen arvon parametrin paivays pohjalta.
// Parametrin on oltava muotoa "p.k.v", eli esimerkiksi "21.7.2011".
// Paluuarvo on true, mikäli parametri on virheetön päivämäärä,
// muutoin paluuarvo on false.
bool Paivays::aseta(const string& paivays) {
    vector<string> kentat{ split(paivays, '.') };
    if ( kentat.size() != 3 ) {
        return false;
    }

    unsigned int pp;
    unsigned int kk;
    unsigned int vvvv;

    if ( not string_unsignediksi(kentat.at(0), pp)
         or not string_unsignediksi(kentat.at(1), kk)
         or not string_unsignediksi(kentat.at(2), vvvv) ) {

        return false;
    }

    // aseta(unsigned, unsigned, unsigned)-metodin paluuarvo sopii
    // suoraan tämän metodin paluuarvoksi: true jos pp, kk ja vvvv
    // esittävät hyväksyttävää päivämäärää, false muussa tapauksessa.
    return aseta(pp, kk, vvvv);
}


// Funktio siirtää päiväystä yhden päivän eteenpäin.
// Tätä metodia ei ole testattu kunnolla. Mikäli tarvitset sitä
// ohjelmassasi, joudut ehkä testaamaan sitä itse lisää.
void Paivays::seuraava_paiva() {
    if ( onko_paivays_olemassa(paiva_ + 1, kuu_, vuosi_) ) {
        ++paiva_;

    } else if ( onko_paivays_olemassa(1, kuu_ + 1, vuosi_) ) {
        paiva_ = 1;
        ++kuu_;

    } else {

        paiva_ = 1;
        kuu_ = 1;
        ++vuosi_;
    }
}


// Tämä metodi on ylikurssiainesta, mutta se on määriteltävä,
// jos Paivays-tyyppisiä olioita halutaan käyttää map-säiliön
// haluavaimen tyyppinä tai niitä halutaan tallettaa set-säiliöön.
// Metodi operator< toteuttaa Paivays-luokalla pienempi-kuin-operaattorin.
// Kun metodi on määritelty, kahta Paivays-tyyppistä oliota voi vertailla
// olio1 < olio2, eli normaalisti <-operaattorilla.  Myös algorithm-kirjaston
// sort-funktio osaa tämän jälkeen lajitella Paivays-olioita.
bool Paivays::operator<(const Paivays& oikealla) const {
    if ( vuosi_ < oikealla.vuosi_ ) {
        return true;

    } else if ( vuosi_ == oikealla.vuosi_
                and kuu_ < oikealla.kuu_) {
        return true;

    } else if ( vuosi_ == oikealla.vuosi_
                and kuu_ == oikealla.kuu_
                and paiva_ < oikealla.paiva_ ) {

        return true;

    } else {

        return false;
    }
}


// merkkijonoksi-metodin avulla Paivays-tyyppinen olio saadaan
// muutettua merkkijonoesitykseen.  Tulos perustuu formaatti-merkkijonon
// arvoon. Paluuarvona saatava merkkijono riippuu formaatista siten,
// että jokainen:
//
//    %{PAIVA}  korvattu päivänumerolla
//    %{PAIVA2} korvattu päivänumerolla (täydennetty nollilla 2:n pituiseksi)
//    %{KUU}    korvattu kuun numerolla
//    %{KUU2}   korvattu kuun numerolla (täydennetty nollilla 2:n pituiseksi)
//    %{VUOSI}  korvattu vuoden numerolla
//
// Jos siis esimerkiksi päivämäärä on kesäkuun 7 vuonna 2013,
// ja formaatti-parametrin arvo on "p:%{PAIVA2},k:%{KUU},v:%{VUOSI}",
// palauttaisi metodi merkkijonon "p:07,k:6,v:2013".
string Paivays::merkkijonoksi(string formaatti) const {
    map<string, string> muunnokset {
        { "%{PAIVA}",  to_string(paiva_) },
        { "%{KUU}",    to_string(kuu_) },
        { "%{VUOSI}",  to_string(vuosi_) },
    };


    muunnokset.insert( { "%{PAIVA2}", muunnokset.at("%{PAIVA}") } );
    if ( muunnokset.at("%{PAIVA2}").length() < 2 ) {
        muunnokset.at("%{PAIVA2}").insert(0, "0");
    }

    muunnokset.insert( { "%{KUU2}", muunnokset.at("%{KUU}") } );
    if ( muunnokset.at("%{KUU2}").length() < 2 ) {
        muunnokset.at("%{KUU2}").insert(0, "0");
    }


    for ( auto muunnos : muunnokset ) {

        // Viitteitä voi käyttää ohjelmakoodin selkeyttämiseen.
        // Seuraavassa annetaan väliaikainen lisänimi
        // muunnos.first:ille ja muunnos.second:ille, jotta niiden
        // käyttötarkoitus on helpompi ymmärtää.

        const string& korvattava{ muunnos.first };
        const string& korvaaja{ muunnos.second };

        while ( true ) {
            string::size_type korvauskohta{ formaatti.find(korvattava) };
            if ( korvauskohta == string::npos ) {
                break;
            }
            formaatti.replace(korvauskohta, korvattava.length(), korvaaja);
        }
    }
    return formaatti;
}


void Paivays::tulosta(const string& formaatti) const {
    cout << merkkijonoksi(formaatti) << endl;
}

//-----------------------------------------------------------------------------

#ifdef PAIVAYS_MAIN

#include <set>


int main() {
    Paivays p;

    cout << "***** asetus-testit:" << endl;

    const vector<string> TESTATTAVAT{
        "6.10.2020",
        "20.10.2015",
        "21.10.2015",
        "22.10.2015",
        "1.2.1999",
        "1.2.2000",
        "1.2.2001",
        "10.5.1912",
        "10.6.1912",
        "10.7.1912",
        "29.2.2000",
        "29.2.2016",

        // virheellisiä arvoja

        "29.2.1900",
        "29.2.2015",
        "31.4.2015",
        "32.5.2015",
        "20.13.2015",
    };

    for ( auto testiarvo: TESTATTAVAT ) {
        cout << string(50, '-') << endl;
        if ( p.aseta(testiarvo) ) {
            p.tulosta();
            p.tulosta("--%{PAIVA2}--%{KUU2}--%{VUOSI}--");

            cout << p.merkkijonoksi( "[%{PAIVA}/%{PAIVA2}/"
                                     "%{KUU}/%{KUU2}/%{VUOSI}]"
                                     "[%{PAIVA}/%{PAIVA2}/"
                                     "%{KUU}/%{KUU2}/%{VUOSI}]" ) << endl;


        } else {

            cout << "Virheellinen paivamaara " << testiarvo << endl;
        }
    }


    cout << endl << "***** set<Paivays> -testit:" << endl;
    set<Paivays> data;

    for ( auto testiarvo: TESTATTAVAT ) {
        p.aseta(testiarvo);
        data.insert(p);
    }

    for ( auto arvo : data ) {
        arvo.tulosta("%{PAIVA2}/%{KUU2}/%{VUOSI}");
    }


    // cout << endl << "***** seuraava_paiva-testit:" << endl;
    // p.aseta("31.12.2015");
    // for ( int i=0; i < 368; ++i ) {
    //     p.tulosta();
    //     p.seuraava_paiva();
    // }
}

#endif
