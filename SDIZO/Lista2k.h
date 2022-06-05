#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;
#ifndef SDIZO_LISTA2K_H
#define SDIZO_LISTA2K_H

#endif //SDIZO_LISTA2K_H
struct ellisty { // element listy
    int liczba;
    struct ellisty *next;
    struct ellisty *prev;
};


class listmain {// struktura i funkcje listy
private:
    struct ellisty *head;
    struct ellisty *tail;
    int rozm;
public:

    listmain(string npliku);

    ~listmain();

    ellisty *GetNewel(int x);

    void init(string nazwa);

    void menu();

    void show();

    void insertp(int co);

    void insertk(int co, boolean inic);

    void inserts(int gdz, int co);

    void usun(int pozycja);

    void search();

    boolean testw();

    void purge();


// mierzenie czasu
    long long int read_QPC();



};