#include <bits/stdc++.h>

const int MAX_N = 100;
const long long INFINITY_VAL = 1e18;
int numNodes, numEdges, numQueries, numConditions; 
long long distances[MAX_N][MAX_N]; 

std::vector<int> queryU, queryV, queryTime, queryCost;

std::vector<int> conditionA, conditionB, conditionTime; 

bool IsFeasible(int maxCost) { 
    long long floyd[MAX_N][MAX_N];

    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            floyd[i][j] = distances[i][j];
        }

    }
    for (int i = 0; i < numQueries; ++i) {
            if (queryCost[i] <= maxCost) {
                floyd[queryU[i]][queryV[i]] = queryTime[i];
                floyd[queryV[i]][queryU[i]] = queryTime[i];
            }
        }

    
    for (int t = 0; t < numNodes; ++t) {
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                floyd[i][j] = std::min(floyd[i][j], floyd[i][t] + floyd[t][j]);
            }
        } 
    }

    for (int i = 0; i < numConditions; ++i) {
        if (floyd[conditionA[i]][conditionB[i]] > conditionTime[i]) {
            return false;
        }   
        
    }
   return true;
}

void search() {
    std::cin >> numNodes >> numEdges;

    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            if (i == j) {
                continue;
            }
            distances[i][j] = INFINITY_VAL;
        }
        
    }

    for (int i = 0; i < numEdges; ++i) {
        int u, v , t;
        std::cin >> u >> v >> t;
        u--;
        v--;
        distances[u][v] = distances[v][u] = t;
    }

    std::cin >> numQueries;

    queryU.resize(numQueries), queryV.resize(numQueries), queryTime.resize(numQueries), queryCost.resize(numQueries);

    for (int i = 0 ; i < numQueries; ++i) {
        std::cin >> queryU[i] >> queryV[i] >> queryTime[i] >> queryCost[i];
        queryU[i]--;
        queryV[i]--;
    }
    std::cin >> numConditions;


    conditionA.resize(numConditions), conditionB.resize(numConditions), conditionTime.resize(numConditions);


    for (int i = 0; i < numConditions; ++i) {
        std::cin >> conditionA[i] >> conditionB[i] >> conditionTime[i];
        conditionA[i]--;
        conditionB[i]--;
    }

    int low = 0, high = 1e9;
    int answer = -1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (IsFeasible(mid)) {
            high = mid - 1;
            answer = mid;
        } else {
            low = mid + 1;
        }
    }
    std::vector<int> validIds;
    for (int i = 0; i < numQueries; ++i) {
        if (queryCost[i] <= answer) {
            validIds.push_back(i + 1);
        }
    }
    if (answer == -1) {
        std::cout << answer << std::endl;
        return;
    }
    std::cout << validIds.size() << std::endl;
    for (int id : validIds) {
        std::cout << id << " ";
    }
} 

int main(){
    std::ios::sync_with_stdio(NULL), std::cin.tie(0), std::cout.tie(0);
    int numTests = 1;
    //cin >> numTests;
    while (numTests--) {
        search();
    }
    return 0;
}
    