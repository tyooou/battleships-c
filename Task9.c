#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAP_SIZE 6


int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]) {
    int numTargets = (MAP_SIZE * MAP_SIZE) - CountValues(0, map);
    int hitTargets = 0;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] > 0 && shots[i][j] > 0) {
                hitTargets++;
            }
        }
    }
    if (hitTargets == numTargets) {
        return 1;
    } else {
        return 0;
    }
}