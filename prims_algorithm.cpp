#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

int parent[1005], rnk[1005];

int findSet(int x) {
    if (parent[x] == x) return x;
    return parent[x] = findSet(parent[x]);
}

void unionSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            parent[a] = b;
        else if (rnk[a] > rnk[b])
            parent[b] = a;
        else {
            parent[b] = a;
            rnk[a]++;
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges;

    vector<pair<int,int>> adj[1005];

    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int root;
    cin >> root;

    /* ================= PRIM'S ALGORITHM ================= */

    bool visited[1005] = {false};
    int key[1005], par[1005];

    for (int i = 0; i < N; i++) {
        key[i] = INT_MAX;
        par[i] = -1;
    }

    key[root] = 0;

    int primCost = 0;

    for (int count = 0; count < N; count++) {
        int u = -1;

        for (int i = 0; i < N; i++) {
            if (!visited[i] && (u == -1 || key[i] < key[u]))
                u = i;
        }

        visited[u] = true;
        primCost += key[u];

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (!visited[v] && w < key[v]) {
                key[v] = w;
                par[v] = u;
            }
        }
    }

    cout << "Prim's Algorithm\n";
    cout << "Total weight " << primCost << "\n";
    cout << "Root node " << root << "\n";
    for (int i = 0; i < N; i++) {
        if (par[i] != -1)
            cout << par[i] << " " << i << "\n";
    }

    cout << "\n";
}
