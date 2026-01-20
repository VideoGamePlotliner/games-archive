// This file was created on 25 Dec 2025.

#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

/**
 * The number of rows in a tic-tac-toe game.
 * This is also the number of columns.
 */
#define TICTACTOE_SIZE 3

/**
 * A true/false question:
 * Is the given number a valid row/column index for a tic-tac-toe game?
 */
#define TICTACTOE_IS_IN_BOUNDS(i) (i >= 0 && i < TICTACTOE_SIZE)

/**
 * Constants for `cell_value` below.
 * Refer to `tictactoe::get_cell()` and `tictactoe::set_cell()`.
 */
#define TICTACTOE_CELL_VALUE_FOR_EMPTY ' '
#define TICTACTOE_CELL_VALUE_FOR_X 'X'
#define TICTACTOE_CELL_VALUE_FOR_O 'O'
#define TICTACTOE_BAD_CELL_VALUE '?'

/**
 * A true/false question:
 * Is the given number a valid cell value for a tic-tac-toe game?
 */
#define TICTACTOE_IS_VALID_CELL_VALUE(cell_value)        \
    (((cell_value) == TICTACTOE_CELL_VALUE_FOR_EMPTY) || \
     ((cell_value) == TICTACTOE_CELL_VALUE_FOR_X) ||     \
     ((cell_value) == TICTACTOE_CELL_VALUE_FOR_O))

/**
 * A class representing the state of a tic-tac-toe game.
 */
class tictactoe
{
private:
    char board[TICTACTOE_SIZE][TICTACTOE_SIZE];

public:
    tictactoe();

    /**
     * Each of the following functions returns -1 if error or 0 otherwise.
     */
    int print(void) const;
    int get_cell(int row, int col, char *cell_value) const;
    int set_cell(int row, int col, char cell_value);
    int who_won(int *winner_value) const;
};

/**
 * The only acceptable "winner values".
 * Refer to `tictactoe::who_won()`.
 */
#define WINNER_VALUE_PLAYER_WHO_USED_X_WON 10001
#define WINNER_VALUE_PLAYER_WHO_USED_O_WON 10002
#define WINNER_VALUE_DRAW 10003
#define WINNER_VALUE_CAN_KEEP_PLAYING 10004

/**
 * Each of the following `#if/#endif` blocks is a sanity check.
 */
#if TICTACTOE_CELL_VALUE_FOR_EMPTY == '\0'
#error "TICTACTOE_CELL_VALUE_FOR_EMPTY must not equal '\0'."
#endif
#if TICTACTOE_CELL_VALUE_FOR_X == '\0'
#error "TICTACTOE_CELL_VALUE_FOR_X must not equal '\0'."
#endif
#if TICTACTOE_CELL_VALUE_FOR_O == '\0'
#error "TICTACTOE_CELL_VALUE_FOR_O must not equal '\0'."
#endif
#if TICTACTOE_BAD_CELL_VALUE == '\0'
#error "TICTACTOE_BAD_CELL_VALUE must not equal '\0'."
#endif
#if !TICTACTOE_IS_VALID_CELL_VALUE(TICTACTOE_CELL_VALUE_FOR_EMPTY)
#error "TICTACTOE_CELL_VALUE_FOR_EMPTY must be valid."
#endif
#if !TICTACTOE_IS_VALID_CELL_VALUE(TICTACTOE_CELL_VALUE_FOR_X)
#error "TICTACTOE_CELL_VALUE_FOR_X must be valid."
#endif
#if !TICTACTOE_IS_VALID_CELL_VALUE(TICTACTOE_CELL_VALUE_FOR_O)
#error "TICTACTOE_CELL_VALUE_FOR_O must be valid."
#endif
#if TICTACTOE_IS_VALID_CELL_VALUE(TICTACTOE_BAD_CELL_VALUE)
#error "TICTACTOE_BAD_CELL_VALUE must not be valid."
#endif

#endif // TICTACTOE_HPP
