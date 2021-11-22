//
//  main.c
//  ex3
//
//  Created by shaked chen on 13/11/2021.
//

#include <stdio.h>
#include <ctype.h>

#define AMOUNT_PER_PLAYER_REMOVED 10000
char ToUpper(char v);
int IsCommandValid(int v);
int IsNumberValidFromStatus(int v);
int AmountToBank(int totalPlayers, int playersRemoved, int bank);
int AmountToCharity(int totalPlayers, int playersRemoved, int bank);
void PrintRepete(int amount, char letter);
void PrintSqure(int size);
void PrintTriangle(int size);
void PrintStart(int size);

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
    printf("user input is %d\n", userInput);
    // printf("%d", Inputs[userInput]);
    enum Inputs {Statues = 1,Dalgona = 2,Gganbu = 3,Bridge = 4,Exist=-1};
    enum Inputs inputUser = userInput;
    printf("%d", inputUser);
    int playersNumber = 456;
    int charity = 0;
    int bank = 0;
    while (inputUser != Exist) {
        // first option
        
        if (inputUser == Statues) {
            //region Status
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
            // the amount to go to charity and bank to move it to be wiht a function
            charity = charity + AmountToCharity(playersNumber, totalToRemove, bank);
            bank = AmountToBank(playersNumber, totalToRemove, bank);
            
        }
        else if (inputUser == Dalgona) {
            printf("Dalgona\n");
            printf("What shape do you want to pick?\n");
            printf("1 – square, 2 – triangle, 3 – star\n");
            int shape;
            scanf("%d", &shape);
            printf("Enter Size (10-20):");
            // gettting the size while the user did not enter number between 10 to 20 re ask him
            int size = 0;
            while (!(size > 9 && size < 21)) {
                scanf("%d", &size);
            }
            switch (shape) {
                case 1:
                    PrintSqure(size);
                    break;
                case 2:
                    PrintTriangle(size);
                    break;
                case 3:
                    PrintStart(size);
                    break;
                default:
                    break;
            }
            // TODO: need to check what to do about the removoal
            int minNumberToRemove = size / 2;
            if (playersNumber >= minNumberToRemove) {
                int upperNumberToRemove = size * size;
                int amountToRemove;
                // calc the amount of players to remove
                if (upperNumberToRemove <= playersNumber) amountToRemove = upperNumberToRemove - minNumberToRemove;
                else amountToRemove = playersNumber - minNumberToRemove;
                playersNumber = playersNumber - amountToRemove;
                // the amount to go to charity and bank to move it to be wiht a function
                charity = charity + AmountToCharity(playersNumber, amountToRemove, bank);
                bank = AmountToBank(playersNumber, amountToRemove, bank);
            }
        }
        else if (inputUser == Gganbu) {
            printf("Gganbu");
            printf("Death number?\n");
            int deathNumber;
            scanf("%d", &deathNumber);
            // logic to remove the amount of players
            int playersToRemove = playersNumber / deathNumber;
            int i = 1;
            for (; i < playersNumber; i++) {
                int mulNumber = deathNumber * i;
                if (mulNumber > playersNumber) break;
            }
            printf("%d amount of players to remove %d", playersToRemove, i); 
            // TODO: need to check if devision is good enough
            playersNumber = playersNumber - i;
            // the amount to go to charity and bank to move it to be wiht a function
            charity = charity + AmountToCharity(playersNumber, i, bank);
            bank = AmountToBank(playersNumber, i, bank); 
        }
        
    }
    // int d = int(firstName) - 30 // enum Inputs {Statues = 1, Dalgona = 2, Gganbu = 3, Bridge = 4, Exist = -1};
    // toupper(firstName);
    // toupper(firstName[0])
    // insert code here...
    // printf("Hello, World! %d %c %c \n", asciiFirstName, firstName, t);
    return 0;
}

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
int AmountToBank(int totalPlayers, int playersRemoved, int bank) {
    int totalBankMoeny = (playersRemoved + totalPlayers) * bank;
    int totalMoeny = playersRemoved * AMOUNT_PER_PLAYER_REMOVED + totalBankMoeny;
    return totalMoeny / totalPlayers ;
}

int AmountToCharity(int totalPlayers, int playersRemoved, int bank) {
    int totalBankMoeny = (playersRemoved + totalPlayers) * bank;
    int totalMoeny = playersRemoved * AMOUNT_PER_PLAYER_REMOVED + totalBankMoeny;
    return totalMoeny % totalPlayers ;
}
void PrintRepete(int amount, char letter) {
    int i = 0;
    for (;i < amount; i++) {
        printf("%c",letter);
    }
}
void PrintSqure(int size) {
    int i = 0;
    char const letter = 'O';
    for (; i < size; i++) {
        
        if( i == 0 || i == size - 1) {
            // printing the line when is the first or the last row
            PrintRepete(size, letter);
        }
        else {
            printf("%c", letter);
            PrintRepete(size-2, '-');
            printf("%c", letter);
        }
        printf("\n");
    }
}
void PrintTriangle(int size) {
    int totalLoopSize = (size * 2) + 1;
    const char sideLetter = 'O';
    int i = 0;
    for (; i < totalLoopSize; i++) {
        if (i == totalLoopSize - 1 || i == 0) {
            // using i in order to avoid nested loop and conditions
            PrintRepete(i + 1, sideLetter);
        } else {
            // calculating how much -- needed for the Triangle
            int fillerAmount = i - 2;
            printf("%c", sideLetter);
            PrintRepete(fillerAmount, '-');
            printf("%c", sideLetter);
        }
        printf("\n");
    }
}
void PrintStarLine(int size, int row) {
    if (row == 1) {
        PrintRepete(size - 1, '-');
        printf("O");
        PrintRepete(size - 1, '-');
    } else if (row == 2) {
        PrintRepete(size - 2, '-');
        printf("O-O");
        PrintRepete(size - 2, '-');
    } else if (row == 4) {
        printf("-O");
        PrintRepete((size * 2) - 5, '-');
        printf("O-");
    }
    else if (row == 5) {
        printf("--O");
        PrintRepete((size * 2) - 7, '-');
        printf("O--");
    }
    printf("\n");
    
}
void PrintStart(int size) {
    int rowLen = (size * 2) - 1;
    PrintStarLine(size, 1);
    PrintStarLine(size, 2);
    PrintRepete(rowLen, 'O');
    printf("\n");
    PrintStarLine(size, 4);
    PrintStarLine(size, 5);
    PrintStarLine(size, 4);
    PrintRepete(rowLen, 'O');
    printf("\n");
    PrintStarLine(size, 2);
    PrintStarLine(size, 1);
}
