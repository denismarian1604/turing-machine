/* VLADULESCU DENIS - MARIAN - 314CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula {
    char *info;
    struct celula *urm;
}TCelula, *TLista;

typedef struct celula2 {
    char info;
    struct celula2 *ant, *urm;
}TCelula2, *TLista2;

typedef struct coada {
    TLista inc, sf;
}TCoada;

typedef struct banda {
    TLista2 l, crt;
}TBanda;

typedef struct undo_redo {
    TLista2 inf;
    struct undo_redo* urm;
}TUR;

TLista AlocCelula(char *inf);
TLista2 AlocCelula2(char inf);
TBanda* AlocBanda(TLista2* l);
TCoada* AlocCoada();
int Muta_Din_Op_In_Undo(TBanda* b, TCoada* op, TUR** undo, int ok);
void Muta_Din_Undo_In_Redo(TUR** undo, TUR** redo, TLista2* adr);
void Muta_Din_Redo_In_Undo(TUR** redo, TUR** undo, TLista2* adr);
void AfisareLista(TLista L);
int AdaugaCoada(TCoada* c, char *inf);
void AfisareCoada(TCoada* c);
int MOVE_RIGHT(TBanda* b);
int MOVE_LEFT(TBanda *b, FILE* afisare);
void WRITE(TBanda* b, char c);
int MOVE_RIGHT_CHAR(TBanda* b, char c);
int MOVE_LEFT_CHAR(TBanda* b, char c, FILE* afisare);
int INSERT_LEFT(TBanda* b, char c, FILE* afisare);
int INSERT_RIGHT(TBanda* b, char c);
void DistrugeLista(TLista* L);
void DistrugeTUR(TUR** C);
void DistrugeLista2(TLista2* L2);
void DistrugereCoada(TCoada** c);
void DistrugereBanda(TBanda** b);
void SHOW(TBanda* b, FILE* afisare);
void SHOW_CURRENT(TBanda* b, FILE* afisare);
void ElimOp(TCoada* op);
int EXECUTE(TCoada** op, TBanda* b, TUR** undo, TUR** redo, FILE* afisare);
void QUERY_UR(char* operatie, TBanda* b, FILE* afisare, TUR** undo, TUR** redo);
