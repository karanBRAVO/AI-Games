import time


class BlockWorld:
    def __init__(self, initial_state, goal_state):
        self.initial_state = initial_state
        self.goal_state = goal_state
        self.visited = set()
        self.path = []

    def is_goal(self, state):
        return state == self.goal_state

    def get_possible_moves(self, state):
        moves = []
        for i in range(len(state)):
            if state[i]:  # Check if stack `i` is non-empty
                for j in range(len(state)):
                    if i != j:  # Avoid moving onto the same stack
                        # Perform the move
                        new_state = [stack[:] for stack in state]
                        block = new_state[i].pop()
                        new_state[j].append(block)
                        moves.append(new_state)
        return moves

    def dfs(self, state):
        if self.is_goal(state):
            self.path.append(state)
            return True

        self.visited.add(tuple(tuple(stack) for stack in state))
        self.path.append(state)

        for next_state in self.get_possible_moves(state):
            if tuple(tuple(stack) for stack in next_state) not in self.visited:
                if self.dfs(next_state):
                    return True

        self.path.pop()
        return False

    def solve(self):
        if self.dfs(self.initial_state):
            return self.path
        else:
            return "No solution exists."


def main():
    initial_state = [["A", "B"], ["C"], []]
    goal_state = [[], [], ["A", "B", "C"]]

    print("Initial State:", initial_state)
    print("Goal State:", goal_state)

    start_time = time.time()  # Start timing

    block_world = BlockWorld(initial_state, goal_state)
    result = block_world.solve()

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
