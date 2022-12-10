#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WYJSCIE 9
bool czy_pierwszy_raz = 1;

struct student{
    int ocena;
    char nazwisko[100];
    struct student *next_adress;
};

// dodanie czegos studenic
//ok
void wpisz_dane_studenta(struct student *s){
    printf("podaj ocene: \n");
    scanf("%d", &s->ocena);
    printf("Podaj nazwisko: \n");
    scanf("%s", s->nazwisko);
    s->next_adress=0;
}
//ok
void wypisz_studenta( struct student s){
    printf("Ocena: %d Nazwisko: %s\n", s.ocena, s.nazwisko);
}

void wypisz_wszystkich(struct student *pierwszy){
    struct student *lista_studentow;
    lista_studentow=pierwszy;
    wypisz_studenta(*pierwszy);
    while(lista_studentow->next_adress){
        wypisz_studenta(*lista_studentow);
        lista_studentow=lista_studentow->next_adress;
    }
}

void dodaj_studenta(int ilosc, struct student *root){
    struct student *wsk_listy;
    int i=0;
    wsk_listy=root; // wsk_listy wskazuje na roota

    if (czy_pierwszy_raz) { // za pierwszym razem mamy roota, nie ma w nim wartosci
        wpisz_dane_studenta(wsk_listy);
        czy_pierwszy_raz = 0; // bo juz wpisalismy pierwszego
        i++;
    }

    while(wsk_listy->next_adress){ // przejście na koniec lsity
        wsk_listy=wsk_listy->next_adress;
    }

    for(i; i<ilosc;i++) {
        wsk_listy->next_adress= malloc(sizeof (struct student));
        wsk_listy=wsk_listy->next_adress;
        if(wsk_listy==NULL){printf("blad pamieci"); return;}
        wpisz_dane_studenta(wsk_listy);
    }

}


int main() {
    struct student *root = 0, **ws_root; // to są unsigned int (u) /  unsigned long int  (lu)
    root = malloc(sizeof(struct student));
    if(root==NULL){printf("blad pamieci"); return 0;}
    root->next_adress = 0;
    root->ocena = -1;

    ws_root = &root;
    printf("pierwszy root jest w %u\n", root);
    printf("ocena roota to %d\n", root->ocena);
    printf("a ws_root ma w sobie: %u\n", *ws_root);




    wpisz_dane_studenta(root);
    wypisz_studenta(*root);

    wypisz_wszystkich(root);



    /*
       while (1) {
           int wybor, ilosc;


           printf("Wybierz dzialanie:\n0 - dodawanie studentow\n1 - wyswietlanie wszystkich studentow\n");
           printf("2 - OCENA znajdywanie studenta\n3 - NAZWISKO znajdywnie studenta\n%d - wyjscie\n", WYJSCIE);
           scanf("%d", &wybor);

           switch (wybor) {
               case 0:

                   break;
               case 1:

                   break;
               case 2:

                   break;
               case 3:

                   break;
               case WYJSCIE:
                   printf("dzieki za skorzystanie z programu\n");
                   free(root);
                   //fflush(stdout); // z bufora na stdout (standardowe wyjście); // pokazac ze bez tego nie wypisze // ew mozna zamienic z free(root)
                   return 0;
           }
           return 0;
       }   */
}