#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "tablica.h"
#include "Lista2k.h"
#include "kopiec.h"
#include "BST.h"

using namespace std;

/*
 * AUTOR: BARTOSZ SULIMA 234310
 */

string nplik[60]; // tablica nazw plików danych
string bpzd; //badany plik z danymi

void wprowadzpliki();

int Mainmenu();

void mtest();

//FUNKCJA MAIN
int main() {
    int w1;
    wprowadzpliki();// wprowadzenie naz plikow


    boolean koniec = false;
    while (!koniec) {
        w1 = Mainmenu();

        if ((w1 > 0) && (w1 < 5)) {
            mtest();
            cout << endl << bpzd << endl;
        }

        switch (w1) {
            case 1://inicjalizacja tabliy
            {
                tabmain t(bpzd);
                t.menu();
            }
                break;
            case 2://inicjalizacja listy
            {
                listmain l(bpzd);
                l.menu();
            }
                break;
            case 3://inicjalizacja kopca
            {
                kopmain k(bpzd);
                k.menu();
            }
                break;
            case 4://inicjalizacja drzewa bst
            {
                bstmain b(bpzd);
                b.menu();
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
    system("PAUSE");
    return 0;
}

void wprowadzpliki() { // wprowadznie tablicy z nazwami plików do testowania
    string a = "dane100k";
    string b = "dane250k";
    string c = "dane500k";
    string d = "dane1000k";
    string e = "dane2000k";
    string f = "datest20liczb";
    string t = ".txt";
    int j = 0;
    for (int i = 0; i < 60; ++i) {
        string tym;
        string z;
        if (i % 10 == 0) { j = 0; }


        if (i < 10) {
            z = a;
        } else if (i < 20) {
            z = b;
        } else if (i < 30) {
            z = c;
        } else if (i < 40) {
            z = d;
        } else if (i < 50) {
            z = e;
        } else if (i < 60) {
            z = f;
        }
        stringstream ss;
        ss << j;
        string s;
        ss >> s;
        tym = z + s + t;
        j++;
        nplik[i] = tym;
    }


}

int Mainmenu() { //menu główne
    int w = 0;
    cout << "Co chcesz Zrobic?" << endl << endl;
    cout << "1-Badanie tablic" << endl;
    cout << "2-Badanie listy dwukierunkowej" << endl;
    cout << "3-Badanie kopca Binarnego" << endl;
    cout << "4-Badanie drzewa BST" << endl;
    cout << "0-Zakoncz program" << endl;
    cin >> w;
    return w;
}

void mtest() { // wybór pliku do testowania
    boolean pentla = true;
    int wybor;


    while (pentla) {
        cout << "Wybiez plik z danymi:" << endl << endl;
        cout << "1-Zestaw testowy" << endl;
        cout << "2-Zestaw wlasny" << endl;
        cin >> wybor;
        switch (wybor) {
            case 1:
            mtestt:
                cout << "Wybiez zestaw testowy:" << endl << endl;
                cout << "(0-9)-Zestawy z 100 tys. liczb" << endl;
                cout << "(10-19)-Zestawy z 250 tys. liczb" << endl;
                cout << "(20-29)-Zestawy z 500 tys. liczb" << endl;
                cout << "(30-39)-Zestawy z 1 mln. liczb" << endl;
                cout << "(40-49)-Zestawy z 2 mln. liczb" << endl;
                cout << "(50-59)-Zestawy z 20 liczbami do sprawdzenia poprawnosci" << endl;
                cin >> wybor;
                if (wybor >= 0 && wybor <= 59) {
                    bpzd = nplik[wybor];
                } else {
                    goto mtestt;
                }
                pentla = false;
                break;
            case 2: {
                cout << "Wpisz nazwe pliku:" << endl;
                string n;
                cin >> n;
                bpzd = n;
                pentla = false;
            }
                break;
            default:;


        }

    }

}










