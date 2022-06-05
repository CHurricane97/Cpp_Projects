#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "geneticAlgorithm.h"


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

                Gmain gm(npl, 0, 200,1,0.05);
                gm.geneticAlgorithm();



            }
                break;
            case 2: {
                menu2();


            }
                break;
            case 0: {
                koniec = true;
            }

                break;
            default: {

            }
        }


    }


    return 0;
}

int menu() {
    //menu główne
    int w = -1;
    while (w < 0 || w > 2) {
        cout << "Co chcesz Zrobic?" << endl << endl;
        cout << "1-Badanie metoda za pomoca algorytmu genytycznego" << endl;
        cout << "0-Zakoncz program" << endl;
        cin >> w;
    }

    return w;


}

int menu2() {
    cout << "Podaj nazwe pliku: " << endl;
    cin >> npl;
}

