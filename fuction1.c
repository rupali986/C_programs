#include<stdio.h>
void printHello();
void printGoodbye();

int main() {
   printHello(); //fuction call
   printGoodbye();
   return 0;
}

// fuction defination
void printHello() {
     printf("Hello!\n");
    
}
 
void printGoodbye() {
    printf("Goodbye :)\n");
}