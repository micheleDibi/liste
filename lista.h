#ifndef LISTA_H
#define LISTA_H

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

template <class T, class P>
class linearList{
public:
    typedef T valueType;
    typedef P position;

    virtual void createList() = 0;
    virtual bool isEmpty()const = 0;
    virtual valueType readList(position) const = 0;
    virtual void writeList(position, valueType) = 0;
    virtual position _begin() const = 0;
    virtual position _last() const = 0;
    virtual bool _end(position) const = 0;
    virtual position next(position) const = 0;
    virtual position prec(position) const = 0;
    virtual void insList(position, valueType) = 0;
    virtual void delList(position) = 0;

    int listSize() const;
    void invertireLista();
    bool palindroma() const;                          //verifica se una lista e' palindroma

    //virtual void clearList();                       //svuota la lista
    //int numElements(position, position);            //calcola il numero di elementi presenti dalla pos x alla posizione y - accertarsi che x > y
    //void exchangeElements(position, position);      //cambia la posizione del elemento in pos x con quello in posizione y - non � necessario che x > y
    //void moveMinAndMax();                           //inserisce il minimo in prima posizione e il minimo in ultima posizione
} ;

template <class T, class P>
int linearList<T, P>::listSize() const{
    position pos = _begin();
    int c = 0;

    while(!_end(pos)) {
        c++;
        pos = next(pos);
    }

    return c;
}

template <class T, class P>
void linearList<T, P>::invertireLista() {
    position head, tail;
    head = _begin();
    tail = _last();

    for (int i = 0; i < (listSize()/2); i++) {
        valueType supportH = readList(head);
        valueType supportT = readList(tail);
        writeList(head, supportT);
        writeList(tail, supportH);

        tail = prec(tail);
        head = next(head);
    }
}

template <class T, class P>
bool linearList<T, P>::palindroma() const {
    if(!isEmpty()) {
        position head = _begin(), tail = _last();

        for(int i = 0; i < listSize(); i++) {
            if(readList(head) != readList(tail)) {
                return false;
            }
        }
    }

    return true;
}

template <class T, class P>
ostream& operator<<(ostream& os, linearList<T, P> &l) {
    typename linearList<T, P>::position pos;
    pos = l._begin();
    cout << "[";
    while(!l._end(pos)) {
        if(pos != l._begin()) {
            cout << ", " << l.readList(pos);
        } else {
            cout << l.readList(pos);
        }
        pos = l.next(pos);
    }
    cout << "]" << endl;
    return os;
}

template <class T, class P, typename N>
void fillList(linearList<T, P> &l, N noc) {
    while(noc > 0) {
        l.insList(l._begin(), noc);
        noc--;
    }
}
#endif // LISTA_H
