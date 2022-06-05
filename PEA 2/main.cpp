#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "TS.h"
#include "SA.h"

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
                TSmain ts(npl, 0);

                ts.poczrozw();

                ts.tabusearch();


            }
                break;
            case 2: {
                menu2();
                SAmain sa(npl,0);
                sa.poczrozw();
                sa.simulatedannealing();




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
        cout << "1-Badanie metoda Tabu Search" << endl;
        cout << "2-Badanie metoda Symulated Anealing" << endl;
        cout << "0-Zakoncz program" << endl;
        cin >> w;
    }

    return w;


}

int menu2() {
    cout << "Podaj nazwe pliku: " << endl;
    cin >> npl;
}

