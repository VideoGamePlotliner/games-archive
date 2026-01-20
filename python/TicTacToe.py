# This file was created on 16 Jan 2026.

from enum import Enum



class TicTacToe:



    #
    # This exception is thrown by `set_cell()` if and only if the cell you're
    # trying to fill is already filled.
    #
    class CellAlreadyFilledException(Exception):
        def __init__(self, s: str) -> None:
            super().__init__(s)



    #
    # Constants for `cell_value` below. Refer to `get_cell()` and `set_cell()`.
    #
    class CellValue(Enum):
        VALUE_FOR_EMPTY = " "
        VALUE_FOR_X = "X"
        VALUE_FOR_O = "O"



    #
    # The only acceptable "winner values". Refer to `who_won()`.
    #
    class WinnerValue(Enum):
        PLAYER_WHO_USED_X_WON = 10001
        PLAYER_WHO_USED_O_WON = 10002
        DRAW = 10003
        CAN_KEEP_PLAYING = 10004



    #
    # The number of rows and the number of columns.
    #
    SIZE = 3



    def __init__(self) -> None:
        v = self.CellValue.VALUE_FOR_EMPTY
        self.__board = [[v,v,v],[v,v,v],[v,v,v]]



    def __str__(self) -> str:
        s = "\n"
        for row in range(TicTacToe.SIZE):
            if row > 0:
                s += "---+---+---\n"
            for col in range(TicTacToe.SIZE):
                if col > 0:
                    s += "|"
                cell_value = self.get_cell(row, col)
                s += f" {cell_value.value} "
            s += "\n"
        return s



    def get_cell(self, row: int, col: int) -> CellValue:
        self.__ensure_row_col_in_bounds(row, col)
        return self.__board[row][col]



    def set_cell(self, row: int, col: int, new_cell_value: CellValue) -> None:
        self.__ensure_row_col_in_bounds(row, col)

        if new_cell_value == TicTacToe.CellValue.VALUE_FOR_EMPTY:
            raise RuntimeError("New cell value is empty")

        old_cell_value = self.__board[row][col]

        if old_cell_value != TicTacToe.CellValue.VALUE_FOR_EMPTY:
            raise TicTacToe.CellAlreadyFilledException(f"Cell at row {row} and column {col} has non-empty cell value '{old_cell_value.value}'.")

        self.__board[row][col] = new_cell_value



    #
    # A true/false question: Is the given number a valid row/column index for a
    # tic-tac-toe game?
    #
    def __is_in_bounds(self, i: int) -> bool:
        return (i >= 0 and i < TicTacToe.SIZE)



    def __ensure_row_col_in_bounds(self, row: int, col: int) -> None:
        row_is_in_bounds = self.__is_in_bounds(row)
        col_is_in_bounds = self.__is_in_bounds(col)

        if (not row_is_in_bounds and not col_is_in_bounds):
            raise IndexError(f"Row {row} and column {col} are both out of bounds.")
        if (not row_is_in_bounds):
            raise IndexError(f"Row {row} (but not column {col}) is out of bounds.")
        if (not col_is_in_bounds):
            raise IndexError(f"Column {col} (but not row {row}) is out of bounds.")



    def __ensure_valid_winners_variable(self, variable_name: str, variable_itself: list[bool]) -> None:
        if (len(variable_itself) != 2):
            raise RuntimeError(f"`{variable_name}.length` is {len(variable_itself)}, even though it should be 2.")



    #
    # This method is only to be called by `who_won()`.
    #
    # `winners_of_this_line[0]` is whether the player who used X won this line.
    #
    # `winners_of_this_line[1]` is whether the player who used O won this line.
    #
    def __who_won___react_to_cell_value(self, row: int, col: int, cell_value: CellValue, winners_of_this_line: list[bool]) -> None:
        self.__ensure_valid_winners_variable("winners_of_this_line", winners_of_this_line)

        match cell_value:
            case TicTacToe.CellValue.VALUE_FOR_X:
                winners_of_this_line[1] = False
            case TicTacToe.CellValue.VALUE_FOR_O:
                winners_of_this_line[0] = False
            case TicTacToe.CellValue.VALUE_FOR_EMPTY:
                winners_of_this_line[0] = False
                winners_of_this_line[1] = False
            case _:
                raise RuntimeError(f"Cell at row {row} and column {col} has invalid cell value.")



    #
    # This method is only to be called by `who_won()`.
    #
    # `winners_of_this_line[0]` is whether the player who used X won this line.
    #
    # `winners_of_this_line[1]` is whether the player who used O won this line.
    #
    # `winners_of_this_game[0]` is whether the player who used X won this game.
    #
    # `winners_of_this_game[1]` is whether the player who used O won this game.
    #
    def __who_won___apply_line_results(self, which_line_is_this: str, winners_of_this_line: list[bool], winners_of_this_game: list[bool]) -> None:
        self.__ensure_valid_winners_variable("winners_of_this_line", winners_of_this_line)
        self.__ensure_valid_winners_variable("winners_of_this_game", winners_of_this_game)

        if winners_of_this_line[0] and winners_of_this_line[1]:
            raise RuntimeError(f"Somehow, both players won {which_line_is_this}.")
        elif winners_of_this_line[0]:
            winners_of_this_game[0] = True
        elif winners_of_this_line[1]:
            winners_of_this_game[1] = True



    def who_won(self) -> WinnerValue:
        #
        # Index 0 is for the player who used X.
        #
        # Index 1 is for the player who used O.
        #
        winners_of_this_game = [False, False]

        #
        # Index 0 is for the player who used X.
        #
        # Index 1 is for the player who used O.
        #
        winners_of_this_line = [False, False]

        for row in range(TicTacToe.SIZE):
            # Within this block, "this line" refers to the row with the given index (that is, `row`).
            winners_of_this_line[0] = True
            winners_of_this_line[1] = True

            for col in range(TicTacToe.SIZE):
                self.__who_won___react_to_cell_value(row, col, self.__board[row][col], winners_of_this_line)

            self.__who_won___apply_line_results(f"row {row}", winners_of_this_line, winners_of_this_game)

        for col in range(TicTacToe.SIZE):
            # Within this block, "this line" refers to the column with the given index (that is, `col`).
            winners_of_this_line[0] = True
            winners_of_this_line[1] = True

            for row in range(TicTacToe.SIZE):
                self.__who_won___react_to_cell_value(row, col, self.__board[row][col], winners_of_this_line)

            self.__who_won___apply_line_results(f"column {col}", winners_of_this_line, winners_of_this_game)

        if True:
            # Within this block, "this line" refers to the bottom-left-to-top-right diagonal.
            winners_of_this_line[0] = True
            winners_of_this_line[1] = True

            for row in range(TicTacToe.SIZE):
                col = TicTacToe.SIZE - 1 - row
                self.__who_won___react_to_cell_value(row, col, self.__board[row][col], winners_of_this_line)

            self.__who_won___apply_line_results("the bottom-left-to-top-right diagonal", winners_of_this_line, winners_of_this_game)

        if True:
            # Within this block, "this line" refers to the top-left-to-bottom-right diagonal.
            winners_of_this_line[0] = True
            winners_of_this_line[1] = True

            for row in range(TicTacToe.SIZE):
                col = row
                self.__who_won___react_to_cell_value(row, col, self.__board[row][col], winners_of_this_line)

            self.__who_won___apply_line_results("the top-left-to-bottom-right diagonal", winners_of_this_line, winners_of_this_game)

        if (winners_of_this_game[0] and winners_of_this_game[1]):
            raise RuntimeError("Somehow, both players won this game, but how?")
        elif (winners_of_this_game[0]):
            return TicTacToe.WinnerValue.PLAYER_WHO_USED_X_WON
        elif (winners_of_this_game[1]):
            return TicTacToe.WinnerValue.PLAYER_WHO_USED_O_WON
        elif self.__get_num_empty_cells() > 0:
            return TicTacToe.WinnerValue.CAN_KEEP_PLAYING
        else:
            return TicTacToe.WinnerValue.DRAW



    def __get_num_empty_cells(self) -> int:
        num_empty_cells = 0
        for row in range(TicTacToe.SIZE):
            for col in range(TicTacToe.SIZE):
                if self.__board[row][col] == TicTacToe.CellValue.VALUE_FOR_EMPTY:
                    num_empty_cells += 1
        return num_empty_cells
