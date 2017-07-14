1> run make using command "make"

2> executable file produced will be named hashtagcounter

3> to run use the command format
	./hashtagcounter arg1 arg2
	arg1	-	compulsory argument, give the input filename along with extension. ex: sample_input1.txt
	arg2	-	optional argument, give the output filename along with extension. ex: fib_output_file.txt
	if arg2 is not provided then default output file name is output_file.txt
	ex: ./hashtagcounter sample_input1.txt fibo_output.txt or ./hashtagcounter sample_input1.txt
	 
4> to clean run "make clean"



The data given below is for the fibonacciHeap.h and fibonacciHeap.cpp 
Node structure 
struct fibNode 
int key;     //key value of the node 
 string hashval;    //hashvalue of the input string 
 int degree;    //degree of the subtree rooted at this node 
 bool childcut;    //childcut flag of the node 
 struct fibNode *parent;   //parent pointer of the current node 
 struct fibNode *child;   //child pointer of the current node 
 struct fibNode *left;   //left sibling pointer of the current node 
 struct fibNode *right;   //right sibling pointer of the current node 
 
Class Structure 
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
2 
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
fibNode *createNode(int, string); 
This method creates a node of type fibNode given an integer input (the frequency of the hashtag which becomes the key in Fibonacci heap) and the string value(the hashtag string). It returns a pointer to the created node. Return type is struct fibNode *. 
 
void insertNode(struct fibNode *, struct fibNode *, int); 
This method inserts a node into the Fibonacci heap. If there exists no Fibonacci heap then it creates one. 
Passed arguments are a pointer to the node which becomes the sibling of the inserted node, pointer to the node to be inserted and an integer code. This code is reused in increase key and pairwise combine, so the integer code helps differentiate between a new node insertion and an existing node reposition within the heap. Doing this helps in keeping track of the total number of nodes in the heap 
 
 
int increaseKey(struct fibNode *, int); 
This method accepts a pointer to a fibNode, whose key will be increased and an integer value which represents the value by which the key will be increased. This method checks if the key increase is a valid increase, i.e., whether the passed argument is positive or not. If not, it throws an error. Once the key has 
3 
been increased, it is removed from its current position and put in the top level list only if its key value has become greater than the key value of its parent. Internally this method calls  
insertNode(struct fibNode *, struct fibNode *, int); 
followChildCut(struct fibNode *); 
 
void arbitraryRemove(struct fibNode *); 
accepts an argument of type struct fibNode * and removes the node pointed to by the passed argument from the heap. Internally calls  
followChildCut(struct fibNode *), combineList(struct fibNode *) and followChildCut(struct fibNode *); 
 
void maxRemove(); 
Removes the node with the max key, i.e., the node pointed to by the max pointer. Internally it calls in the specified order 
combineList(struct fibNode *); 
paiwiseCombine(struct fibNode *); 
 
void combineList(struct fibNode *); 
Called by the functions arbitrary remove. This combines the circular list to which the passed argument belongs with the top-level circular list to which max node belongs. 
 
void pairwiseCombine(struct fibNode *); 
internally calls initializeDegreeTable(). Fills the degree table with nodes at indexed position equal to the degree of the node being inserted. Whenever there’s a collision, it resolves this by performing a pairwise combine operation and then by calling the method shifter(struct fibNode **) to check if there exist any cascaded collisions. If there exist then the shifter method resolves this by recursively performing a pairwise combine operation. Once all collisions have been resolved the shifter returns to the pairwiseCombine() method. Once the degree table has been filled and all the nodes in the top level list have been exhausted the pairwiseCombine() method makes a new top level circular list from the degree table and assigns a new max. 
 
void followChildCut(struct fibNode *); 
This method takes  an argument of type struct fibNode * and performs a cascading cut operation. 
 
4 
int initializeDegreeTable(); 
This method creates a degree table of max size = ceil [ log (√5 * no. of nodes) / log( 𝜙)] 
Where 𝜙 = (1 + √5)/2 
This method returns the max size to the calling method. 
  
int getNumNodes(); 
Returns the total number of nodes in the heap at the time of calling this method 
 
void shifter(struct fibNode **, int); 
This method accepts an argument of type struct fibNode **  (degree table) and an int (degree) and performs a recursive pairwise combine if any degree collisions exist. 
 
struct fibNode *getMax(); 
This method returns a pointer to the node pointed by the max pointer in the fibonacciHeap object. 
 
The following section describes the readLine program (readLine.cpp) code. 
readLine program 
This program accepts two parameters as argument. Argument 1 is the input filename with the extension and argument 2 is an optional parameter which if given is used as the output filename. If the output filename is not given it uses a default name output_file.txt. The function prototype is as described, 
Int main(int argc, char **argv); 
This program is a single block of code which reads the input file linewise and separates the words and the associated frequencies. It stores these data in a fibNode and stores the hashtag value and the fibNode pointer in an unordered map. 
Whenever the readLine program encounters a query. It goes into a loop and removes the max element iteratively. Each time it removes the max node it creates a new node in its place and stores it in a store_table. The max size of the store table is equal to the query value. Also, while filling the store table, it writes the output to the file. 
Once the iteration is completed, the code again iterates through the store_table and inserts the removed nodes back in to the fibbonacci heap. 
The code exists when it reads a stop in the input file without the hashtag. 
 
5 
To compile and run the file, follow these rules 
1> run make using command "make" 
 
2> executable file produced will be named hashtagcounter 
 
3> to run use the command format 
 ./hashtagcounter arg1 arg2 
 arg1 - compulsory argument, give the input filename along with extension. ex: sample_input1.txt 
 arg2 - optional argument, give the output filename along with extension. ex: fib_output_file.txt 
 if arg2 is not provided then default output file name is output_file.txt 
make sure to give the output filename in the form *output*.txt 
 ex: ./hashtagcounter sample_input1.txt fibo_output.txt or ./hashtagcounter sample_input1.txt 
   
4> to clean run "make clean" 