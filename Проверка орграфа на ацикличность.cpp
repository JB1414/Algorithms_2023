#include <iostream>
#include <vector>

using namespace std;

vector<int> restoreCycle(vector<int>& from, int lastVertex) {
    vector<int> cycle = { };
    int v = from[lastVertex];
    while (v != lastVertex) {
        cycle.push_back(v);
        v = from[v];
    }
    cycle.push_back(lastVertex);
    reverse(cycle.begin(), cycle.end());
    return cycle;
}


void dfs(vector<vector<int>>& graph, int v, vector<int>& visited, vector<int>& from, vector<int>& cycle) {
    visited[v] = 1;
    for (int to : graph[v]) {
        if (visited[to] == 0) {
            from[to] = v;
            dfs(graph, to, visited, from, cycle);
            if (!cycle.empty())
                return;
        }
        else if (visited[to] == 1) {
            from[to] = v;
            cycle = restoreCycle(from, to); 
            return;
        }
    }
    visited[v] = 2;
} 
/*
    Формат ввода программы:
    сначала в одной строке написать количество вершин и количество ребер графа
    потом написать все вершины в формате (a b) - значит что есть направленное ребро из вершины а в вершину b
*/

int main() { 
    int vertexNumber;
    int edgeNumber;
    cin >> vertexNumber >> edgeNumber;

    vector<vector<int>> graph(vertexNumber);
    for (int v = 0; v < edgeNumber; v++) {
        int from;
        int to;
        cin >> from >> to;
        from -= 1;
        to -= 1;
        graph[from].push_back(to);
    }
    vector<int> visited(vertexNumber);
    vector<int> restoringCycle(vertexNumber, -1);
    vector<int> cycle;

    for (int currentVertex = 0; currentVertex < vertexNumber; currentVertex++) {
        if (!visited[currentVertex]) {
            dfs(graph, currentVertex, visited, restoringCycle, cycle);
            if (!cycle.empty()) {
                break;
            }
        }
    }

    if (!cycle.empty()) {
        cout << "Found cycle with vertixes: \n";
        for (int i = 0; i < cycle.size(); i++) {
            cout << cycle[i] + 1 << " ";
        }
    }
    else {
        cout << "Еhe graph is acyclic";
    }
}