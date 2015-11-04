#include "resurssilista.hh"
#include <iostream>

using namespace std;


void testilisaus(Resurssilista& resurssilista, const string& kayttaja) {
    cout << "Lisatty " << kayttaja << " koneelle "
         << resurssilista.lisaa(kayttaja) << endl;
}


void testipoisto(Resurssilista& resurssilista,
                 const string& tyopoytakone,
                 const string& kayttaja) {
    if ( resurssilista.poista(kayttaja, tyopoytakone) ) {
        cout << "poistettu onnistuneesti: " << kayttaja
             << " koneelta " << tyopoytakone << endl;
    } else {
        cout << "poisto epaonnistui: " << kayttaja
             << " koneelta " << tyopoytakone << endl;
    }
}


int main() {
    Resurssilista resurssit( {
            "opersk1.cs.tut.fi", "opersk2.cs.tut.fi", "opersk3.cs.tut.fi",
            "opersk4.cs.tut.fi", "opersk5.cs.tut.fi", "opersk6.cs.tut.fi",
            "opersk7.cs.tut.fi", "opersk8.cs.tut.fi", "opersk9.cs.tut.fi"
    } );

    resurssit.tulosta();

    for ( auto kayttaja : { "00", "01", "02", "03", "04", "05", "06", "07",
                            "08", "09", "10", "11", "12", "13", "14", "15",
                            "16", "17", "18", "19", "20", "21", "22", "23" } ) {

        testilisaus(resurssit, kayttaja);
    }

    resurssit.tulosta();

    testipoisto(resurssit, "opersk1.cs.tut.fi", "18");
    testipoisto(resurssit, "opersk2.cs.tut.fi", "10");
    testipoisto(resurssit, "opersk2.cs.tut.fi", "01");
    testipoisto(resurssit, "opersk7.cs.tut.fi", "15");
    testipoisto(resurssit, "opersk7.cs.tut.fi", "06");
    testipoisto(resurssit, "opersk7.cs.tut.fi", "06");

    resurssit.tulosta();

    for ( auto kayttaja : { "vaihe-2-00", "vaihe-2-01", "vaihe-2-02",
                            "vaihe-2-03", "vaihe-2-04", "vaihe-2-05",
                            "vaihe-2-06", "vaihe-2-07", "vaihe-2-08" } ) {

        testilisaus(resurssit, kayttaja);
    }

    resurssit.tulosta();
}
