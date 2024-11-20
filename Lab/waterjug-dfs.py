import time


def water_jug_dfs(jug1_capacity, jug2_capacity, target):
    # Check if target is achievable
    if target > max(jug1_capacity, jug2_capacity):
        return "Target cannot be achieved. It's greater than the largest jug capacity."
    if target % gcd(jug1_capacity, jug2_capacity) != 0:
        return "Target cannot be achieved. It's not a multiple of the GCD of jug capacities."

    # DFS setup
    visited = set()  # To track visited states
    path = []        # To record the path

    def dfs(current_state):
        x, y = current_state

        if x == target or y == target:
            path.append(current_state)
            return True

        visited.add(current_state)
        path.append(current_state)

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

        for state in possible_states:
            if state not in visited:
                if dfs(state):  # Recur for the next state
                    return True

        path.pop()
        return False

    if dfs((0, 0)):
        return path
    else:
        return "No solution exists."


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def main():
    jug1_capacity = int(input("Enter the capacity of Jug 1: "))
    jug2_capacity = int(input("Enter the capacity of Jug 2: "))
    target = int(input("Enter the target amount of water: "))

    start_time = time.time()  # Start timing

    result = water_jug_dfs(jug1_capacity, jug2_capacity, target)

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
