#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

#ifndef SDIZO_2_SHORTESTPATH_H
#define SDIZO_2_SHORTESTPATH_H

#include "Structures.h"


class SPmain {
private:
    int lwierzch;
    int lkrawedzi;
    int wierzchp;
    int wierzchk;
    float density;
    boolean sto;
    int **macierz;
    ellisty **listas;
public:

    SPmain(string nazwap, boolean los, int lw, float dens, boolean series);

    ~SPmain();

    int lkraw(int lwi, float densi);

    void loswpwk(int lwi);

    void generategraff(int lwi, float densi);

    bool file_read_line(ifstream &file, int tab[], int size);

    void wczytajzpliku(string n);

    void show1();

    void show2();

    long long int dijkstramac();

    long long int dijkstralist();

    long long int belmanfmac();

    long long int belmanflist();

    void menu();

    long long int read_QPC();

    void purge();


};
#endif //SDIZO_2_SHORTESTPATH_H