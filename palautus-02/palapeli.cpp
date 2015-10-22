#include "palapeli.hh"
#include "pala.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

Palapeli::Palapeli(deque<Pala> pala_jono):
    pala_jono_{ pala_jono }
{
}

void Palapeli::jarjesta() {
    deque<Pala>::iterator jarjestaja;
    jarjestaja = pala_jono_.begin();
    bool jarjestus_valmis = false;
    int kulmapaloja_valmiina{0};
    int jarjestettu_lkm{0};

    while (!jarjestus_valmis){
        if (jarjestettu_lkm == 0){
            if ((*jarjestaja).onko_aloituspala()){
                //ensimmainen pala on tassa vaiheessa loydetty, kierretaan se ympari
                //oikeinpain ja sijoitetaan alkuun.
                (*jarjestaja).kierra_eka();
                iter_swap(jarjestaja, pala_jono_.begin());
                jarjestettu_lkm++;
                kulmapaloja_valmiina++;
                cout<<"ensimmainen pala valmis"<<endl;
            }
            else {
                jarjestaja++;
            }
        }
        while ((jarjestettu_lkm >= 1) && (kulmapaloja_valmiina < 2)) {
            for(jarjestaja = pala_jono_.begin() + 1;jarjestaja != pala_jono_.end();jarjestaja++){
                if (pala_jono_.at(jarjestettu_lkm - 1).vierekkain((*jarjestaja))){
                    if((*jarjestaja).onko_kulmapala()){
                        kulmapaloja_valmiina++;
                    }
                    iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                    jarjestettu_lkm++;
                    cout<<"toinen pala valmis"<<endl;

                    break;
                }
            }
        }
    }
}

void Palapeli::tulosta() const{

}

//void Palapeli::kierra() {
//}

//metodit
