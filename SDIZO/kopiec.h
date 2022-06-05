#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;
#ifndef SDIZO_KOPIEC_H
#define SDIZO_KOPIEC_H

#endif //SDIZO_KOPIEC_H

class kopmain {// struktura i funkcje kopca
private:
    int rozm;
    int *tablica;
public:

    kopmain(string npliku);

    ~kopmain();

    void init(string nazwa);

    void heap(int inde);

    void heapcreate();

    void repairup();

    void repairdown();

    void menu();

    void show();

    void insertp(int co);

    void usun();

    void search();

    void purge();

    boolean testw();

// mierzenie czasu
    long long int read_QPC();

};
