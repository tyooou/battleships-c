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

// Task 4: "And Counting"
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

// Testing Task 4
void TestCountValues(void) {
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int count, shipSize;
    InitialiseMap(map);
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++) {
        count = CountValues(shipSize, map);
        printf("The value %d appears %d times\n", shipSize,
               count);
    }
}

int main(void) {
    TestCountValues();
}