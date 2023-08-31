//enco_deco.h

#ifndef ENCO_DECO_H
#define ENCO_DECO_H
#include <stdio.h>
#include <stdlib.h>


char* textToBase32( const char* input); //DONE
char* base32ToText( const char* input); //DONE
char* textToBase64( const char* input); //DONE
char* base64ToText( const char* input); //DONE 
void textToBase32File(FILE *file, char* fileName); //DONE
void base32ToTextFile(FILE *file, char* fileName); //DONE
void textToBase64File(FILE *file, char* fileName); //DONE
void base64ToTextFile(FILE *file, char* fileName); //DONE 

char* textToBinary(const char* input); //DONE


#endif // ENCO_DECO_H