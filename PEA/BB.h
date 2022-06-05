#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

#ifndef PEA_BB_H
#define PEA_BB_H

#endif //PEA_BB_H
class BBmain {
private:
    int fst;
    boolean first;
    int lmiast;
    int mstart;
    int **macierz;
    int hamilton;
    bool *visited;
    int finalres;
    int *drogaost;
public:

    BBmain(string nazwap, int ms);

    ~BBmain();



    bool file_read_line(ifstream &file, int tab[], int size);

    void wczytajzpliku(string n);

    void branchandbound();

    int pmin(int i);

    int smin(int i);

    void frec(int cbound, int cweight, int level, int cpath[]);

    void purge();

    long long int read_QPC();

};