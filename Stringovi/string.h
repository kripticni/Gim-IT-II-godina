#ifndef STRING_H
#define STRING_H

#ifndef STDLIB_H
#include <stdlib.h>
#endif
#ifndef STDIO_H
#include <stdio.h>
#endif

inline void puts(char *str) {
  while (*str != '\0') {
    putchar(*str);
    str++;
  }
};

inline unsigned int strlen(char *str) {
  unsigned int br;
  while (*str != '\0') {
    br++;
    str++;
  }
  return br;
}

inline void strcpy(char *dest, char *src) {
  while (*src != '\0') {
    *dest = *src;
    src++;
    dest++;
  };
  *(dest + 1) = '\0';
};

inline void to_upper(char *str) {
  while (*str != '\0') {
    if (*str >= 'a' && *str <= 'z')
      *str = *str - 32; // velika i mala slova su udaljena za po 32
    str++;
  }
}

inline void to_lower(char *str) {
  while (*str != '\0') {
    if (*str >= 'A' && *str <= 'Z')
      *str = *str + 32;
    str++;
  }
}

#endif
