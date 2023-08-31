#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "../src/enco_deco.c"

int check_base32_base64()
{
    assert(base32(0) == 'A');
    assert(base32(1) == 'B');
    assert(base32(15) == 'P');
    assert(base32(25) == 'Z');
    assert(base32(26) == '2');
    assert(base32(31) == '7');
    assert(base32(32) == '\0');

    assert(base64(0) == 'A');
    assert(base64(1) == 'B');
    assert(base64(25) == 'Z');
    assert(base64(26) == 'a');
    assert(base64(51) == 'z');
    assert(base64(62) == '+');
    assert(base64(63) == '/');

    printf("base32() pass\nbase64() pass\n");
}

void check_baseToAscii()
{
    assert(base32ToAscii('A') == 0);
    assert(base32ToAscii('B') == 1);
    assert(base32ToAscii('Z') == 25);
    assert(base32ToAscii('2') == 26);
    assert(base32ToAscii('7') == 31);
    assert(base32ToAscii('P') == 15);
    assert(base32ToAscii('=') == -1);

    assert(base64ToAscii('A') == 0);
    assert(base64ToAscii('B') == 1);
    assert(base64ToAscii('Z') == 25);
    assert(base64ToAscii('a') == 26);
    assert(base64ToAscii('z') == 51);
    assert(base64ToAscii('0') == 52);
    assert(base64ToAscii('+') == 62);
    printf("basetoASCII() pass\n");
}

void check_binaryToASCII()
{
    char *str = "0100100001100101011011000110110001101111001000000101011101101111011100100110110001100100";
    assert(binaryToASCII(str, 0) == 'H');
    assert(binaryToASCII(str, 8) == 'e');
    assert(binaryToASCII(str, 16) == 'l');
    assert(binaryToASCII(str, 24) == 'l');
    assert(binaryToASCII(str, 32) == 'o');
    assert(binaryToASCII(str, 40) == ' ');
    assert(binaryToASCII(str, 48) == 'W');
    assert(binaryToASCII(str, 56) == 'o');
    assert(binaryToASCII(str, 64) == 'r');
    assert(binaryToASCII(str, 72) == 'l');
    assert(binaryToASCII(str, 80) == 'd');
    printf("binaryToASCII() pass\n");
}

void check_addPadding()
{
    char* binary = malloc(sizeof(char)*15);
    char *binary1 = "10101010";
    strcpy(binary,binary1);
    int length1 = strlen(binary1);
    addPadding(&binary, length1, 5);

    assert(strcmp(binary, "1010101000") == 0);
    

    char *binary2 = "110110";
    strcpy(binary,binary2);

    int length2 = strlen(binary2);
    addPadding(&binary, length2, 8);
    assert(strcmp(binary, "11011000") == 0);

    char *binary3 = "1010101";
    strcpy(binary,binary3);

    int length3 = strlen(binary3);
    addPadding(&binary, length3, 8);
    assert(strcmp(binary, "10101010") == 0);

    char *binary4 = "110110";
    strcpy(binary,binary4);

    int length4 = strlen(binary4);
    addPadding(&binary, length4, 6);
    assert(strcmp(binary, "110110") == 0);
    free(binary);
    printf("addPadding() pass\n");

}

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

int compareFiles(FILE *fp1, FILE *fp2)
{
    char ch1 = getc(fp1);
    char ch2 = getc(fp2);
  
    int error = 0, pos = 0, line = 1;
  
    while (ch1 != EOF && ch2 != EOF)
    {
        pos++;
  
        if (ch1 == '\n' && ch2 == '\n')
        {
            line++;
            pos = 0;
        }
  
        if (ch1 != ch2)
        {
           return 0; 
        }
  
        ch1 = getc(fp1);
        ch2 = getc(fp2);
    }
  
    return 1;
}

void check_textToBase32File(){
    FILE *input1 = fopen("input1.txt","r");
    textToBase32File(input1,"output.txt");
    sleep(1);
    FILE *output = fopen("output.txt","r");
    FILE *output1 = fopen("output1.txt","r");
    assert(compareFiles(output1,output)==1);
    // input
    fclose(input1);
    // fclose(output);
    fclose(output1);
    sleep(1);
    FILE *input = fopen("input2.txt","r");
    textToBase32File(input1,"output.txt");
    // sleep(1);
    // // FILE *output = fopen("output.txt","r");
    FILE *output2 = fopen("output1.txt","r");
    assert(compareFiles(output2,output)==1);


    printf("textToBase32File() pass\n");

}

int main()
{
    check_base32_base64();
    check_baseToAscii();
    check_binaryToASCII();
    check_addPadding();
    check_textToBase32();
    check_base32toText();
    check_textToBase64();
    check_base64ToText();
    check_textToBase32File();
}