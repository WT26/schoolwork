from tkinter import *
import random
import time

# TIE-02100 JOHOH K2016 Harjoitustyö T7
# Joel Alanko 246479
# Harjoitustyötä tein 15h~


# Alkuselostus/käyttöohje: Harjoitustyö on pieni 15 puzzle peli. Päämääränä on
# saada 15 eri palasta oikeaan järjestykseen mahdollisimman nopeasti.
# Palasia liikutellaan klikkailemalla niitä. Jos klikattu pala on tyhjän
# kohdan vieressä, liikahtaa palanen tyhjään kohtaan.
# Lisätietoa: fi.wikipedia.org/wiki/15-peli
# Kun peli on läpäisty, kysyy ohjelma pelaajan nimen ja lisää sen
# topten.txt listaan oikeaan kohtaan. Missä pelin vaiheessa tahansa
# voi palaset sekoittaa uudelleen ja aloittaa alusta, sekä katsella
# topten listaa. Koska peli on hyvin yksinkertainen, pelissä vain yksi luokka,
# jolla pelaaminen tapahtuu.

# Lista kuvista, jotka halutaan palojen paikalle. Tätä ei kuitenkaan
# käytetä, koska kuvia sai olla vain 10.
# PALAT = ["kuva.png"]

# Graafinen käyttöliittymä luokka. Koko pelin toiminta tapahtuu tämän sisällä.
class Puzzle:

    # Alustetaan kaikki mahdollinen.
    def __init__(self):
        self.__ikkuna = Tk()
        self.__ikkuna.title("15 Puzzle")
        self.__ikkuna.option_add("*Font", "Helvetica 15")
        self.__ikkuna.resizable(width=FALSE, height=FALSE)

        self.__ikkuna.protocol('WM_DELETE_WINDOW',
                               lambda:  quit())

        self.__aika_label = Label

        self.__peli_kaynnissa = False
        self.__top_lista_nakyvissa = False
        self.__voitto_ikkuna_nakyvissa = False

        self.__tyhjän_kohta = 16
        self.__kuvabuttonit = []

        self.__käyttäjän_nimi = ""
        self.__voitto_aika = 0
        self.__aloitus_aika = -1
        self.__siirrot = 0
        self.__RUUDUKON_KOKO = 16

        # Tämä osio kommentoitu pois, koska kuvia saikin olla vain 10.
        # Peli toimisi siis millä vain halutulla kuvalla, joka olisi jaettu
        # 16-15 osaan.
        # self.__kuvat = []
        # for kuvatiedosto in PALAT:
        #     kuva = PhotoImage(file=kuvatiedosto)
        #     self.__kuvat.append(kuva)

        # Alku järjestys. Hyvä, jotta pelaajat tietävät mihin pyrkiä.
        self.__järjestys = [1, 2, 3, 4, 5, 6, 7, 8, 9,
                            10, 11, 12, 13, 14, 15, 16]

        # Järjestetään Puzzlen buttonit self.__järjestys:ksen mukaan.
        self.järjestä_puzzle()

        # Luodaan tarvittavat nappulat.
        self.__sekoitaButton = Button(self.__ikkuna, text="SEKOITA",
                                      command=self.sekoita, height=3)
        self.__sekoitaButton\
            .grid(row=0, column=1, columnspan=2, sticky=W+E+N+S)

        Button(self.__ikkuna, text="TOP 10", command=self.luo_top_lista)\
            .grid(row=7, column=0, columnspan=2, sticky=N+W+S+E)

        Button(self.__ikkuna, text="Lopeta", command=self.__ikkuna.destroy)\
            .grid(row=7, column=2, columnspan=2, sticky=N+W+S+E)

        self.paivita_kello_ja_siirrot()

        self.__ikkuna.mainloop()

    # Metodi päivittää kellon sekä siirtojen lukumäärän sekunnin välein.
    def paivita_kello_ja_siirrot(self):

        # Jos peli on käynnissä, käynnistetään kello. Muuten luodaan
        # vain label.
        if self.__peli_kaynnissa:

            # Jollei peliä ole vielä aloitettu, lasketaan aloitusaika.
            if self.__aloitus_aika == -1:
                self.__aloitus_aika = time.time()

            # Vaihdetaan aika labelin teksti.
            aika_nyt = time.time() - self.__aloitus_aika
            kellostr = "Aika: " + str(int(aika_nyt))

            self.__aika_label = Label(self.__ikkuna, text=kellostr)\
                .grid(row=0, column=3, sticky=N+W+S+E)

        else:
            self.__aika_label = Label(self.__ikkuna, text="Aika: 0")\
                .grid(row=0, column=3, sticky=N+W+S+E)

        # Päivitetään myös siirtojen lukumäärä label.
        siirrot_txt = "Siirrot: " + str(self.__siirrot)
        Label(self.__ikkuna, text=siirrot_txt)\
            .grid(row=0, column=0, sticky=N+W+S+E)

        # Sekunnin päästä kutsutaan metodia uudelleen.
        self.__ikkuna.after(1000, self.paivita_kello_ja_siirrot)

    # Metodi sekoittaa palat ja käynnistää pelin.
    def sekoita(self):
        self.nollaa_peli()

        # Etsitään järjestystä niin kauvan kunnes löytyy sellainen jonka
        # voi ratkaista.
        voi_ratkaista = False
        while not voi_ratkaista:

            # Tyhjennetään järjestys, ja valitaan randomilla uusi järjestys.
            self.__järjestys = []

            while len(self.__järjestys) < self.__RUUDUKON_KOKO:
                numero = random.randint(1, self.__RUUDUKON_KOKO)

                # Jollei numero ole vielä listassa, lisätään se sinne.
                if numero not in self.__järjestys:
                    self.__järjestys.append(numero)

            # Tarkistetaan voiko peliä ratkaista tällä järjestyksellä.
            voi_ratkaista = self.ratkaistavissa()

        # Järjestetään puzzle palaset nyt uudestaan uudella
        # self.__järjetyksellä.
        self.järjestä_puzzle()

    # Metodi nollaa pelin sekä kaikki tilastot.
    def nollaa_peli(self):
        self.__aloitus_aika = -1
        self.__peli_kaynnissa = True
        self.__siirrot = 0

    # Metodi käynnistyy kun yhtä palaa on painettu. Metodi tarkistaa
    # on painettu näppäin tyhjän vieressä, jos on muuttaa järjestystä
    # sekä tarkistaa onko peli voitettu.
    def siirra(self, luku):
        if self.__peli_kaynnissa:
            if self.tyhjän_vieressä(self.__järjestys[luku - 1]):
                self.muuta_järjestys(luku)
                self.__siirrot += 1
                self.järjestä_puzzle()

                # Tarkistetaan voitettiinko peli tällä siirrolla.
                if self.tarkista_voitto():
                    self.peli_voitettu()

    # Metodi tarkistaa onko parametrinä saatu luku tyhjän vieressä.
    def tyhjän_vieressä(self, luku):

        # Haetaan luvun, sekä tyhän kohdan luvun rivit ja sarakkeet.
        rivi, sarake = self.numeron_rivi_ja_sarake(luku)
        tyhjän_rivi, tyhjän_sarake =\
            self.numeron_rivi_ja_sarake(self.__tyhjän_kohta)

        # Jos rivit ovat samat, sekä sarakkeet eroavat vain yhdellä,
        # eli |x-y| == 1, niin palautetaan true.
        if rivi == tyhjän_rivi:
            if abs(sarake - tyhjän_sarake) == 1:
                return True

        # Sama kuin ylempänä, nyt vain sarakkeet samat.
        elif sarake == tyhjän_sarake:
            if abs(rivi - tyhjän_rivi) == 1:
                return True
        else:
            return False

    # Metodi etsii luvun sarakkeen ja rivin ja palauttaa ne.
    def numeron_rivi_ja_sarake(self, luku):

        # Haetaan luvun rivi ja sarake.
        #   1   2   3   4
        #   5   6   7   8
        #   9   10  11  12
        #   13  14  15  16
        # Apuna käytetty yllä olevaa ruudukkoa. Rivillä 1 on siis
        # luvut 1,2,3,4 ja sarakkeella 1 luvut 1,5,9,13 jne. Sarakkeita
        # tarkistaessa tutkittavat indeksit vaihtelee siis välein 1 5 9 13
        # ja rivit vaihtelevat neljän kertoimen välein. Näistä for-loopin
        # avulla selviää rivi ja sarake.

        i = self.__järjestys.index(luku) + 1
        rivi = 1
        sarake = 1

        for indeksi in range(4):
            if i == indeksi + 1 or i == indeksi + 5 or i == indeksi + 9\
                    or i == indeksi + 13:
                sarake = indeksi + 1

            if i == (indeksi * 4) + 1 or i == (indeksi * 4) + 2\
                    or i == (indeksi * 4) + 3 or i == (indeksi * 4) + 4:
                rivi = indeksi + 1

        return rivi, sarake

    # Metodi järjestää puzzlen uudelleen self.__järjestys tavoin.
    def järjestä_puzzle(self):

        # Tuhotaan vanhat buttonit ja tyhjennetään lista.
        for button in self.__kuvabuttonit:
            button.destroy()
        self.__kuvabuttonit = []

        # Käydään läpi 16 eri numeroa self.__järjestyksessä ja luodaan buttonit
        # oikeille kohdille.
        oikeassa_järjestyksessä = True
        for i in range(self.__RUUDUKON_KOKO):
            palan_numero = self.__järjestys[i]

            if not palan_numero == i + 1:
                oikeassa_järjestyksessä = False

            # Jos palan numero on 16, on se tyhjä, eli skipataan.
            if palan_numero != self.__RUUDUKON_KOKO:

                # Haetaan palan rivi ja sarake.
                y, x = self.numeron_rivi_ja_sarake(palan_numero)

                # Luodaan button, ja annetaan sen commandille parametri luku=i.
                uusi_button = \
                    Button(self.__ikkuna, text=str(palan_numero),
                           command=lambda luku=i + 1: self.siirra(luku))

                # Jos halutaan käyttää kuvaa, täytyy käyttää tätä
                # ja ottaa muut configit pois.
                # uusi_button.configure(image=self.__kuvat[i + 1])

                # Asetetaan ja muokataan buttoneita paremmiksi.
                uusi_button.grid(row=y, column=x-1)
                uusi_button.configure(height=3, width=6)
                uusi_button.configure(font=("Helvetica", 22, "bold"))

                # Oikeassa järjestyksessä alusta alkaen vaihdetaan väriä
                # vaaleammaksi.
                if oikeassa_järjestyksessä:
                    uusi_button.configure(bg="LightSteelBlue1")
                else:
                    uusi_button.configure(bg="LightSteelBlue3")
                uusi_button.configure(activebackground="LightSteelBlue4")

                self.__kuvabuttonit.append(uusi_button)

    # Metodi muuttaa self.__järjestys:tä. Se vaihtaa parametrinä saadun luvun
    # sekä tyhjän kohdan paikkaa.
    def muuta_järjestys(self, luku):

        # Etsitään mikä luku on listassa.
        luku_listassa = self.__järjestys[luku - 1]

        # Nyt etsitään indeksit ja vaihdetaan ne tyhjän kanssa päittäin.
        luvun_index, tyhjän_index = \
            self.__järjestys.index(luku_listassa),\
            self.__järjestys.index(self.__tyhjän_kohta)

        self.__järjestys[luvun_index], self.__järjestys[tyhjän_index] =\
            self.__järjestys[tyhjän_index], self.__järjestys[luvun_index]

    # Metodi tarkistaa onko peli voitettu. Jos self.__järjestyksessä
    # on 16 lukua järjestyksessä, on peli voitettu.
    def tarkista_voitto(self):
        for i in range(self.__RUUDUKON_KOKO - 1):
            if i != (self.__järjestys[i] - 1):
                return False
        return True

    # Metodi näyttää ikkunan, joka kertoo että peli voitettu ja pyytää
    # pelaajan nimeä top10 listaa varten.
    def peli_voitettu(self):

        # Asetetaan peli pois käynnistä, jottei paloja voi enää siirrellä.
        self.__peli_kaynnissa = False

        self.__voitto_ikkuna_nakyvissa = True

        voitit_pelin = Tk()
        voitit_pelin.title("VOITIT PELIN!")
        voitit_pelin.resizable(width=FALSE, height=FALSE)
        voitit_pelin.protocol('WM_DELETE_WINDOW',
                              lambda:
                              self.voitto_ikkuna_suljettu(voitit_pelin))

        # Lasketaan voittoaika.
        self.__voitto_aika = int(time.time() - self.__aloitus_aika)

        voitto_label = Label(voitit_pelin,
                             text="     Onneksi olkoon, Voitit pelin!     "
                             "\n\nAikaa kului: " + str(self.__voitto_aika)
                             + "s\nSiirtoja käytit: " + str(self.__siirrot)
                             + "\n\nKirjoita nimesi TOP 10 Listalle.")
        voitto_label.grid(row=0, column=0, sticky=N)

        # Luodaan nimenkirjoitus kenttä ja ok näppäin. Tkinterin
        # dokumentaatiosta ei löytynyt minkään näköistä rajoitusta entryn
        # pituudelle. Netistä löytyi kyllä vino pino kirjastoja joilla tämä
        # saataisiin rajoitettua helposti ja muutama keino rajoittaa
        # entryn pituutta ilman kirjastoja. Kuitenkin nämä keinot olivat
        # sellaisia joiden käyttöä en tajunnut/saanut toimimaan, on pelissä
        # nyt bugi, jos kenttään laittaa tuhansia kirjaimia hidastuu/loppuu
        # pelin toiminta.
        voitto_entry = Entry(voitit_pelin)
        voitto_entry.grid(row=1, column=0, sticky=N)

        voitto_button = Button(voitit_pelin, text="  OK  ",
                               command=lambda: self.uusi_huippuluku
                               (voitit_pelin, voitto_entry))

        voitto_button.configure(state=NORMAL)
        voitto_button.grid(row=3, column=0, sticky=N)

    def voitto_ikkuna_suljettu(self, voitit_pelin):
        self.__voitto_ikkuna_nakyvissa = False
        voitit_pelin.destroy()

    # Metodi sulkee voitit_pelin ikkunan, päivittää top10 listan uudella
    # ennätyksellä sekä käynnistää top10 ikkunan.
    def uusi_huippuluku(self, voitit_pelin, voitto_entry):
        self.__käyttäjän_nimi = voitto_entry.get()
        # Jollei käyttäjän nimi ole yhtään merkkiä pitkä, ei edetä metodiin.
        if len(self.__käyttäjän_nimi) > 0:
            voitit_pelin.destroy()

            self.paivita_topten()

            # Voitto ikkuna ei ole enää näkyvissä.
            self.__voitto_ikkuna_nakyvissa = False

            # Näytetään toplista.
            self.luo_top_lista()

    # Metodi, joka lukee topten.txt tiedostosta kymmenen parasta pelaajaa,
    # ja luo niistä pienen windowin jossa ne näkyvät järjestyksessä.
    def luo_top_lista(self):
        # Jollei toplista ole näkyvissä, voidaan luoda uusi lista näkyviin.
        # Tämä sen takia, ettei listoja voi klikata miljoonaa samaan aikaan.
        if (not self.__top_lista_nakyvissa) and \
                (not self.__voitto_ikkuna_nakyvissa):
            top_lista = Tk()
            top_lista.title("TOP 10")
            top_lista.resizable(width=FALSE, height=FALSE)

            self.__top_lista_nakyvissa = True

            # Jotta sulkemistaja listan näkyvissäolemista voisi tarkkailla
            # tarvitaan tätä protokollaa. Eli kun X näppäintä painetaan,
            # suoritetaan metodi sulje_topten. Ja se suoritetaan lambda
            # funktiona, jotta saadaan parametri mukaan.
            top_lista.protocol('WM_DELETE_WINDOW',
                               lambda:  self.sulje_topten(top_lista))

            # Tarvittavat labelit
            teksti_label = Label(top_lista,
                                 text="            TOP TEN             ")
            teksti_label.grid(row=0, column=1, sticky=N)
            tyhjä_label = Label(top_lista, text="")
            tyhjä_label.grid(row=1, column=1, sticky=N)

            nimi_label = Label(top_lista, text="NIMI")
            nimi_label.grid(row=2, column=0, sticky=W)
            aika_label = Label(top_lista, text="AIKA(s)")
            aika_label.grid(row=2, column=1, sticky=N)
            siirrot_label = Label(top_lista, text="SIIRROT")
            siirrot_label.grid(row=2, column=2, sticky=E)

            # Nyt luetaan top10 lista ja muodostetaan niistä tarvittavat
            # labelit näkyviin sopiviin kohtiin.
            topten = open("topten.txt", 'r')
            i = 1
            for rivi in topten:
                tiedot = rivi.split(':')
                nimi_teksti = str(i) + ". " + tiedot[0]
                pelaaja_nimi_label = Label(top_lista, text=nimi_teksti)
                pelaaja_nimi_label.grid(row=2 + i, column=0, sticky=W + N)

                pelaaja_aika_label = Label(top_lista, text=tiedot[1])
                pelaaja_aika_label.grid(row=2 + i, column=1, sticky=N)

                pelaaja_siirrot_label = Label(top_lista, text=tiedot[2])
                pelaaja_siirrot_label.grid(row=2 + i, column=2, sticky=E + N)

                i += 1

            # Nappula jolla top10 voidaan sulkea.
            top_button = Button(top_lista, text="  OK  ",
                                command=lambda:  self.sulje_topten(top_lista))
            top_button.configure(state=NORMAL)
            top_button.grid(row=13, column=1, sticky=S)

    # Topten_listan sulkija metodi. Pitää huolta että se tulee suljettua
    # sekä sen ettei niitä voi olla näkyvissä kuin vain yksi kerrallaan.
    def sulje_topten(self, top_lista):
        top_lista.destroy()
        self.__top_lista_nakyvissa = False

    # Metodi päivittää mahdollisesti topten listan uudella ennätyksellä.
    def paivita_topten(self):

        nimi_string = self.muokkaa_nimi_kelvolliseksi()

        topten = open("topten.txt", 'r')

        # Splitataan rivit, ja otetaan listoihin talteen nimet, ajat
        # ja siirtojen lukumäärät
        ajat = []
        nimet = []
        siirrot = []
        for rivi in topten:
            tiedot = rivi.split(':')
            nimi = tiedot[0]
            nimet.append(nimi)
            aika = int(tiedot[1])
            ajat.append(aika)
            siirto = tiedot[2]
            siirrot.append(siirto)

        # Käydään läpi kaikki top10:n ajat. Jos pelaajan voittoaika on
        # pienempi kuin verrattavan aika, pysäytetään etsiminen
        # ja otetaan talteen se väli johon pelaajan aika tulee listaan.
        i = 0
        for aika in ajat:
            if aika == 0:
                break
            elif self.__voitto_aika < aika:
                break
            i += 1

        topten = open("topten.txt", 'w')

        # Kirjoitetaan topten.txt tiedostoon uudet kymmenen parasta.
        # Jos läpikäytävä kohta on sama kuin mihin uusi ennätys pitäisi
        # mennä(eli i), sijoitetaankin uusi ennätys, ja lisätään loput
        # luetuista sen jälkeen. Viimeinen tipahtaa luonnollisesti pois.
        indeksi = 0
        uusi_lisätty = False
        while indeksi != 10:
            # Jollei uutta ole vielä lisätty, tutkitaan kohtaako indeksit.
            # Jollei kohtaa, lisätään luetuista tiedoista.
            if not uusi_lisätty:

                if indeksi == i:
                    # Lisätään uusi ennätys tiedostoon.
                    topten.write(nimi_string + ":" + str(self.__voitto_aika)
                                 + ":" + str(self.__siirrot) + "\n")
                    uusi_lisätty = True

                else:
                    # Lisätään vanha tieto tiedostoon.
                    topten.write(nimet[indeksi] + ":" + str(ajat[indeksi])
                                 + ":" + str(siirrot[indeksi]))
                indeksi += 1
            else:
                # Lisätään vanha tieto tiedostoo, mutta indeksi on -1, koska
                # listaan on nyt lisätty myös uusi ennätys.
                topten.write(nimet[indeksi - 1] + ":" + str(ajat[indeksi - 1])
                             + ":" + str(siirrot[indeksi - 1]))
                indeksi += 1
        topten.close()

    def muokkaa_nimi_kelvolliseksi(self):
        # Käydään nimi läpi, ja muutetaan jokainen merkki joka on ':' merkiksi
        # '*' koska splittaus tapahtuu aina merkillä ':'. Lisäksi yli 40
        # menevät merkit tiputetaan pois, ettei tulisi liian pitkiä nimiä.
        nimi_string = ""
        laskija = 0
        for char in self.__käyttäjän_nimi:
            laskija += 1
            if char == ':':
                nimi_string += '*'
            else:
                nimi_string += char
            if laskija > 40:
                break
        return nimi_string

    # Testatessani peliä kymmeniä kertoja, järjestys ei ollut usein
    # ratkaistavissa. Ratkaisun varmistamiseksi löysin netistä tällaisen
    # koodin: http://stackoverflow.com/a/34570524
    # Jossa hyödynnetty: goo.gl/TPBp2t
    # Vaihdoin syntaksin pythonille ja muut arvot itselle sopiviksi.
    def ratkaistavissa(self):
        parity = 0
        grid_width = 4
        row = 0  # the current row we are on
        blank_row = 0  # the row with the blank tile
        for i in range(len(self.__järjestys)):

            if i % grid_width == 0:  # advance to next row
                row += 1

            if self.__järjestys[i] == 16:  # the blank tile
                blank_row = row  # save the row on which encountered
                continue

            j = i + 1
            while j < len(self.__järjestys):

                if self.__järjestys[j] != 0 \
                        and self.__järjestys[i] > self.__järjestys[j]:
                    parity += 1
                j += 1

        if grid_width % 2 == 0:  # even grid
            if blank_row % 2 == 0:  # blank on odd row; counting from bottom
                return parity % 2 == 0
            else:  # blank on even row; counting from bottom
                return parity % 2 != 0

        else:  # odd grid
            return parity % 2 == 0


def main():
    Puzzle()


main()