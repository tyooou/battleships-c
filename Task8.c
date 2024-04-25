#include <stdio.h>
#define MAP_SIZE 6


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

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col) {
    int shot = (MAP_SIZE * MAP_SIZE) - CountValues(0, shots) + 1;
    if (shots[row][col] == 0) {
        if (map[row][col] == 0) {
            shots[row][col] = shot;
        } else if (map[row][col] <= 5) {
            shots[row][col] = shot + 1000;
            map[row][col] += 10;
        }
    }

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            for (int shipSize = 2; shipSize <= 5; shipSize++) {
                if (CountValues(shipSize, map) == 0 && map[i][j] == 10 + shipSize) {
                    shots[i][j] += 1000 * (shipSize - 1);
                    map[i][j] += 10;
                }
            }
        }
    }
}

void TestFireShot(void) {
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int shots[MAP_SIZE][MAP_SIZE] = {0};
    InitialiseMap(map);
    printf("Map:\n");
    PrintArray(map);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 2, 0);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 2, 1);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 2, 2);
    printf("MA:ORTYSNEOAIRST:\n");
    PrintArray(map);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 2, 3);
    printf("Shots:\n");
    PrintArray(shots);
    FireShot(shots, map, 0, 0);
    FireShot(shots, map, 1, 0);
    FireShot(shots, map, 2, 0);
    FireShot(shots, map, 3, 0);
    FireShot(shots, map, 4, 0);
    FireShot(shots, map, 5, 0);
    printf("Shots:\n");
    PrintArray(shots);
}

int main(void) {
    TestFireShot();
}