import time
from collections import deque


def is_solvable(puzzle):
    """Check if the puzzle is solvable."""
    flat_puzzle = [tile for row in puzzle for tile in row if tile != 0]
    inversions = sum(
        1 for i in range(len(flat_puzzle)) for j in range(i + 1, len(flat_puzzle)) if flat_puzzle[i] > flat_puzzle[j]
    )
    return inversions % 2 == 0


def find_blank_space(puzzle):
    """Find the position of the blank space (0) in the puzzle."""
    for i, row in enumerate(puzzle):
        for j, value in enumerate(row):
            if value == 0:
                return i, j


def generate_neighbors(puzzle):
    """Generate all possible neighbors by moving the blank space."""
    directions = [(-1, 0, 'U'), (1, 0, 'D'), (0, -1, 'L'),
                  (0, 1, 'R')]  # Up, Down, Left, Right
    x, y = find_blank_space(puzzle)
    neighbors = []

    for dx, dy, move in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < len(puzzle) and 0 <= ny < len(puzzle[0]):
            new_puzzle = [row[:] for row in puzzle]
            new_puzzle[x][y], new_puzzle[nx][ny] = new_puzzle[nx][ny], new_puzzle[x][y]
            neighbors.append((new_puzzle, move))

    return neighbors


def bfs_8_puzzle(start, goal):
    """Solve the 8-puzzle problem using BFS and return the path."""
    start_time = time.time()

    # Each element is (current_state, moves_to_state)
    queue = deque([(start, [])])
    visited = set()
    visited.add(tuple(map(tuple, start)))

    while queue:
        current, moves = queue.popleft()

        if current == goal:
            end_time = time.time()
            return moves, end_time - start_time

        for neighbor, move in generate_neighbors(current):
            neighbor_tuple = tuple(map(tuple, neighbor))
            if neighbor_tuple not in visited:
                visited.add(neighbor_tuple)
                queue.append((neighbor, moves + [move]))

    end_time = time.time()
    return None, end_time - start_time


start_state = [
    [1, 0, 3],
    [4, 2, 5],
    [7, 8, 6]
]
goal_state = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 0]
]

if not is_solvable(start_state):
    print("The puzzle is not solvable.")
else:
    solution_moves, elapsed_time = bfs_8_puzzle(start_state, goal_state)
    if solution_moves:
        print("Path to solution (moves):", " -> ".join(solution_moves))
        print(f"Puzzle solved in {elapsed_time:.4f} seconds.")
        print(f"Number of moves: {len(solution_moves)}")
    else:
        print("No solution found.")