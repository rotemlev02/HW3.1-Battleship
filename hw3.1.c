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
void copyBoard(const char matrix[ROWS][COLS], char choseBrd[ROWS][COLS],
    int *subCounter);
int getBoardNumber();
void copyChoseBrd(int boardNum, char choseBrd[ROWS][COLS],
    int* subCounter);
int inputVal(int* rowPos, int* colPos, char* ltrPos,
    char curStatBoard[ROWS][COLS]);
int prepareBoard(char chosenBoard[ROWS][COLS], int* submarineCounter);
int turnPosAndVal(char curStatBoard[ROWS][COLS], int* rowPos, int* colPos);
void checkRow(char chosenBoard[ROWS][COLS], char curStatBoard[ROWS][COLS],
    int* numberOfS, const int* rowPos, const int* colPos);
void checkCol(char chosenBoard[ROWS][COLS], char curStatBoard[ROWS][COLS],
    int* numberOfS, const int* rowPos, const int* colPos);
int checkSub(char chosenBoard[ROWS][COLS], char curStatBoard[ROWS][COLS],
    int* rowPos, int* colPos, int* countOfMoves, int* numberOfS, int totalSubs);
void initMatrix(char matrix[ROWS][COLS]);

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
        } else {
            // Waiting until Valid board number
            return boardNum;
        }
    }
    return -1;
}

void copyChoseBrd(int boardNum, char choseBrd[ROWS][COLS], int* subCounter) {
    switch (boardNum) {
        case 1: copyBoard(MATRIX_1, choseBrd, subCounter);
            break;
        case 2: copyBoard(MATRIX_2, choseBrd, subCounter);
            break;
        case 3: copyBoard(MATRIX_3, choseBrd, subCounter);
            break;
        case 4: copyBoard(MATRIX_4, choseBrd, subCounter);
            break;
        case 5: copyBoard(MATRIX_5, choseBrd, subCounter);
            break;
        default:
            break;
    }

}

int prepareBoard(char chosenBoard[ROWS][COLS], int* submarineCounter) {
    int boardNum = getBoardNumber();
    if (boardNum == -1) {
        return -1;
    }
    //Copy chosen board
    copyChoseBrd(boardNum, chosenBoard, submarineCounter);
    return 0;
}

void copyBoard(const char matrix[ROWS][COLS], char choseBrd[ROWS][COLS],
    int *subCounter) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            choseBrd[i][j] = matrix[i][j];
            if (choseBrd[i][j] == SUBMARINE) {
                (*subCounter)++;
            }
        }
    }
}

int turnPosAndVal(char curStatBoard[ROWS][COLS], int* rowPos, int* colPos) {
    //Get position from user in each turn
    char letterPos = '\0';
    print_enter_position();
    if (scanf("%d %c", rowPos, &letterPos) != 2) {
        return -1;
    }
    *colPos = letterPos - 'A';
    return inputVal(rowPos, colPos, &letterPos, curStatBoard);
}

int inputVal(int* rowPos, int* colPos, char* ltrPos,
    char curStatBoard[ROWS][COLS]) {
    //Input validation for letters
    if ((*ltrPos >= 'A' && *ltrPos <= 'Z') ||
        (*ltrPos >= 'a' && *ltrPos <= 'z')) {
        if (*ltrPos < 'A' || *ltrPos > 'H' ) {
            print_error_row_or_col();
            return 0;
        }
    } else {
        return -1;
    }
    //Input validation for numbers
    if (*rowPos < 0 || *rowPos > 7 ) {
        print_error_row_or_col();
        return 0;
    }
    //Input validation for bombed positions
    if (curStatBoard[*rowPos][*colPos] == SUBMARINE ||
        curStatBoard[*rowPos][*colPos] == EMPTY) {
        print_error_position_already_bombed();
        return 0;
    }
    return 6;
}


int checkSub(char chosenBoard[ROWS][COLS], char curStatBoard[ROWS][COLS],
    int* rowPos, int* colPos, int* countOfMoves, int* numberOfS, int totalSubs){
    // Check if EMPTY
    if (chosenBoard[*rowPos][*colPos] == EMPTY) {
        curStatBoard[*rowPos][*colPos] = EMPTY;
        (*countOfMoves)++;
    } else if (chosenBoard[*rowPos][*colPos] == SUBMARINE) {
        //If submarine logic
        curStatBoard[*rowPos][*colPos] = SUBMARINE;
        (*countOfMoves)++;
        (*numberOfS)++;
        checkRow(chosenBoard, curStatBoard, numberOfS, rowPos, colPos);
        checkCol(chosenBoard, curStatBoard, numberOfS, rowPos, colPos);
        totalSubs++;
    }
    return totalSubs;

}

void checkRow(char chosenBoard[ROWS][COLS], char curStatBoard[ROWS][COLS],
     int* numberOfS, const int* rowPos, const int* colPos){
    for (int i = *rowPos + 1; i < 8; i++) {
        if (chosenBoard[i][*colPos] == SUBMARINE) {
            curStatBoard[i][*colPos] = SUBMARINE;
            (*numberOfS)++;
        } else {
            break;
        }
    }
    for (int i = *rowPos - 1; i >= 0; i--) {
        if (chosenBoard[i][*colPos] == SUBMARINE) {
            curStatBoard[i][*colPos] = SUBMARINE;
            (*numberOfS)++;
        } else {
            break;
        }
    }
}

void checkCol(char chosenBoard[ROWS][COLS], char curStatBoard[ROWS][COLS],
    int* numberOfS, const int* rowPos, const int* colPos) {
    for (int j = *colPos + 1; j < 8; j++) {
        if (chosenBoard[*rowPos][j] == SUBMARINE) {
            curStatBoard[*rowPos][j] = SUBMARINE;
            (*numberOfS)++;
        } else {
            break;
        }
    }
    for (int j = *colPos - 1; j >= 0; j--) {
        if (chosenBoard[*rowPos][j] == SUBMARINE) {
            curStatBoard[*rowPos][j] = SUBMARINE;
            (*numberOfS)++;
        } else {
            break;
        }
    }
}

void initMatrix(char matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = ' ';
        }
    }
}

int main(void) {
    int submarineCounter = 0; int numOfS = 0, totSubs = 0,
    counterOfMoves = 0, rowPos = 0, colPos = 0, retVal = 1;
    char curStatBoard[ROWS][COLS] = {0}; char chosenBrd[ROWS][COLS] = {0};
    initMatrix(curStatBoard);
    print_welcome_message();
    if (prepareBoard(chosenBrd, &submarineCounter) < 0) return 1;

    //==== Main turn loop ====
    while (numOfS < submarineCounter) {
        //Print current board status
        if (retVal > 0) printMatrix(curStatBoard);
        retVal = turnPosAndVal (curStatBoard, &rowPos, &colPos);
        if (retVal < 0) return 1;
        if (retVal == 0) continue;
        totSubs = checkSub(chosenBrd, curStatBoard, &rowPos, &colPos,
            &counterOfMoves, &numOfS, totSubs);
    }
    //==== END Main turn loop ====

    // Print complete board and final message
    printMatrix(chosenBrd);
    print_winning_message(totSubs, counterOfMoves);
    return 0;
}
