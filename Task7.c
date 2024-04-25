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
    // Initialise counter variable.
    int count = 0;

    // For elements at all row and column indexes,
    for (int row = 0; row < MAP_SIZE; row++) {
        for (int col = 0; col < MAP_SIZE; col++) {
            if (map[row][col] == value) { // If the element is equal to the specified value,
                count++; // Add one to the counter variable.
            }
        }
    }
    return count;
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]) {
    // Initialise index variables.
    int row, col, rowStart = 1, colStart = 1, rowEnd = 1, colEnd = 1;

    // Initialise direction and position coordinates of the ship.
    int orientation = TopLeftPosition(size, &row, &col, map);

    // If overlapping occurs on the ship.
    if (CountValues(size, map) != size) {
        return 0; // Return ship's position as invalid.
    }

    if (row == 0) { // If ship's position is at the first row (index 0),
        rowStart = 0; // Set rowStart so that the row above the ship is not searched.
    } else if (row == MAP_SIZE - 1) { // If ship's position is at the last row,
        rowEnd = 0; // Set rowEnd so that the row below the ship is not searched.
    }

    if (col == 0) { // If ship's position is at the first column (index 0),
        colStart = 0; // Set colStart so that the column left of the ship is not searched.
    } else if (col == MAP_SIZE - 1) { // If ship's position is at the last column,
        colEnd = 0; // Set colEnd so that the column right of the ship is not searched.
    }

    for (int shipSize = 0; shipSize < size; shipSize++) {
        if (orientation == 1) { // If the orientation of the ship is horizontal,
            // If any valid spaces adjacent to the ship is not empty.
            if ((colStart == 1 && map[row][col - 1] != 0) || (colEnd == 1 && map[row][col + size] != 0) || (rowStart == 1 && map[row - 1][col + shipSize] != 0) || (rowEnd == 1 && map[row + 1][col + shipSize] != 0)) {
                return 0;
            }
        } else { // If the orientation of the ship is vertical,
            // If any valid spaces adjacent to the ship is not empty.
            if ((rowStart == 1 && map[row - 1][col] != 0) || (rowEnd == 1 && map[row + size][col] != 0) || (colStart == 1 && map[row + shipSize][col - 1] != 0) || (colEnd == 1 && map[row + shipSize][col + 1] != 0)) {
                return 0; // Return ship's position as invalid.
            }
        }
    }

    // Set ship's position as valid if passes all tests.
    return 1;
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]) {
    // Initialise state of the ship.
    int completed = 0;

    // While the ship has not been built,
    while (completed == 0) {

        // Initialise random orientation (vertical = 0, horizontal = 1).
        int orientation = rand() % 2;

        // Initialise random coordinates.
        int row = rand() % MAP_SIZE;
        int col = rand() % MAP_SIZE;

        // Initialise variable that assumes ship will be built.
        int built = 1;

        // Initialise index type variable and difference variables.
        int indexType, rowDiff = 0, colDiff = 0;

        // For the size of the ship,
        for (int shipBuild = 0; shipBuild < size; shipBuild++) {
            if (orientation == 1) { // If ship's orientation is horizontal,
                indexType = col; // Set index type to columns.
                colDiff = shipBuild; // Initialise column difference.
            } else { // If ship's orientation is vertical,
                indexType = row; // Set index type to columns.
                rowDiff = shipBuild; // Initialise row difference.
            }

            // Initialise fit variables.
            int fit1 = indexType - (size - 1);
            int fit2 = indexType + (size - 1);

            if (fit1 >= 0) { // If the ship fits left/up of the assigned coordinates,
                map[row - rowDiff][col - colDiff] = size; // Place ship left/up of the assigned coordinates.
            } else if (fit2 <= MAP_SIZE - 1) { // If the ship fits right/down of the assigned coordinates,
                map[row + rowDiff][col + colDiff] = size; // Place ship right/down of the assigned coordinates.
            } else { // If the ship does not fit to the left/up or right/down of the assigned coordinates,
                built = 0; // Notify that ship has not been built.
                break;
            }
        }

        if (built == 1) { // If ship is built,
            completed = 1; // End while loop.
        }
    }
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]) {
    // Initialise variable that assumes map is not completed.
    int completedMap = 0;

    // While map is not completed,
    while (completedMap == 0) {

        // Initialise variable counting the number of valid ships in the map.
        int count = 0;

        for (int shipSize = 2; shipSize <= 5; shipSize++) { // For ship sizes 2 to 5,
            AddRandomShip(shipSize, map); // Place ship of size shipSize.
        }

        for (int shipSize = 2; shipSize <= 5; shipSize++) { // For ship sizes 2 to 5,
            if (IsShipValid(shipSize, map) == 1) { // If ship placement is valid,
                count++; // Increment number of value of ships.
            } else { // If ship placement is invalid,
                break; // End for loop.
            }
        }

        if (count == 4) { // If all ships are valid,
            completedMap = 1; // End while loop.
        } else { // If ship placements aren't valid,
            memset(map, 0, MAP_SIZE * sizeof *map); // Empty the map.
        }
    }
}

void TestInitialiseRandomMap(void) {
    int map[MAP_SIZE][MAP_SIZE] = {0};
    InitialiseRandomMap(map);
    PrintArray(map);
}

int main(void) {
    srand ( time(NULL) );
    TestInitialiseRandomMap();
}