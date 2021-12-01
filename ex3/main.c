/******************************************
* Shaked Chen
* 207253220
* 83-120-01
* Ex 2
******************************************/

#include <stdio.h>
#include <math.h>

#define AMOUNT_PER_PLAYER_REMOVED 10000
char ToUpper(char v);
int IsNumberValidFromStatus(int v);
int AmountToBank(int totalPlayers, int playersRemoved, int bank , int charity);
int AmountToCharity(int totalPlayers, int playersRemoved, int bank, int charity);
void PrintRepeate(int amount, char letter);
void PrintSquare(int size);
void PrintStart(int size);
void PrintTriangle(int size);
int GetMersenneNumber(int limit, int startAt, int includeLimit);

int main(int argc, const char * argv[]) {
    // get first letter of first and last name
    printf("Hello, what is the first letter of your name?\n");
    char firstName;
    char lastName;
    scanf("%c %c", &firstName, &lastName);
    // conveting to upper case
    firstName = ToUpper(firstName);
    lastName = ToUpper(lastName);
    printf("Hello %c. %c, welcome to Squid Game!\n", firstName, lastName);
    // starting the game
    printf("Choose 1 for Statues, 2 for Dalgona, 3 for Gganbu, 4 for Bridge, -1 for exit\n");
    int userInput = 0;
    scanf("%d", &userInput);
    // enum Inputs {Statues = 1,Dalgona = 2,Gganbu = 3,Bridge = 4,Exist=-1};
    // enum Inputs inputUser = userInput;
    while (userInput != -1) {
        int playersNumber = 456;
        int charity = 0;
        int bank = 0;
        int totalToRemove = 0;
        int tempCharity;
        if (userInput == 1) {
            //region Status
            printf("Statues!\n");
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
        }
        else if (userInput == 2) {
            printf("Dalgona!\n");
            printf("What shape do you want to pick?\n");
            printf("1 - square, 2 - triangle, 3 - star\n");
            int shape;
            scanf("%d", &shape);
            printf("Enter size (10-20):\n");
            // getting the size while the user did not enter number between 10 to 20 re ask him
            int size = 0;
            while (!(size > 9 && size < 21)) {
                scanf("%d", &size);
            }
            switch (shape) {
                case 1:
                    PrintSquare(size);
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
            if (playersNumber >= minNumberToRemove) {
                int upperNumberToRemove = size * size;
                // calc the amount of players to remove
                if (upperNumberToRemove <= playersNumber) remainPlayers = upperNumberToRemove - minNumberToRemove + 1;
                else remainPlayers = playersNumber - minNumberToRemove + 1;
                totalToRemove = playersNumber - remainPlayers;
                playersNumber = playersNumber - totalToRemove;
            }
        }
        else if (userInput == 3) {
            printf("Gganbu!\n");
            printf("Death number?\n");
            int deathNumber;
            scanf("%d", &deathNumber);
            // TODO: need to check what to do when the input is zero; if (deathNumber == 0 ) playersToRemove = 0;
            // logic to remove the amount of players
            int playersRemin = playersNumber / deathNumber;
            totalToRemove = playersNumber - playersRemin;
            playersNumber = playersRemin;
        }
        else if (userInput == 4) {
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
            int playersRemain = 0;
            
            if (minNumber > playersNumber) {
                totalToRemove = playersNumber;
                printf("None\n");
            }
            else {
                // in order to calculate the amount of players remin
                int minMersenneNumber = GetMersenneNumber(minNumber, 0 , 1);
                int maxMersenneNumber = GetMersenneNumber(maxNumber, minMersenneNumber , 0);
                // calculate how many players remain and handle the edge case when there is no Mersenne in range
                if (minMersenneNumber > maxMersenneNumber) {
                    printf("None\n");
                    playersRemain = 0;
                } else {
                    playersRemain = maxMersenneNumber - minMersenneNumber + 1;
                    int i = minMersenneNumber;
                    for (; i < maxMersenneNumber + 1; i++) {
                        int number = pow(2, i) - 1;
                        printf("%d\n", number);
                    }
                }
                totalToRemove = playersNumber - playersRemain;
            }
            // the amount to go to charity and bank to move it to be wiht a function
            playersNumber = playersNumber - totalToRemove;
        }
        // the amount to go to charity and bank
        tempCharity = charity;
        charity = AmountToCharity(playersNumber, totalToRemove, bank, charity);
        bank = AmountToBank(playersNumber, totalToRemove, bank, tempCharity);
        printf("There are %d survival(s), and they got %d$ each. The amount of the rest is: %d$.\n", playersNumber, bank, charity);
        // reget the user input
        printf("Choose 1 for Statues, 2 for Dalgona, 3 for Gganbu, 4 for Bridge, -1 for exit\n");
        // if (playersNumber == 0) break;
        // userInput = 0;
        scanf("%d", &userInput);
        // inputUser = userInput;
    }
    printf("Thank you, %c. %c, have a nice day, the World is Fair!\n", firstName, lastName);
    return 0;
}

/*************************************************************************
Function name: ToUpper
Input: char
Output: char
The function operation: take in char and make it upper case a to A
************************************************************************/
char ToUpper(char v) {
    int letterAscii = v;
    if (letterAscii > 96 && letterAscii < 123) {
        char upperLetter = letterAscii - 32;
        return upperLetter;
    }
    return letterAscii;
}
/*************************************************************************
Function name: IsNumberValidFromStatus
Input: int
Output: int
The function operation: return true/1 if the inputed number is valid for the Status
************************************************************************/
int IsNumberValidFromStatus(int v) {
    return v > 0 && v < 10;
}
/*************************************************************************
Function name: AmountToBank
Input: int totalPlayers, int playersRemoved, int bank, int charity
Output: int
The function operation: Calc the amount of money the bank will have
************************************************************************/
int AmountToBank(int totalPlayers, int playersRemoved, int bank, int charity) {
    // calc the amount of moeny before the removal;
    int totalBankMoney = ( (playersRemoved + totalPlayers) * bank) + charity;
    int totalMoney = playersRemoved * AMOUNT_PER_PLAYER_REMOVED + totalBankMoney;
    if (totalPlayers == 0) return 0;
    return totalMoney / totalPlayers ;
}
/*************************************************************************
Function name: AmountToCharity
Input: int totalPlayers, int playersRemoved, int bank, int charity
Output: int
The function operation: Calc the amount of moeny the Charity will have
************************************************************************/
int AmountToCharity(int totalPlayers, int playersRemoved, int bank, int charity) {
    int totalBankMoney = (playersRemoved + totalPlayers) * bank + charity;
    int totalMoney = playersRemoved * AMOUNT_PER_PLAYER_REMOVED + totalBankMoney;
    if (totalPlayers == 0) return totalMoney;
    return totalMoney % totalPlayers ;
}
/*************************************************************************
Function name: PrintRepeate
Input: int amount, char letter
Output: void
The function operation: Print the inputed letter the amount of time inputed in the same line
************************************************************************/
void PrintRepeate(int amount, char letter) {
    int i = 0;
    for (;i < amount; i++) {
        printf("%c",letter);
    }
}
/*************************************************************************
Function name: PrintSquare
Input: int size
Output: void
The function operation: Print the Squre for the giving size.
************************************************************************/
void PrintSquare(int size) {
    int i = 0;
    char const letter = 'O';
    for (; i < size; i++) {
        
        if( i == 0 || i == size - 1) {
            // printing the line when is the first or the last row
            PrintRepeate(size, letter);
        }
        else {
            printf("%c", letter);
            PrintRepeate(size-2, '-');
            printf("%c", letter);
        }
        printf("\n");
    }
}
/*************************************************************************
Function name: PrintTriangle
Input: int size
Output: void
The function operation: Print the Triangle for the giving size
************************************************************************/
void PrintTriangle(int size) {
    int totalLoopSize = (size * 2) + 1;
    const char sideLetter = 'O';
    int i = 0;
    for (; i < totalLoopSize; i++) {
        if (i == totalLoopSize - 1 || i < 2) {
            // using i in order to avoid nested loop and conditions
            PrintRepeate(i + 1, sideLetter);
        } else {
            // calculating how much -- needed for the Triangle
            int fillerAmount = i - 1;
            printf("%c", sideLetter);
            PrintRepeate(fillerAmount, '-');
            printf("%c", sideLetter);
        }
        printf("\n");
    }
}
/*************************************************************************
Function name: StarLine
Input: int size
Output: void
The function operation: Print the Star line base in the row type
************************************************************************/
void PrintStarLine(int size, int row) {
    if (row == 1) {
        // full of -- and one O
        PrintRepeate(size - 1, '-');
        printf("O");
        PrintRepeate(size - 1, '-');
    } else if (row == 2) {
        // the expected print is -----o-o-----
        PrintRepeate(size - 2, '-');
        printf("O-O");
        PrintRepeate(size - 2, '-');
    } else if (row == 4) {
        // expected -o-------o-
        printf("-O");
        PrintRepeate((size * 2) - 5, '-');
        printf("O-");
    }
    else if (row == 5) {
        // expected --o-------o--
        printf("--O");
        PrintRepeate((size * 2) - 7, '-');
        printf("O--");
    }
    printf("\n");
    
}
/*************************************************************************
Function name: PrintStart
Input: int size
Output: void
The function operation: Print the Star shape
************************************************************************/
void PrintStart(int size) {
    int rowLen = (size * 2) - 1;
    PrintStarLine(size, 1);
    PrintStarLine(size, 2);
    PrintRepeate(rowLen, 'O');
    printf("\n");
    PrintStarLine(size, 4);
    PrintStarLine(size, 5);
    PrintStarLine(size, 4);
    PrintRepeate(rowLen, 'O');
    printf("\n");
    PrintStarLine(size, 2);
    PrintStarLine(size, 1);
}
/*************************************************************************
Function name: GetMersenneNumber
Input: int limit, int startAt, int includeLimit
Output: void
The function operation: This function will calculate the power of the number needed for the Mersenn number. StartAt param is in order to improve preformance and lower the loop count
Example: limit = 10 startAt = 0 includeLimit = 0 will return 3 because the highest Mersenn number is 7.
Example: limit = 33 startAt = 2 includeLimit = 1 will return 6  because the highest Mersenn included in this limit is 63.
************************************************************************/
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
