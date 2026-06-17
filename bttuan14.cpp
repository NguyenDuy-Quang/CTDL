#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
const int V = 11;
const string vertexNames[V] = {
    "Ha noi",       
    "Son tay",      
    "Hoa binh",     
    "Thai nguyen",  
    "Bac ninh",     
    "Bac giang",   
    "Uong bi",  
    "Hai phong",    
    "Hai duong",    
    "Hung yen",     
    "Phu ly"        
};
const pair<int, int> edges[] = {
    {0, 8},  
    {8, 9},  
    {9, 10}, 
    {0, 10}, 
    {0, 2},  
    {0, 1},  
    {0, 3},  
    {0, 4},  
    {4, 5},  
    {5, 6},  
    {4, 6},  
    {6, 7},  
    {8, 7}   
};
const int E = sizeof(edges) / sizeof(edges[0]);
void BFS_Array(int startVertex) {
    vector<int> adj[V];
    for (int i = 0; i < E; i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool visited[V] = {false};
    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);
    cout << "Thu tu duyet BFS (Mang ke): ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << vertexNames[u] << " -> ";

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "END\n";
}
struct Node {
    int vertex;
    Node* next;
};
void addEdgeLinkedList(Node* adj[], int u, int v) {
    Node* newNode = new Node{v, nullptr};
    if (adj[u] == nullptr) {
        adj[u] = newNode;
    } else {
        Node* temp = adj[u];
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void BFS_LinkedList(int startVertex) {
    Node* adj[V];
    for (int i = 0; i < V; i++) adj[i] = nullptr;
    for (int i = 0; i < E; i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        addEdgeLinkedList(adj, u, v);
        addEdgeLinkedList(adj, v, u);
    }
    bool visited[V] = {false};
    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);
    cout << "Thu tu duyet BFS (Danh sach lien ket): ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << vertexNames[u] << " -> ";
        Node* temp = adj[u];
        while (temp != nullptr) {
            int v = temp->vertex;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
            temp = temp->next;
        }
    }
    cout << "END\n";
    // Giải phóng bộ nhớ
    for (int i = 0; i < V; i++) {
        Node* temp = adj[i];
        while (temp != nullptr) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
}
int main() {
    int start = 0; // Đỉnh 0 là Hà nội
    cout << "--- KET QUA DO THI GIAO THONG (DA CHUAN HOA) ---" << endl << endl;
    BFS_Array(start);
    cout << endl;
    BFS_LinkedList(start);
    return 0;
}