#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// #include "enco_deco.h"

void addPadding(char **binary_data, int length, int base)
{
    int remaining_bits = length % base;
    if (remaining_bits != 0)
    {
        int padding_bits = base - remaining_bits;
        char *padded_data = (char *)malloc((length + padding_bits) * sizeof(char));
        memcpy(padded_data, *binary_data, length);
        for (int i = length; i < length + padding_bits; ++i)
        {
            padded_data[i] = '0';
        }
        padded_data[length + padding_bits] = '\0'; // Null-terminate the string
        free(*binary_data); // Free the original data
        *binary_data = padded_data;*binary_data = padded_data;
    }
    printf("%d\n",strlen(*binary_data));
}

char *text_to_binary(const char *input, int base)
{
    int len = strlen(input);
    char *binary_string = (char *)malloc((len * 8 + 1) * sizeof(char));

    for (int i = 0; i < len; ++i)
    {
        char ch = input[i];
        for (int j = 7; j >= 0; --j)
        {
            binary_string[i * 8 + (7 - j)] = (ch & (1 << j)) ? '1' : '0';
        }
    }
    binary_string[len * 8] = '\0';

    if (strlen(binary_string) % base != 0)
    {
        addPadding(&binary_string, strlen(binary_string), base);
    }

    return binary_string;
}

char base32(int a)
{
    char* anskey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    return anskey[a];
}

char base64(int a){
    char* anskey = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    return anskey[a];
}

char binarysubstring(char *ch, int start, int base)
{
    int a = 0;
    int two = 1;
    for (int i = start + base-1; i >= start; i--)
    {
        if (ch[i] == '1')
        {
            a += two;
        }
        two *= 2;
    }
    if( base == 5)
    return base32(a);
    else if(base == 6){
        return base64(a);
    }
    else{
        return '\0';
    }
}

char *textToBase32(const char *input)
{
    char *ch = text_to_binary(input, 5);
    char *ans = (char *)malloc(strlen(ch) / 5 + 9);
    int j = 0;
    for (int i = 0; i < strlen(ch); i = i + 5)
    {
        ans[j++] = binarysubstring(ch, i, 5);
    }
    if (j % 8 != 0)
    {
        while (j % 8 != 0)
        {
            ans[j++] = '=';
        }
    }
    ans[j] = '\0';
    free(ch);
    return ans;
}

int base32_to_ascii(char c)
{
    int ans;
    if (c == '=')
    {
        ans=32;
    }
    else if (c <= 'Z' && c >= 'A')
    {
        ans=c - 'A';
    }
    else{
    ans = c - '0' + 24;
    }
    return ans;

}

char binaryToASCII( char* binarysubstring, int start){
    int a = 0;
    int two = 1;
    for(int i=start+7; i>=start; i--){
        if(binarysubstring[i]=='1'){
            a += two;
        }
        two *=2;
    }
    return a;
}

char* base32ToText(const char* input){
    int size=0;

    for(int i=0;i<strlen(input);i++){
        if(input[i]=='='){
            break;
        }
        else{
            size++;
        }
    }

    char* binaryString = (char*)malloc(size*sizeof(char)*8);

    for(int i=0; i<size;i++){

        int ascii = base32_to_ascii(input[i]);

        for (int j = 4; j >= 0; --j)
        {
            binaryString[i * 5 + (4 - j)] = (ascii & (1 << j)) ? '1' : '0';
        }

    }

    char* ans = (char*) (malloc(strlen(binaryString)*sizeof(char)+1));
    int j = 0;

    for(int i =0; i<strlen(binaryString); i+=8){
        ans[j++] = binaryToASCII(binaryString,i);
    }
    ans[j]='\0';
    free(binaryString);

    return ans;
}

char* textToBase64( const char* input){
    char* ch = text_to_binary(input,6);
    char* ans = (char*) malloc(strlen(ch)/6*4 + 5);
    int j = 0;
    for( int i = 0; i<strlen(ch); i = i+6){
        ans[j++] = binarysubstring(ch,i,6);
    } 
    while (j % 4 != 0 && j % 8 != 0) {
        ans[j++] = '=';
    }
    ans[j] = '\0';
    free(ch);
    return ans;
}

void textToBase32File(FILE *file, char* fileName){
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(file_size + 1); 
    fread(content, 1, file_size, file);
    content[file_size] = '\0';
    printf("\n%s.",content);
    char* str = textToBase32(content);
    FILE *ans = fopen(fileName,"w");
    fprintf(ans,"%s",str);
    
    free(str);
    fclose(ans);
    fclose(file);

}




int main()
{
    char ch[] = "00010";
    assert(binarysubstring(ch, 0,5) == 'C');
    assert(base32(28) == '4');
    assert(base32(2) == 'C');
    // assert(base32(32) == '=');
    assert(base32(20) == 'U');
    char *ch1 = "11";
    char *str = "Hello World\nI am Ansh Singla";
    char c = ' ';
    ch1 = textToBase32(str);
    printf("%s\n", ch1);
    // int a = base32_to_ascii('2');
    // str = base32ToText(ch1);
    // printf("\n%s.",str);
    char* ch64 = textToBase64(str);
    printf("\n%s",ch64);
    FILE *file = fopen("input.txt","r");
    textToBase32File(file,"output.txt");
    fclose(file);
    free(ch64);
    free(str);
    free(ch1);

}