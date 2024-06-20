#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int index;                           // Promenljiva za indeks tenka
    char ime[50];                        // Promenljiva za ime tenka
    int nivo;                            // Promenljiva za nivo tenka
    char klasa[4];                       // Promenljiva za klasu tenka
    char nacija[21];                     // Promenljiva za naciju tenka
    int vrednost_kamulaze;               // Promenljiva za vrednost kamulaze
    int vrednost_kamuflaze_nakon_pucanja;// Promenljiva za vrednost kamuflaze nakon pucanja
    int brzina_granate;                  // Promenljiva za brzinu granate
    int vidokrug;                        // Promenljiva za vidokrug
    int nevidjeno_ubistvo;               // Polje za rastojanje na kojem mo�e ostati nevidjen prilikom ubistva
} Tenk;

// Definicija strukture Liste_Tenk
typedef struct Lista_Tenk {
    Tenk tenk;                // Element liste koji sadr�i Tenk strukturu
    struct Lista_Tenk *levi;  // Pokaziva� na levi element liste (tipa Lista_Tenk)
    struct Lista_Tenk *desni; // Pokaziva� na desni element liste (tipa Lista_Tenk)
} Lista_Tenk;

// Funkcija za upisivanje podataka u datoteku
int upisiPodatke(Lista_Tenk *glava) {
    FILE *file = fopen("Tenkovi.txt", "w");
    if (file == NULL) {
        printf("Greska prilikom otvaranja datoteke za pisanje.\n");
        return 0;
    }

    Lista_Tenk *trenutni = glava;
    while (trenutni != NULL) {
        fprintf(file, "%d %s %d %s %s %d %d %d %d %d\n",
                trenutni->tenk.index, trenutni->tenk.ime, trenutni->tenk.nivo,
                trenutni->tenk.klasa, trenutni->tenk.nacija, trenutni->tenk.vrednost_kamulaze,
                trenutni->tenk.vrednost_kamuflaze_nakon_pucanja, trenutni->tenk.brzina_granate,
                trenutni->tenk.vidokrug, trenutni->tenk.nevidjeno_ubistvo);
        trenutni = trenutni->desni;
    }

    fclose(file);
    return 1;
}

// Funkcija koja izra�unava maksimalnu distancu za neprime�ivanje
int udaljenost_nevidjenost(int brzina_granate) {
    int udaljenost = (brzina_granate / 6) - 5;
    if (udaljenost < 51) {
        printf("Nije mogu�e ostati nevi�en.\n");
        return 0;
    } else {
        return udaljenost;
    }
}

// Funkcija za kreiranje novog elementa Liste_Tenk
Lista_Tenk* kreirajElement(Tenk tenk) {
    Lista_Tenk *novi = (Lista_Tenk*)malloc(sizeof(Lista_Tenk));
    if (novi == NULL) {
        printf("Gre�ka pri alokaciji memorije za novi element liste.\n");
        return NULL;
    }
    novi->tenk = tenk;
    novi->tenk.nevidjeno_ubistvo = udaljenost_nevidjenost(tenk.brzina_granate); // Izra�unavanje maksimalne udaljenosti
    novi->levi = NULL;
    novi->desni = NULL;
    return novi;
}

// Funkcija za dodavanje novog elementa na kraj liste
Lista_Tenk* dodajNaKraj(Lista_Tenk *glava, Tenk tenk) {
    Lista_Tenk *novi = kreirajElement(tenk);
    if (novi == NULL) {
        return glava; // Vra�amo postoje�u glavu ako nije uspelo dodavanje
    }

    if (glava == NULL) {
        return novi; // Ako je lista prazna, novi element postaje glava liste
    }

    Lista_Tenk *trenutni = glava;
    while (trenutni->desni != NULL) {
        trenutni = trenutni->desni;
    }

    trenutni->desni = novi;
    novi->levi = trenutni;

    return glava; // Vra�amo glavu liste
}

// Funkcija za ispisivanje liste Tenkova
void ispisiListu(Lista_Tenk *glava) {
    Lista_Tenk *trenutni = glava;
    while (trenutni != NULL) {
        printf("Index: %d, Ime: %s, Nivo: %d, Klasa: %s\n", trenutni->tenk.index, trenutni->tenk.ime, trenutni->tenk.nivo, trenutni->tenk.klasa);
        trenutni = trenutni->desni;
    }
}

// Funkcija koja ra�una udaljenost na kojoj �e biti vi�en tenk1 od tenk2
int udaljenost(Tenk tenk1, Tenk tenk2) {
    int daljina_vidljivosti = tenk2.vidokrug - ((tenk2.vidokrug - 50) * tenk2.vrednost_kamulaze / 100);
    return daljina_vidljivosti;
}

// Funkcija za ispisivanje celog sadrzaja datoteke Tenkovi.txt
void ispisiSadrzajDatoteke() {
    FILE *file = fopen("Tenkovi.txt", "r");
    if (file == NULL) {
        printf("Greska prilikom otvaranja datoteke 'Tenkovi.txt'.\n");
        return;
    }

    printf("Sadrzaj datoteke 'Tenkovi.txt':\n");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// Funkcija za osloba�anje memorije liste
void oslobodiListu(Lista_Tenk *glava) {
    Lista_Tenk *trenutni = glava;
    while (trenutni != NULL) {
        Lista_Tenk *za_brisanje = trenutni;
        trenutni = trenutni->desni;
        free(za_brisanje);
    }
}

// Funkcija za sortiranje dvostruke liste selection sort algoritmom
void selectionSort(Lista_Tenk *glava) {
    if (glava == NULL || glava->desni == NULL) {
        return; // Ako lista ima 0 ili 1 element, ve� je sortirana
    }

    Lista_Tenk *pocetak = glava;

    while (pocetak->desni != NULL) {
        Lista_Tenk *min_element = pocetak;
        Lista_Tenk *trenutni = pocetak->desni;

        while (trenutni != NULL) {
            // Poredimo po nivou tenka
            if (trenutni->tenk.nivo < min_element->tenk.nivo) {
                min_element = trenutni;
            }
            trenutni = trenutni->desni;
        }

        // Zamena sadr�aja
        Tenk temp = pocetak->tenk;
        pocetak->tenk = min_element->tenk;
        min_element->tenk = temp;

        pocetak = pocetak->desni;
    }
}

// Funkcija za ispisivanje tenkova iz datoteke po odre�enoj klasi
void ispisiListuIzDatoteke(char *filename, char *trazene_klase[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Greska prilikom otvaranja datoteke '%s'.\n", filename);
        return;
    }

    Tenk tenk;
    while (fscanf(file, "%d %s %d %s %d %d %d %d %d\n",
                  &tenk.index, tenk.ime,
                  &tenk.nivo, tenk.klasa,
                  &tenk.nacija, &tenk.vrednost_kamulaze,
                  &tenk.vrednost_kamuflaze_nakon_pucanja,
                  &tenk.brzina_granate, &tenk.vidokrug) == 9) {
        // Provera da li je klasa tenka jedna od tra�enih klasa
        int ispravna_klasa = 0;
        for (int i = 0; i < 5; ++i) { // 5 je broj tra�enih klasa ("LT", "MT", "HT", "TD", "SPG")
            if (strcmp(tenk.klasa, trazene_klase[i]) == 0) {
                ispravna_klasa = 1;
                break;
            }
        }

        if (ispravna_klasa) {
            printf("Index: %d, Ime: %s, Nivo: %d, Klasa: %s\n", tenk.index, tenk.ime, tenk.nivo, tenk.klasa);
        }
    }

    fclose(file);
}

int main()
{
    char filename[] = "Tenkovi.txt";
    char *trazene_klase[] = {"LT", "MT", "HT", "TD", "SPG"};
    Lista_Tenk *glava = NULL;
    int izbor;

    while (1) {
        printf("\nIzaberite opciju:\n");
        printf("1 - Unesi novi tenk\n");
        printf("2 - Prebaci sadrzaj liste u datoteku 'Tenkovi.txt'\n");
        printf("3 - Sortiraj listu po nivou tenka\n");
        printf("4 - Prikazi sadrzaj datoteke 'Tenkovi.txt'\n");
        printf("5 - Prikazi udaljenost na kojoj je tenk vidjen\n");
        printf("6 - Ispisi tenkove po odredjenoj klasi\n");
        printf("7 - Ispisi kompletan sadrzaj datoteke Tenkovi.txt\n");
        printf("0 - Izlaz iz programa\n");

        scanf("%d", &izbor);

        switch (izbor) {
            case 0:
                printf("Izlaz iz programa.\n");
                oslobodiListu(glava); // Osloba�anje memorije pre izlaska iz programa
                return 0;

case 1: {
                Tenk noviTenk;
                printf("Unesite podatke za novi tenk:\n");
                printf("Index: ");
                scanf("%d", &noviTenk.index);
                printf("Ime: ");
                scanf("%s", noviTenk.ime);
                printf("Nivo: ");
                scanf("%d", &noviTenk.nivo);
                printf("Klasa: ");
                scanf("%s", &noviTenk.klasa);
                printf("Nacija: ");
                scanf("%s", &noviTenk.nacija);
                printf("Vrednost kamulaze: ");
                scanf("%d", &noviTenk.vrednost_kamulaze);
                printf("Vrednost kamuflaze nakon pucanja: ");
                scanf("%d", &noviTenk.vrednost_kamuflaze_nakon_pucanja);
                printf("Brzina granate: ");
                scanf("%d", &noviTenk.brzina_granate);
                printf("Vidokrug: ");
                scanf("%d", &noviTenk.vidokrug);

                glava = dodajNaKraj(glava, noviTenk);
                printf("Novi tenk je dodat u listu.\n");
                break;
            }

case 2: {
                if (upisiPodatke(glava)) {
                    printf("Podaci su uspesno upisani u datoteku 'Tenkovi.txt'.\n");
                } else {
                    printf("Greska prilikom upisivanja podataka u datoteku.\n");
                }
                break;
            }

case 3: {
                selectionSort(glava);
                printf("Lista je uspesno sortirana po nivou tenka.\n");
                break;
            }

case 4: {
                FILE *file = fopen("Tenkovi.txt", "r");
                if (file == NULL) {
                    printf("Greska prilikom otvaranja datoteke 'Tenkovi.txt'.\n");
                    break;
                }

                printf("Sadrzaj datoteke 'Tenkovi.txt':\n");
                char line[256];
                while (fgets(line, sizeof(line), file)) {
                    printf("%s", line);
                }

                fclose(file);
                break;
            }

case 5: {
    // Prikaz udaljenosti na kojoj je tenk vi�en
    int index1, index2;
    printf("Unesite index prvog tenka: ");
    scanf("%d", &index1);
    printf("Unesite index drugog tenka: ");
    scanf("%d", &index2);

    // Pronalazak odgovaraju�ih elemenata Liste_Tenk
    Lista_Tenk *tenk1 = glava;
    Lista_Tenk *tenk2 = NULL;

    while (tenk1 != NULL) {
        if (tenk1->tenk.index == index1) {
            break;
        }
        tenk1 = tenk1->desni;
    }

    if (tenk1 == NULL) {
        printf("Tenk sa indexom %d nije pronadjen.\n", index1);
        break;
    }

    tenk2 = glava;
    while (tenk2 != NULL) {
        if (tenk2->tenk.index == index2) {
            break;
        }
        tenk2 = tenk2->desni;
    }

    if (tenk2 == NULL) {
        printf("Tenk sa indexom %d nije pronadjen.\n", index2);
        break;
    }

    // Racunanje udaljenosti pozivom funkcije
    int udaljenost_izracunata = udaljenost(tenk1->tenk, tenk2->tenk);
    printf("Udaljenost na kojoj je tenk sa indexom %d vidjen od tenka sa indexom %d: %d\n", index1, index2, udaljenost_izracunata);
    break;
            }

case 6: {
                // Implementacija ispisivanja tenkova po odre�enoj klasi
                char trazena_klasa[4];
                printf("Unesite trazenu klasu (LT, MT, HT, TD, SPG): ");
                scanf("%s", trazena_klasa);
                ispisiListuIzDatoteke(filename, trazena_klasa);
                break;
            }

case 7: {
    printf("\n");
    ispisiSadrzajDatoteke();
    printf("\n");
    break;
}
            default:
                printf("Nepostojeca opcija. Pokusajte ponovo.\n");
                break;
        }
    }

    oslobodiListu(glava); // Osloba�anje memorije pre izlaska iz programa




    return 0;
}

