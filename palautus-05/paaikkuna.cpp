#include "paaikkuna.hh"
#include "ui_paaikkuna.h"
#include "apufunktiot.hh"
#include "yksikko.hh"
#include <sstream>
#include <iostream>

#include <vector>

Paaikkuna::Paaikkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Paaikkuna)
{
    ui->setupUi(this);
    //muunnoskaaviot_;
    //lista_yksikoista_joissa_lisattavaa_;
    //kohdeyksikot_;
}

Paaikkuna::~Paaikkuna()
{
    delete ui;
}

void Paaikkuna::on_valitse_lahto_clicked()
{
    ui->haku_label->setText("Haetaan kaikki mahdolliset kohdeyksikot..");
    qApp->processEvents();
    ui->kohdeyksikot_dropdown->setEnabled(false);
    ui->muunna_button->setEnabled(false);
    ui->muutettava_yksikko->setEnabled(false);
    ui->valitse_kohde->setEnabled(false);

    for(int tyhjentaja{0};tyhjentaja != ui->kohdeyksikot_dropdown->count();){
        ui->kohdeyksikot_dropdown->removeItem(tyhjentaja);
    }
    ui->kohdeyksikot_dropdown->removeItem(0);
    qApp->processEvents();


    unsigned int index{0};
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

    ui->kohdeyksikot_dropdown->setEnabled(true);
    ui->muunna_button->setEnabled(false);
    ui->muutettava_yksikko->setEnabled(false);
    ui->valitse_kohde->setEnabled(true);
    qApp->processEvents();

    kohdeyksikot_ = loytyy_listasta;
    for(unsigned int i{0};i != loytyy_listasta.size();i++){
        QString lisattava = QString::fromStdString(loytyy_listasta[i]);
        if(lisattava != ui->muutettavat_dropdown->currentText()){
            ui->kohdeyksikot_dropdown->addItem(lisattava);
        }
    }
    ui->haku_label->setText("");
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

        QString q_luku = ui->muutettava_yksikko->text();
        string luku = q_luku.toUtf8().constData();
        muunna_luku(luku, lahto, kohde);
    }
    else {
        cout<<"Virhe: muutettava kohta on tyhja."<<endl;
    }
}


void Paaikkuna::muunna_luku(string luku, string lahto, string kohde){
    pair<double, int> suhde_maara{1, 0};
    pair<double, int> suhteet;
    //double suhde_maara{1};
    double lisattava_summa{0};
    unsigned int indeksi{0};
    vector<string> lapi_kaydyt;
    while(indeksi != muunnoskaaviot_.size()){
        if (muunnoskaaviot_[indeksi].vertaa_yksikon_nimea(lahto)){
            suhteet = muunnoskaaviot_[indeksi].etsi_kohteen_suhde(suhde_maara, lahto, lahto, kohde, muunnoskaaviot_, lapi_kaydyt);
            double d_luku = stod(luku);
            double tulos = d_luku * suhteet.first;

            for(auto yksikon_nimi : lista_yksikoista_joissa_lisattavaa_){
                if(yksikon_nimi == lahto || yksikon_nimi == kohde){
                    vector<string> lapi_kaydyt_yksikot;
                    lisattava_summa = muunnoskaaviot_[indeksi].etsi_kohteen_lisattava(lisattava_summa, lahto, kohde, muunnoskaaviot_, lapi_kaydyt_yksikot);
                    break;
                }
            }
            cout<<suhteet.first<<"<-kerroin lisattava->"<<lisattava_summa<<endl;
            tulos += lisattava_summa;

            QString lisattava = QString::number(tulos);
            lisattava += " " + QString::fromStdString(kohde);

            ui->tulos_maara_label->setText(lisattava);

            break;
        }
        indeksi++;
    }
}

void Paaikkuna::on_lue_button_clicked()
{
    // Haetaan QString teksti tiedoston_nimi input kentasta ja tehdaan siita
    // Std string.
    string tiedoston_nimi = ui->tiedosto_kentta->text().toUtf8().constData();

    if (tiedoston_nimi == ""){
        // TODO virhe !
    }
    else{
        ui->muutettavat_dropdown->setEnabled(false);
        ui->kohdeyksikot_dropdown->setEnabled(false);
        ui->valitse_lahto->setEnabled(false);
        ui->muunna_button->setEnabled(false);
        ui->muutettava_yksikko->setEnabled(false);
        ui->valitse_kohde->setEnabled(false);
        qApp->processEvents();

        muunnoskaaviot_.clear();
        lista_yksikoista_joissa_lisattavaa_.clear();

        // Jos tiedostoa luetaan toista kertaa, tyhjennetaan kohdeyksikot_dropdown
        for(int tyhjentaja{0};tyhjentaja != ui->muutettavat_dropdown->count();){
            ui->muutettavat_dropdown->removeItem(tyhjentaja);
        }
        ui->muutettavat_dropdown->removeItem(0);
        qApp->processEvents();

        muunnoskaaviot_ = lue_muunnoskaaviot(tiedoston_nimi);

        for(auto yksikko : muunnoskaaviot_){
            lista_yksikoista_joissa_lisattavaa_ = yksikko.kohdeyksikoiden_lisattavyys(lista_yksikoista_joissa_lisattavaa_);
        }

        unsigned int indeksi{0};
        while(indeksi != muunnoskaaviot_.size()){
            string nimi = muunnoskaaviot_[indeksi].tulosta_yksikon_nimi();
            QString qnimi = QString::fromStdString(nimi);
            ui->muutettavat_dropdown->addItem(qnimi);
            indeksi++;
        }

        ui->muutettavat_dropdown->setEnabled(true);
        ui->valitse_lahto->setEnabled(true);
        qApp->processEvents();
    }


}
