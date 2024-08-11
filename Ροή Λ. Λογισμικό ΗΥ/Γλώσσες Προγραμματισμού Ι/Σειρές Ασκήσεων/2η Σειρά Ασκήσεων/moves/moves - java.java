import java.io.*;
import java.util.*;

public class Moves {

    // Directions in order of (N, S, W, E, NE, NW, SE, SW)
    private static final int[] dRow = {-1, 1, 0, 0, -1, -1, 1, 1};
    private static final int[] dCol = {0, 0, -1, 1, 1, -1, 1, -1};
    private static final String[] directionNames = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};

    public static void main(String[] args) throws IOException {
        // Read the input file
        BufferedReader br = new BufferedReader(new FileReader(args[0]));
        int N = Integer.parseInt(br.readLine().trim());
        int[][] grid = new int[N][N];

        for (int i = 0; i < N; i++) {
            String[] line = br.readLine().trim().split("\\s+");
            for (int j = 0; j < N; j++) {
                grid[i][j] = Integer.parseInt(line[j]);
            }
        }

        // Perform BFS to find the shortest path
        String result = findShortestPath(grid, N);
        System.out.println(result);
    }

    private static String findShortestPath(int[][] grid, int N) {
        boolean[][] visited = new boolean[N][N];
        int[][] prevRow = new int[N][N];
        int[][] prevCol = new int[N][N];

        for (int[] row : prevRow) Arrays.fill(row, -1);
        for (int[] col : prevCol) Arrays.fill(col, -1);

        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0});
        visited[0][0] = true;

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int curRow = current[0];
            int curCol = current[1];

            if (curRow == N - 1 && curCol == N - 1) {
                return reconstructPath(prevRow, prevCol, curRow, curCol);
            }

            for (int d = 0; d < 8; d++) {
                int newRow = curRow + dRow[d];
                int newCol = curCol + dCol[d];

                if (isInBounds(newRow, newCol, N) && !visited[newRow][newCol] && grid[newRow][newCol] < grid[curRow][curCol]) {
                    queue.offer(new int[]{newRow, newCol});
                    visited[newRow][newCol] = true;
                    prevRow[newRow][newCol] = curRow;
                    prevCol[newRow][newCol] = curCol;
                }
            }
        }

        return "IMPOSSIBLE";
    }

    private static boolean isInBounds(int row, int col, int N) {
        return row >= 0 && row < N && col >= 0 && col < N;
    }

    private static String reconstructPath(int[][] prevRow, int[][] prevCol, int endRow, int endCol) {
        List<String> path = new ArrayList<>();
        int row = endRow;
        int col = endCol;

        while (row != 0 || col != 0) {
            int prevRowIdx = prevRow[row][col];
            int prevColIdx = prevCol[row][col];

            for (int d = 0; d < 8; d++) {
                if (row == prevRowIdx + dRow[d] && col == prevColIdx + dCol[d]) {
                    path.add(directionNames[d]);
                    break;
                }
            }

            row = prevRowIdx;
            col = prevColIdx;
        }

        Collections.reverse(path);
        return path.toString();
    }
}
