#include "paaikkuna.hh"
#include "ui_paaikkuna.h"
#include "apufunktiot.hh"
#include "yksikko.hh"
#include <iostream>

#include <vector>

Paaikkuna::Paaikkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Paaikkuna)
{
    ui->setupUi(this);
    muunnoskaaviot_ = lue_muunnoskaaviot();

    int indeksi{0};
    while(indeksi != muunnoskaaviot_.size()){
        string nimi = muunnoskaaviot_[indeksi].tulosta_yksikon_nimi();
        QString qnimi = QString::fromStdString(nimi);
        ui->muutettavat_dropdown->addItem(qnimi);
        indeksi++;
    }


    ui->muutettavat_dropdown->currentText();
}

Paaikkuna::~Paaikkuna()
{
    delete ui;
}

void Paaikkuna::on_valitse_lahto_clicked()
{
    ui->kohdeyksikot_dropdown->setEnabled(true);

    for(int tyhjentaja{0};tyhjentaja != ui->kohdeyksikot_dropdown->count();tyhjentaja++){
        ui->kohdeyksikot_dropdown->removeItem(tyhjentaja);
    }

    int index{0};
    QString q_etsittava = ui->muutettavat_dropdown->currentText();
    string etsittava = q_etsittava.toUtf8().constData();
    while(index != muunnoskaaviot_.size()){
        if(muunnoskaaviot_[index].vertaa_yksikon_nimea(etsittava)){


            for (int i{0};i != muunnoskaaviot_[index].kohdeyksikkojen_maara();i++){
                string kohde = muunnoskaaviot_[index].tulosta_kohdeyksikot_kohdassa(i);
                QString qkohde = QString::fromStdString(kohde);

                for(auto tulostaja: muunnoskaaviot_[index].tulosta_kohdeyksikot_kohdassa(i));
                ui->kohdeyksikot_dropdown->addItem(qkohde);
            }
        }
        index++;
    }
}


