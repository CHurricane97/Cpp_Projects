#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "MST.h"
#include "ShortestPath.h"
#include <locale.h>


using namespace std;

int Mainmenu();

int Mainmenu2();

int Mainmenu3();

void Mainmenu4();

int Mainmenu5();

string bplik = "a.txt";

int main() {


    boolean koniec = false;
    while (!koniec) {
        int w1 = Mainmenu();
        int w2 = 0, w3 = 0, w4 = 0;


        switch (w1) {
            case 1://MST
            {
                w2 = Mainmenu2();
                if (w2 == 1) {
                    Mainmenu4();
                    MSTmain m(bplik, false, 25, 1, false);
                    m.menu();
                } else if (w2 > 1 && w2 < 4) {

                    w3 = Mainmenu3();
                    w4 = Mainmenu5();
                    int roz = 25;
                    float den = 0.25;

                    boolean x100 = false;
                    if (w2 == 3) {
                        x100 = true;
                    }
                    switch (w3) {

                        case 1:
                            roz = 20;
                            break;
                        case 2:
                            roz = 40;
                            break;
                        case 3:
                            roz = 60;
                            break;
                        case 4:
                            roz = 80;
                            break;
                        case 5:
                            roz = 100;
                            break;

                    }
                    switch (w4) {

                        case 1:
                            den = 0.25;
                            break;
                        case 2:
                            den = 0.50;
                            break;
                        case 3:
                            den = 0.75;
                            break;
                        case 4:
                            den = 0.99;
                            break;

                    }
                    MSTmain m(bplik, true, roz, den, x100);
                    m.menu();


                }


            }
                break;
            case 2://Shortest Path
            {
                w2 = Mainmenu2();
                if (w2 == 1) {
                    Mainmenu4();
                    SPmain m(bplik, false, 25, 1, false);
                    m.menu();
                } else if (w2 > 1 && w2 < 4) {

                    w3 = Mainmenu3();
                    w4 = Mainmenu5();
                    int roz = 25;
                    float den = 0.25;

                    boolean x100 = false;
                    if (w2 == 3) {
                        x100 = true;
                    }
                    switch (w3) {

                        case 1:
                            roz = 20;
                            break;
                        case 2:
                            roz = 40;
                            break;
                        case 3:
                            roz = 60;
                            break;
                        case 4:
                            roz = 80;
                            break;
                        case 5:
                            roz = 100;
                            break;

                    }
                    switch (w4) {

                        case 1:
                            den = 0.25;
                            break;
                        case 2:
                            den = 0.50;
                            break;
                        case 3:
                            den = 0.75;
                            break;
                        case 4:
                            den = 0.99;
                            break;

                    }
                    SPmain m(bplik, true, roz, den, x100);
                    m.menu();


                }


            }
                break;

            case 0: //koniec
            {
                koniec = true;
            }
                break;
            default:;
        }

    }
//    system("PAUSE");
    return 0;
}


int Mainmenu() { //menu 1
    int w = 0;
    cout << "Co chcesz Zrobic?" << endl << endl;
    cout << "1-Wyznaczanie  minimalnego  drzewa  rozpinajacego" << endl;
    cout << "2-Wyznaczanie najkrotszej sciezki w grafie " << endl;
    cout << "0-Zakoncz program" << endl;
    cin >> w;
    return w;
}

int Mainmenu2() {//menu 2

    int w = 0;
    if (!(w > 0 && w < 4)) {
        cout << "Co chcesz Zrobic?" << endl << endl;
        cout << "1-Przeprowadzic badanie dla grafu z pliku" << endl;
        cout << "2-Przeprowadzic badanie dla losowego grafu " << endl;
        cout << "3-Przeprowadzic badanie seryjne dla 100 losowych grafow " << endl;
        cin >> w;
    }
    return w;
}

int Mainmenu3() {//menu 3
    int w = 0;
    while (!(w > 0 && w < 6)) {

        cout << "Wybierz rozmiar grafu?" << endl << endl;
        cout << "1-20 wierzcholkow" << endl;
        cout << "2-40 wierzcholkow " << endl;
        cout << "3-60 wierzcholkow  " << endl;
        cout << "4-80 wierzcholkow  " << endl;
        cout << "5-100 wierzcholkow  " << endl;
        cin >> w;
        cout << endl;

    }

    return w;
}

void Mainmenu4() {//menu 4
    string w;
    cout << "Podaj nazwe pliku" << endl << endl;
    cin >> w;
    bplik = w;
}

int Mainmenu5() {//menu 5
    int w = 0;
    while (!(w > 0 && w < 5)) {
        cout << "Wybierz gestosc grafu?" << endl << endl;
        cout << "1-25% wierzcholkow" << endl;
        cout << "2-50% wierzcholkow " << endl;
        cout << "3-75% wierzcholkow  " << endl;
        cout << "4-99% wierzcholkow  " << endl;
        cin >> w;
        cout << endl;
    }
    return w;
}

