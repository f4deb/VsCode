#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

#include <stdint.h>

#define CR 0x0D
#define LF 0x0A

void compilCharUtils(void);

char* truncString(char* str, int posInit, int length);

char* stringToString(char* str,char* rxBuffer, int size);

int readHex(char* str);

int readDec(char* str);

char readChar(char* str);

uint8_t readSeparator(char* str);

#endif