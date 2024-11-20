import time
import heapq

GOAL_STATE = (1, 2, 3, 4, 5, 6, 7, 8, 0)


def manhattan_distance(state):
    distance = 0
    for i, value in enumerate(state):
        if value != 0:  # Ignore the empty space (0)
            goal_index = GOAL_STATE.index(value)
            current_row, current_col = i // 3, i % 3
            goal_row, goal_col = goal_index // 3, goal_index % 3
            distance += abs(current_row - goal_row) + \
                abs(current_col - goal_col)
    return distance


def get_neighbors(state):
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
            new_state = list(state)
            new_state[zero_index], new_state[new_zero_index] = new_state[new_zero_index], new_state[zero_index]
            neighbors.append((tuple(new_state), move))

    return neighbors


def a_star_search(start):
    start_time = time.time()
    open_list = []
    heapq.heappush(open_list, (manhattan_distance(start), 0, start, []))

    visited = set()

    while open_list:
        f_cost, g_cost, current_state, path = heapq.heappop(open_list)

        if current_state == GOAL_STATE:
            end_time = time.time()
            return path, len(path), end_time - start_time

        visited.add(current_state)

        for neighbor, move in get_neighbors(current_state):
            if neighbor not in visited:
                h_cost = manhattan_distance(neighbor)
                new_f_cost = g_cost + 1 + h_cost  # f = g + h
                new_path = path + [move]
                heapq.heappush(
                    open_list, (new_f_cost, g_cost + 1, neighbor, new_path))

    return None, 0, 0  # Return None if no solution found


def print_solution(solution):
    if solution:
        print("Solution found:")
        for move in solution:
            print(move, end=" -> ")
        print()
    else:
        print("No solution found.")


if __name__ == "__main__":
    start_state = (1, 2, 3, 4, 0, 5, 6, 7, 8)  # Initial state

    solution, path_length, total_time = a_star_search(start_state)

    if solution:
        print_solution(solution)
        print("Number of moves:", path_length)
        print("Time taken (seconds):", total_time)
    else:
        print("No solution found.")
