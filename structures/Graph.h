#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <limits>
#include <stack>

// Simple undirected weighted graph for campus navigation
class Graph {
private:
    struct Edge {
        int to;
        int weight;
    };

    std::vector<std::string> locations;
    std::unordered_map<std::string, int> locIndex;
    std::vector<std::vector<Edge>> adj;

public:
    void addLocation(const std::string& name) {
        if (locIndex.count(name) == 0) {
            locIndex[name] = locations.size();
            locations.push_back(name);
            adj.push_back({});
        }
    }

    void addEdge(const std::string& from, const std::string& to, int weight) {
        addLocation(from);
        addLocation(to);
        int u = locIndex[from];
        int v = locIndex[to];
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // undirected
    }

    void printShortestPath(const std::string& start, const std::string& end) {
        if (locIndex.count(start) == 0 || locIndex.count(end) == 0) {
            std::cout << "Lokasi tidak ditemukan.\n";
            return;
        }
        int n = locations.size();
        std::vector<int> dist(n, std::numeric_limits<int>::max());
        std::vector<int> prev(n, -1);
        std::vector<bool> visited(n, false);

        int s = locIndex[start];
        dist[s] = 0;
        using P = std::pair<int, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        pq.push({0, s});
        while (!pq.empty()) {
            int d = pq.top().first, u = pq.top().second; pq.pop();
            if (visited[u]) continue;
            visited[u] = true;
            for (const Edge& e : adj[u]) {
                if (dist[e.to] > dist[u] + e.weight) {
                    dist[e.to] = dist[u] + e.weight;
                    prev[e.to] = u;
                    pq.push({dist[e.to], e.to});
                }
            }
        }
        int t = locIndex[end];
        if (dist[t] == std::numeric_limits<int>::max()) {
            std::cout << "Tidak ada jalur dari " << start << " ke " << end << ".\n";
            return;
        }
        std::stack<int> path;
        for (int at = t; at != -1; at = prev[at])
            path.push(at);

        std::cout << "Jalur terpendek dari " << start << " ke " << end << " (berjarak " << dist[t] << "):\n";
        while (!path.empty()) {
            std::cout << locations[path.top()];
            path.pop();
            if (!path.empty()) std::cout << " -> ";
        }
        std::cout << std::endl;
    }

    void printLocations() const {
        std::cout << "Lokasi kampus:\n";
        for (const auto& loc : locations)
            std::cout << "- " << loc << std::endl;
    }
};

#endif // GRAPH_H