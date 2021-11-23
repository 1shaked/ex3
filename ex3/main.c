//
//  main.c
//  ex3
//
//  Created by shaked chen on 13/11/2021.
//

#include <stdio.h>
// #include <ctype.h>
#include <math.h>

#define AMOUNT_PER_PLAYER_REMOVED 10000
char ToUpper(char v);
int IsCommandValid(int v);
int IsNumberValidFromStatus(int v);
int AmountToBank(int totalPlayers, int playersRemoved, int bank , int charity);
int AmountToCharity(int totalPlayers, int playersRemoved, int bank, int charity);
void PrintRepete(int amount, char letter);
void PrintSqure(int size);
void PrintStart(int size);
void PrintTriangle(int size);
int GetMersenneNumber(int limit, int startAt, int includeLimit);


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
    int playersNumber = 456;
    int charity = 0;
    int bank = 0;
    while (inputUser != Exist) {
        int totalToRemove = 0;
        int tempCharity;
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
            int i = 0;
            for (;i < playersNumber; i++) {
                int reminder = i % firstNumber;
                int digit = i % 10;
                if (reminder == 0 ||  digit == secondNumber ) {
                    totalToRemove = totalToRemove + 1;
                }
            }
            playersNumber = playersNumber - totalToRemove;
            // the amount to go to charity and bank to move it to be wiht a function
            tempCharity = charity;
            charity = AmountToCharity(playersNumber, totalToRemove, bank, charity);
            bank = AmountToBank(playersNumber, totalToRemove, bank, tempCharity);
        }
        else if (inputUser == Dalgona) {
            printf("Dalgona\n");
            printf("What shape do you want to pick?\n");
            printf("1 – square, 2 – triangle, 3 – star\n");
            int shape;
            scanf("%d", &shape);
            printf("Enter Size (10-20):\n");
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
            int minNumberToRemove = size / 2 + 1;
            int remainPlayers = 0;
            // TODO: fix the filtring
            if (playersNumber >= minNumberToRemove) {
                int upperNumberToRemove = size * size;
                // int amountToRemove;
                // calc the amount of players to remove
                if (upperNumberToRemove <= playersNumber) remainPlayers = upperNumberToRemove - minNumberToRemove + 1;
                else remainPlayers = playersNumber - minNumberToRemove + 1;
                totalToRemove = playersNumber - remainPlayers;
                playersNumber = playersNumber - totalToRemove;
                // the amount to go to charity and bank to move it to be wiht a function
                tempCharity = charity;
                charity = AmountToCharity(playersNumber, totalToRemove, bank, charity);
                bank = AmountToBank(playersNumber, totalToRemove, bank, tempCharity);
            }
        }
        else if (inputUser == Gganbu) {
            printf("Gganbu\n");
            printf("Death number?\n");
            int deathNumber;
            scanf("%d", &deathNumber);
            // TODO: need to check what to do when the input is zero; if (deathNumber == 0 ) playersToRemove = 0;
            // logic to remove the amount of players
            int playersRemin = playersNumber / deathNumber;
            totalToRemove = playersNumber - playersRemin;
            playersNumber = playersRemin;
            // the amount to go to charity and bank to move it to be wiht a function
            tempCharity = charity;
            charity = AmountToCharity(playersNumber, totalToRemove, bank, charity);
            bank = AmountToBank(playersNumber, totalToRemove, bank, tempCharity);
        }
        else if (inputUser == Bridge) {
            printf("Bridge!\n");
            printf("Enter two numbers:\n");
            // temp is needed in order to get the min and the max from num1 and num2
            int minNumber, maxNumber;
            scanf("%d %d", &minNumber, &maxNumber);
            if (minNumber > maxNumber) {
                // when the input is first the big number and then the smaller one
                int temp = maxNumber;
                maxNumber = minNumber;
                minNumber = temp;
            }
            // when there less players then the number inputed
            if (maxNumber > playersNumber) maxNumber = playersNumber;
            int playersToRemove, playersRemain = 0;
            if (minNumber > playersNumber) {
                playersToRemove = playersNumber;
            } else {
                // in order to calculate the amount of players remin
                int minMersenneNumber = GetMersenneNumber(minNumber, 0 , 1);
                int maxMersenneNumber = GetMersenneNumber(maxNumber, minMersenneNumber , 0);
                // calculate how many players remain and handle the edge case when there is no Mersenne in range
                if (minMersenneNumber > maxMersenneNumber) {
                    printf("None");
                    playersRemain = 0;
                } else playersRemain = maxMersenneNumber - minMersenneNumber + 1;
                playersToRemove = playersNumber - playersRemain;
            }
            // the amount to go to charity and bank to move it to be wiht a function
            playersNumber = playersNumber - playersToRemove;
            tempCharity = charity;
            charity = AmountToCharity(playersNumber, playersToRemove, bank, charity);
            bank = AmountToBank(playersNumber, playersToRemove, bank, tempCharity);
        }
        printf("There are %d survival(s), and they got %d each. The amount of the rest is: %d$.\n", playersNumber, bank, charity);
        printf("Choose 1 for Statues, 2 for Dalgona, 3 for Gganbu, 4 for Bridge, -1 for exit\n");
        if (playersNumber == 0) break;
        userInput = 0;
        scanf("%d", &userInput);
        inputUser = userInput;
    }
    printf("Thank for playing");
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
int AmountToBank(int totalPlayers, int playersRemoved, int bank, int charity) {
    // calc the amount of moeny before the removal;
    int totalBankMoeny = ( (playersRemoved + totalPlayers) * bank) + charity;
    int totalMoeny = playersRemoved * AMOUNT_PER_PLAYER_REMOVED + totalBankMoeny;
    return totalMoeny / totalPlayers ;
}

int AmountToCharity(int totalPlayers, int playersRemoved, int bank, int charity) {
    int totalBankMoeny = (playersRemoved + totalPlayers) * bank + charity;
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
int GetMersenneNumber(int limit, int startAt, int includeLimit) {
    int n = startAt;
    while (pow(2, n) - 1 < limit) {
        n++;
    }
    if (!includeLimit) {
        if (pow(2, n) - 1 == limit) return n;
        return n - 1;
    }
    return n;
}
