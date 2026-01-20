// This file was created on 29 Dec 2025.

import java.util.Scanner;

public class TicTacToe_Main {

    private static void print_player_info(int which_player_is_using_x, int which_player_has_turn_right_now) {
        if (which_player_has_turn_right_now < 1 || which_player_has_turn_right_now > 2) {
            throw new Error(String.format("Fatal error: it is somehow Player %d's turn right now.\n",
                    which_player_has_turn_right_now));
        }
        if (which_player_is_using_x < 1 || which_player_is_using_x > 2) {
            throw new Error(String.format("Fatal error: it is somehow Player %d who is using X.\n",
                    which_player_is_using_x));
        }

        final char cell_value_for_x_as_char = TicTacToe.CellValue.VALUE_FOR_X.get_as_char();
        final char cell_value_for_o_as_char = TicTacToe.CellValue.VALUE_FOR_O.get_as_char();

        System.out.printf("\n\n\n\n\nPlayer 1 is using %c.\nPlayer 2 is using %c.\nIt is Player %d's turn.\n\n",
                (which_player_is_using_x == 1) ? cell_value_for_x_as_char : cell_value_for_o_as_char,
                (which_player_is_using_x == 2) ? cell_value_for_x_as_char : cell_value_for_o_as_char,
                which_player_has_turn_right_now);
    }

    private static void play_game(Scanner input_scanner) {
        if (input_scanner == null) {
            throw new NullPointerException("Null input scanner");
        }

        final TicTacToe ttt = new TicTacToe();

        /* Is it Player 1 or Player 2 who's using X? */
        final int which_player_is_using_x = ScannerFunctions.get_int_from_to(input_scanner, "Who will be playing as X? Player 1 or Player 2?", 1, 2);

        /* Which player's turn is it right now? */
        int which_player_has_turn_right_now = 1;

        while (true) {
            print_player_info(which_player_is_using_x, which_player_has_turn_right_now);

            ttt.print();

            final TicTacToe.WinnerValue winner_value = ttt.who_won();

            switch (winner_value) {
                case PLAYER_WHO_USED_X_WON:
                    System.out.printf("Game over. The winner is Player %d.\n", (which_player_is_using_x == 1) ? 1 : 2);
                    return;
                case PLAYER_WHO_USED_O_WON:
                    System.out.printf("Game over. The winner is Player %d.\n", (which_player_is_using_x == 1) ? 2 : 1);
                    return;
                case DRAW:
                    System.out.printf("Game over. The game is a draw.\n");
                    return;
                case CAN_KEEP_PLAYING:
                    System.out.printf("The game continues.\n");
                    break;
                default:
                    throw new Error(String.format("Fatal error: this game's \"winner value\" somehow equals %s.\n", winner_value));
            }

            while (true) {
                final int row = ScannerFunctions.get_int_from_to(input_scanner,
                        "In which row do you want to place your piece? (Note: 0 represents the top row.)",
                        0, TicTacToe.SIZE - 1);
                final int col = ScannerFunctions.get_int_from_to(input_scanner,
                        "In which column do you want to place your piece? (Note: 0 represents the leftmost column.)",
                        0, TicTacToe.SIZE - 1);

                final TicTacToe.CellValue cell_value = (which_player_has_turn_right_now == which_player_is_using_x)
                        ? TicTacToe.CellValue.VALUE_FOR_X
                        : TicTacToe.CellValue.VALUE_FOR_O;

                try {
                    ttt.set_cell(row, col, cell_value);
                } catch (TicTacToe.CellAlreadyFilledException e) {
                    System.out.printf("Failed to place piece. Try again.\n");
                    continue;
                }
                break;
            }

            switch (which_player_has_turn_right_now) {
                case 1:
                    which_player_has_turn_right_now = 2;
                    break;
                case 2:
                    which_player_has_turn_right_now = 1;
                    break;
                default:
                    throw new Error(String.format("Fatal error: it is somehow Player %d's turn right now.\n", which_player_has_turn_right_now));
            }
        }
    }

    public static void main(String[] args) {
        try (Scanner input_scanner = new Scanner(System.in)) {
            play_game(input_scanner);
        }
    }
}
