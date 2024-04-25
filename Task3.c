#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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

// Task 3: "Very Unpredictable"
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]) {
    int completed = 0;


    while (completed == 0) {

        int orientation = rand() % 2;
        int row_pos = rand() % MAP_SIZE;
        int col_pos = rand() % MAP_SIZE;
        int built = 1;

        for (int shipBuild = 0; shipBuild < size; shipBuild++) {
            if (orientation == 1) {


                int leftFit = col_pos - (size - 1);
                int rightFit = col_pos + (size - 1);

                if (leftFit >= 0) { map[row_pos][col_pos - shipBuild] = size;
                } else if (rightFit <= MAP_SIZE - 1) { map[row_pos][col_pos + shipBuild] = size;
                } else { built = 0;
                    break;
                }

            } else {
                int upFit = row_pos - (size - 1);
                int downFit = row_pos + (size - 1);


                if (upFit >= 0) { map[row_pos - shipBuild][col_pos] = size;;
                } else if (downFit <= MAP_SIZE - 1) { map[row_pos + shipBuild][col_pos] = size;
                } else { built = 0;
                    break;
                }
            }
        }
        if (built == 1) { completed = 1;
        }
    }
}

// Testing Task 3
void TestAddRandomShip(void) {
    int map2[MAP_SIZE][MAP_SIZE] = {0};
    AddRandomShip(2, map2);
    printf("Map: \n");
    PrintArray(map2);
    AddRandomShip(3, map2);
    printf("Map: \n");
    PrintArray(map2);
    AddRandomShip(4, map2);
    printf("Map: \n");
    PrintArray(map2);
    AddRandomShip(5, map2);
    printf("Map: \n");
    PrintArray(map2);
}

int main(void) {
    srand ( time(NULL) );
    TestAddRandomShip();
}