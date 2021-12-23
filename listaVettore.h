#ifndef LISTAVETTORE_H
#define LISTAVETTORE_H
#include "lista.h"

#define MAX 10

template <class T>
class vectorList : public linearList<T, int> {
public:
    typedef typename linearList<T, int>::valueType valueType;
    typedef typename linearList<T, int>::position position;

    //costruttori
    vectorList();
    vectorList(int);

    //distruttore
    ~vectorList();

    //metodi
    void createList();
    bool isEmpty() const;
    valueType readList(position) const;
    void writeList(position, valueType);
    position _begin() const;
    position _last() const;
    bool _end(position) const;
    position next(position) const;
    position prec(position) const;
    void insList(position, valueType);
    void delList(position);
    void fillList(valueType&);

    vectorList<T>& operator=(const vectorList<T> &);
    bool operator==(const vectorList<T> &l);
    bool operator!=(const vectorList<T> &l);

private:
    valueType *elements;
    int lenght;
    int dim;

};

template <class T>
class orderedVectorList : public vectorList<T> {
    public:
        typedef typename vectorList<T>::valueType valueType;
        typedef typename vectorList<T>::position position;

        void insertOrdList(valueType);
        void removeOrdList(position);          //si potrebbe eliminare
        bool searchOrdList(valueType);
        void mergeOrdList(orderedVectorList<T> &ordList, bool duplicati);
    private:
    vectorList<T> listaOrdinata;
};

template <class T>
void orderedVectorList<T>::insertOrdList(orderedVectorList<T>::valueType elem) {
    if(vectorList<T>::isEmpty()) {
        vectorList<T>::insList(vectorList<T>::_begin(), elem);
    } else if(!vectorList<T>::isEmpty()) {
        position pos = vectorList<T>::_begin();
        bool check = false;

        while(!vectorList<T>::_end(pos) && check == false) {
            if(elem < vectorList<T>::readList(pos)) {
                vectorList<T>::insList(pos, elem);
                check = true;
            } else {
                pos = vectorList<T>::next(pos);
            }
        }

        if(vectorList<T>::_end(pos)) {
            vectorList<T>::insList(pos, elem);
        }
    }
}

template <class T>
void orderedVectorList<T>::removeOrdList(orderedVectorList<T>::position pos) {
    vectorList<T>::delList(pos);
}

template <class T>
bool orderedVectorList<T>::searchOrdList(orderedVectorList<T>::valueType elem) {
    position pos = vectorList<T>::_begin();
    bool check = false;

    while(!vectorList<T>::_end(pos) && check == false) {
        if(vectorList<T>::readList(pos) == elem) {
            check = true;
        }

        pos = vectorList<T>::next(pos);
    }

    return check;
}

template <class T>
void orderedVectorList<T>::mergeOrdList(orderedVectorList<T> &ordList, bool duplicati) {
    position pos = ordList._begin();

    while(!ordList._end(pos)) {
        if(searchOrdList(ordList.readList(pos))) {
            if(duplicati == true) {
                insertOrdList(ordList.readList(pos));
            }
        } else {
            insertOrdList(ordList.readList(pos));
        }

        pos = ordList.next(pos);
    }
}

//operazione di copia
template <class T>
vectorList<T>& vectorList<T>::operator=(const vectorList<T> &l) {
    if(this != &l) {
        dim = l.dim;
        lenght = l.lenght;
        delete this -> elements;
        this -> elements = new T[dim];
        for (int i = 0; i < dim; i++)
            elements[i] = l.elements[i];
    }

    return *this;
}

//operazione di confronto
template <class T>
bool vectorList<T>::operator==(const vectorList<T> &l) {
    if(this->lenght != l.lenght) {
        return false;
    }
    for (int i = 0; i < dim; i++) {
        if(elements[i] != l.elements[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool vectorList<T>::operator!=(const vectorList<T> &l) {
    if(this->lenght != l.lenght) {
        return true;
    }

    for (int i = 0; i < dim; i++) {
        if(elements[i] != l.elements[i]) {
            return true;
        }
    }
    return false;
}

//realizzazione costruttori
template <class T>
vectorList<T>::vectorList() {
    dim = MAX;
    this->createList();
}

template <class T>
vectorList<T>::vectorList(int dimension) {
    dim = dimension;
    this->createList();
}

template <class T>
vectorList<T>::~vectorList() {
    delete[] elements;
}

//realizzazione metodi
template <class T>
void vectorList<T>::createList() {
    elements = new T[dim];
    lenght = 0;
}

template <class T>
bool vectorList<T>::isEmpty() const{
    if(lenght == 0) {
        return true;
    } else return false;
}

template <class T>
typename vectorList<T>::valueType vectorList<T>::readList(vectorList<T>::position pos) const{
    if((pos > 0) && (pos < lenght+1)) {
        return elements[pos - 1];
    }
}

template <class T>
void vectorList<T>::writeList(vectorList<T>::position pos, vectorList<T>::valueType e) {
    if((pos > 0) && (pos < lenght+1)) {
        elements[pos - 1] = e;
    }
}

template <class T>
typename vectorList<T>::position vectorList<T>::_begin() const{
    return 1;
}

template <class T>
typename vectorList<T>::position vectorList<T>::_last() const {
    return lenght;
}

template <class T>
bool vectorList<T>::_end(vectorList<T>::position pos) const{
    if ((pos > 0) && (pos <= lenght + 1)) {
        if(pos == lenght + 1)
            return true;
        else
            return false;
    } else return false;
}

template <class T>
typename vectorList<T>::position vectorList<T>::next(vectorList<T>::position pos) const{
    if((pos > 0) && (pos < lenght + 1))
        return pos + 1;
    else return pos;
}

template <class T>
typename vectorList<T>::position vectorList<T>::prec(vectorList<T>::position pos) const{
    if((pos > 1) && (pos < lenght + 1))
        return (pos - 1);
    else return pos;
}

template <class T>
void vectorList<T>::insList(vectorList<T>::position pos, vectorList<T>::valueType e) {
    if((pos > 0) && (pos <= lenght + 1)) {
        for (int i = lenght; i >= pos; i--) {
            elements[i] = elements[i - 1];
        }
        elements[pos - 1] = e;
        lenght++;
    }
}

template <class T>
void vectorList<T>::delList(vectorList<T>::position pos) {
    if((pos > 0) && (pos < lenght+1)) {
        for (int i = pos-1; i < lenght-1; i++) {
            elements[i] = elements[i + 1];
        }
        lenght = lenght - 1;
    }
}


template <class T>
void vectorList<T>::fillList(vectorList<T>::valueType &noc) {
    while(noc > 0) {
        insList(_begin(), noc);
        noc--;
        lenght++;
    }
}

#endif // LISTAVETTORE_H

/* #MAIN#
    int number = 1414;
    vectorList<int> listOne;                                                                //iniziliazzazione lista con costruttore di default
    fillList(listOne, 10);                                                                  //inserimento di valori 1-10 nella lista

    vectorList<int>::position pos;
    pos = listOne.next(listOne.next(listOne._begin()));                                     //recupero posizione 3 della lista, partendo dall'inizio della lista e andando due volte avanti
    listOne.writeList(pos, number);                                                         //sovrascrittura dell'elemento in posizione 3 con 'number'

    pos = listOne.prec(pos);                                                                //torno indietro di una posizione
    cout << "A-valore presente in posizione 2: " << listOne.readList(pos) << endl;

    listOne.delList(listOne._begin());                                                      //eliminazione del primo elemento

    vectorList<int> listTwo(20);                                                            //inizializzazione lista con costruttore di default che imposta la dimensione della lista, in questo caso '20'
    fillList(listTwo, 20);                                                                  //inserimento di valori 1-20 nella lista

    listTwo.invertireLista();                                                               //invertire l'ordine delle posizioni della lista

    if(listOne != listTwo) {                                                                //controllo che le due liste siano differenti
        cout << "E-le due liste sono differenti" << endl;
    } else {
        cout << "E-le due liste sono uguali" << endl;
    }

    if(!(listOne.isEmpty()) && !(listTwo.isEmpty())) {                                      //controllo che la lista non sia vuota
        cout << "B-lista uno completa:" << listOne;
        cout << "B-lista due completa:" << listTwo;

        listTwo = listOne;                                                                  //utilizzo del costruttore di copia per copiare 'listOne' in 'listTwo'

        if(listOne == listTwo) {                                                            //utilizzo del costruttore di confronto per le due liste
            cout << "le due liste sono uguali" << endl;
            cout << "C-lista uno completa:" << listOne;
            cout << "C-lista due completa:" << listTwo;
        } else cout << "le due liste sono diverse" << endl;
    }
    else cout << "le due liste sono vuote" << endl;

    //liste vettoriali ordinate

    orderedVectorList<int> lisa;
    orderedVectorList<int> bart;

    lisa.insertOrdList(15);
    lisa.insertOrdList(21);
    lisa.insertOrdList(17);
    lisa.insertOrdList(14);

    bart.insertOrdList(9);
    bart.insertOrdList(51);
    bart.insertOrdList(21);
    bart.insertOrdList(0);

    lisa.delList(lisa._begin());

    cout << lisa << endl;
    cout << bart << endl;

    lisa.mergeOrdList(bart, true);

    cout << lisa << endl;

    int x = 15;
    if(lisa.searchOrdList(x)) {
        cout << "il valore e' presente" << endl;
    } else cout << "il valore NON e' presente" << endl;
*/
