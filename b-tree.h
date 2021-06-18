
/****************************************************************
 * Node23 struct
 *   This struct represents a node in the 2-3 balanced tree
 ***************************************************************/
struct Node23
{
  // variable state flags
  bool full = false;
  bool empty = true;
  // data
  int small;
  int large;
  // child nodes
  Node23 *left = nullptr;
	Node23 *mid = nullptr;
  Node23 *right = nullptr;
};

class Tree{
  private:
    Node23 *root;

    /**************
     ** MUTATORS **
     **************/
    Node23* findParent(Node23* source);
    void split(Node23* source, int data, Node23* temp = nullptr);
    void insert(Node23* source, int data);
    void fixTree(Node23* source);
    bool remove(Node23* source, int data);

    /***************
     ** ACCESSORS **
     ***************/
    void InOrderDisplay(Node23* source) const;
    void PreOrderDisplay(Node23* source) const;
    void PostOrderDisplay(Node23* source) const;
    Node23* find(Node23* source, int data) const;
    Node23* successor(Node23* source, int target) const;

  public:
    /******************************
     ** CONSTRUCTOR & DESTRUCTOR **
     ******************************/
    Tree();
    ~Tree();

    /**************
     ** MUTATORS **
     **************/
    void insert(int data);
    bool remove(int data);
    
    /***************
     ** ACCESSORS **
     ***************/
    void InOrderDisplay() const;
    void PreOrderDisplay() const;
    void PostOrderDisplay() const;
};


/****************************************************************
 * Tree Class
 *   This class represents 2-3 balanced tree using pointers.
 ***************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/
  
/***********************************************************
* Tree()
*_________________________________________________________
* Constructor; initializes variable data
*_________________________________________________________
* PRE-CONDITIONS
*   none
*
* POST-CONDITIONS
*   Initializes all values to zero or null.   
***********************************************************/
  
/***********************************************************
* ~Tree();
*_________________________________________________________
* Destructor; recursively frees any dynamically allocated 
*             memory
*_________________________________________________________
* PRE-CONDITIONS
*   none
*
* POST-CONDITIONS
*   frees any dynamically allocated memory recursively
***********************************************************/

  
/***************
 ** ACCESSORS **
 ***************/
 
/****************************************************************
 * void InOrderDisplay() const;
 *
 *   Accessor; This method will return all data in the Tree using
 *             InOrder method.
 * --------------------------------------------------------------
 *   Parameters: none
 * --------------------------------------------------------------
 *   Return: output tree to screen
 ***************************************************************/
 
/****************************************************************
 * void PreOrderDisplay() const;
 *
 *   Accessor; This method will return all data in the Tree using
 *             PreOrder method.
 * --------------------------------------------------------------
 *   Parameters: none
 * --------------------------------------------------------------
 *   Return: output tree to screen
 ***************************************************************/
 
/****************************************************************
 * void PostOrderDisplay() const;
 *
 *   Accessor; This method will return all data in the Tree using
 *             PostOrder method.
 * --------------------------------------------------------------
 *   Parameters: none
 * --------------------------------------------------------------
 *   Return: output tree to screen
 ***************************************************************/
 
/****************************************************************
 * void InOrderDisplay(Node23* source, int data) const;
 *
 *   Accessor; This is a helper method to print the tree in
 *             InOrder starting from the given node.
 * --------------------------------------------------------------
 *   Parameters: source (Node23*) // IN - node to print from
 * --------------------------------------------------------------
 *   Return: output tree to screen
 ***************************************************************/
 
/****************************************************************
 * void PreOrderDisplay(Node23* source, int data) const;
 *
 *   Accessor; This is a helper method to print the tree in
 *             PreOrder starting from the given node.
 * --------------------------------------------------------------
 *   Parameters: source (Node23*) // IN - node to print from
 * --------------------------------------------------------------
 *   Return: output tree to screen
 ***************************************************************/
 
/****************************************************************
 * void PostOrderDisplay(Node23* source, int data) const;
 *
 *   Accessor; This is a helper method to print the tree in
 *             PostOrder starting from the given node.
 * --------------------------------------------------------------
 *   Parameters: source (Node23*) // IN - node to print from
 * --------------------------------------------------------------
 *   Return: output tree to screen
 ***************************************************************/
 
/****************************************************************
 * Node23* find(Node23* source, int data) const;
 *
 *   Accessor; This method returns the node that contains the 
 *             given data point by searching the tree starting
 *             from source.
 * --------------------------------------------------------------
 *   Parameters: source (Node23*) // IN - node to search from
 *               data (int)       // IN - data to search for
 * --------------------------------------------------------------
 *   Return: output pointer to node with data
 ***************************************************************/

 /****************************************************************
 * Node23* successor(Node23* source, int data) const;
 *
 *   Accessor; This method returns the node that is the successor
 *             to the given node and data.
 * --------------------------------------------------------------
 *   Parameters: source (Node23*) // IN - node to succeed
 *               data (int)       // IN - data to succeed
 * --------------------------------------------------------------
 *   Return: output pointer to successor node.
 ***************************************************************/


 /**************
  ** MUTATORS **
  **************/
    
/****************************************************************
 * void insert(int data);
 *
 *   Mutator; This function will add the given int to the Tree
 *            while maintaining balance. The int must not exist
 *            in the Tree.
 * --------------------------------------------------------------
 *   Parameters: data (int) // IN - int to add 
 * --------------------------------------------------------------
 *   Return: none
 ***************************************************************/

/****************************************************************
 * void remove(int data);
 *
 *   Mutator; This function will remove the data from the tree
 *            and replace it with the successor, while maintaining
*             balance.
 * --------------------------------------------------------------
 *   Parameters: data (int) // IN - int to remove
 * --------------------------------------------------------------
 *   Return: none
 ***************************************************************/

/****************************************************************
 * void findParent(Node23* source);
 *
 *   Mutator; This is a function that returns the parent of
 *            the given source node.
 * --------------------------------------------------------------
 *   Parameters: source (Node23*) // IN - node to find parent of
 * --------------------------------------------------------------
 *   Return: none
 ***************************************************************/

/****************************************************************
 * void split(Node23* source, int data);
 *
 *   Mutator; This is a helper function to split the tree when
 *            inserting data.
 * --------------------------------------------------------------
 *   Parameters: source (Node23*) // IN - node to split
 *               data (int)       // IN - data to insert
 * --------------------------------------------------------------
 *   Return: none
 ***************************************************************/
    
/****************************************************************
 * void insert(Node23* source, int data);
 *
 *   Mutator; This is a helper function to insert the data into
 *            the given node.
 * --------------------------------------------------------------
 *   Parameters: souorce (Node23*) // IN - node to start from
 *               data (int)        // IN - data to insert
 * --------------------------------------------------------------
 *   Return: none
 ***************************************************************/
    
/****************************************************************
 * bool remove(Node23* source, int data);
 *
 *   Mutator; This is a helper function to delete the given data
 *            value if found in the tree.
 * --------------------------------------------------------------
 *   Parameters: souorce (Node23*) // IN - node to start from
 *               data (int)        // IN - data to delete
 * --------------------------------------------------------------
 *   Return: bool - true on success, false otherwise
 ***************************************************************/

/****************************************************************
 * void fixTree(Node23* source);
 *
 *   Mutator; This is a function that restructures the tree
 *            after deleting an element.
 * --------------------------------------------------------------
 *   Parameters: souorce (Node23*) // IN - node of deleted value
 * --------------------------------------------------------------
 *   Return: none
 ***************************************************************/
 
