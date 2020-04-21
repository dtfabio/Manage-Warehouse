/*
  The General Manager of a large warehouse needs a program for management of products in stock in its warehouse. Specifically, the program will have to make available the following features:
  1. Inserting a new product. A product is characterized by a code (number of 6 digits), a name, a description, a purchase price (unit), a number of
  units of product present in the warehouse (quantity), and a minimum stock. At first the units of product in the warehouse are zero.
  2. Loading / Unloading of a product. The functionality takes the product code as input, a date, and the units of product (quantity) to be loaded / unloaded,
  displays the name of the product and asks for confirmation of the load. Note: if the quantity is positive it is a load, otherwise it will be a discharge.
  3. View extract loading / unloading. The functionality takes the code of the input
  product and displays: the name of the product and the list of all loading operations e unloading the product.
  4. Display list of products in reserve. View the list of all products in reserve (whose quantity is less than the minimum stock) with an estimate of the expenditure to be faced
  to reload the entire warehouse. To estimate spending: to. calculate the expense to reload each product in reserve, multiplying the price of acquired per unit for the minimum number of units to report the quantity of product in warehouse equal to 110% of the minimum stock.
  b. add up all the amounts to top up each product in reserve.
*/

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
* File:   ManageWarehouse.c
* Author: dtfabio96
*
* Created on 26 gennaio 2016, 10.33
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNG_CODICE 6
#define LUNG_NOME 50
#define LUNG_DESCRIZIONE 100
#define LUNG_DATA 10
#define DIM_MASSIMA 100
#define dim_logica 50

#define Ok 0
#define Error -1

#define INSERIMENTO_PRODOTTO 1
#define CARICO_SCARICO 2
#define ESTRATTO_CS 3
#define PRODOTTI_IN_RISERVA 4
#define ESCI 0

typedef struct{
    char tipo;
    char data[LUNG_DATA+1];
    int quantita_cs;
}carico_scarico;

typedef struct{
    carico_scarico lista_cs[DIM_MASSIMA];
    int dimensione;
}operazioni_cs;

typedef struct{
    char codice[LUNG_CODICE+1];
    char nome[LUNG_NOME+1];
    char descrizione[LUNG_DESCRIZIONE+1];
    float prezzo;
    int quantita;
    int giacenza_minima;
    operazioni_cs lista_operazioni_cs;
}prodotto;

typedef struct{
    int dimensione;
    prodotto prodotti[DIM_MASSIMA];
}lista_prodotti;

typedef struct{
    char _codici[LUNG_CODICE+1];
}codici;

typedef struct {
    int dimensione;
    codici codice[DIM_MASSIMA];
}lista_codici;

//Creazione prodotto
int crea_prodotto(prodotto p, lista_prodotti *l){
    if(l->dimensione<DIM_MASSIMA){
    l->prodotti[l->dimensione]=p;
    l->dimensione++;
    return Ok;
    }
    return Error;
}


//Quantità pari a zero
void init_quantita(prodotto *_prodotti){
    _prodotti->quantita=0;
}


//Fuonzione di ricerca
int ricerca(char codice[], lista_prodotti l){
    int i=0;

    while((i<l.dimensione)&&(strcmp(l.prodotti[i].codice,codice)!=0)){
        i++;
    }
    if(i<l.dimensione){
        return i;
    }
    else
        return Error;
}



//Carico e scarico
int _carico_scarico(int codice, carico_scarico cs, lista_prodotti *l){

    int indice2;
    indice2=l->prodotti[codice].lista_operazioni_cs.dimensione;

    if(indice2>=DIM_MASSIMA){
        return Error;
    }
        l->prodotti[codice].lista_operazioni_cs.lista_cs[indice2]=cs;
        l->prodotti[codice].lista_operazioni_cs.dimensione++;
        if(l->prodotti[codice].lista_operazioni_cs.lista_cs[indice2].quantita_cs>1){
         l->prodotti[codice].quantita=l->prodotti[codice].quantita+l->prodotti[codice].lista_operazioni_cs.lista_cs[indice2].quantita_cs;
        }
        else{
         l->prodotti[codice].quantita-=l->prodotti[codice].quantita-l->prodotti[codice].lista_operazioni_cs.lista_cs[indice2].quantita_cs;
        }
    return Ok;
}



//Visualizzazione prodotti in riserva
int visualizza_prodotti_riserva(lista_prodotti l, lista_codici *lc){
    int i;
    for(i=0;i<l.dimensione;i++){
        if (l.prodotti[i].quantita<l.prodotti[i].giacenza_minima){
            strcpy(lc->codice,l.prodotti[i].codice);
            lc->dimensione++;
        }
    }

    if(lc->dimensione==0){
        return Error;
    }
    else
        return Ok;
}


//Stima spesa

float stima_spesa(lista_prodotti lp, int i){
    float spesa;
    int unmin;
    unmin=lp.prodotti[i].giacenza_minima*110/100;
    spesa=lp.prodotti[i].prezzo*unmin;

    return spesa;
}





int main(int argc, char** argv) {
    int scelta;
    int esito;
    char _codice[LUNG_CODICE+1];
    char scelta2;
    int i;
    int index=0;
    int index2=0;
    float somma=0;
    lista_codici _lc;
    float spesa;


    lista_prodotti _lp;
    prodotto _nuovoprod;
    carico_scarico _cs;

    prodotto prodotti;
    init_quantita(&prodotti); //Chiamata al puntatore

    printf("Magazzino.\n\n\n");

    do{
        printf("\n\n");
        printf("Menu': \n");
        printf("1. Inserimento di un nuovo prodotto\n");
        printf("2. Carico/Scarico di un prodotto\n");
        printf("3. Visualizzazione estratto carico/scarico\n");
        printf("4. Visualizzazione lista prodotti in riserva\n");
        printf("0. Esci\n");
        scanf("%d", &scelta);

        switch(scelta){
            case INSERIMENTO_PRODOTTO:
                printf("Inserisci un nuovo prodotto\n");
                printf("Codice: ");
                scanf("%s", _nuovoprod.codice);
                printf("Nome: ");
                scanf("%s", _nuovoprod.nome);
                printf("Descrizione: ");
                scanf("%s", _nuovoprod.descrizione);
                printf("Prezzo unitario: ");
                scanf("%f", &_nuovoprod.prezzo);
                printf("Quantita': ");
                scanf("%d", &_nuovoprod.quantita);
                printf("Giacenza minima: ");
                scanf("%d", &_nuovoprod.giacenza_minima);

                esito=crea_prodotto(_nuovoprod, &_lp); //Salva il risultato della funzione in esito
                if (esito!=Error){
                    printf("Inserimento riuscito!\n");
                }
                else
                    printf("Archivio pieno!\n");


                break;

            case CARICO_SCARICO:


                printf("Inserire codice da ricercare:\n");
                scanf("%s", _codice);

                esito=ricerca(_codice, _lp);
                if(esito==Error){
                printf("Elemento non trovato!\n");
                }
                else{
                printf("Inserire data:\n");
                scanf("%s", _cs.data);
                printf("Inserire quantita':\n");
                scanf("%s", _cs.quantita_cs);
                printf("Inserire tipo(C o S):\n");
                scanf("%s", _cs.tipo);

                printf("Il nome prodotto e': %s", _lp.prodotti[esito].nome);
                printf("Confermare l'operazione?(S o N)\n");
                scanf("%c", scelta2);

                if(scelta2=='S'){
                   esito=_carico_scarico(esito, _cs, &_lp);
                   if(esito==Ok){
                       printf("Operazione riuscita!\n");
                    }
                   else{
                       printf("Archivio pieno!\n");
                    }
                }
                else
                    printf("Operazione annullata!\n");
                }
                break;

            case ESTRATTO_CS:


                printf("Inserire codice da ricercare:\n");
                scanf("%s", _codice);

                esito=ricerca(_codice, _lp);
                if(esito==Error){
                printf("Elemento non trovato!\n");
                }

                printf("Nome prodotto: %s", _lp.prodotti[esito].nome);
                printf("Tipo:\tData:\tQuantita:\tIn magazzino:\n");

                for(i=0;i<_lp.prodotti[esito].lista_operazioni_cs.dimensione;i++){

                    printf("%c\t%s\t%d\t%d", _lp.prodotti[esito].lista_operazioni_cs.lista_cs[i].tipo, _lp.prodotti[esito].lista_operazioni_cs.lista_cs[i].data, _lp.prodotti[esito].lista_operazioni_cs.lista_cs[i].quantita_cs, _lp.prodotti[esito].quantita);
                }


                break;

            case PRODOTTI_IN_RISERVA:

                index=0;
                index2=0;
                somma=0ì

                esito=visualizza_prodotti_riserva(_lp, &_lc);

                if(esito==Error){
                    printf("Nessun prodotto in riserva!\n");
                }
                else
                    while(index<_lc.dimensione){
                        while(index2<_lp.dimensione){
                            if(_lc.codice[index]._codici==_lp.prodotti[index2].codice){
                                printf("Nome prodotto: %s", _lp.prodotti[index2].nome);

                                spesa=stima_spesa(_lp, index2);

                                somma+=spesa;
                            }
                            index2++;
                        }
                        index++;
                    }

                printf("La spesa complessiva e': %0.2f", somma);


                break;

            case ESCI:
                printf("Arrivederci!!\n");
                break;

            default:
                printf("Scelta non valida!\n");

        }
    }while(scelta!=0);



   return 0;
}
