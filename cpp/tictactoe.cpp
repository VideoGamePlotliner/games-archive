// This file was created on 25 Dec 2025.

#include "error_strings.hpp"
#include "tictactoe.hpp"

#include <cerrno>
#include <cstring>

#define PRINTF___OTHER_ERROR___INVALID_CELL_VALUE(row, col, cell_value) printf("%s(): Error: Cell at row %d and column %d has invalid cell value '%c'.\n", __func__, row, col, cell_value)

tictactoe::tictactoe()
{
    memset(this, 0, sizeof(*this));

    for (int row = 0; row < TICTACTOE_SIZE; row++)
    {
        for (int col = 0; col < TICTACTOE_SIZE; col++)
        {
            this->board[row][col] = TICTACTOE_CELL_VALUE_FOR_EMPTY;
        }
    }
}

int tictactoe::print(void) const
{
    char cell_value = TICTACTOE_BAD_CELL_VALUE;

    printf("\n");
    for (int row = 0; row < TICTACTOE_SIZE; row++)
    {
        if (row > 0)
        {
            printf("---+---+---\n");
        }
        for (int col = 0; col < TICTACTOE_SIZE; col++)
        {
            if (col > 0)
            {
                printf("|");
            }
            if (this->get_cell(row, col, &cell_value))
            {
                PRINTF___OTHER_ERROR___FUNCTION_FAILURE(&tictactoe::get_cell);
                return -1;
            }
            printf(" %c ", cell_value);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

int tictactoe::get_cell(int row, int col, char *cell_value) const
{
    if (!cell_value)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(cell_value);
        errno = EINVAL;
        return -1;
    }
    if (!TICTACTOE_IS_IN_BOUNDS(row) && !TICTACTOE_IS_IN_BOUNDS(col))
    {
        printf("%s(): Error: Row %d and column %d are both out of bounds.\n", __func__, row, col);
        errno = EINVAL;
        return -1;
    }
    if (!TICTACTOE_IS_IN_BOUNDS(row))
    {
        printf("%s(): Error: Row %d (but not column %d) is out of bounds.\n", __func__, row, col);
        errno = EINVAL;
        return -1;
    }
    if (!TICTACTOE_IS_IN_BOUNDS(col))
    {
        printf("%s(): Error: Column %d (but not row %d) is out of bounds.\n", __func__, col, row);
        errno = EINVAL;
        return -1;
    }
    char c = this->board[row][col];
    if (!TICTACTOE_IS_VALID_CELL_VALUE(c))
    {
        PRINTF___OTHER_ERROR___INVALID_CELL_VALUE(row, col, c);
        errno = ENOTRECOVERABLE;
        return -1;
    }
    *cell_value = c;
    return 0;
}

int tictactoe::set_cell(int row, int col, char cell_value)
{
    if (!TICTACTOE_IS_IN_BOUNDS(row) && !TICTACTOE_IS_IN_BOUNDS(col))
    {
        printf("%s(): Error: Row %d and column %d are both out of bounds.\n", __func__, row, col);
        errno = EINVAL;
        return -1;
    }
    if (!TICTACTOE_IS_IN_BOUNDS(row))
    {
        printf("%s(): Error: Row %d (but not column %d) is out of bounds.\n", __func__, row, col);
        errno = EINVAL;
        return -1;
    }
    if (!TICTACTOE_IS_IN_BOUNDS(col))
    {
        printf("%s(): Error: Column %d (but not row %d) is out of bounds.\n", __func__, col, row);
        errno = EINVAL;
        return -1;
    }
    if (!TICTACTOE_IS_VALID_CELL_VALUE(cell_value))
    {
        printf("%s(): Error: new cell value ('%c') is invalid.\n", __func__, cell_value);
        errno = EINVAL;
        return -1;
    }
    if (cell_value == TICTACTOE_CELL_VALUE_FOR_EMPTY)
    {
        printf("%s(): Error: new cell value ('%c') is empty.\n", __func__, cell_value);
        errno = EINVAL;
        return -1;
    }
    char c = this->board[row][col];
    if (!TICTACTOE_IS_VALID_CELL_VALUE(c))
    {
        PRINTF___OTHER_ERROR___INVALID_CELL_VALUE(row, col, c);
        errno = ENOTRECOVERABLE;
        return -1;
    }
    if (c != TICTACTOE_CELL_VALUE_FOR_EMPTY)
    {
        printf("%s(): Error: Cell at row %d and column %d has non-empty cell value '%c'.\n", __func__, row, col, c);
        errno = EACCES;
        return -1;
    }
    this->board[row][col] = cell_value;
    return 0;
}

/**
 * This function is only to be called by `tictactoe::who_won()`.
 *
 * This function returns -1 if error or 0 otherwise.
 */
static int tictactoe_who_won___react_to_cell_value(int row, int col, char cell_value,
                                                   bool *player_who_used_x_won_this_line, bool *player_who_used_o_won_this_line)
{
    if (!player_who_used_x_won_this_line)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(player_who_used_x_won_this_line);
        errno = EINVAL;
        return -1;
    }
    if (!player_who_used_o_won_this_line)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(player_who_used_o_won_this_line);
        errno = EINVAL;
        return -1;
    }
    bool invalid_cell_value;
    switch (cell_value)
    {
    case TICTACTOE_CELL_VALUE_FOR_X:
        *player_who_used_o_won_this_line = false;
        invalid_cell_value = false;
        break;
    case TICTACTOE_CELL_VALUE_FOR_O:
        *player_who_used_x_won_this_line = false;
        invalid_cell_value = false;
        break;
    case TICTACTOE_CELL_VALUE_FOR_EMPTY:
        *player_who_used_x_won_this_line = false;
        *player_who_used_o_won_this_line = false;
        invalid_cell_value = false;
        break;
    default:
        invalid_cell_value = true;
        break;
    }
    if (invalid_cell_value)
    {
        PRINTF___OTHER_ERROR___INVALID_CELL_VALUE(row, col, cell_value);
        errno = ENOTRECOVERABLE;
        return -1;
    }
    return 0;
}

/**
 * This function is only to be called by `tictactoe::who_won()`.
 *
 * This function returns -1 if error or 0 otherwise.
 */
static int tictactoe_who_won___apply_line_results___with_index(const char *what_kind_of_line_is_this, int index,
                                                               bool player_who_used_x_won_this_line,
                                                               bool player_who_used_o_won_this_line,
                                                               bool *player_who_used_x_won,
                                                               bool *player_who_used_o_won)
{
    if (!what_kind_of_line_is_this)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(what_kind_of_line_is_this);
        errno = EINVAL;
        return -1;
    }
    if (!player_who_used_x_won)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(player_who_used_x_won);
        errno = EINVAL;
        return -1;
    }
    if (!player_who_used_o_won)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(player_who_used_o_won);
        errno = EINVAL;
        return -1;
    }

    if (player_who_used_x_won_this_line && player_who_used_o_won_this_line)
    {
        printf("%s(): Error: Somehow, both players won %s %d.\n", __func__, what_kind_of_line_is_this, index);
        errno = ENOTRECOVERABLE;
        return -1;
    }
    else if (player_who_used_x_won_this_line)
    {
        *player_who_used_x_won = true;
    }
    else if (player_who_used_o_won_this_line)
    {
        *player_who_used_o_won = true;
    }
    return 0;
}

/**
 * This function is only to be called by `tictactoe::who_won()`.
 *
 * This function returns -1 if error or 0 otherwise.
 */
static int tictactoe_who_won___apply_line_results(const char *what_kind_of_line_is_this,
                                                  bool player_who_used_x_won_this_line,
                                                  bool player_who_used_o_won_this_line,
                                                  bool *player_who_used_x_won,
                                                  bool *player_who_used_o_won)
{
    if (!what_kind_of_line_is_this)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(what_kind_of_line_is_this);
        errno = EINVAL;
        return -1;
    }
    if (!player_who_used_x_won)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(player_who_used_x_won);
        errno = EINVAL;
        return -1;
    }
    if (!player_who_used_o_won)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(player_who_used_o_won);
        errno = EINVAL;
        return -1;
    }

    if (player_who_used_x_won_this_line && player_who_used_o_won_this_line)
    {
        printf("%s(): Error: Somehow, both players won %s.\n", __func__, what_kind_of_line_is_this);
        errno = ENOTRECOVERABLE;
        return -1;
    }
    else if (player_who_used_x_won_this_line)
    {
        *player_who_used_x_won = true;
    }
    else if (player_who_used_o_won_this_line)
    {
        *player_who_used_o_won = true;
    }
    return 0;
}

int tictactoe::who_won(int *winner_value) const
{
    if (!winner_value)
    {
        PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(winner_value);
        errno = EINVAL;
        return -1;
    }

    bool player_who_used_x_won = false;
    bool player_who_used_o_won = false;

    for (int row = 0; row < TICTACTOE_SIZE; row++)
    {
        // Within this block, "this line" refers to the row with the given index (that is, `row`).
        bool player_who_used_x_won_this_line = true;
        bool player_who_used_o_won_this_line = true;
        for (int col = 0; col < TICTACTOE_SIZE; col++)
        {
            char cell_value = this->board[row][col];

            if (tictactoe_who_won___react_to_cell_value(row, col, cell_value,
                                                        &player_who_used_x_won_this_line,
                                                        &player_who_used_o_won_this_line))
            {
                PRINTF___OTHER_ERROR___FUNCTION_FAILURE(tictactoe_who_won___react_to_cell_value);
                return -1;
            }
        }
        if (tictactoe_who_won___apply_line_results___with_index("row", row,
                                                                player_who_used_x_won_this_line,
                                                                player_who_used_o_won_this_line,
                                                                &player_who_used_x_won,
                                                                &player_who_used_o_won))
        {
            PRINTF___OTHER_ERROR___FUNCTION_FAILURE(tictactoe_who_won___apply_line_results___with_index);
            return -1;
        }
    }

    for (int col = 0; col < TICTACTOE_SIZE; col++)
    {
        // Within this block, "this line" refers to the column with the given index (that is, `col`).
        bool player_who_used_x_won_this_line = true;
        bool player_who_used_o_won_this_line = true;
        for (int row = 0; row < TICTACTOE_SIZE; row++)
        {
            char cell_value = this->board[row][col];

            if (tictactoe_who_won___react_to_cell_value(row, col, cell_value,
                                                        &player_who_used_x_won_this_line,
                                                        &player_who_used_o_won_this_line))
            {
                PRINTF___OTHER_ERROR___FUNCTION_FAILURE(tictactoe_who_won___react_to_cell_value);
                return -1;
            }
        }
        if (tictactoe_who_won___apply_line_results___with_index("column", col,
                                                                player_who_used_x_won_this_line,
                                                                player_who_used_o_won_this_line,
                                                                &player_who_used_x_won,
                                                                &player_who_used_o_won))
        {
            PRINTF___OTHER_ERROR___FUNCTION_FAILURE(tictactoe_who_won___apply_line_results___with_index);
            return -1;
        }
    }

    {
        // Within this block, "this line" refers to the bottom-left-to-top-right diagonal.
        bool player_who_used_x_won_this_line = true;
        bool player_who_used_o_won_this_line = true;
        for (int row = 0; row < TICTACTOE_SIZE; row++)
        {
            int col = TICTACTOE_SIZE - 1 - row;

            char cell_value = this->board[row][col];

            if (tictactoe_who_won___react_to_cell_value(row, col, cell_value,
                                                        &player_who_used_x_won_this_line,
                                                        &player_who_used_o_won_this_line))
            {
                PRINTF___OTHER_ERROR___FUNCTION_FAILURE(tictactoe_who_won___react_to_cell_value);
                return -1;
            }
        }
        if (tictactoe_who_won___apply_line_results("the bottom-left-to-top-right diagonal",
                                                   player_who_used_x_won_this_line,
                                                   player_who_used_o_won_this_line,
                                                   &player_who_used_x_won,
                                                   &player_who_used_o_won))
        {
            PRINTF___OTHER_ERROR___FUNCTION_FAILURE(tictactoe_who_won___apply_line_results);
            return -1;
        }
    }

    {
        // Within this block, "this line" refers to the top-left-to-bottom-right diagonal.
        bool player_who_used_x_won_this_line = true;
        bool player_who_used_o_won_this_line = true;
        for (int row = 0; row < TICTACTOE_SIZE; row++)
        {
            int col = row;

            char cell_value = this->board[row][col];

            if (tictactoe_who_won___react_to_cell_value(row, col, cell_value,
                                                        &player_who_used_x_won_this_line,
                                                        &player_who_used_o_won_this_line))
            {
                PRINTF___OTHER_ERROR___FUNCTION_FAILURE(tictactoe_who_won___react_to_cell_value);
                return -1;
            }
        }
        if (tictactoe_who_won___apply_line_results("the top-left-to-bottom-right diagonal",
                                                   player_who_used_x_won_this_line,
                                                   player_who_used_o_won_this_line,
                                                   &player_who_used_x_won,
                                                   &player_who_used_o_won))
        {
            PRINTF___OTHER_ERROR___FUNCTION_FAILURE(tictactoe_who_won___apply_line_results);
            return -1;
        }
    }

    if (player_who_used_x_won && player_who_used_o_won)
    {
        printf("%s(): Error: Somehow, both players won this game, but how?\n", __func__);
        errno = ENOTRECOVERABLE;
        return -1;
    }
    else if (player_who_used_x_won)
    {
        *winner_value = WINNER_VALUE_PLAYER_WHO_USED_X_WON;
        return 0;
    }
    else if (player_who_used_o_won)
    {
        *winner_value = WINNER_VALUE_PLAYER_WHO_USED_O_WON;
        return 0;
    }
    else
    {
        int num_empty_cells = 0;
        for (int row = 0; row < TICTACTOE_SIZE; row++)
        {
            for (int col = 0; col < TICTACTOE_SIZE; col++)
            {
                if (this->board[row][col] == TICTACTOE_CELL_VALUE_FOR_EMPTY)
                {
                    num_empty_cells++;
                }
            }
        }

        *winner_value = (num_empty_cells > 0) ? WINNER_VALUE_CAN_KEEP_PLAYING : WINNER_VALUE_DRAW;
        return 0;
    }
}
