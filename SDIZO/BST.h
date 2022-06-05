#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

#ifndef SDIZO_BST_H
#define SDIZO_BST_H

#endif //SDIZO_BST_H


struct eldrzewa { //element drzewa

    struct eldrzewa *parentt;
    struct eldrzewa *left;
    struct eldrzewa *right;
    int liczba;
};


class bstmain {// struktura i funkcje drzewa bst
private:
    int rozm;
    eldrzewa *head;
public:

    bstmain(string npliku);
    ~bstmain();

    eldrzewa *GetNewed(int x);

    void init(string nazwa);

    void menu();

    void show(eldrzewa *k);

    void show2(eldrzewa *k);

    void show3(eldrzewa *k);

    void show4(eldrzewa *k);

    eldrzewa *insertp(eldrzewa *head1, int co, boolean inic);

    eldrzewa *min(eldrzewa *drzewo);

    eldrzewa *max(eldrzewa *drzewo);

    void usun();

    void search(int co, eldrzewa *head1);

    void rotateright(eldrzewa *a);

    void rotateleft(eldrzewa *a);

    void makespine();

    void breakspine();

    void balancetree();

    void purge(eldrzewa *korzen) ;

    boolean testw();

// mierzenie czasu
    long long int read_QPC();

};

