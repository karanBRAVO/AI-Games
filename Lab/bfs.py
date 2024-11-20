import time


class Q:
    def __init__(self):
        self.arr = []

    def enq(self, val):
        self.arr.append(val)

    def deq(self):
        if self.isEmpty():
            return None
        return self.arr.pop(0)

    def isEmpty(self):
        return True if len(self.arr) == 0 else False


# number of nodes
n = 6
# graph
graph = {
    1: [2, 3],
    2: [4, 5],
    3: [6],
    4: [],
    5: [],
    6: []
}

start_time = time.time()

q = Q()  # queue
v = [False] * n  # visited array
start_node = 1  # start node
q.enq(start_node)  # add to queue
v[start_node - 1] = True  # mark visited


while not q.isEmpty():
    node = q.deq()  # get the first value
    print(node, end=" ")
    for i in graph[node]:  # check for connected nodes
        if not v[i-1]:  # not visited
            q.enq(i)
            v[i-1] = True
print()

end_time = time.time()

print("Execution time:", end_time - start_time)
