/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // TODO
    // Get Max Number
    int n = (d * d) - 1;

    // Manual assignment of n to board.
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            board[i][j] = n;
            n--;
        }
    }

    // Swap 1 and 2 depending on dimensions
    if(d % 2 == 0){
        // Swap the last 2 tiles
        board[d - 1][d - 3] = 1;
        board[d - 1][d - 2] = 2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    // Add vertical margin
    printf("\v");
    // print the entire board
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            if(board[i][j] == 0){
                printf("\t\033[48;5;87m\033[38;5;196m %c \033[0m", '_');
            } else {
                printf("\t\033[48;5;87m\033[38;5;196m %i \033[0m", board[i][j]);
            }
        }
        printf("\v\n");
    }

}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // TODO
    // Search coordinate based on the tile
    int row, col;

    // Perform a linear search
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            if(board[i][j] == tile){
                row = i;
                col = j;
                // Fuck it, this is one of the cases that goto is applicable, suck my dick elitists.
                goto FOUND;
            }
        }
    }

    // Not in Field
    return false;

    // Coordinates are given
    FOUND:

    // Check cardinality and swap 2 elements if 0 is found
    // Check if selected element is top left of the board
    if(row == 0 && col == 0){
        // Only check right and down
        if(board[0][1] == 0){
            board[0][1] = tile;
            board[0][0] = 0;
        }

        if(board[1][0] == 0){
            board[1][0] = tile;
            board[0][0] = 0;
        }
    } else if (row == 0 && col == (d - 1)) {
        // Check if selected tile is at the top right
        // Only check left and down
        if(board[0][col - 1] == 0){
            board[0][col - 1] = tile;
            board[0][col] = 0;
        }

        if(board[1][col] == 0){
            board[1][col] = tile;
            board[0][col] = 0;
        }
    } else if (row == 0){
        // Check if selected tile is in the top row
        // Check left, right and down
        if(board[0][col - 1] == 0){
            board[0][col - 1] = tile;
            board[0][col] = 0;
        }

        if(board[0][col + 1] == 0){
            board[0][col + 1] = tile;
            board[0][col] = 0;
        }

        if(board[1][col] == 0){
            board[1][col] = tile;
            board[0][col] = 0;
        }
    } else if(row == (d - 1) && col == 0){
        // Check if selected tile is at the bottom left
        // Check up and right
        if(board[row - 1][0] == 0){
            board[row - 1][0] = tile;
            board[row][0] = 0;
        }

        if(board[row][1] == 0){
            board[row][1] = tile;
            board[row][0] = 0;
        }
    } else if(row == (d - 1) && col == (d - 1)){
        // Check if selected tile is at the bottom right
        // Check up and left
        if(board[row][col - 1] == 0){
            board[row][col - 1] = tile;
            board[row][col] = 0;
        }

        if(board[row - 1][col] == 0){
            board[row - 1][col] = tile;
            board[row][col] = 0;
        }
    } else if(row == (d - 1)){
        // Check if selected tile is at the bottom row
        // check left, up and right
        if(board[row][col - 1] == 0){
            board[row][col - 1] = tile;
            board[row][col] = 0;
        }

        if(board[row][col + 1] = 0){
            board[row][col + 1] = tile;
            board[row][col] = 0;
        }
    }

    usleep(5000000);
    return true;

}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // TODO
    return false;
}
