#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

#ifndef PEA_BF_H
#define PEA_BF_H

#endif //PEA_BF_H


class BFmain {
private:
    int lmiast;
    int mstart;
    int **macierz;
    int hamilton;
public:

    BFmain(string nazwap, int ms);

    ~BFmain();


    bool file_read_line(ifstream &file, int tab[], int size);

    void wczytajzpliku(string n);

    void bruteforce();

    void purge();

    long long int read_QPC();

};