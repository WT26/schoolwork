# TIE-02100 Johdatus Ohjelmointiin, kevät 2016
# Harjoitustyo
# 246479 joel.alanko@student.tut.fi (15h)

# ALKUKOMMENTTI:
# Yksinkertainen peli kahdelle pelaajalle, jota pelataan tekstikomennoilla.
# Pelissä päämääränä on tartuttaa oman numeron palalla ainakin kolme
# robottia samanaikaisesti, joita toinen ei yritä tartuttaa samalla hetkellä.
# Peliä pelataan omalla vuorolla sijoittamalla paloja joko pysty tai
# vaakasuunnassa muuttuva läbyrintti -pelin tavoin. Palat luetaan ensin
# palat.txt tiedostosta ja aloituslauta luetaan ja muodostetaan
# tiedostosta pelilauta.txt.


def main():
    # Pääfunktio, joka lukee tiedostot ja alustaa pelin, ja käynnistää
    # käyttöliittymän.

    palalista = lue_palat()
    alustettu_lauta, aloitus_pala = lue_pelilauta(palalista)
    käyttöjärjestelmä(alustettu_lauta, aloitus_pala)


def lue_palat():
    # Lukee palat tiedostosta ja muodostaa niistä Pala oliot sekä
    # palauttaa ne listassa.

    palalista = []
    palan_merkki = ""

    pala_tiedosto = open("palat.txt", "r")
    rivi = pala_tiedosto.readline()

    # Käy tiedostoa rivi-riviltä läpi, ottaen talteen palan merkin sekä
    # palan tiedot, jonka jälkeen luo näistä Pala -olion.
    while rivi != "":
        if len(rivi) == 2:
            palan_merkki = rivi[0]

        elif len(rivi) == 4:
            palan_tiedot = ""
            palan_tiedot += rivi[0:3]

            rivi = pala_tiedosto.readline()
            palan_tiedot += rivi[0:3]

            rivi = pala_tiedosto.readline()
            palan_tiedot += rivi[0:3]

            palalista.append(Pala(palan_merkki, palan_tiedot))

        rivi = pala_tiedosto.readline()
    pala_tiedosto.close()

    return palalista


def lue_pelilauta(palalista):
    # Lukee valmiin pelilaudan merkit ja muodostaa niistä Pala oliot.
    # Näin alustuu pelilauta. Viimeinen luettu pala on aloituspala.
    # Lopuksi funktio palauttaa alustetun laudan sekä aloituspalan.

    alustettu_lauta = []
    pelilauta_tiedosto = open("pelilauta.txt", "r")
    rivi = pelilauta_tiedosto.readline()
    indeksi = 0
    rivin_numero = 0

    # Käy läpi kirjain kirjaimelta tiedoston merkkejä ja luo niistä
    # Pala-olioita ja sijoittaa ne alustuslauta listaan.
    while rivi != "":
        merkki = rivi[indeksi]
        for pala in palalista:

            # Jos merkki täsmää, eli pala on se mikä halutaan luoda,
            # Luodaan se ja sijoitetaan alustettu_lauta listaan.
            if pala.merkki_täsmää(merkki):
                alustettu_lauta.append(pala.palauta_samanlainen_pala())

        # Lasketaan koska rivin kaikki merkit on tutkittu, jonka
        # jälkeen vaihdetaan riviä. Kun kaikki rivitkin on käyty läpi
        # luodaan vielä aloitus_pala ja palautetaan tiedot.
        if indeksi == 3:
            if rivin_numero == 3:
                rivi = pelilauta_tiedosto.readline()
                merkki = rivi[0]

                for pala in palalista:
                    if pala.merkki_täsmää(merkki):
                        aloitus_pala = pala
                        pelilauta_tiedosto.close()
                        return alustettu_lauta, aloitus_pala

            else:
                indeksi = -1
                rivin_numero += 1
                rivi = pelilauta_tiedosto.readline()
        indeksi += 1


def käyttöjärjestelmä(alustettu_lauta, aloitus_pala):
    # Käyttöjärjestelmä joka kertoo pelilaudan tilanteen, peli vuoron ja jota
    # voi käyttää tekstikomennoin. Mahdollisia komentoja ovat lauta, käännä,
    # vaaka ja pysty.

    nykyinen_lauta = alustettu_lauta
    komento = ""
    vuoro = "Pelaajan 1 vuoro."
    pelattava_pala = aloitus_pala
    nykyinen_lauta = päivitä_lauta(nykyinen_lauta)

    # Tulostaa pelivuoron ja pelilaudan sekä pelattavan palan.
    vuoron_alkutoimet(vuoro, nykyinen_lauta, pelattava_pala)

    edellinen_siirto = 0
    edellinen_suunta = "vaaka"

    while komento != "lopeta":
        komento = input("> ")
        komento = komento.split()

        if len(komento) > 2 or len(komento) == 0:
            print("Virheellinen syöte.")

        elif komento[0] == "lauta":
            tulosta_lauta(nykyinen_lauta)

        elif komento[0] == "käännä":
            pelattava_pala.käännä_pala()

        # Komento, jolla yritetään siirtää pala vaakasuunnassa haluttuun
        # kohtaan.
        elif komento[0] == "vaaka":

            # Tarkistetaan onko luku laudalla.
            if int(komento[1]) < 1 or int(komento[1]) > 8:
                print("Virhe: luku ei laudalla.")

            # Tarkistetaan onko siirto mahdollinen, eli kumoisiko se edellisen
            # siirron.
            elif (mahdollinen_siirto(int(komento[1]), "vaaka",
                                     edellinen_siirto, edellinen_suunta)):

                nykyinen_lauta, pelattava_pala = vaaka_siirto(int(komento[1]),
                                                              nykyinen_lauta,
                                                              pelattava_pala)
                vuoro = vaihda_vuoro(vuoro)
                edellinen_siirto = komento[1]
                edellinen_suunta = komento[0]

                if tarkista_onko_voittajaa(nykyinen_lauta):
                    return

                else:
                    vuoron_alkutoimet(vuoro, nykyinen_lauta, pelattava_pala)

            else:
                print("Virhe: kumoaa edellisen siirron.")

        # Komento, jolla yritetään siirtää pala pystysuunnassa haluttuun
        # kohtaan.
        elif komento[0] == "pysty":
            if int(komento[1]) < 1 or int(komento[1]) > 8:
                print("Virhe: luku ei laudalla.")

            elif (mahdollinen_siirto(int(komento[1]), "pysty",
                                     edellinen_siirto, edellinen_suunta)):

                nykyinen_lauta, pelattava_pala = pysty_siirto(int(komento[1]),
                                                              nykyinen_lauta,
                                                              pelattava_pala)
                vuoro = vaihda_vuoro(vuoro)
                edellinen_siirto = komento[1]
                edellinen_suunta = komento[0]

                if tarkista_onko_voittajaa(nykyinen_lauta):
                    return
                else:
                    vuoron_alkutoimet(vuoro, nykyinen_lauta, pelattava_pala)

            else:
                print("Virhe: kumoaa edellisen siirron.")
        else:
            print("Virheellinen syöte.")


def vaaka_siirto(siirron_numero, nykyinen_lauta, pelattava_pala):
    # Funktio siirtää palan vaakasuunnassa nykyiselle laudalle.

    uusi_pala = pelattava_pala

    # Vaihdetaan palat järjestyksessä viereisiin paloihin, ja otetaan talteen
    # ylijäävä pala(uusi_pala).
    if siirron_numero <= 4:
        uusi_pala = nykyinen_lauta[(siirron_numero * 4 - 1)]
        nykyinen_lauta[(siirron_numero * 4 - 1)] =\
            nykyinen_lauta[(siirron_numero * 4 - 2)]

        nykyinen_lauta[(siirron_numero * 4 - 2)] =\
            nykyinen_lauta[(siirron_numero * 4 - 3)]

        nykyinen_lauta[(siirron_numero * 4 - 3)] =\
            nykyinen_lauta[(siirron_numero * 4 - 4)]

        nykyinen_lauta[(siirron_numero * 4 - 4)] = pelattava_pala

        uusi_pala.poista_virus()

    elif siirron_numero >= 5:
        uusi_pala = nykyinen_lauta[((siirron_numero - 4) * 4 - 4)]
        nykyinen_lauta[((siirron_numero - 4) * 4 - 4)] =\
            nykyinen_lauta[((siirron_numero - 4) * 4 - 3)]

        nykyinen_lauta[((siirron_numero - 4) * 4 - 3)] =\
            nykyinen_lauta[((siirron_numero - 4) * 4 - 2)]

        nykyinen_lauta[((siirron_numero - 4) * 4 - 2)] =\
            nykyinen_lauta[((siirron_numero - 4) * 4 - 1)]

        nykyinen_lauta[((siirron_numero - 4) * 4 - 1)] = pelattava_pala

        uusi_pala.poista_virus()

    return nykyinen_lauta, uusi_pala


def pysty_siirto(siirron_numero, nykyinen_lauta, pelattava_pala):
    # Kuten ylempi funktio, siirtää pelattavan palan laudalle, mutta vain
    # pystysuunnissa olevien numeroiden perusteella.

    uusi_pala = pelattava_pala

    # Vaihdetaan palat järjestyksessä alempiin paloihin, ja otetaan talteen
    # ylijäävä pala(uusi_pala).
    if siirron_numero <= 4:
        uusi_pala = nykyinen_lauta[(siirron_numero + 11)]
        nykyinen_lauta[(siirron_numero + 11)] =\
            nykyinen_lauta[(siirron_numero + 7)]

        nykyinen_lauta[(siirron_numero + 7)] =\
            nykyinen_lauta[(siirron_numero + 3)]

        nykyinen_lauta[(siirron_numero + 3)] =\
            nykyinen_lauta[(siirron_numero - 1)]

        nykyinen_lauta[(siirron_numero - 1)] = pelattava_pala

        uusi_pala.poista_virus()

    # Vaihdetaan palat järjestyksessä ylempiin paloihin, ja otetaan talteen
    # ylijäävä pala(uusi_pala).
    elif siirron_numero >= 5:
        uusi_pala = nykyinen_lauta[siirron_numero - 5]
        nykyinen_lauta[siirron_numero - 5] = nykyinen_lauta[siirron_numero - 1]
        nykyinen_lauta[siirron_numero - 1] = nykyinen_lauta[siirron_numero + 3]
        nykyinen_lauta[siirron_numero + 3] = nykyinen_lauta[siirron_numero + 7]
        nykyinen_lauta[siirron_numero + 7] = pelattava_pala

        uusi_pala.poista_virus()

    return nykyinen_lauta, uusi_pala


def mahdollinen_siirto(siirron_numero, suunta, edellinen_siirto,
                       edellinen_suunta):
    # Tarkistaa kumoaako haluttu siirto edellisen siirron ja palauttaa
    # boolean arvon.

    if edellinen_suunta == "vaaka" and suunta == "vaaka":
        if ((siirron_numero == int(edellinen_siirto) + 4) or
                (siirron_numero == int(edellinen_siirto) - 4)):
            return False
        else:
            return True

    elif edellinen_suunta == "pysty" and suunta == "pysty":
        if ((siirron_numero == int(edellinen_siirto) + 4) or
                (siirron_numero == int(edellinen_siirto) - 4)):
            return False
        else:
            return True

    # Muissa tapauksissa siirto on mahdollinen.
    else:
        return True


def tarkista_onko_voittajaa(nykyinen_lauta):
    # Funktio palauttaa boolean arvon onko jompi kumpi pelaajista
    # pelin voittaja.

    nykyinen_lauta = päivitä_lauta(nykyinen_lauta)
    pelaaja_1_tartuttanut = 0
    pelaaja_2_tartuttanut = 0

    # Käy kaikki palat läpi ja tarkistaa onko ne tartutettu, jos on niin
    # kumpi tartutuksen on tehnyt, pelaaja 1 vai 2 ja antaa pisteitä sen
    # mukaan. Jos jommalla kummalla on 3 tai enemmän tartutuksia, on se
    # pelin voittaja ja funktio palauttaa boolean arvon tosi.
    for pala in nykyinen_lauta:
        tartutus = pala.onko_tartutettu()
        if tartutus == 1:
            pelaaja_1_tartuttanut += 1

        elif tartutus == 2:
            pelaaja_2_tartuttanut += 1

    if pelaaja_1_tartuttanut >= 3:
        pelaaja_voitti(1)
        return True

    elif pelaaja_2_tartuttanut >= 3:
        pelaaja_voitti(2)
        return True


def pelaaja_voitti(pelaajan_numero):
    # Tulostaa voittaneen pelaajan ja voittotekstin.

    print("Pelin voitti pelaaja " + str(pelaajan_numero) + ".")


def päivitä_lauta(nykyinen_lauta):
    # Päivittää laudalla olevien robottien tilan.

    # Haetaan ensin pelaajien sijainnit
    pelaajan_1_sijainti, pelaajan_2_sijainti = \
        etsi_pelaajien_sijainnit(nykyinen_lauta)

    # Neutralisoidaan laudalla olevat robotit, jottei tule virhellisiä
    # muutoksia.
    nykyinen_lauta = tyhjennä_virukset(nykyinen_lauta)

    # Jos pelaaja on pelattavana palana, on sen sijainti 20, muulloin sen
    # sijainti on 1 - 16.
    if pelaajan_1_sijainti != 20:
        nykyinen_lauta = tarkista_vasen(pelaajan_1_sijainti, 1, nykyinen_lauta)
        nykyinen_lauta = tarkista_oikea(pelaajan_1_sijainti, 1, nykyinen_lauta)
        nykyinen_lauta = tarkista_ylä(pelaajan_1_sijainti, 1, nykyinen_lauta)
        nykyinen_lauta = tarkista_ala(pelaajan_1_sijainti, 1, nykyinen_lauta)

    if pelaajan_2_sijainti != 20:
        nykyinen_lauta = tarkista_vasen(pelaajan_2_sijainti, 2, nykyinen_lauta)
        nykyinen_lauta = tarkista_oikea(pelaajan_2_sijainti, 2, nykyinen_lauta)
        nykyinen_lauta = tarkista_ylä(pelaajan_2_sijainti, 2, nykyinen_lauta)
        nykyinen_lauta = tarkista_ala(pelaajan_2_sijainti, 2, nykyinen_lauta)

    return nykyinen_lauta


def tarkista_vasen(sijainti, pelaajan_numero, nykyinen_lauta):
    # Tarkistaa vasemmalla olevat palat yksitellen, ja tartuttaa ne jos ne on
    # robotteja, ja lopettaa tarkistamisen, jos vastaan tulee romu tai laudan
    # reuna. Lopuksi palauttaa muokatun laudan.

    for i in range(3):
        tutkittava_sijainti = sijainti - 1

        # Reunatilanteet, lopetetaan tarkistaminen.
        if (tutkittava_sijainti == 3 or tutkittava_sijainti == 7 or
                tutkittava_sijainti == 11 or tutkittava_sijainti == -1):
            return nykyinen_lauta

        # Pala on romu, lopetetaan tarkistaminen.
        elif nykyinen_lauta[tutkittava_sijainti].onko_romu("leveys"):
            return nykyinen_lauta

        # Tarkistetaan onko pala robotti, jos on, tartutetaan se, muulloin
        # skipataan ja jatketaan tarkistamista.
        elif nykyinen_lauta[tutkittava_sijainti].onko_robotti():
            nykyinen_lauta[tutkittava_sijainti].\
                tartuta_robotti(pelaajan_numero)

        sijainti -= 1

    return nykyinen_lauta


def tarkista_oikea(sijainti, pelaajan_numero, nykyinen_lauta):
    # Samanlainen kuin ylempi, suunta oikea.
    for i in range(3):
        tutkittava_sijainti = sijainti + 1

        if (tutkittava_sijainti == 4 or tutkittava_sijainti == 8 or
                tutkittava_sijainti == 12 or tutkittava_sijainti == 16):
            return nykyinen_lauta

        elif nykyinen_lauta[tutkittava_sijainti].onko_romu("leveys"):
            return nykyinen_lauta

        elif nykyinen_lauta[tutkittava_sijainti].onko_robotti():
            nykyinen_lauta[tutkittava_sijainti].\
                tartuta_robotti(pelaajan_numero)

        sijainti += 1

    return nykyinen_lauta


def tarkista_ylä(sijainti, pelaajan_numero, nykyinen_lauta):
    # Samanlainen kuin ylemmät, suunta ylöspäin.
    for i in range(3):
        tutkittava_sijainti = sijainti - 4

        if tutkittava_sijainti < 0:
            return nykyinen_lauta

        elif nykyinen_lauta[tutkittava_sijainti].onko_romu("pituus"):
            return nykyinen_lauta

        elif nykyinen_lauta[tutkittava_sijainti].onko_robotti():
            nykyinen_lauta[tutkittava_sijainti].\
                tartuta_robotti(pelaajan_numero)

        sijainti -= 4

    return nykyinen_lauta


def tarkista_ala(sijainti, pelaajan_numero, nykyinen_lauta):
    # Samanlainen kuin ylemmät, suunta alaspäin.
    for i in range(3):
        tutkittava_sijainti = sijainti + 4

        if tutkittava_sijainti > 15:
            return nykyinen_lauta

        elif nykyinen_lauta[tutkittava_sijainti].onko_romu("pituus"):
            return nykyinen_lauta

        elif nykyinen_lauta[tutkittava_sijainti].onko_robotti():
            nykyinen_lauta[tutkittava_sijainti].\
                tartuta_robotti(pelaajan_numero)

        sijainti += 4

    return nykyinen_lauta


def tyhjennä_virukset(nykyinen_lauta):
    # Neutralisoi laudan robotit, eli poistaa virukset.
    # Palauttaa tyhjennetyn laudan.

    for pala in nykyinen_lauta:
        if pala.onko_robotti():
            pala.poista_virus()
    return nykyinen_lauta


def etsi_pelaajien_sijainnit(nykyinen_lauta):
    # Etsii pelaajien sijainnit laudalla. Palauttaa molempien sijainnit.
    # Jos pelaaja ei ole laudalla, sen sijainniksi laitetaan 20, joka
    # tarkoittaa, että pelaaja on pelattavana palana.

    laskija = 0
    pelaajien_sijainteja_loytynyt = 0
    pelaaja_1_kohdassa = 20
    pelaaja_2_kohdassa = 20

    # Käydään kaikki palat läpi ja etsitään palat joissa niiden merkki täsmää.
    for pala in nykyinen_lauta:
        if pala.merkki_täsmää("1"):
            pelaajien_sijainteja_loytynyt += 1
            pelaaja_1_kohdassa = laskija

        elif pala.merkki_täsmää("2"):
            pelaajien_sijainteja_loytynyt += 1
            pelaaja_2_kohdassa = laskija

        if pelaajien_sijainteja_loytynyt == 2 or laskija == 15:
            return pelaaja_1_kohdassa, pelaaja_2_kohdassa

        laskija += 1


def tulosta_lauta(nykyinen_lauta):
    # Funktio tulostaa nykyisen laudan siistissä ja selkeässä muodossa.

    tulostettava_teksti = "    1   2   3   4\n  -----------------\n"
    numero_edessa = 1
    numero_perassa = 5

    # Käydään alla oleva algoritmi läpi neljä kertaa. Pidetään muistia
    # sivuille sijoitettavista numeroista(numero_edessä ja -perässä) jotta
    # algoritmi toimii.
    for i in range(4):
        tulostettava_teksti += "  |"
        for indeksi in range(4):
            tulostettava_teksti = nykyinen_lauta[(i * 4) + indeksi].\
                täydennä_tulostettavaan(tulostettava_teksti, "ylin")
            tulostettava_teksti += "|"

        tulostettava_teksti += "\n" + str(numero_edessa) + " |"
        for indeksi in range(4):
            tulostettava_teksti = nykyinen_lauta[(i * 4) + indeksi].\
                täydennä_tulostettavaan(tulostettava_teksti, "keskimmainen")
            tulostettava_teksti += "|"

        tulostettava_teksti += " " + str(numero_perassa) + "\n  |"
        for indeksi in range(4):
            tulostettava_teksti = nykyinen_lauta[(i * 4) + indeksi].\
                täydennä_tulostettavaan(tulostettava_teksti, "alin")
            tulostettava_teksti += "|"

        tulostettava_teksti += "\n  -----------------\n"
        numero_edessa += 1
        numero_perassa += 1
    tulostettava_teksti += "    5   6   7   8"

    print(tulostettava_teksti)


def vaihda_vuoro(vuoro_teksti):
    # Funktio vaihtaa pelaajan vuoron. Muokkaa vuoro_tekstin toisekseen
    # ja palauttaa muutetun vuoro_tekstin.

    if vuoro_teksti == "Pelaajan 1 vuoro.":
        vuoro_teksti = "Pelaajan 2 vuoro."

    else:
        vuoro_teksti = "Pelaajan 1 vuoro."

    return vuoro_teksti


def vuoron_alkutoimet(vuoro, nykyinen_lauta, pelattava_pala):
    # Tulostaa nykyisen pelaajan vuoron, pelilaudan ja pelattavan palan.

    print(vuoro)
    tulosta_lauta(nykyinen_lauta)
    print("Pelattava pala:")
    pelattava_pala.tulosta_pala()


class Pala():
    # Luokka jossa on palan tiedot. Tiedot ovat stringissä peräkkäin
    # josta luodaan ylin, keskimmäinen sekä alin rivi.
    # Esim: xxxyYyzzz
    # tulos:    xxx
    #           yYy
    #           zzz

    def __init__(self, palan_merkki, palan_tiedot):
        self.__palan_merkki = palan_merkki
        self.__palan_tiedot = palan_tiedot
        self.__palan_ylin_rivi = \
            palan_tiedot[0] + palan_tiedot[1] + palan_tiedot[2]

        self.__palan_keskimmäinen_rivi = \
            palan_tiedot[3] + palan_tiedot[4] + palan_tiedot[5]

        self.__palan_alin_rivi =\
            palan_tiedot[6] + palan_tiedot[7] + palan_tiedot[8]

    def käännä_pala(self):
        # Käännöksessä tapahtuvat vaihdot:
        #
        # merkit    1   2   3           # merkit   7   4   1
        # alussa    4   5   6           # lopussa  8   5   2
        #           7   8   9           #          9   6   3

        self.__palan_ylin_rivi = \
            self.__palan_tiedot[6] + self.__palan_tiedot[3]\
            + self.__palan_tiedot[0]

        self.__palan_keskimmäinen_rivi = \
            self.__palan_tiedot[7] + self.__palan_tiedot[4]\
            + self.__palan_tiedot[1]

        self.__palan_alin_rivi = \
            self.__palan_tiedot[8] + self.__palan_tiedot[5]\
            + self.__palan_tiedot[2]

        self.__palan_tiedot = \
            self.__palan_ylin_rivi + self.__palan_keskimmäinen_rivi \
            + self.__palan_alin_rivi

        # Tarkistetaan vielä onko palan merkki '!' tai '-'. Jos on, vaihdetaan
        # se päittäin toiseen.
        if self.__palan_merkki == "!":
            self.__palan_merkki = "-"

        elif self.__palan_merkki == "-":
            self.__palan_merkki = "!"

        self.tulosta_pala()

    def merkki_täsmää(self, merkki):
        # Palauttaa boolean arvon onko merkki sama kuin palan_merkki.

        if self.__palan_merkki == merkki:
            return True
        else:
            return False

    def täydennä_tulostettavaan(self, teksti, rivi):
        # Metodi lisää tekstiin halutun rivin Palasta.

        if rivi == "ylin":
            return teksti + self.__palan_ylin_rivi

        elif rivi == "keskimmainen":
            return teksti + self.__palan_keskimmäinen_rivi

        elif rivi == "alin":
            return teksti + self.__palan_alin_rivi

        else:
            return teksti

    def tulosta_pala(self):
        # Metodi tulostaa palan 3x3 muodossa.
        # Esim:  xxx
        #        yyy
        #        zzz

        print(self.__palan_ylin_rivi + "\n" + self.__palan_keskimmäinen_rivi
              + "\n" + self.__palan_alin_rivi)

    def onko_romu(self, suunta):
        # Metodi palauttaa boolean arvon True palasta, jos se on romu pala.
        # Tarkastelussa täytyy tietää suunta, koska jostain romusta voi
        # lähettää viirusta läpi tietyssä suunnassa(esim "!" palasta
        # pystysuunnassa).

        if suunta == "leveys":
            if self.__palan_merkki == "!" or self.__palan_merkki == "+":
                return True

            else:
                return False

        else:
            if self.__palan_merkki == "-" or self.__palan_merkki == "+":
                return True

            else:
                return False

    def onko_robotti(self):
        # Metodi palauttaa boolean arvon True jos pala on robotti-pala.

        if (self.__palan_merkki == "o" or self.__palan_merkki == "Q" or
                self.__palan_merkki == "@"):
            return True

        else:
            return False

    def tartuta_robotti(self, pelaajan_numero):
        # Metodi tartuttaa robotin, eli muokkaa pelaajan numeron perusteella
        # robottia. Jos robottia yritetään jo tartuttaa, palautuu se takaisin
        # normaaliin tilaan.

        if self.__palan_merkki == "o":
            if pelaajan_numero == 1:
                self.__palan_merkki = "Q"
                self.__palan_keskimmäinen_rivi = ".Q."

            elif pelaajan_numero == 2:
                self.__palan_merkki = "@"
                self.__palan_keskimmäinen_rivi = ".@."

        else:
            self.poista_virus()

    def poista_virus(self):
        # Metodi neutralisoi robotin, eli muuttaa viiruksen saaneet robotit
        # neutraaleiksi(eli "Q" ja "@" muuttuu -> "o").

        if self.__palan_merkki == "Q":
            self.__palan_merkki = "o"
            self.__palan_keskimmäinen_rivi = ".o."

        elif self.__palan_merkki == "@":
            self.__palan_merkki = "o"
            self.__palan_keskimmäinen_rivi = ".o."

    def onko_tartutettu(self):
        # Metodi palauttaa boolean arvon onko Pala tartutettu robotti.

        if self.__palan_merkki == "Q":
            return 1

        elif self.__palan_merkki == "@":
            return 2

        else:
            return 0

    def palauta_samanlainen_pala(self):
        # Metodi palauttaa samanlaisen Palan kuin se itse on.
        # Tätä metodia tarvitaan kun alustetaan pelilautaa, eikä haluta
        # että kaikki samanlaiset palat olisi samoja paloja(sama muistiosoite).

        return Pala(self.__palan_merkki, self.__palan_tiedot)


main()