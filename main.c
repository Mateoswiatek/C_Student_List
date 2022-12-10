#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WYJSCIE 9
bool czy_pierwszy_raz = 1;

struct student{
    int ocena;
    char nazwisko[100];
    struct student *next_adress;
};

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
//ok
void wypisz_wszystkich(struct student *pierwszy){
    struct student *lista_studentow;
    lista_studentow=pierwszy;
    if(lista_studentow->ocena==-1){
        printf("lista jest pusta, uzyj 1 z menu aby dodac studentow\n");
        return;
    }
    printf("wszyscy studenci:\n");
    wypisz_studenta(*pierwszy);
    while(lista_studentow->next_adress){
        lista_studentow=lista_studentow->next_adress;
        wypisz_studenta(*lista_studentow);
    }
}
//ok
void dodaj_studentow(int ilosc, struct student *root){
    struct student *wsk_listy;
    int i=0;
    wsk_listy=root; // wsk_listy wskazuje na roota
    if(!ilosc) {printf("wpisz liczbe >0\n"); return;}

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
        //printf("adres kolejnego to: %u", *wsk_listy);
        wsk_listy=wsk_listy->next_adress;
        if(wsk_listy==NULL){printf("blad pamieci"); return;}
        wpisz_dane_studenta(wsk_listy);
    }
}
//ok
void wyszukiwanie(struct student *root, bool rodzaj, int szukana_ocena, char *szukane_nazwisko){
    struct student *nast_student;
    int litery_w_nazwisku;
    nast_student=root;

    if(rodzaj) { //1 - nazwisko 0- ocena
        char *nazwisko_studenta = nast_student->nazwisko;
        printf("Studenci o nazwisku %s:\n", szukane_nazwisko);
        litery_w_nazwisku = strlen(nazwisko_studenta);

        for(int i=0;i<=litery_w_nazwisku;i++){
            if(szukane_nazwisko[i]==nazwisko_studenta[i]){
                if(i==litery_w_nazwisku) wypisz_studenta(*nast_student);
                continue;
            }
            break;
        }

        while (nast_student->next_adress) {
            nast_student = nast_student->next_adress;
            nazwisko_studenta = nast_student->nazwisko;
            litery_w_nazwisku = strlen(nazwisko_studenta); // w ta strone, bo w sprawdzane moze byc dluzsze

            for(int i=0;i<=litery_w_nazwisku;i++){
                if(szukane_nazwisko[i]==nazwisko_studenta[i]){
                    if(i==litery_w_nazwisku) wypisz_studenta(*nast_student);
                    continue;
                }
                break;
            }
        }
    }
    else{
        printf("Studenci majacy ocene %d:\n", szukana_ocena);
        if (nast_student->ocena == szukana_ocena) wypisz_studenta(*nast_student);
        while (nast_student->next_adress) {
            nast_student = nast_student->next_adress;
            if (nast_student->ocena == szukana_ocena) wypisz_studenta(*nast_student);
        }
    }
}
//ok
void usuwanie_pierwszo_napotkanego(struct student **ws_roota, struct student *root_listy, bool rodzaj, int szukana_ocena, char *skreslane_nazwisko){
    struct student *poprzedni, *aktualny, *nastepny, *ws_nowego_roota;
    int litery_w_nazwisku;
    printf("weszlismy do funkcji\n");
    aktualny=root_listy;

    if(rodzaj) { // 0-ocena, 1-nazwisko
        char *nazwisko_studenta = aktualny->nazwisko;
        litery_w_nazwisku = strlen(nazwisko_studenta);

        for (int i = 0; i <= litery_w_nazwisku; i++) {
            if (skreslane_nazwisko[i] == nazwisko_studenta[i]) {
                if (i == litery_w_nazwisku) {
                    *ws_roota = aktualny->next_adress;
                    free(aktualny);
                    break;
                }
                continue;
            }
            break;
        }

        while (aktualny->next_adress) {
            poprzedni = aktualny;
            aktualny = aktualny->next_adress;
            nazwisko_studenta = aktualny->nazwisko;
            litery_w_nazwisku = strlen(nazwisko_studenta);

            for (int i = 0; i <= litery_w_nazwisku; i++) {
                if (skreslane_nazwisko[i] == nazwisko_studenta[i]) {
                    if (i == litery_w_nazwisku) {
                        nastepny = aktualny->next_adress;
                        free(aktualny);
                        poprzedni->next_adress = nastepny;
                        break;
                    }
                    continue;
                }
                break;
            }
        }
    }
    else {
        printf("weszlismy else\n");
        if (aktualny->ocena == szukana_ocena) {
            ws_nowego_roota = aktualny->next_adress;
            printf("przed *ws_roota\n");
            *ws_roota = ws_nowego_roota;
            printf("po *ws_roota\n");
            free(aktualny);
            return;
        }

        while (aktualny->next_adress) {
            poprzedni = aktualny;
            aktualny = aktualny->next_adress;
            if (aktualny->ocena == szukana_ocena) {
                nastepny = aktualny->next_adress;
                free(aktualny);
                poprzedni->next_adress = nastepny;
                return;
            }
        }
    }
}
//ok
void wpisz_po(struct  student *root, bool rodzaj, int po_ocenie, char *po_nazwisku){
    struct student *nast_student, *n_nast_student;
    int litery_w_nazwisku;
    nast_student=root;

    if(rodzaj) { //1 - nazwisko 0- ocena
        char *nazwisko_studenta = nast_student->nazwisko;
        litery_w_nazwisku = strlen(nazwisko_studenta);

        for(int i=0;i<=litery_w_nazwisku;i++){
            if(po_nazwisku[i]==nazwisko_studenta[i]){
                if(i==litery_w_nazwisku){
                    n_nast_student=nast_student->next_adress;
                    nast_student->next_adress=malloc(sizeof (struct student));
                    if(nast_student==NULL){printf("blad pamieci"); return;}
                    nast_student=nast_student->next_adress;
                    wpisz_dane_studenta(nast_student);
                    nast_student->next_adress=n_nast_student;
                    return;
                }
                continue;
            }
            break;
        }

        while (nast_student->next_adress) {
            nast_student = nast_student->next_adress;
            nazwisko_studenta = nast_student->nazwisko;
            litery_w_nazwisku = strlen(nazwisko_studenta); // w ta strone, bo w sprawdzane moze byc dluzsze

            for(int i=0;i<=litery_w_nazwisku;i++){
                if(po_nazwisku[i]==nazwisko_studenta[i]){
                    if(i==litery_w_nazwisku){
                        n_nast_student=nast_student->next_adress;
                        nast_student->next_adress=malloc(sizeof (struct student));
                        if(nast_student==NULL){printf("blad pamieci"); return;}
                        nast_student=nast_student->next_adress;
                        wpisz_dane_studenta(nast_student);
                        nast_student->next_adress=n_nast_student;
                        return;
                    }
                    continue;
                }
                break;
            }
        }
    }
    else{
        if (nast_student->ocena == po_ocenie){
            n_nast_student=nast_student->next_adress;
            nast_student->next_adress=malloc(sizeof (struct student));
            if(nast_student==NULL){printf("blad pamieci"); return;}
            nast_student=nast_student->next_adress;
            wpisz_dane_studenta(nast_student);
            nast_student->next_adress=n_nast_student;
            return;
        }
        while (nast_student->next_adress) {
            nast_student = nast_student->next_adress;
            if (nast_student->ocena == po_ocenie){
                n_nast_student=nast_student->next_adress;
                nast_student->next_adress=malloc(sizeof (struct student));
                if(nast_student==NULL){printf("blad pamieci"); return;}
                nast_student=nast_student->next_adress;
                wpisz_dane_studenta(nast_student);
                nast_student->next_adress=n_nast_student;
                return;
            }
        }
    }



}

void zwalnianie_listy(struct student *root){
    // tu usuwamy wszystkie, pierwszy zostawiamy, ocene na -1, next adress na 0,
}

int main() {
    bool pom, tryb;
    int wybor=0, ilosc, ocenka;

    char S_nazwisko[100];

    struct student *root = 0, **ws_root; // to są unsigned int (u) /  unsigned long int  (lu)
    root = malloc(sizeof(struct student));
    if(root==NULL){printf("blad pamieci"); return 0;}
    root->next_adress = 0;
    root->ocena = -1;

    ws_root = &root;
    printf("pierwszy root jest w %u\n", root);
    printf("ocena roota to %d\n", root->ocena);
    printf("a ws_root ma w sobie: %u\n", *ws_root);

    while (1) {
        printf("dzialania:\n0-dodawanie stuentow (podana ilosc)\n1-wyswietlanie wszystkich studentow\n2-wyszukiwanie po ocenie / nazwisku\n3-usuwanie pierwszego napotkanego(po ocenie / nazwisku)\n4-dodawanie po danej ocenie/nazwisku\n5-usuwanie listy\n%d-Wyjscie\n", WYJSCIE);
        scanf("%d", &wybor);

        switch (wybor) {
            case 0:
                printf("podaj ilosc studentow do dopisania\n");
                scanf("%d", &ilosc);
                dodaj_studentow(ilosc, root);
                break;
            case 1:
                wypisz_wszystkich(root);
                break;
            case 2:
                printf("wyszukiwanie po\n0-ocena\n1-nazwisko\n");
                scanf("%d",&tryb);
                if(tryb){
                    printf("podaj nazwisko: ");
                    scanf("%s", &S_nazwisko);
                }
                else{
                    printf("podaj ocene:");
                    scanf("%d", &ocenka);
                }
                wyszukiwanie(root, tryb, ocenka, S_nazwisko);
                break;
            case 3:
                printf("usuwanie po\n0-ocena\n1-nazwisko\n");
                scanf("%d",&tryb);
                if(tryb){
                    printf("podaj nazwisko: ");
                    scanf("%s", &S_nazwisko);
                }
                else{
                    printf("podaj ocene:");
                    scanf("%d", &ocenka);
                }
                usuwanie_pierwszo_napotkanego(ws_root, root, tryb, ocenka, S_nazwisko);
                printf("wyszlo\n");
                //root=&ws_root;
                break;
            case 4:

                break;
            case 5:

                break;
            case WYJSCIE:
                printf("dzieki za skorzystanie z programu\n");
                free(root);
                //fflush(stdout); // z bufora na stdout (standardowe wyjście); // pokazac ze bez tego nie wypisze // ew mozna zamienic z free(root)
                return 0;
        }
        printf("chcesz juz wyjsc? 0/1\n");
        scanf("%d", &pom);
        if(pom){
            // zwalnianie calej pamieci
            printf("dzieki za skorzystanie z programu\n");
            return 0;
        }
    }

    /*
    usuwanie_pierwszo_napotkanego(ws_root, 0, 1, S_nazwisko);
    root=*ws_root; // zmiana roota jeśli potrzeba
*/
/*
    wpisz_po(root, 0, 1, S_nazwisko);

    wypisz_wszystkich(root);

*/

    //testy wskaznik do wskaznika
    /*
     printf("\n\n\n\n\nroot to %u\n", root);
    *ws_root=0; // zmieniamy zawartość
    printf("ws_root to %u\n", ws_root);
    printf("*ws_root to %u\n", *ws_root);

    root=*ws_root;
    printf("root po zmianie to %u\n", root); */
}
