#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ballsortpuzzle.h"
#include <time.h>
 
void generator(const int rows, const int columns, char field[rows][columns])
{
    int spaceCol1 = rand() % columns;
    int spaceCol2 = rand() % columns;
    while (spaceCol1 == spaceCol2) {
        spaceCol2 = rand() % columns;
    }
 
    for (int i = 0; i < rows; i++) {
        field[i][spaceCol1] = ' ';
        field[i][spaceCol2] = ' ';
    }
 
    char symbols[10] = {'*', '+', '^', '@', '&', '#', '$', '%', '-', '='};
    int countArr[10];
    for (int i = 0; i < 10; i++) {
        countArr[i] = 0;
    }
 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j == spaceCol1 || j == spaceCol2) {
                continue;
            }
            int index = rand() % (columns - 2);
            if (countArr[index] < rows) {
                countArr[index]++;
                field[i][j] = symbols[index];
            } else {
                while (1) {
                    index = rand() % (columns - 2);
                    if (countArr[index] < rows) {
                        countArr[index]++;
                        field[i][j] = symbols[index];
                        break;
                    }
                }
            }
        }
    }
}
 
void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y)
{
    // x == y
    // не выходить за границы
    // разные элементы
    // не остался висеть в воздухе
    // проверка на число
    if (x == y || x > columns || y > columns || x < 1 || y < 1) {
        // some error
        printf("Wrong input\n");
    } else {
        int indexX = -1;
        char tmp = '\0';
        for (int i = 0; i < rows; i++) {
            if (field[i][x-1] != ' ') {
                tmp = field[i][x-1];
                indexX = i;
                break;
            }
        }
        if (tmp == '\0') {
            printf("Column is empty\n");
        } else {
            if (field[rows-1][y-1] == ' ') {
                field[rows-1][y-1] = tmp;
                field[indexX][x-1] = ' ';
            } else {
                for (int i = 0; i < rows; i++) {
                    if (field[i][y-1] != ' ') {
                        if (field[i][y-1] == tmp && i != 0) {
                            field[i-1][y-1] = tmp;
                            field[indexX][x-1] = ' ';
                        } else {
                            printf("Error\n");
                            break;
                        }
                    }
                }
            }
        }
    }
}

void game_field(const int rows, const int columns, char field[rows][columns]){
    //writing array
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    for (int i = 0; i < rows; i++){
        printf("%d |", i+1);  // index of row
        for(int j = 0; j < columns; j++){
            printf(" %c |", field[i][j]);
        }
        printf("\n");
    }
    //writing line under array
    printf("  ");
    for (int i = 0; i < columns; i++){
        printf(" ---");
    }
    //index of column
    printf("\n");
    printf(" ");
    for (int i = 0; i < columns; i++){
        printf("   %d", i+1);
    }
    printf("\n");
}

bool check(const int rows, const int columns, char field[rows][columns]){

    for(int i = 0; i < columns; i++){

        for(int j = 0; j < rows-1; j++){

            if(field[j][i] != field[j+1][i]){
                return false;
            }
        }
    }
    return true;
}

void ball_sort_puzzle(){

    srand(time(NULL));
    int rows, cols;
    printf("Enter rows: ");
    scanf("%d", &rows);
    printf("Enter cols: ");
    scanf("%d", &cols);
 
    char field[rows][cols];
 
    // call function
    generator(rows, cols, field);
 
    game_field(rows, cols, field);
 
    int x = 0, y = 0;

    while(!check(rows, cols, field)){
    printf("Enter What :");
    scanf("%d", &x);
    printf("Enter Where :");
    scanf("%d", &y);
    down_possible(rows, cols, field, x, y);
    game_field(rows, cols, field);
    }

    printf("You WON\n");
}