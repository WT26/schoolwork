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
    pala_jono_{ pala_jono },
    leveys_{},
    korkeus_{}
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
        while ((jarjestettu_lkm >= 1) && (kulmapaloja_valmiina == 1)) {
            for(jarjestaja = pala_jono_.begin() + jarjestettu_lkm;jarjestaja != pala_jono_.end();jarjestaja++){
                if (pala_jono_.at(jarjestettu_lkm - 1).vierekkain((*jarjestaja))){
                    if((*jarjestaja).onko_kulmapala()){
                        kulmapaloja_valmiina++;
                        leveys_ = jarjestettu_lkm + 1;
                    }
                    iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                    jarjestettu_lkm++;
                    cout<<"toinen pala valmis"<<endl;
                    break;
                }
            }
        }

        while (kulmapaloja_valmiina == 2) {
            int korkeus_selvilla{0};//0=etsitaan alle sopivaa palaa, 1=etsitaan vierekkaisia paloja,
                                    //2=uusi kulmapala loytynyt
            if(korkeus_selvilla == 0){
                for(jarjestaja = pala_jono_.begin() + jarjestettu_lkm;jarjestaja != pala_jono_.end();jarjestaja++){
                    if(pala_jono_.at(jarjestettu_lkm - 1).allekkain(*jarjestaja)){
                        if((*jarjestaja).onko_kulmapala()){
                            kulmapaloja_valmiina++;
                            cout<<"3kulmapalaa valmis"<<endl;
                            iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                            jarjestettu_lkm++;
                            korkeus_selvilla = 2;
                            korkeus_ = (jarjestettu_lkm + leveys_ - 1) / leveys_;
                            break;
                        }
                        else {
                            iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                            jarjestettu_lkm++;
                            korkeus_selvilla = 1;
                            break;
                        }
                    }
                }
            }
            if(korkeus_selvilla == 1){
                for(jarjestaja = pala_jono_.begin() + jarjestettu_lkm;jarjestaja != pala_jono_.end();jarjestaja++){
                    if (pala_jono_.at(jarjestettu_lkm - 1).vierekkain((*jarjestaja))){
                        if((*jarjestaja).onko_kulmapala()){
                            kulmapaloja_valmiina++;
                            korkeus_selvilla = 2;
                            jarjestettu_lkm++;
                            korkeus_ = (jarjestettu_lkm + leveys_ - 1) / leveys_;
                        }
                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        jarjestettu_lkm++;
                        korkeus_selvilla = 0;
                        break;
                    }
                }
            }

        }

        while (kulmapaloja_valmiina == 3) {
            for(jarjestaja = pala_jono_.begin() + jarjestettu_lkm;jarjestaja != pala_jono_.end();jarjestaja++){
                cout<<"taalla"<<endl;
                if(pala_jono_.at(jarjestettu_lkm - 1).vierekkain(*jarjestaja)){
                    if((*jarjestaja).onko_kulmapala()){
                        kulmapaloja_valmiina++;
                        cout<<"4kulmapalaa valmis"<<endl;
                    }
                    iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                    jarjestettu_lkm++;
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
