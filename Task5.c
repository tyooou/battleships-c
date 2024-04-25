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

void TestTopLeftPosition(void) {
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int row, col, direction, shipSize;
    InitialiseMap(map);
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++) {
        direction = TopLeftPosition(shipSize, &row, &col, map);
        printf("Ship %d is at (%d, %d) facing %d\n", shipSize,
               row, col, direction);
    }
}

int main(void) {
    TestTopLeftPosition();
}