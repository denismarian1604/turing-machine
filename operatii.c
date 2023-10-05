/* VLADULESCU DENIS - MARIAN - 314CB*/
#include "header.h"
#define SIX 6
#define SIXTEEN 16
#define FIFTEEN 15
#define THIRTEEN 13
#define TWELVE 12
int AdaugaCoada(TCoada *c, char *inf) {
    TLista aux = AlocCelula(inf);
    if (!aux)
        return 0;
        // coada este vida
    if (c->inc == NULL) {
        c->inc = c->sf = aux;
    } else {
        c->sf->urm = aux;
        c->sf = aux;
    }
    return 1;
}
void AfisareCoada(TCoada *c) {
    TLista aux = c->inc;
    while (aux) {
        printf("%s\n", aux->info);
        aux = aux->urm;
    }
}
int MOVE_RIGHT(TBanda *b) {
    if (b->crt->urm == NULL) {
        // alocam la maxim dreapta o noua celula in banda
        TLista2 aux2 = AlocCelula2('#');
        if (!aux2)
            return 0;
        b->crt->urm = aux2;
        aux2->ant = b->crt;
    }
    // indiferent daca exista sau nu la inceput, ne putem muta ulterior pe ea
    b->crt = b->crt->urm;
    return 1;
}
int MOVE_LEFT(TBanda *b, FILE *afisare) {
    if (b->crt->ant == b->l) {
        // nu ne-am putut deplasa la stanga,
        // deoarece suntem deja la inceputul benzii
        return 0;
    } else {
        b->crt = b->crt->ant;
        return 1;
    }
}
void WRITE(TBanda *b, char c) {
    b->crt->info = c;
}
int MOVE_RIGHT_CHAR(TBanda *b, char c) {
    TLista2 p2 = b->crt;
    int gasit = 0;
    while (p2) {
        if (p2->info == c) {
            gasit = 1;
            break;
        }
        if (!p2->urm)
            break;
        p2 = p2->urm;
    }
    if (!gasit) {
        TLista2 aux2 = AlocCelula2('#');
        if (!aux2)
            return 0;
        p2->urm = aux2;
        aux2->ant = p2;
        p2 = aux2;
    }
    b->crt = p2;
    return 1;
}
int MOVE_LEFT_CHAR(TBanda *b, char c, FILE *afisare) {
    TLista2 p2 = b->crt;
    int gasit = 0;
    while (p2) {
        if (p2->info == c) {
            gasit = 1;
            break;
        }
        if (p2->ant == b->l)
            break;
        p2 = p2->ant;
    }
    if (!gasit) {
        // daca gasit este 0 inseamna ca am ajuns la marginea din stanga
        // a benzii si nu am gasit caracterul cautat
        fprintf(afisare, "ERROR\n");
        return 0;
    } else {
        b->crt = p2;
        return 1;
    }
}
int INSERT_LEFT(TBanda *b, char c, FILE *afisare) {
    if (b->crt == b->l->urm) {
        // cazul in care ne aflam pe prima pozitie a benzii
        fprintf(afisare, "ERROR\n");
        return 0;
    } else {
        TLista2 aux2 = AlocCelula2(c);
        if (!aux2)
            return 0;
        aux2->urm = b->crt;
        aux2->ant = b->crt->ant;
        b->crt->ant = aux2;
        aux2->ant->urm = aux2;
        b->crt = b->crt->ant;
        return 1;
    }
}
int INSERT_RIGHT(TBanda *b, char c) {
    TLista2 aux2 = AlocCelula2(c);
    if (!aux2)
        return 0;
    if (b->crt->urm == NULL) {
        aux2->ant = b->crt;
        aux2->urm = NULL;
        b->crt->urm = aux2;
        b->crt = b->crt->urm;
    } else {
        aux2->ant = b->crt;
        aux2->urm = b->crt->urm;
        aux2->urm->ant = aux2;
        b->crt->urm = aux2;
        b->crt = b->crt->urm;
    }
    return 1;
}
void SHOW(TBanda *b, FILE *afisare) {
    TLista2 p2 = b->l->urm;
    TLista2 crt2 = b->crt;
    while (p2) {
        if (p2 != crt2) {
            fprintf(afisare, "%c", p2->info);
        } else {
            fprintf(afisare, "|%c|", p2->info);
        }
        p2 = p2->urm;
    }
    fprintf(afisare, "\n");
}
void SHOW_CURRENT(TBanda *b, FILE *afisare) {
    fprintf(afisare, "%c\n", b->crt->info);
}
void ElimOp(TCoada *op) {
    // eliminam operatia din coada de operatii
    TLista aux = op->inc;
    op->inc = aux->urm;
    if (op->inc == NULL)
        op->sf = NULL;
    free(aux->info);
    free(aux);
}
int EXECUTE(TCoada **op, TBanda *b, TUR **undo, TUR **redo, FILE *afisare) {
    int ok = 0;
    /*
        se executa prima operatie din coada op
        ulterior se pune operatia in stiva undo
        daca este operatie de tip write, stivele undo si redo se distrug
    */
    if (strcmp((*op)->inc->info, "MOVE_RIGHT") == 0) {
        ok = MOVE_RIGHT(b);
        if (!ok)
            return 0;
        Muta_Din_Op_In_Undo(b, (*op), undo, ok);
    } else if (strcmp((*op)->inc->info, "MOVE_LEFT") == 0) {
        ok = MOVE_LEFT(b, afisare);
        Muta_Din_Op_In_Undo(b, (*op), undo, ok);
    } else if (strstr((*op)->inc->info, "WRITE")) {
        char c = (*op)->inc->info[SIX];
        WRITE(b, c);
        // in cazul in care intalnim operatie de write,
        // golim stivele undo si redo
        DistrugeTUR(undo);
        DistrugeTUR(redo);
        ElimOp((*op));
    } else if (strstr((*op)->inc->info, "MOVE_RIGHT_CHAR")) {
        // retinem in c caracterul spre care ne deplasam
        char c = (*op)->inc->info[SIXTEEN];
        MOVE_RIGHT_CHAR(b, c);
        ElimOp((*op));
    } else if (strstr((*op)->inc->info, "MOVE_LEFT_CHAR")) {
        // retinem in c caracterul spre care ne deplasam
        char c = (*op)->inc->info[FIFTEEN];
        ok = MOVE_LEFT_CHAR(b, c, afisare);
        ElimOp((*op));
    } else if (strstr((*op)->inc->info, "INSERT_RIGHT")) {
        // retinem in c caracterul de inserat
        char c = (*op)->inc->info[THIRTEEN];
        INSERT_RIGHT(b, c);
        ElimOp((*op));
    } else if (strstr((*op)->inc->info, "INSERT_LEFT")) {
        // retinem in c caracterul de inserat
        char c = (*op)->inc->info[TWELVE];
        INSERT_LEFT(b, c, afisare);
        ElimOp((*op));
    }
    return 1;
}
void QUERY_UR(char *operatie, TBanda *b, FILE *afisare, TUR **undo, TUR **redo) {
    if (strcmp(operatie, "SHOW") == 0) {
        SHOW(b, afisare);
    } else if (strcmp(operatie, "SHOW_CURRENT") == 0) {
        SHOW_CURRENT(b, afisare);
    } else if (strcmp(operatie, "UNDO") == 0) {
        // retinem in aux poziti curenta a degetului
        TLista2 aux = b->crt;
        // mutam pozitia curenta a degetului la adresa
        // la care indica celula din varful stivei undo
        b->crt = (*undo)->inf;
        Muta_Din_Undo_In_Redo(undo, redo, &aux);
    } else if (strcmp(operatie, "REDO") == 0) {
        // retinem in aux poziti curenta a degetului
        TLista2 aux = b->crt;
        // mutam pozitia curenta a degetului la adresa
        // la care indica celula din varful stivei redo
        b->crt = (*redo)->inf;
        Muta_Din_Redo_In_Undo(redo, undo, &aux);
    }
}
