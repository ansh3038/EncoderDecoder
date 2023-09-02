#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "enco_deco.h"

// General File Functions

char *inputFile(FILE *file)
{
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(file_size + 1);
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    return content;
}

void closeFile(char *fileName, char *str)
{
    FILE *ans = fopen(fileName, "w");
    fprintf(ans, "%s", str);
    free(str);
    fclose(ans);
}

// ENCODING FUNCTIONS

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
        free(*binary_data);                        // Free the original data
        *binary_data = padded_data;
        *binary_data = padded_data;
    }
}

char *textToBinary(const char *input)
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
    return binary_string;
}

char base32(int a)
{
    if (a > 31)
    {
        return '\0';
    }
    char *anskey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    return anskey[a];
}

char base64(int a)
{
    if (a > 63)
    {
        return '\0';
    }
    char *anskey = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    return anskey[a];
}

char binarysubstring(char *ch, int start, int base)
{
    int a = 0;
    int two = 1;
    for (int i = start + base - 1; i >= start; i--)
    {
        if (ch[i] == '1')
        {
            a += two;
        }
        two *= 2;
    }
    if (base == 5)
        return base32(a);
    else if (base == 6)
    {
        return base64(a);
    }
    else
    {
        return '\0';
    }
}

char *textToBase32(const char *input)
{
    char *ch = textToBinary(input);
    if (strlen(ch) % 5 != 0)
    {
        addPadding(&ch, strlen(ch), 5);
    }
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

void textToBase32File(FILE *file, char *fileName)
{
    char *content = inputFile(file);
    // printf("\n%s.", content);
    char *str = textToBase32(content);
    closeFile(fileName, str);
    free(content);
    fclose(file);
}

char *textToBase64(const char *input)
{
    char *ch = textToBinary(input);
    if (strlen(ch) % 6 != 0)
    {
        addPadding(&ch, strlen(ch), 6);
    }
    char *ans = (char *)malloc(strlen(ch) / 6 * 4 + 5);
    int j = 0;
    for (int i = 0; i < strlen(ch); i = i + 6)
    {
        ans[j++] = binarysubstring(ch, i, 6);
    }
    while (j % 4 != 0 && j % 8 != 0)
    {
        ans[j++] = '=';
    }
    ans[j] = '\0';
    free(ch);
    return ans;
}

void textToBase64File(FILE *file, char *fileName)
{
    char *content = inputFile(file);
    char *str = textToBase64(content);
    closeFile(fileName, str);
    free(content);
    fclose(file);
}

// DECODING FUNCTIONS

int base32ToAscii(char c)
{
    char *anskey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    for (int i = 0; i < strlen(anskey); i++)
    {
        if (anskey[i] == c)
        {
            return i;
        }
    }
    return -1;
}

int base64ToAscii(char c)
{
    char *anskey = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (int i = 0; i < strlen(anskey); i++)
    {
        if (anskey[i] == c)
        {
            return i;
        }
    }
    return -1;
}

char binaryToASCII(char *binarysubstring, int start)
{
    int a = 0;
    int two = 1;
    for (int i = start + 7; i >= start; i--)
    {
        if (binarysubstring[i] == '1')
        {
            a += two;
        }
        two *= 2;
    }
    return a;
}

char *base32ToText(const char *input)
{
    int size = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '=')
        {
            break;
        }
        else
        {
            size++;
        }
    }

    char *binaryString = (char *)malloc(size * sizeof(char) * 8);

    for (int i = 0; i < size; i++)
    {

        int ascii = base32ToAscii(input[i]);

        for (int j = 4; j >= 0; --j)
        {
            binaryString[i * 5 + (4 - j)] = (ascii & (1 << j)) ? '1' : '0';
        }
    }

    char *ans = (char *)(malloc(strlen(binaryString) * sizeof(char) + 1));
    int j = 0;

    for (int i = 0; i < strlen(binaryString); i += 8)
    {
        ans[j++] = binaryToASCII(binaryString, i);
    }
    ans[j] = '\0';
    free(binaryString);

    return ans;
}

void base32ToTextFile(FILE *file, char *fileName)
{
    char *content = inputFile(file);
    char *str = base32ToText(content);
    closeFile(fileName, str);
    free(content);
    fclose(file);
}

char *base64ToText(const char *input)
{
    int size = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '=')
        {
            break;
        }
        else
        {
            size++;
        }
    }

    char *binaryString = (char *)malloc(size * sizeof(char) * 6);

    for (int i = 0; i < size; i++)
    {

        int ascii = base64ToAscii(input[i]);

        for (int j = 5; j >= 0; --j)
        {
            binaryString[i * 6 + (5 - j)] = (ascii & (1 << j)) ? '1' : '0';
        }
    }

    char *ans = (char *)(malloc(size * sizeof(char)));
    int j = 0;

    for (int i = 0; i < strlen(binaryString); i += 8)
    {
        ans[j++] = binaryToASCII(binaryString, i);
    }
    ans[j] = '\0';
    free(binaryString);

    return ans;
}

void base64ToTextFile(FILE *file, char *fileName)
{
    char *content = inputFile(file);
    char *str = base64ToText(content);
    closeFile(fileName, str);
    free(content);
    fclose(file);
}

// int main(){
//     char * str = "Hello World";
//     char * ans = textToBase32(str);
//     printf("%s",ans);
//     free(ans);
// }