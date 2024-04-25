#include <stdio.h>
#define MAP_SIZE 6

// Task 1: "Let's See The Map!"
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

// Testing Task 1
void TestPrintArray(void) {
    int map1[MAP_SIZE][MAP_SIZE] = {0};
    printf("Map 1:\n");
    PrintArray(map1);

    int map2[MAP_SIZE][MAP_SIZE] = {0};
    for (int i = 0; i < MAP_SIZE; i++) {
        map2[MAP_SIZE-i-1][i] = i;
    }
    printf("\nMap 2:\n");
    PrintArray(map2);
}

int main(void) {
    TestPrintArray();
}
