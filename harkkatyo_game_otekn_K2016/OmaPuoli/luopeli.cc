#include "luopeli.hh"
#include "kaupunki.hh"
#include "kaupunkirp.hh"
#include <QDebug>
#include <memory>
#include "alkukuva.hh"


// Pieni selostus ohjelman toiminnasta:
// Ensin naytetaan alkukuva. Se on dialog, eli homma jatkuu kun siita
// ollaan painettu OK. Sen jalkeen luodaan kaupunki, joka luo itselleen
// Pelinakyman, tilaston seka droonin. Kaupungilla on yksi metodi, joka
// paivittyy PAIVITYS_VALI_ valein. Tama metodi pyorayttaa droonin liikeeseen
// tarvittavat toimet, paivittaa pisteet tilastoon, ja piirtaa kuvat nakyviin
// Pelinakyma-luokan avulla. Turhia piirtamisia ei ole siis lainkaan.
// Peli jatkuu nain, kunnes 200 pistetta on saavutettu, jonka jalkeen
// kerrotaan pelaajalle etta peli on paasty lapi.
// Pelia voi jatkaa viela jos haluaa, tai lopettaa sen valikosta.
// Lisaosia olen merkinnyt metodin ylle lisaamalla tekstin __LISAOSA?__
// Kysymysmerkki sen takia, ettei lisaosista taida mikaan olla tismalleen
// samanlainen kuin ohjeissa. Muistin hallinta todella hyvalla tasolla,
// alussa pommien seka shaderin gifit tuottivat hankaluutta, mutta nyt ne
// poistetaan ja hoidetaan asiallisesti. Missaan vaiheesa ei muistia pitaisi
// tarvita aaretonta maaraa, eli peli pysyy pelattavana ainakin itse testaamani
// puolituntia.
// Pelille sopivin aloitusaika on itseni mielesta 16:23

namespace Rajapinta
{

std::shared_ptr<KaupunkiRP> luoPeli() {

    // Naytetaan alkukuva dialog, jossa ohjeet seka motiivi pelin pelaamiselle.
    Alkukuva *alku = new Alkukuva();
    alku->scrollaaYlos();
    alku->setModal(true);
    alku->exec();

    std::shared_ptr<KaupunkiRP> kaupunki_ptr = std::make_shared<OmaPuoli::Kaupunki>();

    return kaupunki_ptr;
}

}

// Oma resource kansio toimimaan.
void accio_resource(){Q_INIT_RESOURCE(kuvat);}
