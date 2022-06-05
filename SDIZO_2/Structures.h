//
// Created by barsu on 15.06.2021.
//

#ifndef SDIZO_2_STRUCTURES_H
#define SDIZO_2_STRUCTURES_H


struct kraw {// krawędź
    int wp;
    int wk;
    int waga;
};

struct kraw2 : kraw {//lista krawędzi
    kraw2 * next;
};

struct ellisty {//element listy sąsiedztwa
    int wk;
    int waga;
    ellisty *next;

};
struct elscie{// element listy ścierzek
    int path;
    elscie * next;
};




#endif //SDIZO_2_STRUCTURES_H
