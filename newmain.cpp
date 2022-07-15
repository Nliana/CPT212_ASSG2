#include <bits/stdc++.h>
#include <iostream>
using namespace std;
# define INF 0x3f3f3f3f

class Graph {
	
   int V;
   list<pair<int, int>> *adj;
   list<int> *adjNoWt;
   void isSCUtil(int u, bool visited[]);		// A recursive function to print DFS starting from v
   bool isCyclicUtil(int v, bool visited[], bool *recurStack);		// A recursive function to print DFS starting from v
   
   public:
	// Constructor	
   Graph(int V) {
      this->V = V;
      adj = new list<pair<int,int>>[V];
      adjNoWt = new list<int>[V];
   }
   
   // Destructor
   ~Graph() {
      delete [] adj;
      delete [] adjNoWt;
   }
   
   void addEdge(int u, int v, int w);	// To add a new edge
   void addEdge2(int u, int v); // To add new edge without weight
   //void deleteEdge(int u, int v); // To delete existing edge
   void addRandomEdge(); // Add random edge
   void printGraph();	// To print graph
   bool isStronglyConnected();	// To check whether graph is strongly connected
   bool isCyclic();		// To check whether graph contains cycle
   Graph transpose();	// To create a reverse graph
   void shortestPath(int u, int v); // To output shortest path between source and destination
};

void menu(){
	
   cout << "\n\n\n\n\n";
   cout << "\t\t\t\t\t\tWELCOME\n\n";
   cout << "*************************************************************************************************************\n\n";
   cout << "\t\tThis program displays the default graph in the form of adjacency list.\n";
   cout << "\tThe graph consists of 5 cities represented by integer 0 to 4 and the distance between connected cities.\n\n";
   cout << "*************************************************************************************************************\n\n";
   cout << "\t\t\t\t    The cities are:\n";
   cout << "\t\t\t\t    0 - \t Dublin, Ireland\n";
   cout << "\t\t\t\t    1 - \t Kigali, Rwanda\n";
   cout << "\t\t\t\t    2 - \t Split, Croatia\n";
   cout << "\t\t\t\t    3 - \t Copenhagen, Denmark\n";
   cout << "\t\t\t\t    4 - \t Raykjavik, Iceland\n";
   cout << "\n***********************************************************************************************************";
   cout << "\n\n\n";
   
   cout << "\t\t   This program can do the following on the default graph:\n";
   cout << "\t\t   1: \t Check if the graph is strongly connected.\n";
   cout << "\t\t   2: \t Check if the graph contains any cycle.\n";
   cout << "\t\t   3: \t Find the shortest path betweent two cities.\n";
   cout << "\t\t   4: \t Find the minimum spanning tree between several cities.\n";
   cout << "\t\t   5: \t Remove edge from the graph.\n";
   cout << "\t\t   6: \t Reset the graph to default.\n";
	
}

// Recursive function to print DFS starting from ver used by isStronglyConnected()
void Graph::isSCUtil(int ver, bool VISITED[]) {
   VISITED[ver] = true; // assign true value, showing that have visited the vertex
   // other adjacent vertices to the vertex above are also set to true
   list<int>::iterator i;
    for (i = adjNoWt[ver].begin(); i != adjNoWt[ver].end(); ++i) 
   		if (!VISITED[*i])
		   isSCUtil(*i, VISITED);
}

// Recursive function to print DFS starting from v used by isCyclic()
bool Graph::isCyclicUtil(int ver, bool VISITED[], bool *recurStack)
{
    if(VISITED[ver] == false)
    {
        VISITED[ver] = true;
        recurStack[ver] = true;
        
        list<int>::iterator i;
    	for (i = adjNoWt[ver].begin(); i != adjNoWt[ver].end(); ++i)
        {
        	if ( !VISITED[*i] && isCyclicUtil(*i, VISITED, recurStack) )
                return true;
            else if (recurStack[*i])
                return true; 
        }
    }
    recurStack[ver] = false; // Remove vertex from recursion stack
    return false;
}

// Function to reverse graph used by isStronglyConnected()
Graph Graph::transpose() {
   Graph G(V); // intialise object and variable
   int wt;
   for (int v = 0; v < V; v++) { // reversing graph
      	list<int>::iterator i;
        for(i = adjNoWt[v].begin(); i != adjNoWt[v].end(); ++i)
            G.adjNoWt[*i].push_back(v);
   }
   return G;
}

// Function to add new edge into adjacency list used by main()
void Graph::addEdge(int u, int v, int w) {
   adj[u].push_back(make_pair(v, w)); // function call
}

// Function to add new edge without weight
void Graph::addEdge2(int u, int v) {
   adjNoWt[u].push_back(v); // function call
}

// Function to add random edge
void Graph::addRandomEdge() {
	// Initialise variables
	int distance;
	int randSrc= rand()%5;
	int randDest= rand()%5;
	// inputting into adjacent list according to user choice
	switch(randSrc) {
		case 0:
			if (randDest==2) {
				distance=1988;
				adj[0].push_back(make_pair(2, 1988));
				adjNoWt[0].push_back(2);
			}
			else if (randDest==3) {
				distance=1239;
				adj[0].push_back(make_pair(3, 1239));
				adjNoWt[0].push_back(3);
			}
			
		case 1:
			if (randDest==3) {
				distance=6602;
				adj[1].push_back(make_pair(3, 6602));
				adjNoWt[1].push_back(2);
			}
			else if (randDest==4) {
				distance=8478;
				adj[1].push_back(make_pair(4, 8478));
				adjNoWt[1].push_back(4);
			}
			
		case 2:
			if (randDest==0) {
				distance=1988;
				adj[2].push_back(make_pair(0, 1988));
				adjNoWt[2].push_back(0);
			}
			else if(randDest==4) {
				distance=3318;
				adj[2].push_back(make_pair(4, 3318));
				adjNoWt[2].push_back(4);
			}

		case 3:
			if (randDest==0) {
				distance=1239;
				adj[3].push_back(make_pair(0, 1239));
				adjNoWt[3].push_back(0);
			}
			else if(randDest==1) {
				distance=6602;
				adj[3].push_back(make_pair(1, 6602));
				adjNoWt[3].push_back(1);
			}

		case 4:
			if (randDest==1) {
				distance=8478;
				adj[4].push_back(make_pair(1, 8478));
				adjNoWt[4].push_back(1);
			}
			else if(randDest==2) {
				distance=3318;
				adj[4].push_back(make_pair(2, 3318));
				adjNoWt[4].push_back(2);
			}

		default:
			break;
	}
}

/* Function to delete edge 
void Graph::deleteEdge(int u, int v){
	
	// remove edge from u to v
   list<pair<int, int>> it = find (adj[u].begin(), adj[u].end(), v);
   adj[u].erase(v);
   
}*/

// Function to print the resulting adjacency list used by main()
void Graph::printGraph() {
	int v, w; // initialise variable
	for (int u = 0; u < V; u++) { // looping throught the adjacent list and print the contents
		for (auto i = adj[u].begin(); i!=adj[u].end(); ++i)
        {
            v = i->first;
            w = i->second;
	    cout << "\t\t" << u;
            cout << " -> (" << v << ", " << w << ")";
        }
        cout << endl;
	}
	cout << endl;
}

// Function 1
// Function that shows graph is strongly connected by returning true 
bool Graph::isStronglyConnected() {
   
   bool VISITED[V]; // initialise the variable
   for (int i = 0; i < V; i++) // for loop to loop all the vertices to be false
   		VISITED[i] = false;
   	
   isSCUtil(0, VISITED); // function call to DFS the graph starting from 0
   
   for (int i = 0; i < V; i++) // for loop to check if there is still any vertices unvisited
      if (VISITED[i] == false) // if there is any vertices unvisited, return false
         return false; 
         
   Graph greverse = transpose(); // initialising object and assigning it with reversed graph
   
   for(int i = 0; i < V; i++) // for loop to loop all the vertices to be false
      VISITED[i] = false;
	
   greverse.isSCUtil(0, VISITED); // function call to DFS the reversed graph starting from 0
   
   for (int i = 0; i < V; i++) // for loop to check if there is still any vertices unvisited
      if (VISITED[i] == false)  // if there is any vertices unvisited, return false
         return false;
         
   return true; // if graph strongly connected return true
}


// Function 2
// Function that returns true if graph contains cycle
bool Graph::isCyclic()
{
    bool *visited = new bool[V];
    bool *recurStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recurStack[i] = false;
    }
  
    for(int i = 0; i < V; i++)
        if ( !visited[i] && isCyclicUtil(i, visited, recurStack))
            return true;
  
    return false;
}

// Function 3
// Function that prints shortest path between two vertices from user inputs
void Graph::shortestPath(int src, int dest) {
	
	set<pair<int,int>> setds;
	vector<int> dist(V,INF);
	setds.insert(make_pair(0, src));
    dist[src] = 0;
    while (!setds.empty())
    {
        pair<int, int> temp = *(setds.begin());
        setds.erase(setds.begin());
 
        int u = temp.second;
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = i->first;
            int w = i->second;
 
            if (dist[v] > dist[u] + w)
            {
                if (dist[v] != INF)
                    setds.erase(setds.find(make_pair(dist[v], v)));
                    
                dist[v] = dist[u] + w;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }
    cout << "\n\t\t     Shortest path from " << src << " to " << dest << ": " << dist[dest] << endl;
}

	
int main() {
   
   // Initialising the variables
   char start;
   int choice = 0;
   
   // Initialising object graph
   Graph graph(5);
   // Calling menu function
   menu();
   
   cout << "\n\n\n";
   cout << "\t\t   Enter Y to start: ";
   cin >> start; // Input from user
   
   // Will loop if user do not input 'y' or 'Y'
   while (start != 'y' && start != 'Y')
		{
			cout << "\t\t   PLEASE ENTER 'y' OR 'Y' ONLY:";
			cin >> start;
		}
	// clear command prompt		
   system("CLS");
	// if conditional statement has to be true for the contents to be run
   if (start=='y' || start=='Y') {
   		system("CLS");
   		cout << "\n\n\n\n\n";
   		cout << "Program is building the default graph. . .\n";
		
		// function call for adding edge into adjacent list
		graph.addEdge(0, 1, 7009);
		graph.addEdge(1, 2, 5234);
		graph.addEdge(2, 3, 1381);
		graph.addEdge(3, 4, 2107);
		graph.addEdge(0, 4, 1495);
		
		graph.addEdge2(0, 1);
		graph.addEdge2(1, 2);
		graph.addEdge2(2, 3);
		graph.addEdge2(3, 4);
		graph.addEdge2(0, 4);
	}
 
	// do while is used to loop the program 
   do {	
		system("CLS"); //clear command prompt
   		// output to user to understand how graph is displayed
   		cout << "The graph is represented like this example: \n";
   		cout << "\n\t\t\t '0 -> (1, 7009)' ";
   		cout << "\n\n (0 is source, -> is the directed edge pointing to, 1 is the destination and 7009 is the weight)\n";
   		
   		cout << "\nThis is the default graph\n\n";
   		graph.printGraph(); // printing the graph 
   		
   		cout << "\t\t\t    The cities are:\n";
   		cout << "\t\t\t    0 - \t Dublin, Ireland\n";
   		cout << "\t\t\t    1 - \t Kigali, Rwanda\n";
   		cout << "\t\t\t    2 - \t Split, Croatia\n";
   		cout << "\t\t\t    3 - \t Copenhagen, Denmark\n";
   		cout << "\t\t\t    4 - \t Raykjavik, Iceland\n";
   
   		cout << "\nPlease choose what would you like to do...\n\n";
   		cout << "*************************************************************\n";
   		cout << "1. Check if the graph is strongly connected.\n";
   		cout << "2. Check if the graph contains any cycle.\n";
   		cout << "3. Find the shortest path betweent two cities.\n";
   		cout << "4. Find the minimum spanning tree between several cities.\n";
   		cout << "5: Remove edge from the graph.\n";
        cout << "6: Reset the graph to default.\n";
   		cout << "*************************************************************\n\n";
		//asking for user input
   		cout << "Please enter 1, 2, 3, 4, 5 or 6: ";
   		cin >> choice;
   		// Will loop if user do not input the correct no. from 1-6
   		while (choice < 0 && choice > 6)
		{
			cout << "PLEASE ENTER 1, 2, 3 4, 5 OR 6 ONLY:";
			cin >> choice;
		}
	
		// switch use to enable a systematic program 
		switch (choice)
		{
			// Outputs the results for strong connectivity function
		case 1: system("CLS");
			cout << "\n\n\n\n\n";
   			cout << "\t\t     Program is checking connectivity within the default graph. . .\n";
   			cout << "\n\t\t     "; 
			system("PAUSE"); // system pause
   			cout << "\n\n\n";
   			// if graph is strongly connected
   			if (graph.isStronglyConnected()) {
   				cout << "\t\t     This graph is strongly connected.\n";
   				cout << "\n\n";
   				graph.printGraph(); // print graph
			}
			// if graph is not strongly connected
			else {
				cout << "\t\t     This graph is not strongly connected.\n";
   				cout << "\n\n";
   				cout << "\t\t     Program is adding random edges to the default graph. . .\n";
   				// random edge will be added until graph is strongly connected
   				while (graph.isStronglyConnected()==false) {
   					graph.addRandomEdge();
				}
				cout << "\n\n\t\t     Graph is finally strongly connected!\n";
				cout << "\n\t\t     Displaying the new graph. . .\n";
   				cout << "\n\t\t     ";
				system("PAUSE");
   				cout << "\n\n";
   				graph.printGraph();
			}
			break;
		// outputs the results for whether the graph contains cycle or not 
		case 2: system("CLS");
			cout << "\n\n\n\n\n";
   			cout << "\t\t     Program is checking whether the graph contains cycle. . .\n";
   			cout << "\n\n\t\t     ";
   			system("PAUSE");
			cout << "\n\n\n";
   			// if graph is cyclic
   			if (graph.isCyclic()) {
   				cout << "\t\t     This graph contains cycle.\n";
   				cout << "\n\n";
   				graph.printGraph();
			}
			// if graph is not cyclic, a random edge will be added until graph is cyclic
			else {
				cout << "\t\t     This graph does not contain cycle.\n";
   				cout << "\n\n";
   				cout << "\t\t     Program is adding random edges to the default graph. . .\n";
   				// adding random edge, when there is no cycle
   				while (graph.isCyclic()==false) {
   					graph.addRandomEdge();
				}
				cout << "\n\t\t     Graph finally contains cycle!\n";
				cout << "\n\t\t     Displaying the new graph. . .\n";
   				cout << "\n\t\t     ";
				system("PAUSE");
   				cout << "\n\n";
   				graph.printGraph();
			}
			break;
		// outputs the shortest path for the graph	
		case 3: system("CLS");
			cout << "\n\n\n\n\n";
   			int src, dest;
		    cout<<"\t\t     Choose the first city as the source - 0, 1, 2, 3, or 4: ";
		    cin >> src; // accepts user input for the source vertex
		    cout << "\n\t\t     Choose the second city as the destination - 0, 1, 2, 3, or 4: ";
		    cin >> dest; // accepts user input for the destination vertex
		    cout << "\n\n\n";
		    cout << "\t\t     Program is calculating the shortest path between " << src << " and " << dest << ". . .\n";
		    cout << "\n\t\t     ";
			system("PAUSE");
		    graph.shortestPath(src, dest);  // function call to find shortest path
			break;
		// outputs the minimum spanning tree between several cities from the graph
		case 4: system("CLS");
			cout << "The program is finding the minimum spanning tree between several cities...";
		
			break;
		
		// outputs the edge remove function
		case 5: system("CLS");
			cout << "Choose which edge to remove from the graph..";
		
			break;
		
		// outputs the reset function
		case 6: system("CLS");
			cout << "The program is resetting the graph back to default...";
		
			break;
		}	
		// asking user whether they would like to continue using the program 
		cout << "\n\n\t\t   Please enter Y to continue or any key to exit: ";
		cin >> start;
		} while (start=='y' || start=='Y'); // program will loop as long as user inpit 'y' or 'Y'
   
   return 0;
}
