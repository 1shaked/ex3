//
//  main.c
//  ex3
//
//  Created by shaked chen on 13/11/2021.
//

#include <stdio.h>
#include <ctype.h>

char ToUpper(char v) {
    int letterAscii = v;
    if (letterAscii > 96 && letterAscii < 123) {
        char upperLetter = letterAscii - 32;
        return upperLetter;
    }
    return letterAscii;
}

int IsCommandValid(int v) {
    return v > -2 && v < 5 && v != 0;
}
int IsNumberValidFromStatus(int v) {
    return v > 0 && v < 10;
}



int main(int argc, const char * argv[]) {
    // get first letter of first and last name
    printf("Hello, what is the first letter of your name?\n");
   
    char firstName;
    char lastName;
    
    scanf(" %c", &firstName);
    scanf(" %c", &lastName);
    // conveting to upper case
    firstName = ToUpper(firstName);
    lastName = ToUpper(lastName);
    
    printf("Hello %c. %c, welcome to Squid Game!\n", firstName, lastName);
    // starting the game
    printf("Choose 1 for Statues, 2 for Dalgona, 3 for Gganbu, 4 for Bridge, -1 for exit\n");

    int userInput = 0;
    scanf("%d", &userInput);
    printf("user input is %d", userInput);
    // printf("%d", Inputs[userInput]);
    enum Inputs {
        Statues = 1,
        Dalgona = 2,
        Gganbu = 3,
        Bridge = 4,
        Exist = -1
    };
    enum Inputs inputUser = userInput;
    printf("%d", inputUser);
    int playersNumber = 456;
    while (inputUser != Exist) {
        // first option
        if (inputUser == Statues) {
            printf("Statues! %d\n", playersNumber);
            printf("Enter 2 numbers (single digit each):\n");
            int firstNumber = 0;
            int secondNumber = 0;
            while (!(IsNumberValidFromStatus(firstNumber) && IsNumberValidFromStatus(secondNumber))) {
                scanf("%d", &firstNumber);
                scanf("%d", &secondNumber);
            }
            // remove players which match that conditions
            int totalToRemove = 0;
            int i = 0;
            for (;i < playersNumber; i++) {
                if (i % firstNumber == 0 || secondNumber % 10 == i ) {
                    totalToRemove = totalToRemove + 1;
                }
            }
            playersNumber = playersNumber - totalToRemove;
            // TODO: calculate the amount to add to each user
            
        }
        
    }
    // int d = int(firstName) - 30 // enum Inputs {Statues = 1, Dalgona = 2, Gganbu = 3, Bridge = 4, Exist = -1};
    // toupper(firstName);
    // toupper(firstName[0])
    // insert code here...
    // printf("Hello, World! %d %c %c \n", asciiFirstName, firstName, t);
    return 0;
}
