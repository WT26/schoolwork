#ifndef PAAIKKUNA_HH
#define PAAIKKUNA_HH

#include <QMainWindow>
#include <vector>
#include "yksikko.hh"

namespace Ui {
class Paaikkuna;
}

class Paaikkuna : public QMainWindow
{
    Q_OBJECT

public:
    explicit Paaikkuna(QWidget *parent = 0);
    ~Paaikkuna();

    void muunna_luku(string luku, string lahto, string kohde);

private slots:
    void on_valitse_lahto_clicked();

    void on_valitse_kohde_clicked();

    void on_muunna_button_clicked();

    void on_lue_button_clicked();

private:
    Ui::Paaikkuna *ui;
    vector<Yksikko> muunnoskaaviot_;
    vector<string> kohdeyksikot_;
    vector<string> lista_yksikoista_joissa_lisattavaa_;
};

#endif // PAAIKKUNA_HH
