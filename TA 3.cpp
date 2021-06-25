#include<iostream>
#include<stack>
#include <list> 

using namespace std;
class Graph
{
    int V;
    list<int>* adj;
    void fillOrder(int v, bool visited[], stack<int>& Stack);
    void DFSUtil(int v, bool visited[]);
public:
    Graph(int V);
    void addEdge(int v, int w);
    void printSCCs();
    Graph getTranspose();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::DFSUtil(int v, bool visited[])
{
    visited[v] = true;
    cout << v << " ";

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::fillOrder(int v, bool visited[], stack<int>& Stack)
{

    visited[v] = true;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            fillOrder(*i, visited, Stack);


    Stack.push(v);
}


void Graph::printSCCs()
{
    stack<int> Stack;
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            fillOrder(i, visited, Stack);

    Graph gr = getTranspose();

    for (int i = 0; i < V; i++)
        visited[i] = false;


    while (Stack.empty() == false)
    {
        int v = Stack.top();
        Stack.pop();
        if (visited[v] == false)
        {
            gr.DFSUtil(v, visited);
            cout << endl;
        }
    }
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void findComponent(int u, int disc[], int low[], stack<int>& stk, bool stkItem[], int NODE, int** graph) {
    static int time = 0;
    disc[u] = low[u] = ++time;
    stk.push(u);
    stkItem[u] = true;

    for (int v = 0; v < NODE; v++) {
        if (graph[u][v]) {
            if (disc[v] == -1) {
                findComponent(v, disc, low, stk, stkItem, NODE, graph);
                low[u] = min(low[u], low[v]);
            }
            else if (stkItem[v])
                low[u] = min(low[u], disc[v]);
        }
    }

    int poppedItem = 0;
    if (low[u] == disc[u]) {
        while (stk.top() != u) {
            poppedItem = stk.top();
            cout << poppedItem << " ";
            stkItem[poppedItem] = false;
            stk.pop();
        }
        poppedItem = stk.top();
        cout << poppedItem << endl;
        stkItem[poppedItem] = false;
        stk.pop();
    }
}

void strongConComponent(int NODE, int** graph) {
    int disc[NODE], low[NODE];
    bool stkItem[NODE];
    stack<int> stk;

    for (int i = 0; i < NODE; i++) {
        disc[i] = low[i] = -1;
        stkItem[i] = false;
    }

    for (int i = 0; i < NODE; i++)
        if (disc[i] == -1)
            findComponent(i, disc, low, stk, stkItem, NODE, graph);
}

void kosaraju() {
    int num, check;
    int a, b;
    int c[50][50];
    do {
        cout << "Enter number of vertexes: ";
        check = scanf("%d", &num);
        if (check != 1 || num > 50 || num <= 1) {
            cout << "Try again!\n";
            fflush(stdin);
        }
    } while (!check || num > 50 || num <= 1);
    cout << num << endl;
    int i, j;
    Graph g(num);
    cout << "Enter matrix:\n";

    for (i = 0; i < num; i++)
    {
        for (j = 0; j < num; j++) {
            do {
                check = scanf("%d", &c[i][j]);
                if (!check) { cout << "Try again!\n"; fflush(stdin); }
            } while (check != 1);
        }
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (c[i][j] == 1) {
                g.addEdge(i, j);
            }
        }
    }
    cout << "Your SCC:\n";
    g.printSCCs();
}

void tarjan() {
    int NODE, check;
    do {
        cout << "Enter number of vertexes: ";
        check = scanf("%d", &NODE);
        if (check != 1 || NODE <= 1) {
            cout << "Try again!\n";
            fflush(stdin);
        }
    } while (!check || NODE <= 1);
    int i, j;
    int** graph = new int* [NODE];
    for (int i = 0; i < NODE; ++i)
        graph[i] = new int[NODE];

    cout << "Enter matrix:\n";
    for (i = 0; i < NODE; i++)
    {
        for (j = 0; j < NODE; j++) {
            do {
                check = scanf("%d", &graph[i][j]);
                if (!check) { cout << "Try again!\n"; fflush(stdin); }
            } while (check != 1);
        }
    }
    cout << "Your SCC:\n";
    strongConComponent(NODE, graph);
    for (int i = 0; i < NODE; ++i)
        delete[] graph[i];
    delete[] graph;
}

int main() {
    int type, check;
    do {
        cout << "1: Tarjan's algorithm\n2: Kosaraju's algorithm\nChoose algorithm: ";
        check = scanf("%d", &type);
        if (check != 1 || (type != 1 && type != 2)) {
            cout << "Try again!\n";
            fflush(stdin);
        }
    } while (check != 1 || (type != 1 && type != 2));
    if (type == 1) tarjan();
    else kosaraju();
    return 0;
}
