#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 100; // Maximum number of vertices

class BipartiteGraph {
public:
    int X, Y; // Number of vertices in sets X and Y
    int edges[MAX][MAX]; // Adjacency matrix to represent the graph
    int matchX[MAX], matchY[MAX]; // Arrays to store the matching
    bool visitedX[MAX], visitedY[MAX]; // Arrays to track whether a vertex is already visited in sets X and Y

    // Default constructor
    BipartiteGraph() {
    }

    // Parameterized constructor
    BipartiteGraph(int x, int y) : X(x), Y(y) {
        // Initialize arrays using loops
        for (int i = 0; i < MAX; ++i) {
            for (int j = 0; j < MAX; ++j) {
                edges[i][j] = 0;
            }
            matchX[i] = matchY[i] = -1;
            visitedX[i] = visitedY[i] = false;
        }
    }

    // Copy constructor
    BipartiteGraph(const BipartiteGraph& other) {
        X = other.X;
        Y = other.Y;
        for (int i = 0; i < MAX; ++i) {
            for (int j = 0; j < MAX; ++j) {
                edges[i][j] = other.edges[i][j];
            }
            matchX[i] = other.matchX[i];
            matchY[i] = other.matchY[i];
            visitedX[i] = other.visitedX[i];
            visitedY[i] = other.visitedY[i];
        }
    }

    // Function to add an edge to the graph
    void addEdge(int x, int y) {
        // Avoid self-loops in the matching
        if (x != y) {
            edges[x][y] = 1;
        }
    }

    // Depth-First Search to find augmenting paths
    bool dfs(int x, bool visitedY[]) {
        for (int y = 0; y < Y; ++y) {
            if (edges[x][y] && !visitedY[y]) {
                visitedY[y] = true;
                if (matchY[y] == -1 || (visitedX[matchY[y]] == false && dfs(matchY[y], visitedY))) {
                    matchX[x] = y;
                    matchY[y] = x;
                    return true;
                }
            }
        }
        return false;
    }

    // Augment the matching along a path
    void augmentPath(int x) {
        bool visitedY[MAX];  // Create a local array for visitedY
        for (int i = 0; i < MAX; ++i) {
            visitedY[i] = false;
        }

        if (dfs(x, visitedY)) {
            // Augment the matching
            int y = matchX[x];
            while (y != -1) {
                int nextX = matchY[y];
                matchX[nextX] = -1;
                matchY[y] = -1;
                y = matchX[nextX];
            }
        }
    }

    // Find the maximum matching using augmenting path algorithm
    int maxMatching() {
        int result = 0;
        for (int i = 0; i < MAX; ++i) {
            visitedX[i] = false;
            visitedY[i] = false;
        }

        for (int x = 0; x < X; ++x) {
            if (!visitedX[x] && matchX[x] == -1) {
                bool visitedY[MAX];  // Create a local array for visitedY
                for (int i = 0; i < MAX; ++i) {
                    visitedY[i] = false;
                }

                if (dfs(x, visitedY)) {
                    ++result;
                    visitedX[x] = true;
                }
            }
        }
        return result;
    }

    // Print the edges in the maximum matching
    void printMaximumMatchingEdges() {
        cout << "Edges in Maximum Matching:" << endl;
        for (int x = 0; x < X; ++x) {
            if (matchX[x] != -1) {
                cout << "(" << x << ", " << matchX[x] << ")" << endl;
            }
        }
    }

    // Run augmenting path algorithm for all unmatched vertices
    void augmentingPathAlgorithm() {
        for (int x = 0; x < X; ++x) {
            if (!visitedX[x] && matchX[x] == -1) {
                augmentPath(x);
            }
        }
    }

    // Print the original bipartite graph
    void printGraph() {
        cout << "Bipartite Graph (Edges):" << endl;
        for (int x = 0; x < X; ++x) {
            for (int y = 0; y < Y; ++y) {
                if (edges[x][y] == 1) {
                    cout << "(" << x << ", " << y << ")" << endl;
                }
            }
        }
    }
};

// Function to take user input for bipartite graph
BipartiteGraph& userInputGraph() {
    cout << "\nEnter Vertices In X Graph: ";
    int x;
    cin >> x;
    cout << "\nEnter Vertices In Y Graph: ";
    int y;
    cin >> y;

    // Create bipartite graph
    BipartiteGraph graph(x, y);
    return graph;
}

int main() {
    char ch;
    BipartiteGraph graph;
	here:
    cout << "\nEnter Your Choice:\n\t1. User-Input\n\t2. Hard-Coded Example";
    cin >> ch;

    if (ch == '1') {
        graph = userInputGraph();
        cout << "\nHow many Edges in Your graph?";
        int x;
        cin >> x;

        if (x > 0) {
            for (int i = 0; i < x; i++) {
                cout << "\nEnter Source from X (0...X-1 vertices) :";
                int s;
                cin >> s;
                cout << "\nEnter Target from Y (0...Y-1 vertices) :";
                int t;
                cin >> t;
                graph.addEdge(s, t);
            }
        }
    } else if (ch == '2') {
        // Hard-coded example
        int X = 13; // Number of vertices in set X
        int Y = 13; // Number of vertices in set Y
        BipartiteGraph graph1(X, Y);
        graph = graph1;

        // Add edges to the bipartite graph
        graph.addEdge(0, 7);
        graph.addEdge(1, 8);
        graph.addEdge(2, 7);
        graph.addEdge(3, 7);
        graph.addEdge(3, 8);
        graph.addEdge(3, 9);
        graph.addEdge(4, 8);
        graph.addEdge(4, 9);
        graph.addEdge(5, 9);
        graph.addEdge(5, 10);
        graph.addEdge(6, 8);
        graph.addEdge(6, 11);
        graph.addEdge(6, 12);
    }
    else{
    	cout<<"\nWrong Input....";
    	goto here;
	}

    graph.printGraph();

    // Run the augmenting path algorithm
    graph.augmentingPathAlgorithm();
    int maxMatching = graph.maxMatching();
    cout << "Maximum Matching after Augmenting Path Algorithm: " << maxMatching << endl;

    // Print the edges in the maximum matching
    graph.printMaximumMatchingEdges();

    return 0;
}

