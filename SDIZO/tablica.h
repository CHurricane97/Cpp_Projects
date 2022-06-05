#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

#ifndef SDIZO_TABLICA_H
#define SDIZO_TABLICA_H

#endif //SDIZO_TABLICA_H

class tabmain {// struktura i funkcje tablicy

private:
    int rozm;
    int *tablica;
public:


    tabmain(string npliku);

    ~tabmain();

    void init(string nazwa);

    void menu();

    void show();

    void insertp(int pozycja, int co);

    void usun(int pozycja);

    void search();

    boolean testw();

    void purge();

    // mierzenie czasu
    long long int read_QPC() ;

};
