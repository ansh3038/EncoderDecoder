#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "enco_deco.h"

void addPadding(char **binary_data, int length)
{
    int remaining_bits = length % 5;
    if (remaining_bits != 0)
    {
        int padding_bits = 5 - remaining_bits;
        char *padded_data = (char *)malloc((length + padding_bits) * sizeof(char));
        memcpy(padded_data, *binary_data, length);
        for (int i = length; i < length + padding_bits; ++i)
        {
            padded_data[i] = '0';
        }
        *binary_data = padded_data;
    }
}

char *string_to_binary(const char *input)
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

    if (strlen(binary_string) % 5 != 0)
    {
        addPadding(&binary_string, strlen(binary_string));
    }

    return binary_string;
}

char base32(int a)
{
    if (a > 31)
    {
        return '=';
    }
    if (a <= 25 && a >= 0)
    {
        return ('A' + a);
    }
    else
    {
        return (a - 24 + '0');
    }
}

char binarysubstring(char *ch, int start)
{
    char subs[5];
    int a = 0;
    int two = 1;
    for (int i = start + 4; i >= start; i--)
    {
        if (ch[i] == '1')
        {
            a += two;
        }
        two *= 2;
    }
    return base32(a);
}

char *textToBase32(const char *input)
{
    int size = sizeof(input) / sizeof(char);
    char *ch = string_to_binary(input);
    printf("%d\n", strlen(ch));
    printf("%s\n", ch);
    char *ans = (char *)malloc(sizeof(ch) / 5 + 8);
    int j = 0;
    for (int i = 0; i < strlen(ch); i = i + 5)
    {
        ans[j++] = binarysubstring(ch, i);
    }
    if (j % 8 != 0)
    {
        while (j % 8 != 0)
        {
            ans[j++] = '=';
        }
    }
    ans[j] = '\0';
    return ans;
}