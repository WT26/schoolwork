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
            if((*jarjestaja).onko_aloituspala()){
                //ensimmainen pala on tassa vaiheessa loydetty, kierretaan se ympari
                //oikeinpain ja sijoitetaan alkuun.
                (*jarjestaja).kierra_eka();
                iter_swap(jarjestaja, pala_jono_.begin());
                jarjestettu_lkm++;
                kulmapaloja_valmiina++;
                (*pala_jono_.begin()).tulosta();
                cout<<"ensimmainen pala valmis"<<endl;
            }
            else {
                jarjestaja++;
            }
        }//pala_jono_.at(jarjestettu_lkm - 1).vierekkain((*jarjestaja))
        while ((jarjestettu_lkm >= 1) && (kulmapaloja_valmiina == 1)) {
            for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){
                if (pala_jono_.at(jarjestettu_lkm - 1).vierekkain((*jarjestaja))){
                    if((*jarjestaja).onko_kulmapala()){
                        kulmapaloja_valmiina++;
                        leveys_ = jarjestettu_lkm + 1;
                    }
                    cout<<(*jarjestaja).kryk_<<endl;
                    (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm - 1));
                    cout<<(*jarjestaja).kryk_<<endl;

                    iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                    jarjestettu_lkm++;
                    cout<<"toinen pala valmis"<<endl;
                    (*jarjestaja).tulosta();
                    break;
                }
            }
        }

        while (kulmapaloja_valmiina == 2) {
            int korkeus_selvilla{0};//0=etsitaan alle sopivaa palaa, 1=etsitaan vierekkaisia paloja,
                                    //2=uusi kulmapala loytynyt
            if(korkeus_selvilla == 0){

                for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){

                    if(pala_jono_.at(0).allekkain(*jarjestaja)){

                        if((*jarjestaja).onko_kulmapala()){
                            kulmapaloja_valmiina++;
                            (*jarjestaja).kierra_allekkain(pala_jono_.at(jarjestettu_lkm - leveys_));
                            cout<<"kolme kulmapalaa valmis"<<endl;
                            iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                            jarjestettu_lkm++;
                            korkeus_selvilla = 2;
                            korkeus_ = (jarjestettu_lkm + leveys_ - 1) / leveys_;
                            (*jarjestaja).tulosta();
                            break;
                        }
                        else {
                            iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                            (*jarjestaja).tulosta();
                            jarjestettu_lkm++;
                            korkeus_selvilla = 1;
                            break;
                        }
                    }
                }
            }
            if(korkeus_selvilla == 1){
                for(jarjestaja = pala_jono_.begin() + jarjestettu_lkm;jarjestaja != pala_jono_.end();jarjestaja++){
                    //cout<<pala_jono_.at(jarjestettu_lkm - 1).vasen_laita_<<endl;

                    if (pala_jono_.at(jarjestettu_lkm - 1).vierekkain((*jarjestaja))){
                        if((*jarjestaja).onko_kulmapala()){
                            kulmapaloja_valmiina++;
                            korkeus_selvilla = 2;
                            korkeus_ = (jarjestettu_lkm + leveys_ - 1) / leveys_;
                        }
                        (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm-1));
                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        (*jarjestaja).tulosta();
                        jarjestettu_lkm++;
                        if((*jarjestaja).onko_reunapala()) {
                            korkeus_selvilla = 0;
                        }
                        break;
                    }
                }
            }
        }

        while (kulmapaloja_valmiina == 3) {
            for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){
                if(pala_jono_.at(jarjestettu_lkm - 1).vierekkain(*jarjestaja)){
                    if((*jarjestaja).onko_kulmapala()){
                        cout<<"4kulmapalaa valmis"<<endl;
                        kulmapaloja_valmiina++;
                        (*jarjestaja).kierra_vika();
                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        (*jarjestaja).tulosta();
                        jarjestettu_lkm++;
                        break;
                    }
                    else {
                        cout<<pala_jono_.at(jarjestettu_lkm).kryk_<<endl;
                        (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm - 1));
                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        jarjestettu_lkm++;
                        cout<<"toinen pala valmis"<<endl;
                        (*jarjestaja).tulosta();
                    }
                }
            }
        }
    }
}

void Palapeli::tulosta() const{
    deque<Pala>::iterator tulostaja;
    jarjestaja = pala_jono_.begin();
}


//void Palapeli::kierra() {
//}

//metodit
