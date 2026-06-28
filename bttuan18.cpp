#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;
const int INF = 1e9;
const int V = 11; 
struct Edge {
    int u, v, weight, id;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};
vector<Edge> edges = {
    {1, 7, 1, 1},   // D1
    {7, 8, 2, 2},   // D2
    {8, 9, 3, 3},   // D3
    {1, 9, 4, 4},   // D4
    {1, 10, 5, 5},  // D5
    {1, 11, 6, 6},  // D6
    {1, 2, 7, 7},   // D7
    {1, 3, 8, 8},   // D8
    {3, 4, 9, 9},   // D9
    {4, 5, 10, 10}, // D10
    {3, 5, 11, 11}, // D11
    {5, 6, 12, 12}, // D12
    {7, 6, 13, 13}  // D13
};
void printMSTMatrix(const vector<Edge>& mstEdges) {
    int matrix[V + 1][V + 1] = {0};
    int totalWeight = 0;
    for (const auto& edge : mstEdges) {
        matrix[edge.u][edge.v] = edge.weight;
        matrix[edge.v][edge.u] = edge.weight;
        totalWeight += edge.weight;
    }
    cout << "\nMA TRAN KE CUA CAY KHUNG NHO NHAT (MST):\n   ";
    for (int i = 1; i <= V; i++) cout << setw(4) << i;
    cout << "\n" << string(50, '-') << "\n";
    for (int i = 1; i <= V; i++) {
        cout << setw(2) << i << " |";
        for (int j = 1; j <= V; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << "\n";
    }
    cout << "Tong trong so cay khung: " << totalWeight << "\n";
}
void dijkstra(int start, int target, const vector<vector<pair<int, int>>>& adj) {
    vector<int> d(V + 1, INF);
    vector<int> parent(V + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    d[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        int u = pq.top().second;
        int du = pq.top().first;
        pq.pop();
        if (du > d[u]) continue;
        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                parent[v] = u;
                pq.push({d[v], v});
            }
        }
    }
    cout << "KET QUA DIJKSTRA (Tu " << start << " den " << target << ")\n";
    cout << "Khoang cach ngan nhat: " << d[target] << "\nDuong di: ";
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());   
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
    }
    cout << "\n\n";
}
void prim(int start, const vector<vector<pair<int, int>>>& adj) {
    vector<bool> visited(V + 1, false);
    vector<Edge> mstEdges;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    visited[start] = true;
    for (auto edge : adj[start]) {
        pq.push({edge.second, {start, edge.first}});
    }
    while (!pq.empty() && mstEdges.size() < V - 1) {
        auto top = pq.top();
        pq.pop();
        int w = top.first;
        int u = top.second.first;
        int v = top.second.second;
        if (visited[v]) continue;
        visited[v] = true;
        mstEdges.push_back({u, v, w, 0});
        for (auto edge : adj[v]) {
            if (!visited[edge.first]) {
                pq.push({edge.second, {v, edge.first}});
            }
        }
    }
    cout << "THUAT TOAN PRIM (Bat dau tu dinh " << start << ")";
    printMSTMatrix(mstEdges);
}
int parent_dsu[V + 1];
int find_set(int v) {
    if (v == parent_dsu[v]) return v;
    return parent_dsu[v] = find_set(parent_dsu[v]);
}
bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        parent_dsu[b] = a;
        return true;
    }
    return false;
}
void kruskal() {
    for (int i = 1; i <= V; i++) parent_dsu[i] = i;
    vector<Edge> mstEdges;
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end());
    for (const auto& edge : sortedEdges) {
        if (union_sets(edge.u, edge.v)) {
            mstEdges.push_back(edge);
        }
    }
    cout << "\nTHUAT TOAN KRUSKAL";
    printMSTMatrix(mstEdges);
}
int main() {
    vector<vector<pair<int, int>>> adj(V + 1);
    for (const auto& edge : edges) {
        adj[edge.u].push_back({edge.v, edge.weight});
        adj[edge.v].push_back({edge.u, edge.weight});
    }
    dijkstra(10, 5, adj);
    prim(10, adj);
    kruskal();
    return 0;
}