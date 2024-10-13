#include <stdio.h>
#include <string.h>

void ispis_zadnjih(char *str, unsigned int br) {
  while (*str != '\0')
    str++;
  puts(str - br);
}

void ispis_prvih(char *str, unsigned int br) {
  for (; br > 0 && *str != '\0'; br--) {
    putchar(*str);
    str++;
  }
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

char *obrni_string(char *str) {
  unsigned int i, len = strlen(str);
  char pom;
  for (i = 0; i < len / 2; i++) {
    pom = *(str + i);
    *(str + i) = *(str + len - i - 1);
    *(str + len - i - 1) = pom;
  }
};

int main() {
  char str[40] = "gimnazija";
  obrni_string(str);
  puts(str);
};
