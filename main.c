#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAP_SIZE 6

// Task 1: "Let's See The Map!"
void PrintArray(int values[MAP_SIZE][MAP_SIZE]) {
    // For every element at row and column indexes,
    for (int row = 0; row < MAP_SIZE; row++) {
        for (int col = 0; col < MAP_SIZE; col++) {
            if (col < MAP_SIZE - 1) { // For every element except the last element of each row,
                printf("%d ", values[row][col]); // Print element inline.
            } else { // For the last element of each row,
                printf("%d\n", values[row][col]); // Print element inline and start a new line.
            }
        }
    }
}

// Task 2: "Setting Sail"
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]) {
    // Initialise spacing variable.
    int spacing = 0;

    // Initialise sea.
    for (int row = 0; row < MAP_SIZE; row++) {
        for (int col = 0; col < MAP_SIZE; col++) {
            map[row][col] = 0;
        }
    }

    // Initialise ships.
    for (int shipSize = 2; shipSize <= 5; shipSize++) { // For all ship sizes (2 to 5),
        for (int shipBuild = 0; shipBuild < shipSize; shipBuild++) { // For the length of the ship size,
            if (shipSize < 5) { // If ship size is not 5.
                map[spacing][shipBuild] = shipSize; // Build ship.
            } else { // If ship size is 5.
                map[shipBuild][5] = 5; // Build ship.
            }
        }
        // Space the ships apart so there is an empty row/column between them.
        spacing += 2;
    }
}

// Task 3: "Very Unpredictable"
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

// Task 4: "And Counting"
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

// Task 5: "Top Left"
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]) {
    // For elements at all row and column indexes,
    for (int rowIndex = 0; rowIndex < MAP_SIZE; rowIndex++) {
        for (int colIndex = 0; colIndex < MAP_SIZE; colIndex++) {
            if (map[rowIndex][colIndex] == size) { // If specified ship is found,

                // Return position via indexes.
                *row = rowIndex;
                *col = colIndex;

                if (map[rowIndex][colIndex + 1] == size) { // If the ship continues immediately right,
                    return 1; // Returns ship's orientation as horizontal.
                } else { // If the ship does not continue immediately right,
                    return 2; // Returns ship's orientation as vertical.
                }
            }
        }
    }
    return 0;
}

// Task 6: "Valid Ships Only"
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
    } else if (row == MAP_SIZE - 1 || (orientation == 2 && row + size == MAP_SIZE)) { // If ship's position is at the last row,
        rowEnd = 0; // Set rowEnd so that the row below the ship is not searched.
    }

    if (col == 0) { // If ship's position is at the first column (index 0),
        colStart = 0; // Set colStart so that the column left of the ship is not searched.
    } else if (col == MAP_SIZE - 1 || (orientation == 1 && col + size == MAP_SIZE)) { // If ship's position is at the last column,
        colEnd = 0; // Set colEnd so that the column right of the ship is not searched.
    }

    for (int shipSize = 0; shipSize < size; shipSize++) {
        if (orientation == 1) { // If the orientation of the ship is horizontal,
            // If any valid spaces adjacent to the ship is not empty.
            if ((colStart == 1 && map[row][col - 1] != 0) || (colEnd == 1 && map[row][col + size] != 0) || (rowStart == 1 && map[row - 1][col + shipSize] != 0) || (rowEnd == 1 && map[row + 1][col + shipSize] != 0)) {
                return 0;
            }
        } else if (orientation == 2) { // If the orientation of the ship is vertical,
            // If any valid spaces adjacent to the ship is not empty.
            if ((rowStart == 1 && map[row - 1][col] != 0) || (rowEnd == 1 && map[row + size][col] != 0) || (colStart == 1 && map[row + shipSize][col - 1] != 0) || (colEnd == 1 && map[row + shipSize][col + 1] != 0)) {
                return 0; // Return ship's position as invalid.
            }
        }
    }

    // Set ship's position as valid if passes all tests.
    return 1;
}

// Task 7: "A Random Map"
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]) {
    // Initialise variable that assumes map is not completed.
    int completedMap = 0;

    // While map is not completed,
    while (completedMap == 0) {

        // Initialise sea.
        for (int row = 0; row < MAP_SIZE; row++) {
            for (int col = 0; col < MAP_SIZE; col++) {
                map[row][col] = 0;
            }
        }

        // Initialise variable counting the number of valid ships in the map.
        int count = 0;

        for (int shipSize = 2; shipSize <= 5; shipSize++) { // For ship sizes 2 to 5,
            AddRandomShip(shipSize, map); // Place ship of size shipSize.
        }

        for (int shipSize = 2; shipSize <= 5; shipSize++) { // For ship sizes 2 to 5,
            if (IsShipValid(shipSize, map)) { // If ship placement is valid,
                count++; // Increment number of value of ships.
                if (count == 4) { // If all ships are valid,
                    completedMap = 1; // End while loop.
                }
            } else { // If ship placement is invalid,
                break; // End for loop.
            }
        }
    }
}

// Task 8: "Fire in the Hole"
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col) {

    // Initialise variable that tracks the shot number.
    int shotNumber = (MAP_SIZE * MAP_SIZE) - CountValues(0, shots) + 1;

    // If specified position on the ship map and shot map are both 0.
    if (map[row][col] == 0 && shots[row][col] == 0) {
        shots[row][col] = shotNumber; // Set specified position to shotNumber on shot map.

        // If specified position on the ship map is a ship, whereas shot map is 0.
    } else if (map[row][col] <= 5 && shots[row][col] == 0) {
        shots[row][col] = shotNumber + 1000; // Set specified position to shotNumber + 1000 on shot map.
        //map[row][col] += 10; // Set specified position to +10 on ship map.
    }

    // For all ship sizes,
    for (int shipSize = 2; shipSize <= 5; shipSize++) {
        int flag = 0;

        // Search through map once.
        do {
            // Initialise temporary counter at zero.
            int temp = 0;

            // For elements at every row and column indexes,
            for (int rowIndex = 0; rowIndex < MAP_SIZE; rowIndex++) {
                for (int colIndex = 0; colIndex < MAP_SIZE; colIndex++) {
                    // If all parts of the specified ship has been shot,
                    if (shots[rowIndex][colIndex] > 0 && shots[rowIndex][colIndex] < 2000 && map[rowIndex][colIndex] == shipSize) {
                        if (flag == 0) {
                            // Increase counter.
                            temp++;
                        } else {
                            // Recorded in shot map ship is destroyed.
                            shots[rowIndex][colIndex] += 1000 * (shipSize - 1);
                        }
                    }
                }
            }

            // If ship is destroyed.
            if (temp == shipSize) {
                // Search through map again.
                flag = 1;
            } else {
                // Don't search through map again.
                flag = 0;
            }
        } while (flag);
    }
}

// Task 9: "Game Over"
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]) {

    // Initialise the number of targets.
    int numTargets = (MAP_SIZE * MAP_SIZE) - CountValues(0, map);

    // Initialise counter variable counting the number of hit targets.
    int hitTargets = 0;

    // For elements at every row and column index,
    for (int row = 0; row < MAP_SIZE; row++) {
        for (int col = 0; col < MAP_SIZE; col++) {
            if (map[row][col] != 0 && shots[row][col] != 0) { // If ship has been hit,
                hitTargets++; // Increment the number of hit targets.
            }
        }
    }

    if (hitTargets == numTargets) { // If the number of hit targets is equal the total number of targets,
        return 1; // Return true.
    } else {
        return 0; // Return false.
    }
}

// Task 10: "The Robots are Coming!"


int main(void) {
    srand((unsigned int)time(NULL));
    int map[MAP_SIZE][MAP_SIZE];
}