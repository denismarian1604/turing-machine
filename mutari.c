/* VLADULESCU DENIS - MARIAN - 314CB*/
#include "header.h"
#define FORTYFIVE 45
int Muta_Din_Op_In_Undo(TBanda *b, TCoada *op, TUR **undo, int ok) {
    char info[FORTYFIVE] = "\0";
    strcpy(info, op->inc->info);
    // cazul in care ne-am deplasat la dreapta
    if (strcmp(info, "MOVE_RIGHT") == 0) {
        TUR *aux = (TUR *)malloc(sizeof(TUR));
        if (!aux)
            return 0;
        aux->inf = b->crt->ant;
        aux->urm = (*undo);
        (*undo) = aux;
    } else if (strcmp(info, "MOVE_LEFT") == 0) {
        if (ok) {
            // cazul in care ne-am putut deplasa la stanga
            TUR *aux = (TUR *)malloc(sizeof(TUR));
            if (!aux)
                return 0;
            aux->inf = b->crt->urm;
            aux->urm = (*undo);
            (*undo) = aux;
        }
    }
    // eliminam operatia din coada de operatii
    TLista aux = op->inc;
    op->inc = aux->urm;
    // in cazul in care coada este acum goala,
    // facem si finalul sa indice la NULL
    if (op->inc == NULL)
        op->sf = NULL;
    free(aux->info);
    free(aux);
    return 1;
}
void Muta_Din_Undo_In_Redo(TUR **undo, TUR **redo, TLista2 *adr) {
    // retin in aux celula din vf stivei undo
    TUR *aux = (*undo);
    // deplasam varful stivei undo
    (*undo) = (*undo)->urm;
    // mutam celula in varful stivei redo
    aux->urm = (*redo);
    // actualizam varful stivei redo
    (*redo) = aux;
    // actualizam informatia din celula mutata
    // ca sa pointeze la pozitia corect anterioara
    (*redo)->inf = (*adr);
}
void Muta_Din_Redo_In_Undo(TUR **redo, TUR **undo, TLista2 *adr) {
    // retin in aux celula din vf stivei redo
    TUR *aux = (*redo);
    // deplasam varful stivei redo
    (*redo) = (*redo)->urm;
    // mutam celula in varful stivei undo
    aux->urm = (*undo);
    // actualizam varful stivei undo
    (*undo) = aux;
    // actualizam informatia din celula mutata
    // ca sa pointeze la pozitia corect anterioara
    (*undo)->inf = (*adr);
}
