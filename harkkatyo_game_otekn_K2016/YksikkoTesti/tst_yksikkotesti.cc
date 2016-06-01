#include <QString>
#include <QtTest>

#include "tilasto.hh"

class YksikkoTesti : public QObject
{
    Q_OBJECT

public:
    YksikkoTesti();

private Q_SLOTS:
    void testitapaus_annaPisteet();
    void testitapaus_lisaaPisteita();
    void testitapaus_matkustajiaKuoli(int lkm);
    void testitapaus_lisaaMatkustajia(int lkm);
    void testitapaus_nysseTuhoutui();
    void testitapaus_uusiNysse();
    void testitapaus_nyssePoistui();
};

YksikkoTesti::YksikkoTesti() {
}

// Testataan metodin annaPisteet toiminta.
void YksikkoTesti::testitapaus_annaPisteet() {

    // Lisataan tilastoon yhteensa 190 pistetta vahitellen.
    int lisattavat = 190;

    OmaPuoli::Tilasto t;

    // Testataan onko tilasto tyhja.
    QCOMPARE(t.annaPisteet(), 0);

    // Lisataan pisteita.
    for(unsigned int i = 1; i != 20; i++){
        t.lisaaPisteita(i);
    }

    // Testataan onko pisteita lisatty juuri haluttu maara.
    QCOMPARE(t.annaPisteet(), lisattavat);
}


// Testataan metodin lisaaPisteita toiminta.
void YksikkoTesti::testitapaus_lisaaPisteita() {
    unsigned int lisattavat = 50;
    int ei_unsigned_lisattavat = 50;

    OmaPuoli::Tilasto t;

    QCOMPARE(t.annaPisteet(), 0);

    t.lisaaPisteita(lisattavat);

    QCOMPARE(t.annaPisteet(), ei_unsigned_lisattavat);
}


// Testataan metodin matkustajiaKuoli toiminta.
void YksikkoTesti::testitapaus_matkustajiaKuoli(int lkm = 20) {
    OmaPuoli::Tilasto t;

    int lisattava_maara = 30;

    QCOMPARE(t.annaMatkustijienLkm(), 0);

    t.lisaaMatkustajia(lisattava_maara);

    QCOMPARE(t.annaMatkustijienLkm(), lisattava_maara);

    t.matkustajiaKuoli(lkm);

    QCOMPARE(t.annaMatkustijienLkm(), (lisattava_maara - lkm));
}


// Testataan metodin lisaaMatkustajia toiminta.
void YksikkoTesti::testitapaus_lisaaMatkustajia(int lkm = 20) {
    OmaPuoli::Tilasto t;

    QCOMPARE(t.annaMatkustijienLkm(), 0);

    t.lisaaMatkustajia(lkm);

    QCOMPARE(t.annaMatkustijienLkm(), lkm);
}


// Testataan metodin nysseTuhoutui toiminta.
void YksikkoTesti::testitapaus_nysseTuhoutui() {
    OmaPuoli::Tilasto t;

    t.uusiNysse();

    QCOMPARE(t.annaTuhoutuneidenNyssejenLkm(), 0);

    t.nysseTuhoutui();

    QCOMPARE(t.annaTuhoutuneidenNyssejenLkm(), 1);
}


// Testataan metodin uusiNysse toiminta.
void YksikkoTesti::testitapaus_uusiNysse() {
    OmaPuoli::Tilasto t;

    QCOMPARE(t.annaNyssejenLkm(), 0);

    t.uusiNysse();

    QCOMPARE(t.annaNyssejenLkm(), 1);

}


// Testataan metodin nyssePoistui toiminta.
void YksikkoTesti::testitapaus_nyssePoistui() {
    OmaPuoli::Tilasto t;

    t.uusiNysse();

    QCOMPARE(t.annaNyssejenLkm(), 1);

    t.nyssePoistui();

    QCOMPARE(t.annaNyssejenLkm(), 0);

}

QTEST_APPLESS_MAIN(YksikkoTesti)

#include "tst_yksikkotesti.moc"
