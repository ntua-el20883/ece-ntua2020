import java.io.*;
import java.util.*;

public class Arrange {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Usage: java Arrange <filename>");
            return;
        }

        try {
            BufferedReader br = new BufferedReader(new FileReader(args[0]));
            int N = Integer.parseInt(br.readLine().trim());
            List<Integer> numbers = new ArrayList<>();

            String line;
            while ((line = br.readLine()) != null) {
                String[] tokens = line.trim().split("\\s+");
                for (String token : tokens) {
                    numbers.add(Integer.parseInt(token));
                }
            }
            br.close();

            int result = minimalDifference(numbers);
            System.out.println(result);

        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }

    public static int minimalDifference(List<Integer> numbers) {
        int totalSum = 0;
        for (int num : numbers) {
            totalSum += num;
        }

        boolean[] dp = new boolean[totalSum / 2 + 1];
        dp[0] = true; // Zero sum is always possible

        for (int num : numbers) {
            for (int j = totalSum / 2; j >= num; j--) {
                if (dp[j - num]) {
                    dp[j] = true;
                }
            }
        }

        int bestX = 0;
        for (int i = 0; i <= totalSum / 2; ++i) {
            if (dp[i]) {
                bestX = i;
            }
        }

        return Math.abs(2 * bestX - totalSum);
    }
}
