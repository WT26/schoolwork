#include "paaikkuna.hh"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"moi"<<endl;

    QApplication a(argc, argv);
    Paaikkuna w;
    w.show();

    return a.exec();
}
