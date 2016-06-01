// TIE-02200 Ohjelmoinnin peruskurssi, syksy 2015
// Harjoitustehtava 5
// 246479 joel.alanko@student.tut.fi (40h)

#include "paaikkuna.hh"
#include "apufunktiot.hh"
#include "yksikko.hh"
#include <QApplication>
#include <iostream>

// Alkukommentti: Yksinkertainen ohjelma, jolla voidaan muuttaa lukuja
// yksikoista toisiin. Ohjelma lukee syotetyn tiedoston nimen ja muodostaa
// siita kaavat. Tiedostossa yksikoiden muutokset pitaa olla muotoa
// "lahtoyksikko" <= "suhde" * "kohdeyksikko" + "lisattava". Ohjelmalla on
// graafinen kayttoliittyma, vaikka ohjeissa sellaista ei suositeltu.
// Kysyin sahkopostilla voinko lahettaa ohjelman tallaisena, vai muunnanko
// ohjelman tekstikayttoliittymaiseksi ja sain vastauksen etta voin
// palauttaa sen graafisena.

using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Paaikkuna w;
    w.show();

    return a.exec();
}
