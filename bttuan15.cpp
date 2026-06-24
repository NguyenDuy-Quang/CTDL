#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
const int V = 11;
const string vertexNames[V] = {
    "Ha noi",     // 0
    "Son Tay",    // 1
    "Hoa Binh",   // 2
    "Thai Nguyen",// 3
    "Bac Ninh",   // 4
    "Bac Giang",  // 5
    "Uong bi",    // 6
    "Hai phong",  // 7
    "Hai duong",  // 8
    "Hung yen",   // 9
    "Phu ly"      // 10
};
vector<int> adj[V];
void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}
void initGraph() {
    addEdge(0, 8);  // D1: Hà nội - Hải dương
    addEdge(8, 9);  // D2: Hải dương - Hưng yên
    addEdge(9, 10); // D3: Hưng yên - Phủ lý
    addEdge(0, 10); // D4: Hà nội - Phủ lý
    addEdge(0, 2);  // D5: Hà nội - Hòa bình
    addEdge(0, 1);  // D6: Hà nội - Sơn tây
    addEdge(0, 3);  // D7: Hà nội - Thái nguyên
    addEdge(0, 4);  // D8: Hà nội - Bắc ninh
    addEdge(4, 5);  // D9: Bắc ninh - Bắc giang
    addEdge(5, 6);  // D10: Bắc giang - Uông bí
    addEdge(4, 6);  // D11: Bắc ninh - Uông bí
    addEdge(6, 7);  // D12: Uông bí - Hải phòng
    addEdge(8, 7);  // D13: Hải dương - Hải phòng
}
void findShortestPathBFS(int start, int target) {
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);   
    vector<int> dist(V, -1);     

    queue<int> q;
    visited[start] = true;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == target) break;
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;         
                dist[v] = dist[u] + 1; 
                q.push(v);
            }
        }
    }
    cout << "KET QUA TIM DUONG DI NGAN NHAT :\n";
    cout << "Tu: " << vertexNames[start] << " -> Den: " << vertexNames[target] << "\n";
    if (dist[target] == -1) {
        cout << "Khong co duong di giua hai tinh nay!" << endl;
        return;
    }
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end()); 
    cout << "Lo trinh: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << vertexNames[path[i]];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\nSo chang di qua: " << dist[target] << " chang duong." << endl;
    cout << "\n";
}

int main() {
    initGraph();
    cout << " DANH SACH CAC TINH THANH CHON LUA " << endl;
    for (int i = 0; i < V; i++) {
        cout << i << ". " << vertexNames[i] << endl;
    }
    int xuatPhat, diemDen;
    cout << "Nhap ma so tinh XUAT PHAT: ";
    cin >> xuatPhat;
    cout << "Nhap ma so tinh DEN: ";
    cin >> diemDen;
    if (xuatPhat < 0 || xuatPhat >= V || diemDen < 0 || diemDen >= V) {
        cout << "Ma tinh nhap khong hop le!" << endl;
    } else {
        findShortestPathBFS(xuatPhat, diemDen);
    }
    return 0;
}