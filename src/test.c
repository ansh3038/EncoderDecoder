#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void measure( char* ch){
    int a = 0;
    for(int j = 0; j<strlen(ch); j+=5){
        
    for(int i =4; i>=0;i--){
        if(ch[j+i]=='1'){
            a = 1<<i | a; 
        }
        else{
            // a = a<<1;
        }
    }
    }
    printf("%d",a);
}

int main(){
    char * test_string = "Hello World";
    char* ch = "10010";
    measure(ch);
}