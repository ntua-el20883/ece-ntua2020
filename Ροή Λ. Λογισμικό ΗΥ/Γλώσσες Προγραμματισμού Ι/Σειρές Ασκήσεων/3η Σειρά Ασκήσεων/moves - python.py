
          
import sys
from collections import deque

# Directions in order of (N, S, W, E, NE, NW, SE, SW)
dRow = [-1, 1, 0, 0, -1, -1, 1, 1]
dCol = [0, 0, -1, 1, 1, -1, 1, -1]
directionNames = ["N", "S", "W", "E", "NE", "NW", "SE", "SW"]

def main():
    with open(sys.argv[1], 'r') as file:
        N = int(file.readline().strip())
        grid = [list(map(int, file.readline().strip().split())) for _ in range(N)]

    result = find_shortest_path(grid, N)
    print(result)

def find_shortest_path(grid, N):
    visited = [[False for _ in range(N)] for _ in range(N)]
    prevRow = [[-1 for _ in range(N)] for _ in range(N)]
    prevCol = [[-1 for _ in range(N)] for _ in range(N)]

    queue = deque()
    queue.append((0, 0))
    visited[0][0] = True

    while queue:
        curRow, curCol = queue.popleft()

        if curRow == N - 1 and curCol == N - 1:
            return reconstruct_path(prevRow, prevCol, curRow, curCol)

        for d in range(8):
            newRow = curRow + dRow[d]
            newCol = curCol + dCol[d]

            if is_in_bounds(newRow, newCol, N) and not visited[newRow][newCol] and grid[newRow][newCol] < grid[curRow][curCol]:
                queue.append((newRow, newCol))
                visited[newRow][newCol] = True
                prevRow[newRow][newCol] = curRow
                prevCol[newRow][newCol] = curCol

    return "IMPOSSIBLE"

def is_in_bounds(row, col, N):
    return 0 <= row < N and 0 <= col < N


def reconstruct_path(prevRow, prevCol, endRow, endCol):
    path = []
    row = endRow
    col = endCol

    while row != 0 or col != 0:
        prevRowIdx = prevRow[row][col]
        prevColIdx = prevCol[row][col]

        for d in range(8):
            if row == prevRowIdx + dRow[d] and col == prevColIdx + dCol[d]:
                path.append(directionNames[d])
                break

        row = prevRowIdx
        col = prevColIdx

    path.reverse()
    # Correctly format the path list as a string with square brackets
    return f"[{','.join(path)}]"

if __name__ == "__main__":
    main()
        