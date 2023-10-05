/* VLADULESCU DENIS - MARIAN - 314CB*/
#include "header.h"
#define TWENTY 20
TLista AlocCelula(char *inf) {
    TLista aux = (TLista)malloc(sizeof(TCelula));
    if (!aux)
        return NULL;
    aux->info = (char *)calloc(TWENTY, sizeof(char));
    if (!aux->info) {
        free(aux);
        return NULL;
    }
    for (int i = 0; i < strlen(inf); i++)
        aux->info[i] = inf[i];
    aux->urm = NULL;
    return aux;
}
TLista2 AlocCelula2(char inf) {
    TLista2 aux = (TLista2)malloc(sizeof(TCelula2));
    if (!aux)
        return NULL;
    aux->info = inf;
    aux->urm = NULL;
    aux->ant = NULL;
    return aux;
}
TBanda *AlocBanda(TLista2 *l2) {
    TBanda *b = (TBanda *)calloc(1, sizeof(TBanda));
    if (!b)
        return NULL;
    b->l = (*l2);
    TLista2 aux2 = AlocCelula2('#');
    if (!aux2)
        return 0;
    b->l->urm = aux2;
    aux2->ant = b->l;
    b->crt = aux2;
    return b;
}
TCoada *AlocCoada() {
    TCoada *op = (TCoada *)calloc(1, sizeof(TCoada));
    if (!op)
        return NULL;
    op->inc = op->sf = NULL;
    return op;
}
void DistrugeLista(TLista *L) {
    TLista aux = NULL;
    while ((*L) != NULL) {
        aux = (*L);
        (*L) = (*L)->urm;
        free(aux->info);
        free(aux);
    }
}
void DistrugeTUR(TUR **C) {
    TUR *aux = NULL;
    while ((*C) != NULL) {
        aux = (*C);
        (*C) = (*C)->urm;
        free(aux);
    }
}
void DistrugeLista2(TLista2 *L2) {
    TLista2 p2 = (*L2)->urm, aux2 = NULL;
    (*L2)->urm = (*L2)->ant = NULL;
    free((*L2));
    while (p2) {
        aux2 = p2;
        p2 = p2->urm;
        free(aux2);
    }
}
void DistrugereCoada(TCoada **c) {
    TLista aux = NULL;
    if ((*c) != NULL) {
        while ((*c)->inc) {
            aux = (*c)->inc;
            (*c)->inc = (*c)->inc->urm;
            free(aux->info);
            free(aux);
        }
    }
    (*c)->inc = (*c)->sf = NULL;
    free((*c));
}
void DistrugereBanda(TBanda **b) {
    (*b)->l = (*b)->crt = NULL;
    free((*b));
}
