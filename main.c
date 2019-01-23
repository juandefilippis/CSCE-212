//
//  main.c
//  Hw1
//
//  Created by Juan De filippis on 1/22/19.
//  Copyright © 2019 Juan De filippis. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Welcome to HW1!\n");
    // Declaring the variables
    int a;
    int b;
    printf("Enter the first integer:");
    // Taking the first variable
    scanf("%d", &a);
    printf("Enter the second integer:");
    // Taking the second variable
    scanf("%d", &b);
    // Results of the operations 
    printf("Printing out the & of these two integer %d\n" , a&b);
    printf("Printing out the | of these two integer %d\n" , a|b);
    printf("Printing out the ^ of these two integer %d\n" , a^b);
    printf("Printing out the >> of these two integer %d\n" , a>>2);
    printf("Printing out the << of these two integer %d\n" , a<<2);
    printf("Printing out the ~ of these two integer %d\n", ~a);
    return 0;
}
