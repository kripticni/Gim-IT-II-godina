#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int palindrom(char *str) {
  char *rev; // ovaj pokazivac ide unazad kroz string
  while (*rev != '\0')
    rev++; // sad pokazuje na null
  rev--;   // sad pokazuje na zadnji karakter

  while (
      rev >
      str) { // sluzi da kada se pokazivaci mimoidju, zaustavi se uporedjivanje
    if (*rev != *str)
      return 0; // ako su razliciti onda nije palindrom
    rev--;
    str++;
  }
  return 1; // ako su svi s leve i s desne isti, onda je palindrom
}

void ispis_prvih(char *str, unsigned int br) {
  for (; br > 0 && *str != '\0'; br--) {
    putchar(*str);
    str++;
  }
}

void ispis_zadnjih(char *str, unsigned int br) {
  while (*str != '\0')
    str++;
  puts(str - br);
}

void ispis_zadnjih_putchar(char *str, unsigned int br) {
  while (*str != '\0')
    str++;
  str = str - br;
  while (*str != '\0')
    putchar(*str);
}

void ispis_zadnjih_unazad(char *str, unsigned int br) {
  while (*str != '\0')
    str++;
  str--; // dodje do zadnjeg karaktera
  for (; br > 0; br--) {
    putchar(*str);
    str--;
  }
}

void ispis_od_P_do_K(char *str, unsigned int p, unsigned int k) {
  str = str + p;
  for (; k > 0 && *str != '\0'; k--, str++) {
    putchar(*str);
  }
};

void podstring_od_P(char *str, unsigned int p) {
  while (p > 0) {
    if (*str == '\0')
      return;
    p--;
    str++;
  }
  *str = '\0';
}

void ispis_K_u_jednom_redu(char *str, unsigned int k) {
  unsigned int iterator;
  while (1) {
    for (iterator = k; iterator > 0; iterator--) {
      if (*str == '\0')
        return;
      putchar(*str);
      str++;
    }
    putchar('\n');
  }
}

char *umetni(char *dest, char *src, unsigned int p) {
  unsigned int i, len_src, len_dest;
  len_src = strlen(src);
  len_dest = strlen(dest);

  for (i = len_dest; i >= p; i--) {
    *(dest + i + len_src) = *(dest + i);
  }

  for (i = 0; i < len_src; i++) {
    *(dest + p + i) = *(src + i);
  }

  *(dest + len_dest + len_src) = '\0';
  return dest;
}

int broj_X(char *str, char c) {
  int rez = 0;
  for (; *str != '\0'; str++)
    if (*str == c)
      rez++;
  return rez;
}
