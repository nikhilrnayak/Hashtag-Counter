#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include "fibonacciHeap.h"

using namespace std;

int main(int argc, char **argv)
{
	fibonacciHeap fibHeap_obj1;
	struct fibNode *max, *newNode;
	struct fibNode **store_table;
	ifstream f_var_in;
	ofstream f_var_out;
	int counter, indexer;
	string var1, key, value, var2("stop");
	if(argv[1] == NULL)
	{
		cerr<<"Parameter for input file missing.\n";
		exit(-1);
	}
	f_var_in.open(argv[1], ios::in);
	if(argv[2] != NULL)
		f_var_out.open(argv[2], ios::out|ios::app & ios::out|ios::trunc);
	else
		f_var_out.open("./output_file.txt", ios::out|ios::app & ios::out|ios::trunc);
	unordered_map<string, struct fibNode *> mapper_var1;
	unordered_map<string, struct fibNode *>::iterator it_var1;
	if(f_var_in.fail())
	{
		cerr<<"Error opening file\n";
		exit(-1);
	}
	if(!f_var_out.is_open())
	{
		cerr<<"Error writing to file\n";
		exit(-1);
	}

	while(!f_var_in.eof())
	{
		getline(f_var_in, var1, '\n');
		if(var1[0] == '#')
		{
			stringstream ss_var(var1);
			ss_var>>key;
			ss_var>>value;
			it_var1		= mapper_var1.find(key);
			counter		= atoi(value.c_str());
			if(it_var1 == mapper_var1.end())
			{
				//insert key into the fibheap and hash table
				max	= fibHeap_obj1.getMax();
				newNode	= fibHeap_obj1.createNode(counter, key);
				//insert key into the hash table
				fibHeap_obj1.insertNode(max, newNode, 0);
				mapper_var1.insert(make_pair(key, newNode));
			}
			else
			{
				//increase key of the node in fibheap
				fibHeap_obj1.increaseKey(it_var1->second, counter);
				
			}
			
		}
		else
		{
			if(var1.compare("stop") == 0 || var1.compare("STOP") == 0)
			{
				//cout<<"found stop!!! exiting.\n";	//for debugging only
				f_var_in.close();
				f_var_out.close();
				exit(0);
			}
			else
			{
				counter		= atoi(var1.c_str());
				store_table	= (struct fibNode **)malloc(counter * sizeof(struct fibNode *));
				indexer		= 0;
				string comma	= "";
				//remove top counter number of items, write these items 
				//and insert them back into fibheap
				while(indexer < counter)		//remove the top n hashtags, print them to the file
				{					//and store the nodes in an table
					max	= fibHeap_obj1.getMax();
					if(max == NULL)
						break;
					//cout<<comma<<max->hashval.substr(1)<<"-"<<max->key; //for debugging only
					f_var_out<<comma + max->hashval.substr(1);
					newNode	= fibHeap_obj1.createNode(max->key, max->hashval);
					*(store_table + indexer)	= newNode;
					fibHeap_obj1.maxRemove();
					indexer++;
					comma	= ",";
				}
				indexer--;
				//cout<<endl;				//for debugging only
				f_var_out << endl;
				while(indexer >= 0)			//reinsert the nodes from the table
				{	
					it_var1	= mapper_var1.find((*(store_table + indexer))->hashval);
					if(it_var1 == mapper_var1.end())
					{
						cout<<"Error reinserting node!!\n";
						exit(-1);
					}
					it_var1->second	= *(store_table + indexer);
					max	= fibHeap_obj1.getMax();
					fibHeap_obj1.insertNode(max, *(store_table + indexer), 0);
					indexer--;
				}
				
			}
		}
	}
	f_var_in.close();
	f_var_out.close();
	return 0;

}

