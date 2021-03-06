#ifndef LISTAPUNTATORI_H
#define LISTAPUNTATORI_H

#include "lista.h"

template <class T>
class linkedList;

template <class T>
class node{
    friend class linkedList<T>;

private:
    T nvalue;
    node* prec;
    node* next;
};


template <class T>
class linkedList : public linearList<T, node<T>*> {
public:
    typedef typename linearList<T, node<T>*>::valueType valueType;
    typedef typename linearList<T, node<T>*>::position position;

    //costruttori
    linkedList();

    //distruttore
    ~linkedList();

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

    linkedList<T>& operator=(const linkedList<T>&);
    bool operator==(const linkedList<T>&) const;
    bool operator!=(const linkedList<T>&) const;

private:
    node<T>* head;
    int lenght;
};

template <class T>
class orderedLinkedList : public linkedList<T> {
    public:
        typedef typename linkedList<T>::valueType valueType;
        typedef typename linkedList<T>::position position;

        void insertOrdList(valueType);
        void removeOrdList(position);          //si potrebbe eliminare
        bool searchOrdList(valueType);
        void mergeOrdList(orderedLinkedList<T> &ordList, bool duplicati);
    private:
    linkedList<T> listaOrdinata;
};

template <class T>
void orderedLinkedList<T>::insertOrdList(orderedLinkedList<T>::valueType elem) {
    if(linkedList<T>::isEmpty()) {
        linkedList<T>::insList(linkedList<T>::_begin(), elem);
    } else if(!linkedList<T>::isEmpty()) {
        position pos = linkedList<T>::_begin();
        bool check = false;

        while(!linkedList<T>::_end(pos) && check == false) {
            if(elem < linkedList<T>::readList(pos)) {
                linkedList<T>::insList(pos, elem);
                check = true;
            } else {
                pos = linkedList<T>::next(pos);
            }
        }

        if(linkedList<T>::_end(pos)) {
            linkedList<T>::insList(pos, elem);
        }
    }
}

template <class T>
void orderedLinkedList<T>::removeOrdList(orderedLinkedList<T>::position pos) {
    linkedList<T>::delList(pos);
}

template <class T>
bool orderedLinkedList<T>::searchOrdList(orderedLinkedList<T>::valueType elem) {
    position pos = linkedList<T>::_begin();
    bool check = false;

    while(!linkedList<T>::_end(pos) && check == false) {
        if(linkedList<T>::readList(pos) == elem) {
            check = true;
        }

        pos = linkedList<T>::next(pos);
    }

    return check;
}

template <class T>
void orderedLinkedList<T>::mergeOrdList(orderedLinkedList<T> &ordList, bool duplicati) {
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

template <class T>
linkedList<T>::linkedList() {
    head = new node<T>;
    head->next = head;
    head->prec = head;
    lenght = 0;
}

template <class T>
linkedList<T>::~linkedList() {
    while(!isEmpty())
        delList(_begin());
    lenght = 0;
}

template <class T>
void linkedList<T>::createList() {}

template <class T>
bool linkedList<T>::isEmpty() const{
    if(head->next == head)
        return true;
    else
        return false;
}

template <class T>
typename linkedList<T>::valueType linkedList<T>::readList(linkedList<T>::position pos) const{
    if(!_end(pos))
        return pos->nvalue;
}

template <class T>
void linkedList<T>::writeList(linkedList<T>::position pos, linkedList<T>::valueType e) {
    if(!_end(pos)) {
        pos->nvalue = e;
    }
}

template <class T>
typename linkedList<T>::position linkedList<T>::_begin() const {
    return head->next;
}

template <class T>
typename linkedList<T>::position linkedList<T>::_last() const {
    return head->prec;
}

template <class T>
bool linkedList<T>::_end(linkedList<T>::position pos) const{
    if(pos == head)
        return true;
    else
        return false;
}

template <class T>
typename linkedList<T>::position linkedList<T>::next(linkedList<T>::position pos) const {
    return pos->next;
}

template <class T>
typename linkedList<T>::position linkedList<T>::prec(linkedList<T>::position pos) const {
    if(pos != head)
        return pos->prec;
}

template <class T>
void linkedList<T>::insList(linkedList<T>::position pos, linkedList<T>::valueType e) {
    position posSupp = new node<T>;
    posSupp->nvalue = e;

    posSupp->next = pos;
    posSupp->prec = pos->prec;
    pos->prec->next = posSupp;
    pos->prec = posSupp;

    lenght++;
}

template <class T>
void linkedList<T>::delList(linkedList<T>::position pos) {

    if(!isEmpty() && !_end(pos)) {
        pos->prec->next = pos->next;
        pos->next->prec = pos->prec;

        delete pos;

        lenght--;
    }

}

template <class T>
void linkedList<T>::fillList(linkedList<T>::valueType &noc) {
    while(noc > 0) {
        insList(_begin(), noc);
        noc--;
        lenght++;
    }
}

template <class T>
linkedList<T>& linkedList<T>::operator=(const linkedList<T> &l) {
    if(this != &l) {
        lenght = l.listSize();

        head = new node<T>;
        head->next = head;
        head->prec = head;

        if(!l.isEmpty()) {
            position pos = l._last();

            for(int i = 0; i < l.listSize(); i++) {
                auto elem = l.readList(pos);
                insList(_begin(), elem);
                pos = l.prec(pos);
            }
        }
    }

    return *this;
}

template <class T>
bool linkedList<T>::operator==(const linkedList<T> &l) const {
    if(lenght != l.listSize()) {
        return false;
    }

    position p, pl;
    p = _begin();
    pl = l._begin();

    while(!_end(p)) {
        if(p->nvalue != pl->nvalue) {
            return false;
        }

        p = p->next;
        pl = pl->next;
    }
    return true;
}

template <class T>
bool linkedList<T>::operator!=(const linkedList<T> &l) const {
    if(lenght != l.listSize()) {
        return true;
    }

    position p, pl;
    p = _begin();
    pl = l._begin();

    while(!_end(p)) {
        if(p->nvalue != pl->nvalue) {
            return true;
        }

        p = p->next;
        pl = pl->next;
    }
    return false;
}

#endif // LISTAPUNTATORI_H

/* #MAIN#

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

    //liste ordinate con puntatori

    orderedLinkedList<int> lisa;
    orderedLinkedList<int> bart;

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
