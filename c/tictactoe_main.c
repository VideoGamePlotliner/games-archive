// This file was created on 8 Dec 2025.

// Help from https://www.man7.org/linux/man-pages/man3/getopt.3.html

#include "error_strings.h"
#include "scanf_funcs.h"
#include "tictactoe.h"

#include <errno.h>

static int try_scanf_int_from_to(const char *message, int lower_bound_inclusive, int upper_bound_inclusive)
{
    int int_value_chosen;

    errno = 0;
    if (scanf_int_from_to(message, lower_bound_inclusive, upper_bound_inclusive, &int_value_chosen))
    {
        PRINTF_EXIT___FATAL_ERROR___FUNCTION_FAILURE(scanf_int_from_to);
    }

    return int_value_chosen;
}

static void try_tictactoe_init(struct tictactoe *ttt)
{
    errno = 0;
    if (tictactoe_init(ttt))
    {
        PRINTF_EXIT___FATAL_ERROR___FUNCTION_FAILURE(tictactoe_init);
    }
}

static void try_tictactoe_print(const struct tictactoe *ttt)
{
    errno = 0;
    if (tictactoe_print(ttt))
    {
        PRINTF_EXIT___FATAL_ERROR___FUNCTION_FAILURE(tictactoe_print);
    }
}

static void print_player_info(const int which_player_is_using_x, int which_player_has_turn_right_now)
{
    if (which_player_has_turn_right_now < 1 || which_player_has_turn_right_now > 2)
    {
        printf("%s(): Fatal error: it is somehow "
               "Player %d's turn right now.\n",
               __func__, which_player_has_turn_right_now);
        exit(EXIT_FAILURE);
    }
    if (which_player_is_using_x < 1 || which_player_is_using_x > 2)
    {
        printf("%s(): Fatal error: it is somehow "
               "Player %d who is using X.\n",
               __func__, which_player_is_using_x);
        exit(EXIT_FAILURE);
    }
    printf("\n"
           "\n"
           "\n"
           "\n"
           "\n"
           "Player 1 is using %c.\n"
           "Player 2 is using %c.\n"
           "It is Player %d's turn.\n"
           "\n",
           (which_player_is_using_x == 1) ? TICTACTOE_CELL_VALUE_FOR_X : TICTACTOE_CELL_VALUE_FOR_O,
           (which_player_is_using_x == 2) ? TICTACTOE_CELL_VALUE_FOR_X : TICTACTOE_CELL_VALUE_FOR_O,
           which_player_has_turn_right_now);
}

static int try_tictactoe_who_won(const struct tictactoe *ttt)
{
    int winner_value;

    errno = 0;
    if (tictactoe_who_won(ttt, &winner_value))
    {
        PRINTF_EXIT___FATAL_ERROR___FUNCTION_FAILURE(tictactoe_who_won);
    }

    return winner_value;
}

static void play_game(void)
{
    struct tictactoe ttt = {0};
    try_tictactoe_init(&ttt);

    /* Is it Player 1 or Player 2 who's using X? */
    const int which_player_is_using_x = try_scanf_int_from_to("Who will be playing as X? Player 1 or Player 2?", 1, 2);

    /* Which player's turn is it right now? */
    int which_player_has_turn_right_now = 1;

    while (1)
    {
        print_player_info(which_player_is_using_x, which_player_has_turn_right_now);

        try_tictactoe_print(&ttt);

        const int winner_value = try_tictactoe_who_won(&ttt);

        switch (winner_value)
        {
        case WINNER_VALUE_PLAYER_WHO_USED_X_WON:
            printf("Game over. The winner is Player %d.\n",
                   (which_player_is_using_x == 1) ? 1 : 2);
            return;
        case WINNER_VALUE_PLAYER_WHO_USED_O_WON:
            printf("Game over. The winner is Player %d.\n",
                   (which_player_is_using_x == 1) ? 2 : 1);
            return;
        case WINNER_VALUE_DRAW:
            printf("Game over. The game is a draw.\n");
            return;
        case WINNER_VALUE_CAN_KEEP_PLAYING:
            printf("The game continues.\n");
            break;
        default:
            printf("%s(): Fatal error: this game's "
                   "\"winner value\" somehow equals "
                   "%d.\n",
                   __func__, winner_value);
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            const int row = try_scanf_int_from_to("In which row do you want to place your piece? "
                                                  "(Note: 0 represents the top row.)",
                                                  0, TICTACTOE_SIZE - 1);
            const int col = try_scanf_int_from_to("In which column do you want to place your piece? "
                                                  "(Note: 0 represents the leftmost column.)",
                                                  0, TICTACTOE_SIZE - 1);

            const char cell_value = (which_player_has_turn_right_now == which_player_is_using_x)
                                        ? TICTACTOE_CELL_VALUE_FOR_X
                                        : TICTACTOE_CELL_VALUE_FOR_O;

            errno = 0;
            if (tictactoe_set_cell(&ttt, row, col, cell_value))
            {
                printf("Failed to place piece. Try again.\n");
                continue;
            }
            else
            {
                break;
            }
        }

        switch (which_player_has_turn_right_now)
        {
        case 1:
            which_player_has_turn_right_now = 2;
            break;
        case 2:
            which_player_has_turn_right_now = 1;
            break;
        default:
            printf("%s(): Fatal error: it is somehow "
                   "Player %d's turn right now.\n",
                   __func__, which_player_has_turn_right_now);
            exit(EXIT_FAILURE);
        }
    }
}

int main(void)
{
    play_game();
    return 0;
}
