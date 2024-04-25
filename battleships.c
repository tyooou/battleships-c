/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

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

// Task 7: "A Random Map"
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

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Provided functions needed for playing the Battleships game:

// First, prototype declarations for the bots:
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);

// Gets the input for one move from the human player (an alphabetic row and a numeric column)
// This function converts both inputs to numeric values
void GetMoveHuman(int *row, int *col, int player)
{
	char a = ' ';
	int b = -1;
	printf("Player %d: enter move [row/col]: ", player);
	while (!(a >= 'A' && a <= 'Z')) {
		scanf("%c", &a);
	}
	while (!(b >= 0 && b <= 25)) {
		scanf("%d", &b);
	}
	*row = (int)(a - 'A');
	*col = b;
}

// Takes two "shots" arrays as input (which are the visible parts of the game shown to players) and formats them into a string for printing
// The player currently to move is highlighted
void GetDisplayMapString(int shots1[MAP_SIZE][MAP_SIZE], int shots2[MAP_SIZE][MAP_SIZE], int player, char *boardString)
{
	int i, j;
	char numbers[10];
	// Intialise board string to be empty:
	boardString[0] = '\0';
	strcat(boardString, "  ");

	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "\n  ");

	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "\n");

	for (i = 0; i < MAP_SIZE; i++) {
		int len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots1[i][j] / HIT > 0) {
				if (shots1[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots1[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots1[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots2[i][j] / HIT > 0) {
				if (shots2[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots2[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots2[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "\n");
	}
	if (player == 1) {
		strcat(boardString, "  P1");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	} else {
		for (i = 0; i < MAP_SIZE; i++) {
			strcat(boardString, " ");
		}
		strcat(boardString, "   P2");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	}
	strcat(boardString, "\n");
}

// Plays one game of Battleships, beginning with the specified starting player
// Game type = 1 (human vs human) or 2 (human vs bot) or 3 (bot vs bot)
int PlayOneGame(int startingPlayer, int gameType)
{
	int row, col, player, gameOver;

	// String to display the boards
	char displayBoardString[(2*MAP_SIZE+5)*(MAP_SIZE+5)];

	// The maps containing the locations of the ships
	int mapPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int mapPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	// The locations of the shots
	int shotsPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int shotsPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	player = startingPlayer;
	gameOver = 0;

	// Create random maps for each player
	InitialiseRandomMap(mapPlayer1);
	InitialiseRandomMap(mapPlayer2);

	// Display the board if a human is playing
	if (gameType != 3) {
		GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
		printf("%s", displayBoardString);
	}

	// Process one move for the current player
	while (!gameOver) {
		if (gameType == 1) {
			GetMoveHuman(&row, &col, player);
			if (player == 1) {
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else if (gameType == 2) {
			if (player == 1) {
				GetMoveHuman(&row, &col, player);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot1(shotsPlayer2, &row, &col);
				printf("Player 2 (bot) moves: %c%d\n", (char)(row+'A'), col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else {
			if (player == 1) {
				GetMoveBot1(shotsPlayer1, &row, &col);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot2(shotsPlayer2, &row, &col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}

		// Swap players
		if (!gameOver) {
			player = 3 - player;
		}
		if (gameType != 3) {
			GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
			printf("%s", displayBoardString);
		}
	}
	return player;
}

// Play a Battleships tournament
// If the tournament is between a human and a bot, only one game is played
// If the tournament is between two bots, the number of games is requested
void PlayBattleships(void)
{
	int gameType, numberOfGames, result;
	int i, wins1, wins2, player;

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	// Set win counts to zero
	wins1 = 0;
	wins2 = 0;

	// Player 1 will always start the first game
	// If a tournament is played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, gameType);
		if (result == 1) {
			wins1++;
		} else {
			wins2++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// Show the outcome (of a single game or tournament)
	if (numberOfGames == 1) {
		printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
	} else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d\n\n", numberOfGames, wins1, wins2);
	}
}

// The main function for the Battleships program
int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	printf("ENGGEN131 - C Project 2023\n");
	printf("                          ... presents ...\n");
	printf(" ___    __   _____ _____  _     ____  __   _     _   ___   __  \n");
	printf("| |_)  / /\\   | |   | |  | |   | |_  ( (` | |_| | | | |_) ( (` \n");
	printf("|_|_) /_/--\\  |_|   |_|  |_|__ |_|__ _)_) |_| | |_| |_|   _)_) \n");
	printf("\n                __/___            \n");
	printf("          _____/______|           \n");
	printf("  _______/_____\\_______\\_____     \n");
	printf("  \\              < < <       |    \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");

	PlayBattleships();

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the two bots can be provided below
// The existing implementations are naive:
// - Bot 1 simply takes random shots (without checking for repeated shots)
// - Bot 2 also takes random shots (but makes a single test on each turn for a repeated shot)
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Strategy for Bot 1
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	*row = rand_row;
	*col = rand_col;
}

// Strategy for Bot 2
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	// If the shot has been tried before, try one more time
	if (shots[rand_row][rand_col] > 0) {
		rand_row = rand() % MAP_SIZE;
		rand_col = rand() % MAP_SIZE;
	}

	*row = rand_row;
	*col = rand_col;
}













