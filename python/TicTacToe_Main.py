# This file was created on 15 Jan 2026.

from InputFunctions import get_int_from_to
from TicTacToe import TicTacToe



def print_player_info(which_player_is_using_x: int, which_player_has_turn_right_now: int) -> None:
    if which_player_has_turn_right_now < 1 or which_player_has_turn_right_now > 2:
        raise RuntimeError(f"Fatal error: it is somehow Player {which_player_has_turn_right_now}'s turn right now.")
    if which_player_is_using_x < 1 or which_player_is_using_x > 2:
        raise RuntimeError(f"Fatal error: it is somehow Player {which_player_is_using_x} who is using X.")

    cell_value_for_x_as_str = TicTacToe.CellValue.VALUE_FOR_X.value
    cell_value_for_o_as_str = TicTacToe.CellValue.VALUE_FOR_O.value

    what_player_1_is_using = cell_value_for_o_as_str
    if which_player_is_using_x == 1:
        what_player_1_is_using = cell_value_for_x_as_str

    what_player_2_is_using = cell_value_for_o_as_str
    if which_player_is_using_x == 2:
        what_player_2_is_using = cell_value_for_x_as_str

    print(f"\n\n\n\n\nPlayer 1 is using {what_player_1_is_using}.\nPlayer 2 is using {what_player_2_is_using}.\nIt is Player {which_player_has_turn_right_now}'s turn.\n")



def play_game() -> None:
    ttt = TicTacToe()

    # Is it Player 1 or Player 2 who's using X?
    WHICH_PLAYER_IS_USING_X = get_int_from_to("Who will be playing as X? Player 1 or Player 2?", 1, 2)

    # Which player's turn is it right now?
    which_player_has_turn_right_now = 1

    while True:
        print_player_info(WHICH_PLAYER_IS_USING_X, which_player_has_turn_right_now)

        print(ttt)

        winner_value = ttt.who_won()

        match winner_value:
            case TicTacToe.WinnerValue.PLAYER_WHO_USED_X_WON:
                if WHICH_PLAYER_IS_USING_X == 1:
                    print("Game over. The winner is Player 1.")
                else:
                    print("Game over. The winner is Player 2.")
                return
            case TicTacToe.WinnerValue.PLAYER_WHO_USED_O_WON:
                if WHICH_PLAYER_IS_USING_X == 1:
                    print("Game over. The winner is Player 2.")
                else:
                    print("Game over. The winner is Player 1.")
                return
            case TicTacToe.WinnerValue.DRAW:
                print("Game over. The game is a draw.")
                return
            case TicTacToe.WinnerValue.CAN_KEEP_PLAYING:
                print("The game continues.")
            case _:
                raise RuntimeError(f"Fatal error: this game's \"winner value\" somehow equals {winner_value}.")

        while True:
            row = get_int_from_to("In which row do you want to place your piece? (Note: 0 represents the top row.)", 0, TicTacToe.SIZE - 1)
            col = get_int_from_to("In which column do you want to place your piece? (Note: 0 represents the leftmost column.)", 0, TicTacToe.SIZE - 1)

            cell_value = TicTacToe.CellValue.VALUE_FOR_O
            if which_player_has_turn_right_now == WHICH_PLAYER_IS_USING_X:
                cell_value = TicTacToe.CellValue.VALUE_FOR_X

            try:
                ttt.set_cell(row, col, cell_value)
            except TicTacToe.CellAlreadyFilledException:
                print("Failed to place piece. Try again.")
                continue

            break

        match which_player_has_turn_right_now:
            case 1:
                which_player_has_turn_right_now = 2
            case 2:
                which_player_has_turn_right_now = 1
            case _:
                raise RuntimeError(f"Fatal error: it is somehow Player {which_player_has_turn_right_now}'s turn right now.")



if __name__ == "__main__":
    play_game()
