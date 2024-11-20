magic_square = {
    (0, 0): 8, (0, 1): 1, (0, 2): 6,
    (1, 0): 3, (1, 1): 5, (1, 2): 7,
    (2, 0): 4, (2, 1): 9, (2, 2): 2
}

board = [[" " for _ in range(3)] for _ in range(3)]

player_moves = {"X": [], "O": []}


def print_board():
    """Prints the current state of the board."""
    for row in board:
        print("|".join(row))
        print("-" * 5)


def check_winner(player):
    """Checks if the player has won using magic square logic."""
    moves = player_moves[player]
    n = len(moves)
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                if moves[i] + moves[j] + moves[k] == 15:
                    return True
    return False


def is_valid_move(row, col):
    """Checks if the move is valid."""
    return 0 <= row < 3 and 0 <= col < 3 and board[row][col] == " "


def play_game():
    """Main game loop."""
    current_player = "X"
    for turn in range(9):  # Max 9 turns in a 3x3 Tic-Tac-Toe
        print_board()
        print(f"Player {current_player}'s turn.")

        try:
            row, col = map(int, input(
                "Enter row and column (0, 1, or 2): ").split())
        except ValueError:
            print("Invalid input. Please enter two numbers separated by a space.")
            continue

        if not is_valid_move(row, col):
            print("Invalid move. Try again.")
            continue

        board[row][col] = current_player
        player_moves[current_player].append(magic_square[(row, col)])

        if check_winner(current_player):
            print_board()
            print(f"Player {current_player} wins!")
            return

        current_player = "O" if current_player == "X" else "X"

    print_board()
    print("It's a draw!")


# Run the game
play_game()
