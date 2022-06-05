#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "BST.h"

using namespace std;




//funkcje drzewa bst

eldrzewa *bstmain::GetNewed(int x) {

    eldrzewa *newNode = new eldrzewa();
    newNode->liczba = x;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parentt = NULL;
    return newNode;
}


void bstmain::init(string nazwa) {//inicjalizacja tablicy poprzez wczytanie z pliku

    if (head != NULL) {
        purge(head);
    }

    ifstream file(nazwa.c_str());
    int val;
    head = NULL;
    if (file.is_open()) {
        file >> rozm;
        if (rozm <= 0) {
            cout << "blad wczytania" << endl;
            exit(22);
        }
        if (file.fail()) {
            cout << "File error - READ SIZE" << endl;
            exit(20);
        } else {
            for (int i = 0; i < rozm; i++) {
                file >> val;
                if (file.fail()) {
                    cout << "File error - READ DATA" << endl;
                    exit(20);
                    break;
                } else {
                    head = insertp(head, val, true);
                }
            }
        }
        file.close();
    } else {
        cout << "File error - OPEN" << endl;
        exit(20);
    }


    balancetree();// balansuj drzewo


}

void bstmain::menu() {
    //menu
    int wyb = 0;
    int li, gdz;
    boolean koniec = false;
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    while (!koniec) {
        boolean test = testw();
        cout << "Co chcesz Zrobic?" << endl << endl;
        cout << "1-Wyszukaj liczbe" << endl;
        cout << "2-Wprowadz liczbe" << endl;
        cout << "3-Usun liczbe" << endl;
        cout << "4-Balansowanie drzewa" << endl;
        cout << "5-Wyswietl dane" << endl;
        cout << "6-Wroc do MainMenu" << endl;
        cin >> wyb;
        switch (wyb) {
            case 1:

                cout << endl << "Podaj szukana liczbe:" << endl;
                cin >> li;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                start = read_QPC();

                search(li, head);

                elapsed = read_QPC() - start;
                cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
                break;
            case 2:
                cout << endl << "Jaka liczbe chcesz wstawic?" << endl;
                cin >> li;

                start = read_QPC();

                head=insertp(head, li, false);
                elapsed = read_QPC() - start;
                cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
                if (test) {
                    cout << endl << "Drzewo Inorder:" << endl;
                    show(head);
                    cout << endl;
                    cout << endl << "Drzewo Preorder:";
                    show2(head);
                    cout << endl;
                    cout << endl << "Drzewo Postorder:" << endl;
                    show3(head);
                    cout << endl;
                    cout << endl << "Pierwsze trzy poziomy drzewa:" << endl;
                    show4(head);
                }
                break;
            case 3:
                usun();
                    if (test) {
                        cout << endl << "Drzewo Inorder:" << endl;
                        show(head);
                        cout << endl;
                        cout << endl << "Drzewo Preorder:" << endl;
                        show2(head);
                        cout << endl;
                        cout << endl << "Drzewo Postorder:" << endl;
                        show3(head);
                        cout << endl;
                        cout << endl << "Pierwsze trzy poziomy drzewa:" << endl;
                        show4(head);
                    }

                break;
            case 4:
                balancetree();
                if (test) {
                    cout << endl << "Drzewo Inorder:" << endl;
                    show(head);
                    cout << endl;
                    cout << endl << "Drzewo Preorder:" << endl;
                    show2(head);
                    cout << endl;
                    cout << endl << "Drzewo Postorder:" << endl;
                    show3(head);
                    cout << endl;
                    cout << endl << "Pierwsze trzy poziomy drzewa:" << endl;
                    show4(head);
                }
                break;
            case 5:
                if (test) {
                    cout << endl << "Drzewo Inorder:" << endl;
                    show(head);
                    cout << endl;
                    cout << endl << "Drzewo Preorder:" << endl;
                    show2(head);
                    cout << endl;
                    cout << endl << "Drzewo Postorder:" << endl;
                    show3(head);
                    cout << endl;
                    cout << endl << "Pierwsze trzy poziomy drzewa:" << endl;
                    show4(head);
                }
                break;
            case 6:
                koniec = true;

                break;
            default:
                break;

        }
    }
}

void bstmain::search(int co, eldrzewa *head1) {

//wyszukiwanie elementu
    if (head1 == NULL) {
        cout << endl << "Nie znaleziono liczby" << endl;
    } else if (head1->liczba == co) {
        cout << endl << "Znaleziono liczbe" << endl;
    } else if (co <= head1->liczba) {
        search(co, head1->left);
    } else {
        search(co, head1->right);
    }

}

eldrzewa *bstmain::insertp(eldrzewa *head1, int co, boolean inic) {
// wsadzanie elementu
eldrzewa *trtr=head;
    if (head1 == NULL) {
        head1 = GetNewed(co);
        if (!inic) { rozm++; }
    } else if (co < head1->liczba) {
        head1->left = insertp(head1->left, co, inic);
        head1->left->parentt = head1;
    } else {
        head1->right = insertp(head1->right, co, inic);
        head1->right->parentt = head1;
    }
    return head1;
}

eldrzewa *bstmain::min(eldrzewa *drzewo) {
    //funkcja do następnika
    eldrzewa *t = head;
    if (drzewo->left == NULL) {
        return drzewo;
    }

    while (drzewo->left != NULL) {
        drzewo = drzewo->left;
    }
    return drzewo;
}

eldrzewa *bstmain::max(eldrzewa *drzewo) {
    // funkcja do poprzednika
    eldrzewa *t = head;
    if (drzewo->right == NULL) {
        return drzewo;
    }

    while (drzewo->right != NULL) {
        drzewo = drzewo->right;
    }
    return drzewo;
}

void bstmain::usun() {
    //usuwanie elementu

    if (rozm<=0){
        cout << endl << "Drzewo puste" << endl;
        return;
    }

    int li;
    cout << endl << "Jaka liczbe chcesz usunac?" << endl;
    cin >> li;
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();
    eldrzewa *t = head;
    eldrzewa *temp1;
    boolean dobrze = true;
    boolean wieksze = true;

    if (t != NULL) {

        while ((t->liczba != li)) {

            if (t->liczba < li) {
                t = t->right;
            } else if (t->liczba > li) {
                t = t->left;
            }
            if (t == NULL) {
                break;
            }
        }
    }


    if (t == NULL) {
        cout << endl << "Brak liczby w drzewie" << endl;
        elapsed = read_QPC() - start;
        cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
        cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
        cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
        return;
    }


    if ((t->right != NULL)) {//następnik
        temp1 = min(t->right);
        boolean wieksze = true;
    } else if ((t->left != NULL)) {//poprzednik
        temp1 = max(t->left);
        wieksze = false;
    } else if ((t->left == NULL) && (t->right == NULL)) {

        if (t->parentt != NULL) {//jesli nie korzen
            if (t->parentt->left == t) {
                t->parentt->left = NULL;
            }
            if (t->parentt->right == t) {
                t->parentt->right = NULL;
            }
        }
        if (t == head) {
            head = NULL;
            delete t;
        } else {
            delete t;
        }
        rozm--;
        elapsed = read_QPC() - start;
        cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
        cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
        cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
        dobrze = false;
    }


    if (dobrze) {
        if (wieksze) {

            t->liczba = temp1->liczba;
            if (temp1->parentt != t) {
                temp1->parentt->left = temp1->right;
                if (temp1->parentt->left != NULL) {
                    temp1->parentt->left->parentt = temp1->parentt;
                }
            } else {
                temp1->parentt->right = temp1->right;
                if (temp1->parentt->right != NULL) {
                    temp1->parentt->right->parentt = temp1->parentt;
                }
            }
            delete temp1;


        } else if (!wieksze) {

            t->liczba = temp1->liczba;
            if (temp1->parentt != t) {
                temp1->parentt->right = temp1->left;
                if (temp1->parentt->right != NULL) {
                    temp1->parentt->right->parentt = temp1->parentt;
                }
            } else {
                temp1->parentt->left = temp1->left;
                if (temp1->parentt->left != NULL) {
                    temp1->parentt->left->parentt = temp1->parentt;
                }
            }
            delete temp1;

        }
        rozm--;
        elapsed = read_QPC() - start;
        cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
        cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
        cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;

    }


}

void bstmain::show(eldrzewa *k) {
// wyświetlanie drzewa inorder
    if (k == NULL) return;

    show(k->left);
    if (k == head) { cout << endl << "Korzen: "; }
    cout << k->liczba << " ";
    if (k == head) { cout << endl; }
    show(k->right);
}

void bstmain::show2(eldrzewa *k) {
// wyświetlanie drzewa preorder
    if (k == NULL) return;


    if (k == head) { cout << endl << "Korzen: "; }
    cout << k->liczba << " ";
    if (k == head) { cout << endl; }
    show(k->left);
    show(k->right);
}

void bstmain::show3(eldrzewa *k) {
// wyświetlanie drzewa postorder
    if (k == NULL) return;

    show(k->left);
    show(k->right);
    if (k == head) { cout << endl << "Korzen: "; }
    cout << k->liczba << " ";
    if (k == head) { cout << endl; }
}

void bstmain::show4(eldrzewa *k) {//pierwsze trzy poziomy drzewa
    if (head != NULL) {

        cout << endl << "Korzen:" << head->liczba << endl;

        if (head->left != NULL) {
            cout << "Lewy syn:" << head->left->liczba << endl;

            if (head->left->left != NULL) {
                cout << "Mniejszy lewy wnuk:" << head->left->left->liczba << endl;

            } else {
                cout << "Mniejszy lewy wnuk: EMPTY " << endl;
            }

            if (head->left->right != NULL) {
                cout << "Wiekszy lewy wnuk:" << head->left->right->liczba << endl;

            } else {
                cout << "Wiekszy lewy wnuk: EMPTY " << endl;
            }

        } else {
            cout << "Lewy syn: EMPTY " << endl;
        }

        if (head->right != NULL) {
            cout << "Prawy syn:" << head->right->liczba << endl;

            if (head->right->left != NULL) {
                cout << "Mniejszy prawy wnuk:" << head->right->left->liczba << endl;

            } else {
                cout << "Mniejszy prawy wnuk: EMPTY " << endl;
            }

            if (head->right->right != NULL) {
                cout << "Wiekszy prawy wnuk:" << head->right->right->liczba << endl;

            } else {
                cout << "Wiekszy prawy wnuk: EMPTY " << endl;
            }

        } else {
            cout << "Prawy syn: EMPTY " << endl;
        }

    } else {
        cout << endl << "Puste drzewo" << endl;


    }
}


void bstmain::rotateright(eldrzewa *a) {
//funkcja obrotu w prawo
    if (a->left == NULL) { return; }
    eldrzewa *b = a->left;  //znalezienie elementu z którym będzie zamiana

    a->left = b->right;   //przypisanie lewemu wskaźnikowi elementu a wskaźnika prawego b
    if (a->left != NULL) {
        a->left->parentt = a;
    }
    b->parentt = a->parentt; // przypisanie elementowi b rodzica a
    if (b->parentt != NULL) {
        b->parentt->right = b;
    }
    a->parentt = b;  //przypisanie b jako rodzica a
    b->right = a;   //przypisanie a prawemu wskaźnikowi elementu b



}

void bstmain::rotateleft(eldrzewa *a) {
//funkcja obrotu w lewo
    if (a->right == NULL) { return; }
    eldrzewa *b = a->right;  //znalezienie elementu z którym będzie zamiana
    a->right = b->left;   //przypisanie prawemu wskaźnikowi elementu a wskaźnika lewego b
    if (a->right != NULL) {
        a->right->parentt = a;
    }
    b->parentt = a->parentt; // przypisanie elementowi b rodzica a
    if (b->parentt != NULL) {
        b->parentt->right = b;
    }
    a->parentt = b;  //przypisanie b jako rodzica a
    b->left = a;   //przypisanie a lewemu wskaźnikowi elementu b

}

void bstmain::makespine() {
// tworzenie "kręgosłupa z drzewa bst"
    if (head == NULL) {
        cout << endl << "puste drzewo" << endl;
        return;
    }

    eldrzewa *temp = head;
    while (temp != NULL) {
        if (temp->left != NULL) {
            rotateright(temp);

            if (temp == head) {
                head = temp->parentt;
            }
            temp = temp->parentt;

        } else {
            temp = temp->right;
        }


    }


}

void bstmain::breakspine() {
//"łamanie kręgosłupa w drzewo bst"
    if (head == NULL) {
        cout << endl << "puste drzewo" << endl;
        return;
    }

    int m, n, i;
    n = rozm;
    i = log2((n + 1));
    m = 2;
    for (int j = 1; j < i; ++j) {
        m = m * 2;
    }
    m = m - 1;
    i = n - m;
    eldrzewa *temp = head;

    for (int j = 0; j < i; ++j) {
        rotateleft(temp);
        if (temp == head) {
            head = temp->parentt;
        }
        temp = temp->parentt->right;

    }


    while (m > 1) {
        m = m / 2;
        i = m;
        temp = head;
        for (int j = 0; j < i; ++j) {
            rotateleft(temp);
            if (temp == head) {
                head = temp->parentt;
            }
            temp = temp->parentt->right;

        }
    }


}

void bstmain::balancetree() {
// funkcja balansowania drzewa
    if (head == NULL) {
        cout << endl << "puste drzewo" << endl;
        return;
    }
    makespine();
    breakspine();


}

boolean bstmain::testw() {// test czy mała struktura
    boolean taknie = true;
    if (rozm > 40) {
        taknie = false;
    }
    return taknie;
}

void bstmain::purge(eldrzewa *korzen) {
//czyszczenie pamięci

    if (korzen == NULL) return;
    purge(korzen->left);
    purge(korzen->right);
    delete korzen;

    rozm = 0;
}

long long int bstmain::read_QPC() {
    //pomiar czasu
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}

bstmain::bstmain(string npliku) {//konstruktor
    cout << endl << "Tworze drzewo BST" << endl;
    head = NULL;
    init(npliku);

}

bstmain::~bstmain() {// destruktor
    cout << endl << "Niszcze drzewo BST" << endl;
    purge(head);

}






