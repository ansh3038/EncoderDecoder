#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
}

void check_addPadding(){

    char *binary1 = "10101010";
    int length1 = strlen(binary1);
    addPadding(&binary1, length1, 8);
    assert(strcmp(binary1, "10101010") == 0);

    char *binary2= "110110";
    int length2 = strlen(binary2);
    addPadding(&binary2, length2, 8);
    assert(strcmp(binary2, "11011000") == 0);

    char *binary3= "10101010";
    int length3 = strlen(binary3);
    addPadding(&binary3, length3, 16);
    assert(strcmp(binary3, "10101010") == 0);

    char *binary4= "110110";
    int length4 = strlen(binary4);
    addPadding(&binary4, length4, 16);
    assert(strcmp(binary4, "1101100000000000") == 0);

    char *binary5= "";
    int length5 = strlen(binary5);
    addPadding(&binary5, length5, 8);
    assert(strcmp(binary5, "00000000") == 0);

    char *binary6= "";
    int length6 = strlen(binary6);
    addPadding(&binary6, length6, 16);
    assert(strcmp(binary6, "0000000000000000") == 0);

    char *binary7= "1";
    int length7 = strlen(binary7);
    addPadding(&binary7, length7, 8);
    assert(strcmp(binary7, "10000000") == 0);

    char *binary8= "1";
    int length8 = strlen(binary8);
    addPadding(&binary8, length8, 16);
    assert(strcmp(binary8, "1000000000000000") == 0);

    char *binary9= "110";
    int length9 = strlen(binary9);
    addPadding(&binary9, length9, 8);
    assert(strcmp(binary9, "11000000") == 0);

    char *binary10 = "110";
    int length10 = strlen(binary10);
    addPadding(&binary10, length10, 16);
    assert(strcmp(binary10, "1100000000000000") == 0);

    char *binary11 = "10101";
    int length11 = strlen(binary11);
    addPadding(&binary11, length11, 5);
    assert(strcmp(binary11, "10101") == 0);

    char *binary12 = "1010";
    int length12 = strlen(binary12);
    addPadding(&binary12, length12, 5);
    assert(strcmp(binary12, "1010") == 0);

    char *binary13 = "1111";
    int length13 = strlen(binary13);
    addPadding(&binary13, length13, 5);
    assert(strcmp(binary13, "1111") == 0);

    char *binary14 = "101010";
    int length14 = strlen(binary14);
    addPadding(&binary14, length14, 4);
    assert(strcmp(binary14, "101010") == 0);

    char *binary15 = "1010";
    int length15 = strlen(binary15);
    addPadding(&binary15, length15, 4);
    assert(strcmp(binary15, "1010") == 0);
}

int main()
{
    check_base32_base64();
    check_baseToAscii();
    check_binaryToASCII();
    check_addPadding();
}