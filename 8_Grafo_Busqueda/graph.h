/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 4.1 Implementacion Grafos
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*		Nota: Esta imlpementación es Top Down, no divide al árbol para la operacións
*		de barrado
*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
		vector<int> *adjList;
		int *adjMatrix;

public:
		Graph();
		Graph(int);
  		void loadGraphList(string, int);
  		void loadGraphMat(string, int, int);
		void addEdgeAdjList(int, int);
		void addEdgeAdjMatrix(int, int);
		string printAdjList();
		string printAdjMat();
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int> >&);
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int> >&);
		string print_visited(list<int>);
		string print_path(vector<vector<int> >&,int ,int);
		bool contains(list<int>, int);
		void sortAdjList();
};


void Graph::loadGraphList(string line, int numberVert){
	adjList = new vector<int>[numberVert];
	nodes = numberVert;
	int u, v;

    stringstream ss(line);
    char ch;

    while(ss >> ch >> u >> ch >> v >> ch){
        addEdgeAdjList(u, v);
    }

	sortAdjList();
}

void Graph::loadGraphMat(string line, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	int u, v;
	for (int i = 0; i < a*b; i++){
		adjMatrix[i] = 0;
	}

    stringstream ss(line);
    char ch;

    while(ss >> ch >> u >> ch >> v >> ch){
        addEdgeAdjMatrix(u,v);
    }
}

Graph::Graph() {
	edgesList = 0;
	edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
		aux << "vertex "
				<< i << " :";
		for (int j = 0; j < adjList[i].size(); j ++){
							aux << " " << adjList[i][j];
				}
		aux << " ";
	}
	return aux.str();
}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::DFS(int start, int goal){
	stack<int> auxStack;
	list<int> visited;
	vector<vector<int> > paths(nodes, vector<int>(1,0));
	auxStack.push(start);
	
	stringstream ss;
	ss << depthHelper(start, goal, auxStack, visited, paths) << print_path(paths, start, goal);
	return ss.str();
}

string Graph::depthHelper(int current, int goal, stack<int> &auxStack, list<int> &visited, vector<vector <int> > &paths){
	if(current == goal){
		return print_visited(visited);
	} else if(auxStack.empty()){
		return " node not found";
	} else {
		current = auxStack.top();
		auxStack.pop();
		visited.push_back(current);
		for (int i = 0; i < adjList[current].size(); i++){
			if (!contains(visited, adjList[current][i])){
				auxStack.push(adjList[current][i]);
				paths[adjList[current][i]][0] = current;
			}
		}
		return depthHelper(current, goal, auxStack, visited, paths);
	}
}

string Graph::BFS(int start, int goal){
	queue<int> auxQueue;
	list<int> visited;
	vector<vector<int> > paths(nodes, vector<int>(1,0));
	auxQueue.push(start);
	visited.push_back(start);

	stringstream ss;
	ss << breadthHelper(start, goal, auxQueue, visited, paths) << print_path(paths, start, goal);
	return ss.str();
}

string Graph::breadthHelper(int current, int goal, queue<int> &auxQueue, list<int> &visited, vector<vector<int> > &paths){
	if (current == goal) {
		return print_visited(visited);
	} else if (!auxQueue.empty()) {
		current = auxQueue.front();
		auxQueue.pop();
		for (int i = 0; i < adjList[current].size(); i++){
			if (!contains(visited, adjList[current][i])){
				auxQueue.push(adjList[current][i]);
				visited.push_back(adjList[current][i]);
				paths[adjList[current][i]][0] = current;
				if (adjList[current][i] == goal){
					return print_visited(visited);
				}
			}
		}
		return breadthHelper(current, goal, auxQueue, visited, paths);
	}

	return " node not found";
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
  }
	return aux.str();
}

string Graph::print_path(vector<vector <int> > &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  }
	return aux.str();
}

bool Graph::contains(list<int> ls, int node){
	list<int>::iterator it;
	it = find(ls.begin(), ls.end(), node);
	if(it != ls.end())
		return true;
	else
		return false;
}

void Graph::sortAdjList(){
	for(int i = 0; i < nodes; i++){
		sort(adjList[i].begin(), adjList[i].end());
	}
}


#endif /* Graph_H_ */