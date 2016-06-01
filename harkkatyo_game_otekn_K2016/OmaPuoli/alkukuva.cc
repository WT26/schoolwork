#include "alkukuva.hh"
#include "ui_alkukuva.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QScrollBar>

// Aloitus kuva, jossa naytetaan tiedot, suunnitelma seka ohjeet.
// Kuvasta taytyy klickata OK, jotta pelia paasee pelaamaan.
// __LISAOSA?__: "selkeat" ohjeet pelin pelaamiseen, tausta tarinaa seka
// vahva motiivi pelin voittamiseen.

Alkukuva::Alkukuva(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alkukuva)
{
    ui->setupUi(this);

    setWindowTitle(QString("OPERAATIO TIEDOTE"));

    // Lukitaan pelinakyman leveys ja korkeus. Nailla arvoilla
    // koko on taydellinen.
    QWidget::setFixedSize(520, 580);

    // Luodaan QGraphicsScene ja tallennetaan se scene_
    scene_ = new QGraphicsScene();

    // Ladataan alkunakymalle taustakuva ja asetetaan sceneen.
    QGraphicsPixmapItem * taustakuva_item =
            new QGraphicsPixmapItem(QPixmap(":/kuvat/alkunakyma.png"));

    scene_->addItem(taustakuva_item);

    // Kuvasta Horizontal scrollbaari pois kaytosta.
    ui->graphicsView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    // Scrollataan takaisin ylos.
    scrollaaYlos();

    // Naytetaan luotu scene_ graphicsViewissa
    ui->graphicsView->setScene(scene_);


}


Alkukuva::~Alkukuva()
{
    delete ui;
}


// Metodi scrollaa graphicsViewin takaisin ylos alkuun
// Normaalisti kuvan lisayksen jalkeen scrollauskohta
// olisi noin puolessa valissa.
void Alkukuva::scrollaaYlos()
{
    int uusi_arvo = 120; // Arvo, jolla scrollaus varmasti ylhaalla.

    // Vaihdetaan graphicsViewing scrollbaarin value newValue:ksi
    QScrollBar* yPos=ui->graphicsView->verticalScrollBar();
    yPos->setValue((int) uusi_arvo);
}
