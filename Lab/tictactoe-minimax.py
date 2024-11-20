import time

# Initialize the board
board = [[" " for _ in range(3)] for _ in range(3)]


def print_board():
    """Prints the current state of the board."""
    for row in board:
        print("|".join(row))
        print("-" * 5)


def is_winner(player):
    """Checks if the specified player has won."""
    # Check rows, columns, and diagonals
    for i in range(3):
        if all(board[i][j] == player for j in range(3)) or all(board[j][i] == player for j in range(3)):
            return True
    if all(board[i][i] == player for i in range(3)) or all(board[i][2 - i] == player for i in range(3)):
        return True
    return False


def is_draw():
    """Checks if the game is a draw."""
    return all(board[i][j] != " " for i in range(3) for j in range(3))


def minimax(depth, is_maximizing):
    """Implements the minimax algorithm."""
    if is_winner("O"):  # AI win
        return 10 - depth
    if is_winner("X"):  # Human win
        return depth - 10
    if is_draw():
        return 0

    if is_maximizing:  # AI's turn
        best_score = float("-inf")
        for i in range(3):
            for j in range(3):
                if board[i][j] == " ":
                    board[i][j] = "O"
                    score = minimax(depth + 1, False)
                    board[i][j] = " "
                    best_score = max(best_score, score)
        return best_score
    else:  # Human's turn
        best_score = float("inf")
        for i in range(3):
            for j in range(3):
                if board[i][j] == " ":
                    board[i][j] = "X"
                    score = minimax(depth + 1, True)
                    board[i][j] = " "
                    best_score = min(best_score, score)
        return best_score


def ai_move():
    """Finds the best move for the AI (O) using minimax."""
    best_score = float("-inf")
    move = (-1, -1)
    for i in range(3):
        for j in range(3):
            if board[i][j] == " ":
                board[i][j] = "O"
                score = minimax(0, False)
                board[i][j] = " "
                if score > best_score:
                    best_score = score
                    move = (i, j)
    board[move[0]][move[1]] = "O"


def human_move():
    """Handles the human player's move (X)."""
    while True:
        try:
            row, col = map(int, input(
                "Enter your move (row and column: 0, 1, or 2): ").split())
            if 0 <= row < 3 and 0 <= col < 3 and board[row][col] == " ":
                board[row][col] = "X"
                break
            else:
                print("Invalid move. Try again.")
        except ValueError:
            print("Invalid input. Please enter two numbers separated by a space.")


def play_game():
    """Main function to play the game."""
    print("You are X. AI is O.")
    print_board()
    start_time = time.time()

    for turn in range(9):  # Max 9 moves in a 3x3 game
        if turn % 2 == 0:  # Human's turn
            print("Your turn:")
            human_move()
        else:  # AI's turn
            print("AI's turn:")
            ai_move()
        print_board()

        if is_winner("X"):
            print("Congratulations! You win!")
            break
        if is_winner("O"):
            print("AI wins! Better luck next time.")
            break
        if is_draw():
            print("It's a draw!")
            break

    total_time = time.time() - start_time
    print(f"Total time taken: {total_time:.2f} seconds.")


# Run the game
play_game()
