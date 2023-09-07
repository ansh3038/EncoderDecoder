#include<stdio.h>
#include<string.h>
#include "../include/enco_deco.h"

int main(){
    FILE* file = fopen("","r");

    char *string = "Hello World";
    char *ans = textToBase32(string);
    printf("%s",ans);
    free(ans);
    fclose(file);

}