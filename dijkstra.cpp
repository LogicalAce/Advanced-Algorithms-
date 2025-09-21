#include <bits/stdc++.h>
using namespace std;

int n = 9; // number of nodes
int cost[9][9] = {
    {0, 4, 9999, 9999, 9999, 9999, 8, 9999, 9999},
    {4, 0, 8, 9999, 9999, 9999, 11, 9999, 9999},
    {9999, 8, 0, 7, 9999, 4, 9999, 2, 9999},
    {9999, 9999, 7, 0, 9, 14, 9999, 9999, 9999},
    {9999, 9999, 9999, 9, 0, 10, 9999, 9999, 9999},
    {9999, 9999, 4, 14, 10, 0, 9999, 9999, 2},
    {8, 11, 9999, 9999, 9999, 9999, 0, 1, 9999},
    {9999, 9999, 2, 9999, 9999, 9999, 1, 0, 6},
    {9999, 9999, 9999, 9999, 9999, 2, 9999, 6, 0} // 9999 = infinity
};

int getMin(int dist[], bool visited[]) {
    int key = 0;
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            key = i;
        }
    }
    return key;
}

void display(int dist[], int par[]) {
    for (int i = 0; i < n; i++) {
        int temp = par[i];
        cout << i << " <- ";
        while (temp != -1) {
            cout << temp << " <- ";
            temp = par[temp];
        }
        cout << endl;
        cout << "::::Distance = " << dist[i] << endl;
    }
}

void dijkstra(int src) {
    int par[100], dist[100];
    bool visited[100] = {0};
    fill(dist, dist + n, INT_MAX);

    dist[src] = 0;
    par[src] = -1;

    for (int g = 0; g < n - 1; g++) {
        int u = getMin(dist, visited);
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && (dist[u] + cost[u][v]) < dist[v] && cost[u][v] != 9999) {
                par[v] = u;
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }

    display(dist, par);
}

int main() {
    int src;
    cout << "Enter source node (0-8): ";
    cin >> src;
    dijkstra(src);
}
