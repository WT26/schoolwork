#ifndef ALKUKUVA_H
#define ALKUKUVA_H

/**
  * @file
  * @brief UI luokka, joka näyttää ohjeet pelin pelaamiseen.
  */

#include <QDialog>
#include <QGraphicsScene>

namespace Ui {

/**
 * @brief Alkukuva on UI luokka, joka sisältää ohjeet pelin pelaamiseen.
 *
 * Alkukuva on QDialog, eli toiminta jatkuu kun painetaan OK näppäintä.
 * kuvassa motiivi pelin pelaamiseen, taustatietoa ja tiedot kuvista.
 */
class Alkukuva;
}

class Alkukuva : public QDialog
{
    Q_OBJECT

public:
    explicit Alkukuva(QWidget *parent = 0);
    ~Alkukuva();

    /**
     * @brief scrollaaYlos scrollaa QGraphicsScenen takaisin alkuun ylos.
     * @pre -
     * @param
     * @return pistemäärä
     * @post Poikkeustakuu: nothrow
     */
    void scrollaaYlos();

private:
    Ui::Alkukuva *ui;
    QGraphicsScene *scene_;

};

#endif // ALKUKUVA_H
