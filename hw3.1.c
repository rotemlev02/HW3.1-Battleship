#include <stdio.h>
#include <stdbool.h>

#define ROWS 8
#define COLS 8
#define NUM_OF_BOARDS 5
#define SUBMARINE 'S'
#define EMPTY '~'
#define HIDDEN ' '

// Function Declarations
void print_welcome_message();
void print_wrong_board_number();
void print_enter_position();
void print_error_row_or_col();
void print_error_position_already_bombed();
void print_winning_message(int n_submarines, int n_moves);
void printMatrix(char matrix[ROWS][COLS]);


// Optional Boards

const char MATRIX_1[ROWS][COLS] = {
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'~', '~', 'S', '~', '~', '~', 'S', '~'},
        {'~', '~', 'S', '~', '~', '~', 'S', '~'},
        {'~', '~', 'S', '~', '~', '~', 'S', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'S', '~', '~', 'S', '~', '~', '~', '~'},
        {'S', '~', '~', 'S', '~', '~', '~', '~'},
        {'S', '~', '~', 'S', '~', '~', '~', '~'}
};
const char MATRIX_2[ROWS][COLS] = {
        {'S', '~', '~', '~', '~', '~', '~', '~'},
        {'S', '~', 'S', '~', '~', '~', '~', '~'},
        {'S', '~', 'S', '~', '~', '~', '~', '~'},
        {'~', '~', 'S', '~', '~', '~', '~', 'S'},
        {'~', '~', '~', '~', '~', '~', '~', 'S'},
        {'~', '~', '~', '~', '~', '~', '~', 'S'},
        {'~', 'S', 'S', '~', '~', '~', '~', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'}
};
const char MATRIX_3[ROWS][COLS] = {
        {'~', 'S', 'S', 'S', '~', '~', '~', '~'},
        {'~', '~', '~', '~', '~', 'S', 'S', 'S'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'~', '~', '~', '~', 'S', 'S', '~', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'~', '~', 'S', 'S', 'S', 'S', '~', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'S', '~', '~', '~', '~', '~', '~', '~'}
};
const char MATRIX_4[ROWS][COLS] = {
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'}
};
const char MATRIX_5[ROWS][COLS] = {
        {'S', '~', 'S', '~', '~', '~', '~', 'S'},
        {'~', '~', '~', '~', '~', 'S', '~', '~'},
        {'~', '~', 'S', '~', '~', '~', '~', '~'},
        {'~', '~', '~', '~', '~', '~', 'S', '~'},
        {'~', '~', '~', 'S', '~', '~', '~', '~'},
        {'~', 'S', '~', '~', '~', '~', 'S', '~'},
        {'~', '~', '~', '~', '~', '~', '~', '~'},
        {'S', '~', '~', 'S', '~', '~', '~', 'S'}
};


void print_welcome_message(){
    printf("Welcome to Battleship! Please enter board number:\n");
}
void print_wrong_board_number(){
    printf("Error in board number, try again\n");
}
void print_enter_position(){
    printf("Please enter position:\n");
}
void print_error_row_or_col(){
    printf("Error in row or column - out of bound\n");
}
void print_error_position_already_bombed(){
    printf("This position was already bombed - try again!\n");
}
void print_winning_message(int n_submarines, int n_moves){
    printf("Congratulations, Admiral!\nYou've successfully "
           "revealed all %d submarines in %d moves!\n", n_submarines , n_moves);
}

// Print a ROWSxCOLS matrix
void printMatrix(char matrix[ROWS][COLS]) {
    // Print column headers
    printf("  ");
    for (int j = 0; j < COLS; j++) {
        printf(" %c", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        // Print row label
        printf("%d ",  i);

        // Print row
        for (int j = 0; j < COLS; j++) {
            // Each cell is in "|x|" format
            printf("|%c", matrix[i][j]);
        }
        printf("|\n");
    }
}
int getBoardNumber(){
    int boardNum = 0;
    while (boardNum == 0) {
        if (scanf("%d", &boardNum) != 1) {
            return -1;
        }
        if (boardNum < 1 || boardNum > 5) {
            printf("Error in board number, try again\n");
            boardNum = 0;
        }
        else {
            // Waiting until Valid board number
            return boardNum;
        }
    }
    return -1;
}

// Add your functions here
void copyBoard(const char matrix[ROWS][COLS], char chosenBoard[ROWS][COLS], int *submarineCounter) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chosenBoard[i][j] = matrix[i][j];
            if (chosenBoard[i][j] == SUBMARINE) {
                (*submarineCounter)++;
            }
        }
    }
}


int main(void) {
    //&&&&&only for checking
    setvbuf(stdout, NULL, _IONBF, 0);
    int submarineCounter = 0; int numberOfS = 0, totalSubs = 0, counterOfMoves = 0;
    char currentStatusBoard[ROWS][COLS] = {0}; char chosenBoard[ROWS][COLS] = {0};

    print_welcome_message();

    //Get board number
    int boardNum = getBoardNumber();
    if (boardNum == -1) {
        return 1;
    }

    //Copy chosen board
    switch (boardNum) {
        case 1:
            copyBoard(MATRIX_1, chosenBoard, &submarineCounter);
        break;
        case 2:
            copyBoard(MATRIX_2, chosenBoard, &submarineCounter);
        break;
        case 3:
            copyBoard(MATRIX_3, chosenBoard, &submarineCounter);
        break;
        case 4:
            copyBoard(MATRIX_4, chosenBoard, &submarineCounter);
        break;
        case 5:
            copyBoard(MATRIX_5, chosenBoard, &submarineCounter);
        break;
        default:
            break;
    }


    //==== Main turn loop ====
    while (numberOfS < submarineCounter) {
        //Print current board status
        printMatrix(currentStatusBoard);

        //Get position from user in each turn
        int rowPos = 0;
        char letterPos = '\0';
        print_enter_position();
        if (scanf("%d %c", &rowPos, &letterPos) != 2) {
            return 1;
        }
        int colPos = letterPos - 'A';

        //Input validation for letters
        if ((letterPos >= 'A' && letterPos <= 'Z') || (letterPos >= 'a' && letterPos <= 'z')) {
            if (letterPos < 'A' || letterPos > 'H' ) {
                print_error_row_or_col();
                continue;
            }
        }
        else {
            return 1;
        }

        //Input validation for numbers
        if (rowPos < 0 || rowPos > 7 ) {
        }


        if (currentStatusBoard[rowPos][colPos] == SUBMARINE || currentStatusBoard[rowPos][colPos] == EMPTY) {
            print_error_position_already_bombed();
        }


        // Check if EMPTY
        if (chosenBoard[rowPos][colPos] == EMPTY) {
            currentStatusBoard[rowPos][colPos] = EMPTY;
            counterOfMoves++;
        }

        //if SUBMARINE logic
        else if (chosenBoard[rowPos][colPos] == SUBMARINE){
            currentStatusBoard[rowPos][colPos] = SUBMARINE;
            counterOfMoves++;
            numberOfS ++;
            for (int i = rowPos + 1; i < 8; i++) {
                if (chosenBoard[i][colPos] == SUBMARINE) {
                    currentStatusBoard[i][colPos] = SUBMARINE;
                    numberOfS++;
                }
                else {
                    break;
                }
            }
            for (int i = rowPos - 1; i >= 0; i--) {
                if (chosenBoard[i][colPos] == SUBMARINE) {
                    currentStatusBoard[i][colPos] = SUBMARINE;
                    numberOfS++;
                }
                else {
                    break;
                }
            }
            for (int j = colPos + 1; j < 8; j++) {
                if (chosenBoard[rowPos][j] == SUBMARINE) {
                    currentStatusBoard[rowPos][j] = SUBMARINE;
                    numberOfS++;
                }
                else {
                    break;
                }
            }
            for (int j = colPos - 1; j >= 0; j--) {
                if (chosenBoard[rowPos][j] == SUBMARINE) {
                    currentStatusBoard[rowPos][j] = SUBMARINE;
                    numberOfS++;
                }
                else {
                    break;
                }
            }
            totalSubs++;
        }

    }
            //==== END Main turn loop ====


        // Print complete board and final message
    printMatrix(chosenBoard);
    print_winning_message(totalSubs, counterOfMoves);
    return 0;
}
