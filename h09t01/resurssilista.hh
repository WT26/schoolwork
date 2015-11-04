#ifndef RESURSSILISTA_HH
#define RESURSSILISTA_HH

#include <vector>
#include <string>
#include <memory>

using namespace std;


class Kuluttajalista {
  public:
    Kuluttajalista();
    int pituus() const;
    void tulosta() const;
    void lisaa(const string& kuluttajan_nimi);
    bool poista(const string& kuluttajan_nimi);

    Kuluttajalista(const Kuluttajalista& alustusarvo) = delete;
    Kuluttajalista& operator=(const Kuluttajalista& sijoitettava) = delete;

  private:
    struct Kuluttajalistan_alkio {
        string kuluttajan_nimi;
        shared_ptr<Kuluttajalistan_alkio> seuraavan_kuluttajan_osoite;
    };

    int alkioiden_lukumaara_;
    shared_ptr<Kuluttajalistan_alkio> ensimmaisen_kuluttajan_osoite_;
};


class Resurssilista {
  public:
    Resurssilista(const vector<string>& resurssien_nimet);
    void tulosta() const;
    string lisaa(const string& kuluttajan_nimi);
    bool poista(const string& kuluttajan_nimi, const string& resurssin_nimi);

    Resurssilista(const Resurssilista& alustusarvo) = delete;
    Resurssilista& operator=(const Resurssilista& sijoitettava) = delete;

  private:
    struct Resurssilistan_alkio {
        string resurssin_nimi;
        shared_ptr<Resurssilistan_alkio> seuraavan_resurssin_osoite;
        Kuluttajalista kuluttajat;
    };

    shared_ptr<Resurssilistan_alkio> ensimmaisen_resurssin_osoite_;
};

#endif
