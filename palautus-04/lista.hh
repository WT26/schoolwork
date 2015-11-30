#ifndef LISTA_HH
#define LISTA_HH

#include <string>
#include <memory>

using namespace std;

class Lista
{
public:
    Lista();

    void lisaa_alkio_loppuun(const string& lisattava_string);

    bool poista_alkio_alusta();
    bool onko_tyhja() const;

    int listan_pituus();

    string kohdassa(int alkion_numero);

    void tulosta() const;
private:
    struct Listan_alkio {
        string alkio;
        shared_ptr<Listan_alkio> seuraavan_osoite;
    };

    shared_ptr<Listan_alkio> ensimmaisen_osoite_;
    shared_ptr<Listan_alkio> viimeisen_osoite_;
};

#endif // LISTA_HH
