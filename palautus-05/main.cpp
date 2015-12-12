#include "paaikkuna.hh"
#include "apufunktiot.hh"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    lue_muunnoskaaviot();

    QApplication a(argc, argv);
    Paaikkuna w;
    w.show();

    return a.exec();
}
