#include <stdio.h>
#define MAP_SIZE 6

void PrintArray(int values[MAP_SIZE][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (j < MAP_SIZE - 1) {
                printf("%d ", values[i][j]);
            } else {
                printf("%d\n", values[i][j]);
            }
        }
    }
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]) {
    int spacing = 0;
    for (int shipSize = 2; shipSize <= 5; shipSize++) {
        for (int shipBuild = 0; shipBuild < shipSize; shipBuild++) {
            if (shipSize < 5) {
                map[spacing][shipBuild] = shipSize;
            } else {
                map[shipBuild][5] = 5;
            }
        }
        spacing += 2;
    }
}

int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]) {
    int direction;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == size) {
                *row = i;
                *col = j;
                if (map[i][j + 1] == size) {
                    direction = 1;
                } else {
                    direction = 2;
                }
                return direction;
            }
        }
    }
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]) {
    int count = 0;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == value) {
                count++;
            }
        }
    }
    return count;
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]) {
    int row, col;
    int direction = TopLeftPosition(size, &row, &col, map);
    int validity = 0;
    int rowStart = 1;
    int colStart = 1;
    int rowEnd = 1;
    int colEnd = 1;


    if (CountValues(size, map) != size) {
        return validity;
    }

    if (row == 0) {
        rowStart = 0;
    } else if (row == MAP_SIZE - 1) {
        rowEnd = 0;
    }

    if (col == 0) {
        colStart = 0;
    } else if (col == MAP_SIZE - 1) {
        colEnd = 0;
    }


    for (int i = 0; i < size; i++) {
        if (direction == 1) {
            if ((colStart == 1 && map[row][col - 1] != 0) || (colEnd == 1 && map[row][col + size] != 0) || (rowStart == 1 && map[row - 1][col + i] != 0) || (rowEnd == 1 && map[row + 1][col + i] != 0)) {
                return validity;
            }
        } else {
            if ((rowStart == 1 && map[row - 1][col] != 0) || (rowEnd == 1 && map[row + size][col] != 0) || (colStart == 1 && map[row + i][col - 1] != 0) || (colEnd == 1 && map[row + i][col + 1] != 0)) {
                return validity;
            }
        }
    }
    validity = 1;
    return validity;
}

void TestIsShipValid(void) {
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int valid, shipSize;
    InitialiseMap(map);
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++) {
        valid = IsShipValid(shipSize, map);
        printf("Is ship %d valid? %d\n", shipSize, valid);
    }

    map[0][5] = 0;
    map[1][5] = 0;
    map[2][5] = 0;
    map[3][5] = 0;
    map[4][5] = 0;
    map[0][4] = 5;
    map[1][4] = 5;
    map[2][4] = 5;
    map[3][4] = 5;
    map[4][4] = 5;

    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++) {
        valid = IsShipValid(shipSize, map);
        printf("Is ship %d valid? %d\n", shipSize, valid);
    }
}

int main(void) {
    TestIsShipValid();
}