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
    ui->muunna_button->setEnabled(false);
    ui->muutettava_yksikko->setEnabled(false);
    ui->valitse_kohde->setEnabled(true);

    for(int tyhjentaja{0};tyhjentaja != ui->kohdeyksikot_dropdown->count();tyhjentaja++){
        ui->kohdeyksikot_dropdown->removeItem(tyhjentaja);
    }

    int index{0};
    QString q_etsittava = ui->muutettavat_dropdown->currentText();
    string etsittava = q_etsittava.toUtf8().constData();
    vector<string> loytyy_listasta;
    vector<string> lapi_kaydyt;

    while(index != muunnoskaaviot_.size()){
        if(muunnoskaaviot_[index].vertaa_yksikon_nimea(etsittava)){
            loytyy_listasta.push_back(etsittava);
            loytyy_listasta = muunnoskaaviot_[index].keraa_kohdeyksikot(loytyy_listasta, muunnoskaaviot_, lapi_kaydyt);
        }
        index++;
    }
    for(int i{0};i != loytyy_listasta.size();i++){
        QString lisattava = QString::fromStdString(loytyy_listasta[i]);
        if(lisattava != ui->muutettavat_dropdown->currentText()){
            ui->kohdeyksikot_dropdown->addItem(lisattava);
        }
    }
}


void Paaikkuna::on_valitse_kohde_clicked()
{
    ui->muunna_button->setEnabled(true);
    ui->muutettava_yksikko->setEnabled(true);
}

void Paaikkuna::on_muunna_button_clicked()
{
    if(ui->muutettava_yksikko->text() != ""){
        // Tarkista input
        QString q_lahto = ui->muutettavat_dropdown->currentText();
        string lahto = q_lahto.toUtf8().constData();

        QString q_kohde = ui->kohdeyksikot_dropdown->currentText();
        string kohde = q_kohde.toUtf8().constData();

        muunna_luku(ui->muutettava_yksikko->text(), lahto, kohde);
    }
    else {
        cout<<"Virhe: muutettava kohta on tyhja."<<endl;
    }
}


void Paaikkuna::muunna_luku(string luku, string lahto, string kohde){


}
