#include<stdio.h>
void printNamaste();
void printBonjour();


int main() {
    printf("enter f for french & i for indian :");
    char ch;
    scanf("%c", &ch);

    if(ch == 'i') {
        Namaste();
    } else {
        Bonjour();
    }

    return 0;
}

void Namaste() {
    printf("Namaste\n");
}

void Bonjour() {
    printf("Bonjour\n");
}

