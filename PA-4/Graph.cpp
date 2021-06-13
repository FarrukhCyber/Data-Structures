#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"

//
// Add your constructor code here. It takes the filename and loads
// the graph from the file, storing into your representation of the
// graph. MAKE SURE you use the addEdge function here, and pass the 
// flag to it too.
//
Graph::Graph(string filename, bool flag)
{
	ifstream in ;
	string line;
	int size = 0 ;

	in.open(filename) ;

	// getting file size
	getline(in, line) ;
	//string to char converstion
	char cArray[line.size()+1] ;
	strcpy(cArray, line.c_str()) ;
	size = cArray[2] -48 ;

	//initalizing the matrix
	// seting size
	graph.resize(size) ;
	for (int i = 0; i < graph.size(); i++)
	{
		graph[i].resize(size) ;
	}

	// seting values
		// cout<<"\n test here \n" <<graph.size()<<endl;

	for (int i = 0; i < graph.size(); i++)
	{
		for (int k = 0; k < size; k++)
		{
			graph[i][k] = NULL ;
		}
		
	}
	

	while (in)
	{
		getline(in, line) ;
		// ignore the first two lines (headers) and last endOfFile char
		if (line.substr(0,1) == "n" || line.substr(0,1) == "c" || line.size()<=2)
		{
			
			continue ;
		}
		//string to char converstion
		char cArray[line.size()+1] ;
		strcpy(cArray, line.c_str()) ;
		// char to int converstion
		int w = cArray[4] - 48 ;

		if (flag == false) // undirected graph
		{
			addEdge(cArray[0], cArray[2], w, flag) ; 
			addEdge(cArray[2], cArray[0], w, flag) ;
		}
		else 
			addEdge(cArray[0], cArray[2], w, flag) ;
	}
	
}

//
// Adds an edge to the graph. Useful when loading the graph from file.
// The flag determines whether the edges will be added according to a
// directed or undirected graph.
//
void Graph::addEdge(char start, char end, int weight, bool flag)
{
	shared_ptr<Edge> newEdge( new Edge(start, end, weight)) ;
	int row = start - 65 ;
	int col = end - 65 ;
	graph[row][col] = newEdge ;

	return;
}

//
// Returns the display of the graph as a string. Make sure
// you follow the same output as given in the manual.
//
string Graph::display()
{
	string str ;

	for (int i = 0; i < graph.size(); i++)
	{
		for (int k = 0; k < graph.size(); k++)
		{
			if (graph[i][k] != NULL)
			{
				string start,end,w;
				//----converting char into string--------
				start.push_back(graph[i][k]->origin) ;
				end.push_back(graph[i][k]->dest) ;

				//-----converting int into string--------
				stringstream ss ;
				ss<< graph[i][k]->weight ;
				w = ss.str() ;
				//---------------------------------------

				str+= "(" + start + "," + end + "," + w + ")" + " " ;
			}
			
		}
		if (graph[i].empty() == false)
			str+= '\n';
		
	}
	
	return str ;

}

// Returns whether the destination city is reachable from the
// origin city or not.
//
bool Graph::Reachable(char start, char end)
{
	return false;
// 	char array[graph.size()];
// 	int n=0 ;

// 	for (int i = 0; i < graph.size(); i++)
// 	{
// 		for (int k = 0; k < size; k++)
// 		{
// 			if(graph[i][k] != NULL)
// 			{
// 				if (graph[i][k]->dest == end)
// 				{
// 					return true ;
// 				}
// 				else
// 					array[n] = graph[i][k]->dest ;
// 					n++ ;
// 			}
// 		}
		
// 	}

}

//
// Returns the weight of shortest path between origin and destination cities.
// Return -1 if no path exists.
//
int Graph::Dijkstra(char start, char dest)
{
	// TODO
	return 0;
}

//
// Implement topological sort on the graph and return the string of the sorted cities
//
string Graph::topoSort()
{
	//TODO
	return "";
}

// int main()
// {
// 	Graph mygraph("test2.txt",true); //directed graphs
// 	string test = mygraph.display() ;
// 	cout<< test <<endl;

// }


#endif
