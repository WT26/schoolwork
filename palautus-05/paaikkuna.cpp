#include "paaikkuna.hh"
#include "ui_paaikkuna.h"
#include "apufunktiot.hh"
#include "yksikko.hh"
#include <sstream>
#include <iostream>
#include <vector>

// Paaikkuna, graafinen kayttoliittyma. Siina on kaikki kayttoliittymaan
// liittyvat komennot.

using namespace std;

Paaikkuna::Paaikkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Paaikkuna)
{
    ui->setupUi(this);

}


Paaikkuna::~Paaikkuna()
{
    delete ui;
}


// Valitse_lahto nappainta painamalla haetaan lahtoyksikkoa vastaavat
// kohdeyksikot, ja vain sellaiset kohdeyksikot jotka pystytaan muuttamaan
// tiedetyilla kaavoilla.
void Paaikkuna::on_valitse_lahto_clicked()
{
    ui->haku_label->setText("Haetaan kaikki mahdolliset kohdeyksikot..");
    qApp->processEvents();
    ui->kohdeyksikot_dropdown->setEnabled(false);
    ui->muunna_button->setEnabled(false);
    ui->muutettava_yksikko->setEnabled(false);
    ui->valitse_kohde->setEnabled(false);

    // Looppi tyhjentaa kohdeyksikot_dropdownin jos siella jotain on.
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

    // Etsitaan kaikista yksikoista vain ne kohdeyksikot, jotka
    // pystytaan laskemaan kaavoilla.
    while(index != muunnoskaaviot_.size()){
        if(muunnoskaaviot_[index].vertaa_yksikon_nimea(etsittava)){
            loytyy_listasta.push_back(etsittava);
            loytyy_listasta = muunnoskaaviot_[index].keraa_kohdeyksikot(loytyy_listasta, muunnoskaaviot_, lapi_kaydyt);
        }
        index++;
    }

    ui->kohdeyksikot_dropdown->setEnabled(true);
    ui->valitse_kohde->setEnabled(true);
    qApp->processEvents();

    // Lisataan loydetyt kohdeyksikot kohdeyksikot_dropdowniin.
    kohdeyksikot_ = loytyy_listasta;
    for( unsigned int i{0}; i != loytyy_listasta.size(); i++ ){
        QString lisattava = QString::fromStdString(loytyy_listasta[i]);
        if( lisattava != ui->muutettavat_dropdown->currentText() ){
            ui->kohdeyksikot_dropdown->addItem(lisattava);
        }
    }
    ui->haku_label->setText("");
}


// Kohteen valinta nappainta painamalla tulee mahdollisuus painaa muunna
// nappainta.
void Paaikkuna::on_valitse_kohde_clicked()
{
    ui->muunna_button->setEnabled(true);
    ui->muutettava_yksikko->setEnabled(true);
}


// Muunna nappainta painamalla tulos: kohtaan tulostuu haluttujen valintojen
// perusteella muunnostulos.
void Paaikkuna::on_muunna_button_clicked()
{
    if(ui->muutettava_yksikko->text() != ""){

        QString q_lahto = ui->muutettavat_dropdown->currentText();
        string lahto = q_lahto.toUtf8().constData();

        QString q_kohde = ui->kohdeyksikot_dropdown->currentText();
        string kohde = q_kohde.toUtf8().constData();

        QString q_luku = ui->muutettava_yksikko->text();
        string luku = q_luku.toUtf8().constData();

        if(onko_vain_numeroita(luku)){
            muunna_luku(luku, lahto, kohde);
        }
        else{
            cout<<"Virhe: muutettavassa kohdassa jotain"
                  "muuta kuin numeroita\n";
        }
    }
    else {
        cout<<"Virhe: muutettava kohta on tyhja.\n";
    }
}


// Metodi muuntaa syotetyn luvun lahto ja kohdeyksikoiden perusteella
// oikeanlaiseksi.
void Paaikkuna::muunna_luku(string luku, string lahto, string kohde){

    // Pair<double, int> sisaltaa suhteen double ja intin joka voi olla 1 tai
    // nolla. Yksi tarkoittaa etta lopullinen suhde on loytynyt ja voidaan
    // palata sen etsimis metodista. Nain saadaan rekursioon kaksi parametria
    // vain yhden sijaan ja saadaan etsimisfunktio toimimaan.
    pair<double, int> suhde_maara{1, 0};
    pair<double, int> suhteet;

    double lisattava_summa{0};
    unsigned int indeksi{0};
    vector<string> lapi_kaydyt;

    while(indeksi != muunnoskaaviot_.size()){
        if (muunnoskaaviot_[indeksi].vertaa_yksikon_nimea(lahto)){

            // Lasketaan lahto ja kohdeyksikon perusteella suhde
            // etsi_kohteen_suhde metodin avulla.
            suhteet = muunnoskaaviot_[indeksi].etsi_kohteen_suhde(suhde_maara,
                           lahto, lahto, kohde, muunnoskaaviot_, lapi_kaydyt);

            double d_luku = stod(piste_pilkuksi(luku));

            // Syotetty luku kerrotaan tassa yksikoisen valisella suhteella.
            double tulos = d_luku * suhteet.first;

            // Siina tapauksessa kun yksikoiden valilla on myos lisattavaa
            // taytyy se etsia eriksee.
            for( auto yksikon_nimi : lista_yksikoista_joissa_lisattavaa_ ){
                if( yksikon_nimi == lahto || yksikon_nimi == kohde ){
                    vector<string> lapi_kaydyt_yksikot;

                    lisattava_summa = muunnoskaaviot_[indeksi]
                            .etsi_kohteen_lisattava( lisattava_summa, lahto,
                            kohde, muunnoskaaviot_, lapi_kaydyt_yksikot );

                    break;
                }
            }
            tulos += lisattava_summa;

            // Muutetaan tulos QStringiksi ja naytetaan se tulos: labelissa.
            QString tulos_string = QString::number(tulos);
            tulos_string += " " + QString::fromStdString(kohde);

            ui->tulos_maara_label->setText(tulos_string);

            break;
        }
        indeksi++;
    }
}


// Lue nappainta painamalla luetaan tekstikentasta string ja etsitaan sen
// perusteella luettava tiedosto. Tiedostosta muodostetaan kaaviot.
void Paaikkuna::on_lue_button_clicked()
{
    // Haetaan QString tiedoston_nimi input-kentasta ja tehdaan siita
    // std string.
    string tiedoston_nimi = ui->tiedosto_kentta->text().toUtf8().constData();

    if (tiedoston_nimi == ""){
        cout<<"Virhe: Tiedoston nimi -kentta on tyhja\n";
    }
    else{
        ui->muutettavat_dropdown->setEnabled(false);
        ui->kohdeyksikot_dropdown->setEnabled(false);
        ui->valitse_lahto->setEnabled(false);
        ui->muunna_button->setEnabled(false);
        ui->muutettava_yksikko->setEnabled(false);
        ui->valitse_kohde->setEnabled(false);
        qApp->processEvents();

        // Tyhjennetaan muunnoskaaviot silta varalta etta lukeminen tapahtuu
        // uudelleen.

        muunnoskaaviot_.clear();
        lista_yksikoista_joissa_lisattavaa_.clear();

        // Jos tiedostoa luetaan toista kertaa, tyhjennetaan
        // kohdeyksikot_dropdown
        for( int tyhjentaja{0}; tyhjentaja !=
                                ui->muutettavat_dropdown->count(); ){

            ui->muutettavat_dropdown->removeItem(tyhjentaja);
        }
        ui->muutettavat_dropdown->removeItem(0);
        qApp->processEvents();

        // Luetaan tiedosto.
        muunnoskaaviot_ = lue_muunnoskaaviot(tiedoston_nimi);

        // Muodostetaan lista yksikoista joissa lisattavaa.
        for(auto yksikko : muunnoskaaviot_){
            lista_yksikoista_joissa_lisattavaa_ =
                    yksikko.kohdeyksikoiden_lisattavyys(
                        lista_yksikoista_joissa_lisattavaa_ );

        }

        // Sijoitetaan Yksikot muutettavat_dropdowniin.
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
