#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "../include/enco_deco.h"

void check_textToBase32()
{
    char *input = "Hello World";
    char *str = textToBase32(input);    
    assert(strcmp(str, "JBSWY3DPEBLW64TMMQ======") == 0);
    free(str);

    input = "world";
    str = textToBase32(input);    
    assert(strcmp(str, "O5XXE3DE") == 0);
    free(str);

    input = "1234567890";
    str = textToBase32(input);    
    assert(strcmp(str, "GEZDGNBVGY3TQOJQ") == 0);
    free(str);

    input = "This is a test";
    str = textToBase32(input);    
    assert(strcmp(str, "KRUGS4ZANFZSAYJAORSXG5A=") == 0);
    free(str);

    input = "";
    str = textToBase32(input);
    assert(strcmp(str,"")==0);
    free(str);
    printf("textToBase32() pass\n");
}

void check_base32toText(){
    char * input = "JBSWY3DPEBLW64TMMQ======";
    char * str = base32ToText(input);
    assert(strcmp(str,"Hello World")==0);
    free(str);

    input = "O5XXE3DE";
    str = base32ToText(input);
    assert(strcmp(str,"world")==0);
    free(str);

    input = "GEZDGNBVGY3TQOJQ";
    str = base32ToText(input);
    assert(strcmp(str,"1234567890")==0);
    free(str);

    input = "KRUGS4ZANFZSAYJAORSXG5A=";
    str = base32ToText(input);
    assert(strcmp(str,"This is a test")==0);
    free(str);

    printf("base32ToText() pass\n");

}

void check_textToBase64(){
    char * input = "Hello World";
    char * str = textToBase64(input);
    assert(strcmp(str,"SGVsbG8gV29ybGQ=")==0);
    free(str);

    input = "The quick brown fox jumps over the lazy dog.";
    str = textToBase64(input);
    assert(strcmp(str,"VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZy4=")==0);
    free(str);

    input = "Welcome\nThis is a test case";
    str = textToBase64(input);
    assert(strcmp(str,"V2VsY29tZQpUaGlzIGlzIGEgdGVzdCBjYXNl")==0);
    free(str);

    input = "";
    str = textToBase64(input);
    assert(strcmp(str,"")==0);
    free(str);


    printf("textToBase64() pass\n");

}

void check_base64ToText(){
    char* input = "SGVsbG8gV29ybGQ";
    char * str = base64ToText(input);
    assert(strcmp(str,"Hello World")==0);
    free(str);

    input = "V2VsY29tZQpUaGlzIGlzIGEgdGVzdCBjYXNl";
    str = base64ToText(input);
    assert(strcmp(str,"Welcome\nThis is a test case")==0);
    free(str);


    input = "";
    str = base64ToText(input);
    assert(strcmp(str,"")==0);

    printf("base64ToText() pass\n");
}

int main(){
    check_base32toText();
    check_textToBase32();
    check_base64ToText();
    check_textToBase64();
}