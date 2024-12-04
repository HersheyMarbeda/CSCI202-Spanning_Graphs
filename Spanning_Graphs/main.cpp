/*
    Program Name: Spanning Graphs
    
    Programmer Name: Hershey Marbeda
    Due Date: 12.9.2024
 
    Last Date Updated: 12.04.2024
    Purpose of the Program: To implement Fluery's Algorithm to find the
                            Eulerian Path or Circuit in a graph.
    
 */

#include <algorithm>
#include <iostream>
#include <list>
#include <string.h>

using namespace std;

class Graph
{
    int V;               // No. of vertices
    list<int>* adj;      // Adjacency lists
    
public:
    // Constructor and destructor
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() { delete[] adj; }
    
    // Functions to add and remove edges
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void rmvEdge(int u, int v);
    
    // Methods to print Eulerian tour
    void printEulerTour();
    void printEulerUtil(int s);
    
    // This function returns count of vertices reachabl from v. It does DFS
    int DFSCount(int v, bool visited[]);
    
    // Utility function to check if edge u-v is a valid next edge in Eulerian trail or circuit
    bool isValidNextEdge(int u, int v);
};

// The main function that prints Eulerian Trail.
void Graph::printEulerTour()
{
    // Find a vertex with odd degree
    int u = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1)
        {
            u = i;
            break;
        }
    
    // Print tour starting from the odd vertex
    printEulerUtil(u);
    cout << endl;
}

// Print Euler tour starting from vertex u
void Graph::printEulerUtil(int u)
{
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;
        
        // If edge u-v is not removed and it's a valid next edge
        if (v != -1 && isValidNextEdge(u, v))
        {
            cout << u << "-" << v << " ";
            rmvEdge(u, v);
            printEulerUtil(v);
        }
    }
}

// The function to check if edge u-v can be considered as the next edge in Eulerian Tour
bool Graph::isValidNextEdge(int u, int v)
{
    // The edge u-v is valid in one of the following two cases:
    
    // 1) If v is the only adjacent vertex of u
    int count = 0; // To store the count of adjacent vertices
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
        if (*i != -1)
            count++;
    if (count == 1)
        return true;
    
        // 2) If there are multiple adjacents, then u-v is not a
        // bridge. Do the following steps to check if u-v is a bridge:
    
        // 2.a) Count vertices reachable from u
    bool visited[V];
    memset(visited, false, V);
    int count1 = DFSCount(u, visited);
    
    // 2.b) Remove edge (u, v) and after removing the edge, count vertices reachable from u
    rmvEdge(u, v);
    memset(visited, false, V);
    int count2 = DFSCount(u, visited);
    
    // 2.c) Add the edge back to the graph
    addEdge(u, v);
    
    // 2.d) If count1 is greater, then edge (u, v) is a bridge
    return (count1 > count2) ? false : true;
}

// This function removes edge u-v from the graph. It removes the edge by replacing the adjacent vertex value with -1.
void Graph::rmvEdge(int u, int v)
{
    // Find v in adjacency list of u and replace it with -1
    list<int>::iterator iv
    = find(adj[u].begin(), adj[u].end(), v);
    *iv = -1;
    
    // Find u in adjacency list of v and replace it with -1
    list<int>::iterator iu
    = find(adj[v].begin(), adj[v].end(), u);
    *iu = -1;
}

// A DFS-based function to count reachable vertices from v
int Graph::DFSCount(int v, bool visited[])
{
    // Mark the current node as visited
    visited[v] = true;
    int count = 1;
    
    // Recur for all vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (*i != -1 && !visited[*i])
            count += DFSCount(*i, visited);
    
    return count;
}


int main()
{
    // Table Heading
    cout << string(100, '-') << endl
         << "\t\t\t\t\t\t\t\t\t\tSpanning Graphs\n"
         << "\t\t\t\t\t\tFluery's Algorithm to find Eulerian Path or Circuit\n"
         << string(100, '-') << endl;
    
    // Declaration of variables
    int V, E;
    
    
    /*                  Start of Main Prompt for User                     */
    
    cout << "Enter the number of Vertices: ";
    cin >> V;
    
    // Input Validation
    while (cin.fail() || V <= 0)
    {
        cin.clear();
        cin.ignore();
        cout << "\nInvalid Input. Please enter the number of Vertices: ";
        cin >> V;
    }
    
    Graph g(V);
    
    cout << "Enter the number of Edges: ";
    cin >> E;
    
    // Input Validation
    while (cin.fail() || E < 0 || E > (V * (V - 1)) / 2)
    {
        cin.clear();
        cin.ignore();
        cout << "\nInvalid Input. Please enter the number of Edges (valid range: 0 to " << (V * (V - 1)) / 2 << "): ";
        cin >> E;
    }
    
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        
        // Input Validation for each edge
        while (cin.fail() || u < 0 || v < 0 || u >= V || v >= V || u == v)
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid edge (" << u << " " << v << "). Please enter valid vertices (0 <= u, v < " << V << " and u != v): ";
            cin >> u >> v;
        }
        
        g.addEdge(u, v);
    }
    
    cout << "\nEulerian Path or Circuit: ";
    g.printEulerTour();
    
    // to make it readable to screen
    cout << endl << endl;
    
    return 0;
}

