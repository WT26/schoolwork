#include "paaikkuna.hh"
#include "apufunktiot.hh"
#include "yksikko.hh"

#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Paaikkuna w;
    w.show();

    return a.exec();
}
