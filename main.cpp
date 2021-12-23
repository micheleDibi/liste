#include <iostream>
#include "listaVettore.h"
#include "listaPuntatori.h"

using namespace std;

int main()
{
    int number = 1414;
    linkedList<int> listOne;                                                                //iniziliazzazione lista con costruttore di default
    fillList(listOne, 10);                                                                  //inserimento di valori 1-10 nella lista

    linkedList<int>::position pos;
    pos = listOne.next(listOne.next(listOne._begin()));                                     //recupero posizione 3 della lista, partendo dall'inizio della lista e andando due volte avanti
    listOne.writeList(pos, number);                                                         //sovrascrittura dell'elemento in posizione 3 con 'number'

    pos = listOne.prec(pos);                                                                //torno indietro di una posizione
    cout << "A-valore presente in posizione 2: " << listOne.readList(pos) << endl;

    pos = listOne._last();                                                                  //recupero ultima posizione
    cout << "A-valore presente in ultima posizione: " << listOne.readList(pos) << endl;

    listOne.delList(listOne._begin());                                                      //eliminazione del primo elemento

    linkedList<int> listTwo;                                                                //inizializzazione lista con costruttore di default
    fillList(listTwo, 20);                                                                  //inserimento di valori 1-20 nella lista

    listTwo.invertireLista();                                                               //inverte l'ordine delle posizioni dei valori presenti nella lista

    if(listOne != listTwo) {                                                                //controllo della differenza tra le due liste
        cout << "E-le due liste sono differenti" << endl;
    } else {
        cout << "E-le due liste sono uguali" << endl;
    }

    if(!(listOne.isEmpty()) && !(listTwo.isEmpty())) {                                      //controllo che la lista non sia vuota
        cout << "B-lista uno completa:" << listOne;
        cout << "B-lista due completa:" << listTwo;

        listTwo = listOne;                                                                  //utilizzo del costruttore di copia per copiare 'listOne' in 'listTwo'
        cout << "D-copia effettuata!" << endl;

        if(listOne == listTwo) {                                                            //utilizzo del costruttore di confronto per le due liste
            cout << "le due liste sono uguali" << endl;
            cout << "C-lista uno completa:" << listOne;
            cout << "C-lista due completa:" << listTwo;
        } else cout << "le due liste sono diverse" << endl;
    }
    else cout << "le due liste sono vuote" << endl;

    return 0;
}
