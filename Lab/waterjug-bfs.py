import time
from collections import deque


def water_jug_bfs(jug1_capacity, jug2_capacity, target):
    # Check if target is achievable
    if target > max(jug1_capacity, jug2_capacity):
        return "Target cannot be achieved. It's greater than the largest jug capacity."
    if target % gcd(jug1_capacity, jug2_capacity) != 0:
        return "Target cannot be achieved. It's not a multiple of the GCD of jug capacities."

    visited = set()  # To avoid revisiting states
    queue = deque([(0, 0)])  # Initial state (0, 0)
    parent = {}  # To store the path

    while queue:
        current = queue.popleft()
        x, y = current

        if x == target or y == target:
            path = reconstruct_path(parent, current)
            return path

        visited.add(current)

        possible_states = [
            (jug1_capacity, y),  # Fill jug 1
            (x, jug2_capacity),  # Fill jug 2
            (0, y),              # Empty jug 1
            (x, 0),              # Empty jug 2
            (max(0, x - (jug2_capacity - y)),
             min(jug2_capacity, x + y)),  # Pour jug 1 -> jug 2
            # Pour jug 2 -> jug 1
            (min(jug1_capacity, x + y), max(0, y - (jug1_capacity - x)))
        ]

        # Explore all new states
        for state in possible_states:
            if state not in visited:
                queue.append(state)
                parent[state] = current  # Record the path

    return "No solution exists."


def reconstruct_path(parent, current):
    path = []
    while current:
        path.append(current)
        current = parent.get(current)
    return path[::-1]


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def main():
    jug1_capacity = int(input("Enter the capacity of Jug 1: "))
    jug2_capacity = int(input("Enter the capacity of Jug 2: "))
    target = int(input("Enter the target amount of water: "))

    start_time = time.time()  # Start timing

    result = water_jug_bfs(jug1_capacity, jug2_capacity, target)

    end_time = time.time()  # End timing

    print("\nResult:")
    if isinstance(result, list):
        for step in result:
            print(step)
    else:
        print(result)

    print(f"\nTotal time taken: {end_time - start_time:.4f} seconds.")


if __name__ == "__main__":
    main()
