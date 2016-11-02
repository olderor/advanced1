//  Created by olderor on 22.10.16.
//  Copyright © 2016 olderor. All rights reserved.

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

int busCount, peopleCount, busCapacity;

std::vector<int>              peopleWeights;
std::vector<std::vector<int>> weightsPerOneBus;
std::vector<std::vector<int>> optimalWeights;


void clearData() {
    peopleWeights.clear();
    busCount = 0;
    peopleCount = 0;
    busCapacity = 0;
}

void readData(std::istream& _Istr) {

    clearData();

    _Istr >> busCount >> busCapacity >> peopleCount;

    peopleWeights.resize(peopleCount);

    for (int i = 0; i < peopleCount; ++i) {
        _Istr >> peopleWeights[i];
    }
}

void setWeightsPerOneBus() {

    weightsPerOneBus.clear();
    weightsPerOneBus.resize(peopleCount, std::vector<int>(peopleCount));

    for (int peopleStartIndex = peopleCount - 1; peopleStartIndex >= 0; --peopleStartIndex) {

        std::priority_queue<int> currentWeights;
        int currentWeightsSum = 0;
        int currentWeightsSize = 0;

        for (int peopleEndIndex = peopleStartIndex; peopleEndIndex < peopleCount; ++peopleEndIndex) {

            if (peopleWeights[peopleEndIndex] <= busCapacity - currentWeightsSum) {
                currentWeights.push(peopleWeights[peopleEndIndex]);
                currentWeightsSum += peopleWeights[peopleEndIndex];
                ++currentWeightsSize;
            }
            else {
                const int top = currentWeights.top();
                if (top > peopleWeights[peopleEndIndex]) {
                    currentWeights.pop();
                    currentWeights.push(peopleWeights[peopleEndIndex]);
                    currentWeightsSum += peopleWeights[peopleEndIndex] - top;
                }
            }

            weightsPerOneBus[peopleStartIndex][peopleEndIndex] = currentWeightsSize;
        }
    }
}

void setOptimalWeights() {

    optimalWeights.clear();
    optimalWeights.resize(peopleCount, std::vector<int>(busCount, 0));

    for (int j = 0; j < busCount; ++j) {
        for (int i = peopleCount - 1; i >= 0; --i) {

            optimalWeights[i][j] = std::max(optimalWeights[i][j], weightsPerOneBus[0][i]);

            if (j == 0) {
                continue;
            }

            for (int k = 0; k < i; ++k) {
                optimalWeights[i][j] = std::max(optimalWeights[i][j],
                    optimalWeights[k][j - 1] + weightsPerOneBus[k + 1][i]);
            }
        }
    }
}

int solveProblem() {
    setWeightsPerOneBus();
    setOptimalWeights();
    return optimalWeights[peopleCount - 1][busCount - 1];
}

void writeData(std::ostream& _Istr, int data) {
    _Istr << data << std::endl;
}

int main() {

    readData(std::cin);
    const int answer = solveProblem();
    writeData(std::cout, answer);

    return 0;
}
