import time
import heapq


def manhattan_distance(state, goal):
    """Compute the Manhattan distance heuristic."""
    distance = 0
    for i in range(len(state)):
        if state[i] != 0:  # Ignore the blank tile (represented as 0)
            goal_index = goal.index(state[i])
            distance += abs(i // 3 - goal_index // 3) + \
                abs(i % 3 - goal_index % 3)
    return distance


class PuzzleState:
    def __init__(self, state, parent, move, depth, cost):
        self.state = state
        self.parent = parent
        self.move = move
        self.depth = depth
        self.cost = cost

    def __lt__(self, other):
        return (self.cost + self.depth) < (other.cost + other.depth)


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
            neighbors.append((new_state, move))

    return neighbors


def a_star(start, goal):
    """Solve the 8-puzzle problem using the A* algorithm."""
    start_time = time.time()
    open_list = []
    closed_set = set()

    initial_state = PuzzleState(
        start, None, None, 0, manhattan_distance(start, goal))
    heapq.heappush(open_list, initial_state)

    while open_list:
        current_state = heapq.heappop(open_list)

        if current_state.state == goal:
            end_time = time.time()
            path = []
            while current_state.parent:
                path.append(current_state.move)
                current_state = current_state.parent
            path.reverse()
            return path, len(closed_set), end_time - start_time

        closed_set.add(tuple(current_state.state))

        for neighbor, move in get_neighbors(current_state.state):
            if tuple(neighbor) in closed_set:
                continue

            neighbor_state = PuzzleState(
                neighbor,
                current_state,
                move,
                current_state.depth + 1,
                manhattan_distance(neighbor, goal)
            )

            heapq.heappush(open_list, neighbor_state)

    return None, len(closed_set), time.time() - start_time


if __name__ == "__main__":
    start_state = [1, 2, 3, 4, 0, 5, 6, 7, 8]  # Initial state
    goal_state = [1, 2, 3, 4, 5, 6, 7, 8, 0]   # Goal state

    solution, explored_nodes, total_time = a_star(start_state, goal_state)

    if solution:
        print("Solution found:", solution)
        print("Number of nodes explored:", explored_nodes)
        print("Time taken (seconds):", total_time)
    else:
        print("No solution found.")
