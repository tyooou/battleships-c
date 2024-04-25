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

// Task 2: "Setting Sail"
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

// Testing Task 2
void TestInitialiseMap(void) {
    int map1[MAP_SIZE][MAP_SIZE] = {0};
    InitialiseMap(map1);
    printf("Map: \n");
    PrintArray(map1);
}

int main(void) {
    TestInitialiseMap();
}
