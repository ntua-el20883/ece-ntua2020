#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int minimalDifference(const vector<int>& numbers) {
    int totalSum = 0;
    for (int num : numbers) {
        totalSum += num;
    }

    vector<bool> dp(totalSum / 2 + 1, false);
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

    return abs(2 * bestX - totalSum);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error opening file: " << argv[1] << '\n';
        return 1;
    }

    int N;
    file >> N;
    vector<int> numbers(N);

    for (int i = 0; i < N; ++i) {
        file >> numbers[i];
    }

    int result = minimalDifference(numbers);
    cout << result << '\n';

    return 0;
}