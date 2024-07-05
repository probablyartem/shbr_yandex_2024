#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100;
const long long INFINITY_VAL = 1e18;
int numNodes, numEdges, numQueries, numConditions;
long long distances[MAX_N][MAX_N];
vector<int> queryU, queryV, queryTime, queryCost;
vector<int> conditionA, conditionB, conditionTime;

bool isFeasible(int maxCost) {
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
                floyd[i][j] = min(floyd[i][j], floyd[i][t] + floyd[t][j]);
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

void solve(){
    cin >> numNodes >> numEdges;
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            if (i == j) {
                continue;
            }
            distances[i][j] = INFINITY_VAL;
        }
    }
    for (int i = 0; i < numEdges; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        u--;
        v--;
        distances[u][v] = distances[v][u] = t;
    }
    cin >> numQueries;
    queryU.resize(numQueries), queryV.resize(numQueries), queryTime.resize(numQueries), queryCost.resize(numQueries);
    for (int i = 0; i < numQueries; ++i) {
        cin >> queryU[i] >> queryV[i] >> queryTime[i] >> queryCost[i];
        queryU[i]--;
        queryV[i]--;
    }
    cin >> numConditions;

    conditionA.resize(numConditions), conditionB.resize(numConditions), conditionTime.resize(numConditions);

    for (int i = 0; i < numConditions; ++i) {
        cin >> conditionA[i] >> conditionB[i] >> conditionTime[i];
        conditionA[i]--;
        conditionB[i]--;
    }

    int low = 0, high = 1e9;
    int answer = -1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (isFeasible(mid)) {
            high = mid - 1;
            answer = mid;
        } else {
            low = mid + 1;
        }
    }
    vector<int> validIds;
    for (int i = 0; i < numQueries; ++i) {
        if (queryCost[i] <= answer) {
            validIds.push_back(i + 1);
        }
    }
    if (answer == -1) {
        cout << answer << endl;
        return;
    }
    cout << validIds.size() << endl;
    for (int id : validIds) {
        cout << id << " ";
    }
} 

int main(){
    ios::sync_with_stdio(NULL), cin.tie(0), cout.tie(0);
    int numTests = 1;
    //cin >> numTests;
    while (numTests--) {
        solve();
    }
    return 0;
}