import time


def get_neighbors(state):
    """Return all possible moves from the current state."""
    neighbors = []
    zero_index = state.index(0)
    row, col = zero_index // 3, zero_index % 3

    moves = {
        'UP': (row - 1, col),
        'DOWN': (row + 1, col),
        'LEFT': (row, col - 1),
        'RIGHT': (row, col + 1)
    }

    for move, (r, c) in moves.items():
        if 0 <= r < 3 and 0 <= c < 3:
            new_zero_index = r * 3 + c
            new_state = state[:]
            new_state[zero_index], new_state[new_zero_index] = new_state[new_zero_index], new_state[zero_index]
            # Store the move along with the new state
            neighbors.append((new_state, move))

    return neighbors


def depth_limited_search(state, goal, depth, max_depth):
    """Perform depth-limited search to a given depth."""
    if state == goal:
        return True, []

    if depth == max_depth:
        return False, []

    neighbors = get_neighbors(state)
    for neighbor_state, move in neighbors:
        found, path = depth_limited_search(
            neighbor_state, goal, depth + 1, max_depth)
        if found:
            return True, [(move, state)] + path  # Store the move and the state

    return False, []


def iterative_deepening_search(start, goal):
    """Perform Iterative Deepening Search."""
    start_time = time.time()

    max_depth = 0
    while True:
        found, path = depth_limited_search(start, goal, 0, max_depth)
        if found:
            end_time = time.time()
            return path, len(path), end_time - start_time
        max_depth += 1


def print_solution(solution):
    """Print the solution path."""
    for move, state in solution:
        print(move, end=" -> ")
    print()


if __name__ == "__main__":
    start_state = [1, 2, 3, 4, 0, 5, 6, 7, 8]  # Initial state
    goal_state = [1, 2, 3, 4, 5, 6, 7, 8, 0]   # Goal state

    solution, path_length, total_time = iterative_deepening_search(
        start_state, goal_state)

    if solution:
        print("Solution found:")
        print_solution(solution)
        print("Number of moves:", path_length)
        print("Time taken (seconds):", total_time)
    else:
        print("No solution found.")
