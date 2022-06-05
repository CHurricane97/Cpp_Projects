#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "BF.h"
#include "BB.h"

using namespace std;
string npl = "b.txt";

int menu();

int menu2();

int main() {
    boolean koniec = false;
    while (!koniec) {
        int wyb = menu();

        switch (wyb) {

            case 1: {
                menu2();
                BFmain bf(npl, 0);
                bf.bruteforce();

            }
                break;
            case 2: {
                menu2();
                BBmain bb(npl, 0);
                bb.branchandbound();
            }
                break;
            case 0: {
                koniec = true;
            }

                break;
        }


    }


    return 0;
}

int menu() {
    //menu główne
    int w = -1;
    while (w < 0 || w > 2){
        cout << "Co chcesz Zrobic?" << endl << endl;
        cout << "1-Badanie metoda brute force" << endl;
        cout << "2-Badanie metoda branch and bound" << endl;
        cout << "0-Zakoncz program" << endl;
        cin >> w;
    }

    return w;


}

int menu2() {
    cout << "Podaj nazwe pliku: " << endl;
    cin >> npl;
}
