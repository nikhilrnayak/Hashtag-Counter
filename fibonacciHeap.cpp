#include "fibonacciHeap.h"
#include <cstring>

using namespace std;

fibonacciHeap::fibonacciHeap()
{
	max		= NULL;
	numNodes	= 0;
}

fibonacciHeap::~fibonacciHeap()
{
	//free up stuff	
}

fibNode *fibonacciHeap::createNode(int key, string hashval)
{
	//struct fibNode *newNode = (struct fibNode *)malloc(sizeof(struct fibNode));
	struct fibNode *newNode	= new struct fibNode;
	newNode->parent		= NULL;
	newNode->child		= NULL;
	newNode->left		= NULL;
	newNode->right		= NULL;
	newNode->key		= key;
	newNode->hashval	= hashval;
	newNode->degree		= 0;
	newNode->childcut	= false;
	return newNode;
}

void fibonacciHeap::insertNode(struct fibNode *sibling_node, struct fibNode *key_to_insert, int code)
{
	if(key_to_insert != NULL)
	{
		if(sibling_node == NULL)	//this is used when we're inserting a node into the heap for the first time
		{
			max		= key_to_insert;
			max->parent	= NULL;
			max->right	= key_to_insert;
			max->left	= key_to_insert;
		}
	
		else				//if there exist other nodes in the heap this part of the code is executed
		{
			key_to_insert->parent		= sibling_node->parent;	
			sibling_node->left->right	= key_to_insert;
			key_to_insert->left		= sibling_node->left;
			key_to_insert->right		= sibling_node;
			sibling_node->left		= key_to_insert;	
		}
	
		if(sibling_node == max && key_to_insert->key > max->key)
				max 			= key_to_insert;
		if(code == 0)				//if code = 0 then the inserted node is a new addition
			numNodes++;			//if code = 1 then the inserted node is through an increase key operation
	}
}

int fibonacciHeap::increaseKey(struct fibNode *key_to_increase, int new_key)
{
	if(key_to_increase == NULL)
		return -1;
	//check if this is a valid key increase.
	if((key_to_increase->key + new_key) < key_to_increase->key)
	{
		cout<<"Invalid key increase.\n";
		return -1;
	}
	
	//increse the key
	key_to_increase->key				= key_to_increase->key + new_key;
	if(key_to_increase != max)
	{
		if(key_to_increase->parent != NULL)
		{
			if(key_to_increase->key > key_to_increase->parent->key)
			{
				//remove the key and the subtree rooted at the key to be incresed from its parents subtree
				key_to_increase->left->right 		= key_to_increase->right;
				key_to_increase->right->left 		= key_to_increase->left;
				
				if(key_to_increase->parent->child->left != key_to_increase)
					key_to_increase->parent->child	= key_to_increase->left;
				else
					key_to_increase->parent->child	= NULL;
				key_to_increase->parent->degree--;
				followChildCut(key_to_increase->parent);	//perform a cascading cut operation
				
				key_to_increase->left 			= NULL;
				key_to_increase->right			= NULL;
				key_to_increase->childcut		= NULL;
				//now perform a top level combine
				insertNode(max, key_to_increase, 1);
			}
		}
		if(key_to_increase->key > max->key)
				max					= key_to_increase;
	}
	return 0;

}

void fibonacciHeap::followChildCut(struct fibNode *key)
{
	if(key != max)
	{
		if(key->parent != NULL)
		{
			if(key->childcut == true)
			{
				key->childcut = NULL;
				key->left->right 		= key->right;
				key->right->left 		= key->left;
				if(key->parent->child->left != key)
					key->parent->child	= key->left;
				else
					key->parent->child	= NULL;
				key->parent->degree--;
				followChildCut(key->parent);	//perform a cascading cut operation
				key->left 			= NULL;
				key->right			= NULL;
				insertNode(max, key, 1);
			}
	
			key->childcut	= true;
		}
	}
	
}

void fibonacciHeap::combineList(struct fibNode *guest_list)
{
	//perform a walk of the circular list setting the parent pointer of every node to null
	if(guest_list != NULL)
	{
		struct fibNode *walker = guest_list;
		do
		{
			walker->parent		= NULL;
			walker			= walker->right;
		}while(walker != guest_list);
		struct fibNode *temp		= guest_list->left;
		max->left->right		= guest_list;
		guest_list->left->right		= max;
		guest_list->left		= max->left;
		max->left			= temp;
	}
	

}

void fibonacciHeap::arbitraryRemove(struct fibNode *key_to_remove)
{
	if(key_to_remove == max)
	{
		maxRemove();
	}
	
	else
	{
		//remove the key and the subtree rooted at the key to be increased from its parents subtree 
		if(key_to_remove->parent != NULL)
		{
			key_to_remove->left->right 		= key_to_remove->right;
			key_to_remove->right->left 		= key_to_remove->left;
		
			if(key_to_remove->parent->child->left != key_to_remove)
				key_to_remove->parent->child	= key_to_remove->left;
			else
				key_to_remove->parent->child	= NULL;
				
			key_to_remove->parent->degree--;
			followChildCut(key_to_remove->parent);	//need to follow childcut
			
			key_to_remove->left 			= NULL;
			key_to_remove->right			= NULL;
		}
	
		//now perform a top level combine
		
		if(key_to_remove->child != NULL)
			combineList(key_to_remove->child);

		delete key_to_remove;
	}
	numNodes--;

}

fibNode *fibonacciHeap::getMax()
{
	return max;
}

int fibonacciHeap::initializeDegreeTable()
{
	//calculate the max size of the degree table
	int max_size				= ceil(log(rt_of_5 * numNodes)/log_of_golden_ratio);
	//create a degree table of size calculated in the previous step
	degree_table				= (struct fibNode**)malloc(max_size * sizeof(struct fibNode *));
	//initialize each indexed location in the degree table to null
	int index				= 0;
	while(index < max_size)
		*(degree_table + index++)	= NULL;
	return max_size;
}


//shifter is a recursive function used to check if a degree_table[degree - 1]th node after a degree increase
//has a degree conflict with degree_table[degree]th node
void fibonacciHeap::shifter(struct fibNode **degree_table, int degree)
{
	if(*(degree_table + degree) == NULL)
	{
		*(degree_table + degree)	= *(degree_table + degree - 1);
		*(degree_table + degree - 1)	= NULL;
	}
	else
	{
		if((*(degree_table + degree))->key > (*(degree_table + degree - 1))->key)
		{
			//do a pairwise combine of the locations degree and degree - 1 in the degree table
			if((*(degree_table + degree))->child != NULL)
				insertNode((*(degree_table + degree))->child, *(degree_table + degree - 1), 1);
			(*(degree_table + degree))->child	= *(degree_table + degree - 1);
			(*(degree_table + degree - 1))->childcut	= false;
			(*(degree_table + degree - 1))->parent	= *(degree_table + degree);
			(*(degree_table + degree))->degree++;
			*(degree_table + degree - 1)		= NULL;
			shifter(degree_table, degree + 1);
		}
		else
		{
			//do a pairwise combine of the locations degree and degree - 1 in the degree table
			if((*(degree_table + degree - 1))->child != NULL)
				insertNode((*(degree_table + degree - 1))->child, *(degree_table + degree), 1);
			(*(degree_table + degree - 1))->child	= *(degree_table + degree);
			(*(degree_table + degree))->childcut	= false;
			(*(degree_table + degree))->parent	= *(degree_table + degree - 1);
			(*(degree_table + degree - 1))->degree++;
			*(degree_table + degree)		= *(degree_table + degree - 1);
			*(degree_table + degree - 1)		= NULL;
			shifter(degree_table, degree + 1);
		}
	}

}

//pairwise combine performs a combine of two nodes, in the top level circular list, if they're of 
//the same degree and then calls shifter to resolve any further collisions within the degree table
void fibonacciHeap::pairwiseCombine(struct fibNode *max_sibling)
{
	//delete node
	free(max);
	numNodes--;
	//initialize the degree table
	int degree_table_size			= initializeDegreeTable();
	struct fibNode *walker			= max_sibling;
	struct fibNode *walker_right		= max_sibling->right;
	//start a walk of the top level cicular list and start filling degree table
	do
	{
		walker_right		= walker->right;
		walker->parent		= NULL;
		walker->right		= walker;
		walker->left		= walker;
		if(*(degree_table + walker->degree) == NULL)
		{
			walker->childcut			= NULL;
			*(degree_table + walker->degree)	= walker;
		}
		else
		{
			if((*(degree_table + walker->degree))->key > walker->key)
			{
				//add walker as a child to the node already present in the degree table
				if((*(degree_table + walker->degree))->child != NULL)
					insertNode((*(degree_table + walker->degree))->child, walker, 1);
				(*(degree_table + walker->degree))->child	= walker;
				walker->childcut				= false;
				walker->parent					= *(degree_table + walker->degree);
				(*(degree_table + walker->degree))->degree++;
				shifter(degree_table, (*(degree_table + walker->degree))->degree);
			}
			else
			{
				//add the node present in the degree table as a child of walker
				if(walker->child != NULL)
					insertNode(walker->child, *(degree_table + walker->degree), 1);
				walker->child					= *(degree_table + walker->degree);
				(*(degree_table + walker->degree))->childcut	= false;
				(*(degree_table + walker->degree))->parent	= walker;
				*(degree_table + walker->degree)		= walker;
				walker->degree++;
				shifter(degree_table, walker->degree);
			}
		}
		walker						= walker_right;
	
	}while(walker != max_sibling);
	
	//now perform a walk of the degree table and create a top level circular list and designate a max
	int index			= 0;
	int first_non_null		= 0;
	struct fibNode *temp_node	= NULL;
	
	do
	{
		if(temp_node == NULL)
		{
			if(*(degree_table + index) != NULL)
			{
				temp_node	= *(degree_table + index);
				first_non_null	= index;
				max		= temp_node;
			}
		}
		else
		{
			if(*(degree_table + index) != NULL)
			{
				temp_node->right		= (*(degree_table + index));
				(*(degree_table + index))->left	= temp_node;
				temp_node	 		= *(degree_table + index);
				if(max->key < temp_node->key)
					max			= temp_node;
			}	
		}
		index++;		
	}while(index < degree_table_size);
	temp_node->right 				= (*(degree_table + first_non_null));
	(*(degree_table + first_non_null))->left	= temp_node;
	free((struct fibNode **)degree_table);
}

void fibonacciHeap::maxRemove()
{
	//call combineList
	combineList(max->child);
	//if after a combineList there are no siblings of max that means that
	//max is the only node left. there is no need to call pairwiseCombine as
	//we are removing the last remaining node in the heap.
	if(max->left != max)
	{
		//remove the max node 
		max->left->right	= max->right;
		max->right->left	= max->left;
		
		//call pairwise combine
		pairwiseCombine(max->left);
	}
	
	else
	{
		max	= NULL;
		free(max);
		numNodes--;
	}

	

}

int fibonacciHeap::getNumNodes()
{
	return numNodes;
}
