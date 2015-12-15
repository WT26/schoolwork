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
}

Paaikkuna::~Paaikkuna()
{
    delete ui;
}
