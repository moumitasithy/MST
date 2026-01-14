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

    

    /* ================= KRUSKAL'S ALGORITHM ================= */

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }

    // simple bubble sort by weight
    for (int i = 0; i < edges.size(); i++) {
        for (int j = i + 1; j < edges.size(); j++) {
            if (edges[i].w > edges[j].w)
                swap(edges[i], edges[j]);
        }
    }

    int kruskalCost = 0;

    cout << "Kruskal's Algorithm\n";

    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (findSet(u) != findSet(v)) {
            unionSet(u, v);
            kruskalCost += w;
            cout << u << " " << v << "\n";
        }
    }

    cout << "Total weight " << kruskalCost << "\n";

    return 0;
}
