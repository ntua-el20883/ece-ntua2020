
          
import sys

def minimal_difference(numbers):
    total_sum = sum(numbers)

    dp = [False] * (total_sum // 2 + 1)
    dp[0] = True  # Zero sum is always possible

    for num in numbers:
        for j in range(total_sum // 2, num - 1, -1):
            if dp[j - num]:
                dp[j] = True

    best_x = 0
    for i in range(total_sum // 2 + 1):
        if dp[i]:
            best_x = i

    return abs(2 * best_x - total_sum)

def main(filename):
    try:
        with open(filename, 'r') as file:
            N = int(file.readline().strip())
            numbers = list(map(int, file.readline().strip().split()))
            if len(numbers) != N:
                raise ValueError("Number of integers does not match the specified count")
    except FileNotFoundError:
        print(f"Error opening file: {filename}", file=sys.stderr)
        return 1
    except ValueError:
        print("Error reading number from file", file=sys.stderr)
        return 1

    result = minimal_difference(numbers)
    print(result)
    return 0

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <filename>", file=sys.stderr)
        sys.exit(1)

    filename = sys.argv[1]
    sys.exit(main(filename))
        