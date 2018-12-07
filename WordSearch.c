//
// Created by Isaias Perez Vega
// Goal: Solves a word search puzzle, words to be found are read from a dictioanry text file.
// Dictioanry text file must be in the same directory as the source file.
// Input puzzle example: First int indicates number of puzzles to be solved, the folllwing line indicates
// the size of the puzzles, in this case a 3x3 puzzle, the following lines set the puzzle to be solved.
// -------------------
// 1
// 3 3
// ica
// lon
// lms
// -------------------
// Outputs words found


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_STRING_LENGTH 19
#define MIN_STRING_LENGTH 4

void searchGrid(char** grid, char** dictionaryList, int row, int col, int* numWords, const int DX_SIZE, const int DX[], const int DY[], int gridCount);
char** readList(FILE* dictionary, char** dictionaryList, int* numWords);
int binSearch(char** dictionaryList, int numWords, char* keyWord);
char** makeGrid(char** grid, int row, int col);
void destroyGrid(char** grid, int row);


int main(void) {

    const int DX_SIZE = 8;
    const int DX[] = {-1,-1,-1,0,0,1,1,1};
    const int DY[] = {-1,0,1,-1,1,-1,0,1};
    char** dictionaryList = NULL;
    int* numWords;
    char** grid = NULL;
    int row, col;
    int inputCase;
    FILE* dictionary;

    // Specify path of dictionary file to be read
    dictionary = fopen("dictionary.txt", "r");

    // If file was open successfully
    if (dictionary) {

        // Get number of words in dictionary
        numWords = malloc(sizeof(int));
        fscanf(dictionary, "%d", numWords);

        // Allocate resources to store in 2D array
        dictionaryList = readList(dictionary, dictionaryList, numWords);

        // Get number of search grids
        printf("Enter number of puzzles to solve:\n");
        scanf("%d", &inputCase);

        // For every grid get dimensions, input puzzle, then solve and destroy
        for (int x = 0; x < inputCase; x++) {
            printf("Enter puzzle configuration #%d\n\n", x + 1 );
            scanf("%d", &row);
            scanf("%d", &col);

            grid = makeGrid(grid, row, col);
            searchGrid(grid, dictionaryList, row, col, numWords, DX_SIZE, DX, DY, x + 1);
            destroyGrid(grid, row);
        }

        // Free dictioanry list
        destroyGrid(dictionaryList, *numWords - 1);
    } else {
        printf("Error opening file, dictionary.txt not found. \n");
    }

    return 0;
}


// READ IN LIST FROM FILE, AND RETURN DYNAMICALLY ALLOCATED ARRAY //
char** readList(FILE* dictionary, char** dictionaryList, int* numWords) {
    dictionaryList = malloc(sizeof(char*) * *numWords);

    // For as many words, copy them to array
    for (int i = 0; i < *numWords; i++) {
        dictionaryList[i] = malloc(sizeof(char) * MAX_STRING_LENGTH + 1);
        fscanf(dictionary, "%s", dictionaryList[i]);
    }

    // Done using file
    fclose(dictionary);
    return dictionaryList;
}

// BINARY SEARCH IMPLEMENTATION WITH WORDS, RETURN TRUE IF FOUND //
int binSearch(char** dictionaryList, int numWords, char* keyWord) {
    int low = 0, high = numWords - 1;
    int mid = (low + high) / 2;
    int temp;
    while (low <= high) {
        mid = (low + high) / 2;
        temp = strcmp(dictionaryList[mid], keyWord);
        if (temp == 0) {
            return 1;
        } else if (temp > 0) {
            high = mid - 1;
        } else if (temp < 0) {
            low = mid + 1;
        }
        if (low > high) {
            return 0;
        }
    }
    return 0;
}

// CREATE GRID OF CHARS SIZE (ROW,COL), RETURN READ STRINGS FROM USER //
char** makeGrid(char** grid, int row, int col) {
    grid = malloc(sizeof(char*) * row);
    if (grid) {
        for (int x = 0; x < row; x++) {
            // Memory for null terminator included
            grid[x] = malloc(sizeof(char) * col + 1);
        }
        char string[col + 1];
        for (int x = 0; x < row; x++) {
            scanf("%s", string);
            strcpy(grid[x], string);
        }
    }
    return grid;
}

// SEARCH THRUOUGH GRID IN EVERY DIRECTION, AND PRINT WORDS FOUND //
void searchGrid(char** grid, char** dictionaryList, int row, int col, int* numWords, const int DX_SIZE, const int DX[], const int DY[], int gridCount) {

    int newX, newY, found;
    int keyWordCounter = 0;
    int counter = 0;
    int complt = 0;
    char* keyWord = malloc(sizeof(char) * (col + 1));

    printf("\nWords Found in Grid #%d:\n", gridCount);
    printf("________________________\n\n");

    // Traveling
    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {

            // Looking in all directions
            for (int direction = 0; direction < DX_SIZE; direction++) {
                keyWordCounter = 0;
                newX = x; newY = y;

                // Run as long as we are in bounds
                while ((newX >= 0 && newX < row) && (newY >= 0 && newY < col)) {
                    keyWord[keyWordCounter + 1] = '\0';

                    keyWord[keyWordCounter] = grid[newX][newY];

                    // If keyword meets requirements (3 < length < 20), check if it exists in dictionary
                    if (strlen(keyWord) > 3 || strlen(keyWord) <= 19) {
                        found = binSearch(dictionaryList, *numWords, keyWord);
                        if (found) {
                            counter++;
                            printf("%s\n", keyWord);
                        }
                    }

                    // Moving
                    newX += DX[direction]; newY += DY[direction];
                    keyWordCounter++;
                }
            }
        }
    }
    printf("\nTotal words: %d\n\n", counter);
    free(keyWord);
}

// FREE ALLOCATED MEMORY //
void destroyGrid(char** grid, int row) {
    for (int x = 0; x < row; x++) {
        free(grid[x]);
    }
    free(grid); grid = NULL;
}
