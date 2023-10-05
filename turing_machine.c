/* VLADULESCU DENIS - MARIAN - 314CB*/
#include "header.h"
#define THIRTY 30
#define FORTYFIVE 45
#define ZERO 0
int main() {
    FILE *read = fopen("turing.in", "r");
    FILE *afisare = fopen("turing.out", "w");
    // string cu operatiile care determina executare imediata
    char OPS[] = "EXECUTE_UNDO_REDO_SHOW_SHOW_CURRENT";
    TLista2 l2 = AlocCelula2('?');
    // declarare + initializare banda
    TBanda *b = AlocBanda(&l2);
    // declarare operatii (coada), simplu inlantuita
    TCoada *op = AlocCoada();
    // declarare undo (stiva)
    TUR *undo = NULL;
    // declarare redo (stiva)
    TUR *redo = NULL;
    // aici vom citi operatiile din fisierul de intrare
    char *operatie = (char *)calloc(THIRTY, sizeof(char));
    // calloc pentru a o autoinitializa vida
    // si pentru a nu avea erori in valgrind
    int nr_op = ZERO, ok = ZERO;
    // nr_op = nr de operatii citite;
    // ok = variabila de verificare a reusitei executiei anumitor subprograme
    // care includ alocari sau deplasari
    fscanf(read, "%d", &nr_op);
    fgets(operatie, FORTYFIVE, read);
    // citim operatiile
    for (int i = 0; i < nr_op; i++) {
        fgets(operatie, FORTYFIVE, read);
        // inlocuim ultimul caracter de '\n' cu NULL
        // pentru a finaliza textul operatiei corect
        operatie[strlen(operatie) - 1] = '\0';
        if (strstr(OPS, operatie) == 0) {
            // in acest caz doar punem operatia in coada de operatii
            ok = AdaugaCoada(op, operatie);
            if (!ok)
                return 0;
        } else {
            // executam operatiile din coada op si apoi le mutam in
            if (strcmp(operatie, "EXECUTE") == 0) {
                ok = EXECUTE(&op, b, &undo, &redo, afisare);
                if (!ok)
                    return 0;
            } else {
                QUERY_UR(operatie, b, afisare, &undo, &redo);
            }
        }
    }
    // distrugere pointer de operatii
    free(operatie);
    // distrugere coada operatii
    DistrugereCoada(&op);
    // distrugere lista undo (stiva)
    DistrugeTUR(&undo);
    // distrugere lista redo (stiva)
    DistrugeTUR(&redo);
    // distrugere coada pentru banda, dublu inlantuita
    DistrugeLista2(&l2);
    // distrugere banda
    DistrugereBanda(&b);
    // inchidere fisier citire
    fclose(read);
    // inchidere fisier scriere
    fclose(afisare);
}
