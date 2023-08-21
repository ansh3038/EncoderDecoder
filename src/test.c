#include <stdio.h>
#include <string.h>
#include "enco_deco.c"
#include <assert.h>
int main()
{
    char ch[] = "00010";
    assert(binarysubstring(ch, 0) == 'C');
    assert(base32(28) == '4');
    assert(base32(2) == 'C');
    assert(base32(32) == '=');
    assert(base32(20) == 'U');
    char *ch1 = "11";
    char *str = "Hello World";
    ch1 = textToBase32(str);
    printf("%s", ch1);
    free(ch1);

    // addPadding(&ch1,strlen(ch1));
    // printf("%s",ch1);
}