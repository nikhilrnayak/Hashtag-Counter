#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;


static const float rt_of_5			= sqrt(5);
static const float golden_ratio			= (1 + rt_of_5)/2;
static const float log_of_golden_ratio		= log(golden_ratio);

struct fibNode
{
	int key;				//key value of the node
	string hashval;				//hashvalue of the input string
	int degree;				//degree of the subtree rooted at this node
	bool childcut;				//childcut flag of the node
	struct fibNode *parent;			//parent pointer of the current node
	struct fibNode *child;			//child pointer of the current node
	struct fibNode *left;			//left sibling pointer of the current node
	struct fibNode *right;			//right sibling pointer of the current node
};

class fibonacciHeap
{
	public:
		fibonacciHeap();
		virtual ~fibonacciHeap();
		fibNode *createNode(int, string);
		void insertNode(struct fibNode *, struct fibNode *, int);
		int increaseKey(struct fibNode *, int);
		void arbitraryRemove(struct fibNode *);
		void maxRemove();
		void combineList(struct fibNode *);
		void pairwiseCombine(struct fibNode *);
		void followChildCut(struct fibNode *);
		int initializeDegreeTable();
		int getNumNodes();
		void shifter(struct fibNode **, int);
		struct fibNode *getMax();
		
	protected:
	
	private:
		struct fibNode *max;
		int numNodes;
		struct fibNode **degree_table;
};

#endif //FIBONACCIHEAP_H
