#include<stdio.h>
#include<malloc.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
};



Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(b.nume, nume);
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}


struct Nod {
    Biblioteca info;
    Nod* next;
    Nod* prev;
};


typedef struct ListaDubla ListaDubla;
struct ListaDubla {
    Nod* head;
    Nod* tail;
};

void inserareInceput(ListaDubla* listaDubla, Biblioteca b) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->info = b;
    nod->next = listaDubla->head;
    nod->prev = NULL;
    if (listaDubla->head)
    {
        listaDubla->head->prev = nod;
    }
    else {
        listaDubla->tail = nod;
    }
    listaDubla->head = nod;
}

void afisareListaInceput(ListaDubla listaDubla) {
    while (listaDubla.head)
    {
        printf("Biblioteca: %s, Numar cititori: %d, Numar carti: %d", listaDubla.head->info.nume, listaDubla.head->info.nrCititori, listaDubla.head->info.nrCarti);
        printf("\n");
        listaDubla.head = listaDubla.head->next;
    }

}

void stergereNodNume(ListaDubla* listaDubla, const char* nume) {
    Nod* aux = listaDubla->head;
    while (aux && strcmp(nume, aux->info.nume) != 0) {
        aux = aux->next;
    }
    if (aux)
    {
        if (aux==listaDubla->head)
        {
            if (aux == listaDubla->tail) {
                listaDubla->head = NULL;
                listaDubla->tail = NULL;
            }
            else
            {
                listaDubla->head = listaDubla->head->next;
                listaDubla->head->prev = NULL;
            }
        }
        else
        {
            if (aux==listaDubla->tail)
            {
                aux->prev->next = NULL;
                listaDubla->tail = aux->prev;
            }
            else
            {
                aux->next->prev = aux->prev->next;
                aux->prev->next = aux->next;
            }
        }
        free(aux->info.nume);
        free(aux);
    }
}

int nrCartiTotal(ListaDubla listaDubla) {
    int total = 0;
    while (listaDubla.tail)
    {
        total += listaDubla.tail->info.nrCarti;
        listaDubla.tail = listaDubla.tail->prev;
    }



    return total;
}

void stergereLista(ListaDubla* listaDubla) {

    while (listaDubla->head)
    {
        free(listaDubla->head->info.nume);
        Nod* aux = listaDubla->head;
        listaDubla->head = listaDubla->head->next;
        free(aux);
    }
    listaDubla->head = NULL;
    listaDubla->tail = NULL;
}

void main() {
    Biblioteca b1 = initializare("Mihai Eminescu", 150, 30);
    Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
    Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);

    ListaDubla listaDubla;
    listaDubla.head = NULL;
    listaDubla.tail = NULL;

    inserareInceput(&listaDubla, b1);
    inserareInceput(&listaDubla, b2);
    inserareInceput(&listaDubla, b3);

    afisareListaInceput(listaDubla);

  /*stergereNodNume(&listaDubla, "Ioan Slavici");


    printf("Afisare lista dupa stergere Ioan Slavici\n");
    afisareListaInceput(listaDubla);
    
    printf("Afisare dupa stergere totala lista:\n");
    stergereLista(&listaDubla);
    afisareListaInceput(listaDubla);

    */

    int totalCarti=nrCartiTotal(listaDubla);
    printf("Nr total carti: %d\n", totalCarti);

}
