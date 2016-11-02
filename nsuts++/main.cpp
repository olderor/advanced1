#include <fstream>
#include <algorithm>
#include <queue>

int peopleWeights[301];
int weightsPerOneBus[301][301];
int optimalWeights[301][101];

int main() {

    std::ifstream cin("c.in");
    std::ofstream cout("c.out");

    int busCount, peopleCount, busCapacity;
    cin >> busCount >> busCapacity >> peopleCount;

    for (int i = 0; i < peopleCount; ++i) {
        cin >> peopleWeights[i];
    }

    for (int counterI = peopleCount - 1; counterI >= 0; --counterI) {
        std::priority_queue<int> currentWeights;
        int currentWeightsSum = 0;
        int currentWeightsSize = 0;

        for (int counterJ = counterI; counterJ < peopleCount; ++counterJ) {

            if (peopleWeights[counterJ] <= busCapacity - currentWeightsSum) {
                currentWeights.push(peopleWeights[counterJ]);
                currentWeightsSum += peopleWeights[counterJ];
                ++currentWeightsSize;
            }
            else {
                int top = currentWeights.top();
                if (top > peopleWeights[counterJ]) {
                    currentWeights.pop();
                    currentWeights.push(peopleWeights[counterJ]);
                    currentWeightsSum += peopleWeights[counterJ] - top;
                }
            }

            weightsPerOneBus[counterI][counterJ] = currentWeightsSize;
        }
    }

    for (int j = 0; j < busCount; ++j) {
        for (int i = peopleCount - 1; i >= 0; --i) {

            optimalWeights[i][j] = std::max(optimalWeights[i][j], weightsPerOneBus[0][i]);
            for (int k = 0; k < i; ++k) {
                optimalWeights[i][j] = std::max(optimalWeights[i][j],
                    optimalWeights[k][j - 1] + weightsPerOneBus[k + 1][i]);
            }
        }
    }

    cout << optimalWeights[peopleCount - 1][busCount - 1];

    cin.close();
    cout.close();

    return 0;
}
