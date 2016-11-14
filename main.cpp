/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: umberto
 *
 * Created on November 14, 2016, 4:12 PM
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct node;
struct edge;

// Data structure definition
struct node {
	int name = -1;
	vector<edge*> neighbours;
	bool visited;
	
	node(int name);
};

node::node(int name) {
	this->name = name;
	this->visited = false;
}

struct edge {
	node* from;
	node* to;
};

typedef vector<node*> Graph;

void loadGraph(Graph &g, int &n_nodes, int &n_edges);
void printGraph(Graph &g);
/*
 * 
 */
int main(int argc, char** argv) {

	/*
	 *  initializing variables: number of nodes and edges.
	 *  opening ifstream
	 */
	int n_nodes = 0;
	int n_edges = 0;
	Graph g;
	loadGraph(g, n_nodes, n_edges);
	
	printGraph(g);
	return 0;
}

void loadGraph(Graph &g, int &n_nodes, int &n_edges) {
	ifstream in("./dataset/input/input0.txt");
	
	// reading first line of file containing the values of n_nodes and edges
	in >> n_nodes;
	cout << "N. nodes: " << n_nodes << endl;
	in >> n_edges;
	cout << "N. edges " << n_edges << endl;
	
	g.resize(n_nodes);
	
	for(int i = 0; i<n_edges; i++) {
		int from, to;
		in >> from >> to;
		
		if(g[from] == NULL) {
			g[from] = new node(from);
		}
		
		if(g[to] == NULL) {
			g[to] = new node(to);
		}
		
		edge* e = new edge;
		e->from = g[from];
		e->to = g[to];
		
		g[from]->neighbours.push_back(e);
		
		e = new edge;
		e->from = g[to];
		e->to = g[from];
		g[to]->neighbours.push_back(e);
	}
	
	in.close();
}

void printGraph(Graph &g) {
	for(int i =0; i<g.size();i++) {
		cout << "Node: " << g[i]->name << "." << endl;
		cout << "Neighbours: ";
		for(int j=0; j<g[i]->neighbours.size(); j++) {
			cout << g[i]->neighbours[j]->to->name << " ";
		}
		cout << endl;
	}
}