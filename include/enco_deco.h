// enco_deco.h

#ifndef ENCO_DECO_H
#define ENCO_DECO_H
#include <stdio.h>
#include <stdlib.h>

char *textToBase32(const char *input);             
char *base32ToText(const char *input);             
char *textToBase64(const char *input);             
char *base64ToText(const char *input);             
void textToBase32File(FILE *file, char *fileName); 
void base32ToTextFile(FILE *file, char *fileName); 
void textToBase64File(FILE *file, char *fileName); 
void base64ToTextFile(FILE *file, char *fileName); 

char *textToBinary(const char *input); 

#endif // ENCO_DECO_H