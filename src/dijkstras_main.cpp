#include "dijkstras.h"
#include <algorithm>

int main() {
    try {
        Graph G;
        file_to_graph("graph.txt", G);
        
        vector<int> previous;
        vector<int> distances = dijkstra_shortest_path(G, 0, previous);
        
        for (int i = 0; i < G.numVertices; i++) {
            vector<int> path = extract_shortest_path(distances, previous, i);
            print_path(path, distances[i]);
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}