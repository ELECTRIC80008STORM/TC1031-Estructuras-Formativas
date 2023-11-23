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
  		void loadGraphList(string, int, int);
  		void loadGraphMat(string, int, int);
		void addEdgeAdjList(int, int);
		void addEdgeAdjMatrix(int, int);
		string printAdjList();
		string printAdjMat();
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
		string print_visited(list<int>);
		string print_path(vector<vector<int>>&,int ,int);
		bool contains(list<int>, int);
		void sortAdjList();
};


void Graph::loadGraphList(string file, int numberVert, int numberEdg){
	adjList = new vector<int>[numberVert];
	nodes = numberVert;

	string line;
	ifstream dataFile(file);

	int u, v;

	if(dataFile.is_open()){
		while(getline(dataFile, line)){
			u = stoi(line.substr(1,1));
			v = stoi(line.substr(4,1));
			addEdgeAdjList(u,v);
		}
		dataFile.close();
	} else{
		cout << "Unable to open file";
	}
	sortAdjList();
}

void Graph::loadGraphMat(string name, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
		string line;
		ifstream lee (name);
		int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				u = stoi(line.substr(1,1));
				v = stoi(line.substr(4,1));
				addEdgeAdjMatrix(u,v);
			}
			lee.close(); // Closes the file
		} else {
			cout << "Unable to open file";
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
	stack<int> stck;
	stck.push(start);
	list<int> visited;
	vector<vector<int>> paths;

	return depthHelper(start, goal, stck, visited, paths);
}

string Graph::depthHelper(int current,
	int goal,
	stack<int> &stck,
	list<int> &visited,
	vector<vector <int> > &paths){
	return "";
}

string Graph::BFS(int, int){
	return "";	
}

string Graph::breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&){
	return "";
}

string Graph::print_visited(list<int>){
	return "";
}

string Graph::print_path(vector<vector<int>>&,int ,int){
	return "";
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