#include <iostream>

#include "b-tree.h"

/**********************************************************
 *
 * CONSTRUCTOR Tree 
 *_________________________________________________________
 * This constructor receives nothing and initializes 
 * attributes to nullptr.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will null or zero-initialize attributes.
 ***********************************************************/
Tree::Tree(){
  root = nullptr;
}

/**********************************************************
 *
 * DESTRUCTOR ~Tree
 *_________________________________________________________
 * This destructor receives nothing and deletes any
 * dynamically allocated memory in the tree
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will free all used memory.
 ***********************************************************/
Tree::~Tree(){
  while(root != nullptr){
    remove(root->small);
  }

  std::cout << "Tree Cleared" << std::endl;
}

/**********************************************************
 *
 * FUNCTION findParent 
 *_________________________________________________________
 * This function receives a pointer to a node and returns
 * the parent to the node.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   The following must be defined:
 *     source (Node23*) // IN - child node
 *
 * POST-CONDITIONS
 *   This function will return the pointer to the node if
 *   it exists, a nullptr is returned otherwise.
 ***********************************************************/
Node23* Tree::findParent(Node23* source){
  if(source == nullptr || source == root){
    return nullptr;
  }

  Node23* current = root;
  while(current != nullptr){
    if(current->left == source  ||
       current->right == source ||
       current->mid == source){
         return current;
       }
    if(source->small < current->small){
      current = current->left;
    } else if(source->small > current->large){
      current = current->right;
    } else {
      current = current->mid;
    }
  }

  return nullptr;
}

/**********************************************************
 *
 * FUNCTION split
 *_________________________________________________________
 * This function receives a pointer to a node, the data
 * to insert into the node, and a pointer to a temp fourth
 * node if the child is a 3 node before being split.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   The following must be defined:
 *     source (Node23*) // IN - node to split
 *     data (int)       // IN - data item to insert 
 *     temp (Node23*)   // IN - temp node for fourth child 
 *                              if node is a 3 node prior to 
 *                              split
 *
 * POST-CONDITIONS
 *   Tree is perfectly balanced and all nodes are a max of
 *   3 degrees.
 ***********************************************************/
void Tree::split(Node23* source, // IN - node to split
                 int data,       // IN - data to insert
                 Node23* temp){  // IN - temp 4th child
  if(source == nullptr){
    return;
  }
  Node23* parent;
  int n1, n2, mid;
  // find the middle, left, and right data values
  if(data < source->small){
    n1 = data;
    n2 = source->large;
    mid = source->small;
  } else if(data > source->large){
    n1 = source->small;
    n2 = data;
    mid = source->large;
  } else{
    n1 = source->small;
    n2 = source->large;
    mid = data;
  }
  // create new children based off of 
  // right, middle and left values
  Node23* t1 = new Node23;
  t1->empty = false;
  t1->full = false;
  t1->small = n1;
  t1->large = -1;

  Node23* t2 = new Node23;
  t2->empty = false;
  t2->full = false;
  t2->large = -1;
  t2->small = n2;
  // If the node to split has children
  // redistribute to new nodes
  if(source->left != nullptr){
    if(data < source->small){
      t1->left = source->left;
      t1->right = temp;

      t2->left = source->mid;
      t2->right = source->right;
    } else if(data > source->large){
      t1->left = source->left;
      t1->right = source->mid;

      t2->left = source->right;
      t2->right = temp;
    } else{
      t1->left = source->left;
      t1->right = source->mid;

      t2->left = temp;
      t2->right = source->right;
    }
  }

  // create new root node
  if(source == root){
    parent = new Node23;
    parent->large = -1;
    parent->small = mid;
    parent->empty = false;
    parent->left = t1;
    parent->right = t2;
    root = parent;
  } 
  // split and restructure tree
  else{
    parent = findParent(source);

    if(!parent->full){
      parent->full = true;
      if(mid < parent->small){
        parent->large = parent->small;
        parent->small = mid;
      } else{
        parent->large = mid;
      }

      if(parent->left == source){
        parent->left = t1;
        parent->mid = t2;
      } else{
        parent->mid = t1;
        parent->right = t2;
      }
    } 
    else{
      if(parent->left == source){
        parent->left = t1;
      } else if(parent->mid == source){
        parent->mid = t1;
      } else{
        parent->right = t1;
      }

      split(parent, mid, t2);
    }
  }

  delete source;
}

/**********************************************************
 *
 * FUNCTION insert 
 *_________________________________________________________
 * This function receives a pointer to a node and a data
 * to insert.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   The following must be defined:
 *     source (Node23*) // IN - Node to begin insert
 *
 * POST-CONDITIONS
 *   This function will insert the data value into the tree
 *   while maintaining balance and making sure the tree
 *   remains a 2-3 tree.
 ***********************************************************/
void Tree::insert(Node23* source, // IN - node to begin inserting
                  int data){      // IN - data to insert
  if(source == nullptr){
    return;
  }
  // find correct leaf node
  Node23* current = source;
  while(current->left != nullptr){
    if(data < current->small){
      current = current->left;
    } else if(data > current->large){
      current = current->right;
    } else{
      current = current->mid;
    }
  }
  // no need to rebuild if the node is not full
  if(!current->full){
    if(data < current->small){
      current->large = current->small;
      current->small = data;
    } else{
      current->large = data;
    }
    current->full = true;
  }
  // current is full, must rebuild
  else{
    std::cout << "Rebuilding Tree" << std::endl;
    split(current, data);
  }
}

/**********************************************************
 *
 * FUNCTION insert 
 *_________________________________________________________
 * This function receives a data value to insert.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   The following must be defined:
 *     data (int) // IN - data value to insert
 *
 * POST-CONDITIONS
 *   This function will insert the data value into the tree
 *   while maintaining balance and making sure the tree
 *   remains a 2-3 tree.
 ***********************************************************/
void Tree::insert(int data) // IN - value to insert
{ 
  std::cout << "Attempting to insert: " << data << std::endl;
  if(find(root, data) != nullptr){
    std::cout << "Already Exists" << std::endl;
    return;
  }
  // insert into empty tree
  if(root == nullptr){
    root = new Node23;
    root->empty = false;
    root->small = data;
    root->large = -1;
  } 
  // if tree is not empty,
  // must handle more cases
  else{
    insert(root, data);
  }
  std::cout << data << " Inserted!" << std::endl;
}

/**********************************************************
 *
 * FUNCTION find 
 *_________________________________________________________
 * This function receives a pointer to a node and a data
 * to find.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   The following must be defined:
 *     source (Node23*) // IN - Node to begin search
 *     data (int)       // IN - data value to find
 *
 * POST-CONDITIONS
 *   This function will find the data value in the tree
 *   beginning the search at the given node. The found
 *   node is returned, or nullptr if the data does not exist.
 ***********************************************************/
Node23* Tree::find(Node23* source, // IN - node to begin search
                   int data) const // IN - value to find
{
  Node23* current = source;

  while(current != nullptr){
    if(current->small == data){
      return current;
    }
    if(current->full){
      if(current->large == data){
        return current;
      }
    }
    // search the correct branch
    if(data < current->small){
      current = current->left;
    } else if(data > current->large){
      current = current->right;
    } else{
      current = current->mid;
    }
  }

  return nullptr;
}

/**********************************************************
 *
 * FUNCTION successor 
 *_________________________________________________________
 * This function receives a pointer to a node and a data
 * to succeed.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   The following must be defined:
 *     source (Node23*) // IN - Node to begin search
 *     target (int)     // IN - value to succeed
 * 
 * POST-CONDITIONS
 *   This function will return a pointer to the node that 
 *   succeeds the given value.
 ***********************************************************/
Node23* Tree::successor(Node23* source,   // IN - node to begin search
                        int target) const //IN - value to succeed
{
  if(source == nullptr){
    return nullptr;
  }

  // choose right branch to search
  Node23* current;
  if(source->full && target == source->small){
    current = source->mid;
  } else{
    current = source->right;
  }

  while(current != nullptr){
    if(current->left == nullptr){
      return current;
    }
    // successor is in leftmost node
    current = current->left;
  }

  return nullptr;
}

/**********************************************************
 *
 * FUNCTION fixTree 
 *_________________________________________________________
 * This function receives a pointer to a node
 *_________________________________________________________
 * PRE-CONDITIONS
 *   The following must be defined:
 *     source (Node23*) // IN - Node to deleted value
 *
 * POST-CONDITIONS
 *   This function will fix the tree to maintain balance
 *   after deleting a 2 node.
 ***********************************************************/
void Tree::fixTree(Node23 *source) // IN - deleted node
{
  // replace root with correct value
  if(source == root){
    if(source->left != nullptr){
      root = source->left;
    } else{
      root = source->right;
    }
    delete source;
  } 
  else{
    Node23* parent = findParent(source);
    Node23* lSib = parent->left;
    Node23* mSib = parent->mid;
    Node23* rSib = parent->right;
    // if all siblings only have 1 item
    if(!lSib->full && !rSib->full){
      if(parent->full && !mSib->full){
        parent->full = false;
        if(source == lSib){
          lSib->small = parent->small;
          parent->small = mSib->small;
          rSib->large = rSib->small;
          rSib->small = parent->large;
          rSib->full = true;
          delete mSib;
        } else if(source == mSib){
          lSib->large = parent->small;
          lSib->full = true;
          parent->small = parent->large;
          delete mSib;
        } else{
          rSib->empty = false;
          rSib->full = false;

          rSib->small = parent->large;
          lSib->large = parent->small;

          parent->small = mSib->small;

          delete mSib;
        }
      }
      else if(!parent->full){
        parent->empty = true;
        if(source == lSib){
          rSib->full = true;
          rSib->large = rSib->small;
          rSib->small = parent->small;
          
          if(source->right != nullptr || source->left != nullptr){
            rSib->mid = rSib->left;
            if(source->right != nullptr)
              rSib->left = source->right;
            else
              rSib->left = source->left;
          }
        }
        else{
          lSib->full = true;
          lSib->large = parent->small;

          if(source->right != nullptr || source->left != nullptr){
            lSib->mid = lSib->right;
            if(source->right != nullptr)
              lSib->right = source->right;
            else
              lSib->right = source->left;
          }
        }

        delete source;
      }
      if(parent->empty)
        fixTree(parent);
    }
    // at least 1 sibling has 2 items
    else{
      if(source == rSib){
        rSib->empty = false;
        rSib->full = false;

        if(parent->full){
          rSib->small = parent->large;
          if(mSib->full){
            parent->large = mSib->large;
            mSib->full = false;
          } else{
            parent->large = mSib->small;
            mSib->small = parent->small;
            parent->small = lSib->large;
            lSib->full = false;
          }
        } else{
          rSib->small = parent->small;
          parent->small = lSib->large;
          lSib->full = false;
        }
      } else if(source == mSib){
        mSib->empty = false;
        mSib->full = false;

        if(lSib->full){
          mSib->small = parent->small;
          lSib->full = false;
          parent->small = lSib->large;
        } else{
          mSib->small = parent->large;
          parent->large = rSib->small;
          rSib->small = rSib->large;
          rSib->full = false;
        }
      } else{
        lSib->empty = false;
        lSib->full = false;

        lSib->small = parent->small;
        if(parent->full){
          parent->small = mSib->small;
          if(mSib->full){
            mSib->small = mSib->large;
            mSib->full = false;
          } else{
            mSib->small = parent->large;
            parent->large = rSib->small;
            rSib->full = false;
            rSib->small = rSib->large;
          }
        } else{
          parent->small = rSib->small;
          rSib->small = rSib->large;
          rSib->full = false;
        }
      }
    }
  }
}

/**********************************************************
 *
 * FUNCTION remove 
 *_________________________________________________________
 * This function receives a pointer to a node and a data
 * to remove.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   The following must be defined:
 *     source (Node23*) // IN - Node to begin removal
 *     data (int)       // IN - value to remove
 *
 * POST-CONDITIONS
 *   This function will remove the data value from the tree
 *   while maintaining balance and making sure the tree
 *   remains a 2-3 tree.
 ***********************************************************/
bool Tree::remove(Node23 *source, // IN - node to begin from
                  int data)       // IN - value to remove
{
  // find the node with the value
  Node23* dataItem = find(root, data);
  // if data is found in tree
  if(dataItem != nullptr){
    // node is not a leaf, must handle complex cases
    if(dataItem->right != nullptr){
      Node23* leafNode = successor(dataItem, data);
      if(dataItem->small == data){
        dataItem->small = leafNode->small;
      } else{
        dataItem->large = leafNode->small;
      }
      if(leafNode->full){
        leafNode->full = false;
        leafNode->small = leafNode->large;
      } else{
        leafNode->empty = true;
        std::cout << "Rebuilding Tree" << std::endl;
        fixTree(leafNode);
      }
    }
    // dataItem is a leaf
    else{
      if(dataItem->full){
        dataItem->full = false;
        dataItem->small = dataItem->large;
      } else{
        dataItem->empty = true;
        std::cout << "Rebuilding Tree" << std::endl;
        fixTree(dataItem);
      }
    }
    std::cout << data << " Removed!" << std::endl;
    return true;
  }
  std::cout << data << " Not Found!" << std::endl;
  return false;
}

/**********************************************************
 *
 * FUNCTION remove 
 *_________________________________________________________
 * This function receives a data value to remove.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   The following must be defined:
 *     data (int)       // IN - value to remove
 *
 * POST-CONDITIONS
 *   This function will remove the data value from the tree
 *   while maintaining balance and making sure the tree
 *   remains a 2-3 tree.
 ***********************************************************/
bool Tree::remove(int data) // IN - value to remove
{
  std::cout << "Attempting to remove: " << data << std::endl;
  return remove(root, data);
}

/**********************************************************
 *
 * FUNCTION InOrderDisplay
 *_________________________________________________________
 * This function receives nothing and prints the tree 
 * using In Order sequence.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will print the contents of the tree onto
 *   the console, in In Order sequence.
 ***********************************************************/
void Tree::InOrderDisplay() const {
  std::cout << "Printing tree In Order Display" << std::endl;
  InOrderDisplay(root);
  std::cout << std::endl;
}

/**********************************************************
 *
 * FUNCTION PreOrderDisplay
 *_________________________________________________________
 * This function receives nothing and prints the tree 
 * using Pre Order sequence.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will print the contents of the tree onto
 *   the console, in Pre Order sequence.
 ***********************************************************/
void Tree::PreOrderDisplay() const {
  std::cout << "Printing tree Pre Order Display" << std::endl;
  PreOrderDisplay(root);
  std::cout << std::endl;
}

/**********************************************************
 *
 * FUNCTION PostOrderDisplay
 *_________________________________________________________
 * This function receives nothing and prints the tree 
 * using Post Order sequence.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will print the contents of the tree onto
 *   the console, in Post Order sequence.
 ***********************************************************/
void Tree::PostOrderDisplay() const {
  std::cout << "Printing tree Post Order Display" << std::endl;
  PostOrderDisplay(root);
  std::cout << std::endl;
}

/**********************************************************
 *
 * FUNCTION InOrderDisplay
 *_________________________________________________________
 * This function receives a node and prints the tree 
 * using In Order sequence starting from that node.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will print the contents of the tree onto
 *   the console, in In Order sequence.
 ***********************************************************/
void Tree::InOrderDisplay(Node23* source) const // IN - node to print from
{
  if(source == nullptr){
    return;
  }

  InOrderDisplay(source->left);
  std::cout << source->small << " ";

  if(source->full){
    InOrderDisplay(source->mid);
    std::cout << source->large << " ";
  }
  
  InOrderDisplay(source->right);
}

/**********************************************************
 *
 * FUNCTION PreOrderDisplay
 *_________________________________________________________
 * This function receives a node and prints the tree 
 * using Pre Order sequence starting from that node.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will print the contents of the tree onto
 *   the console, in Pre Order sequence.
 ***********************************************************/
void Tree::PreOrderDisplay(Node23* source) const // IN - Node to print from
{
  if(source == nullptr){
    return;
  }

  std::cout << "(" << source->small << ", ";
  if(source->full){
    std::cout << source->large;
  }
  std::cout << ") ";
  PreOrderDisplay(source->left);
  if(source->full){
    PreOrderDisplay(source->mid);
  }
  PreOrderDisplay(source->right);
}

/**********************************************************
 *
 * FUNCTION PostOrderDisplay
 *_________________________________________________________
 * This function receives a node and prints the tree 
 * using Post Order sequence starting from that node.
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will print the contents of the tree onto
 *   the console, in Post Order sequence.
 ***********************************************************/
void Tree::PostOrderDisplay(Node23* source)const // IN - node to start print
{
  if(source == nullptr){
    return;
  }

  PostOrderDisplay(source->left);
  if(source->full){
    PostOrderDisplay(source->mid);
  }
  PostOrderDisplay(source->right);

  std::cout << "(" << source->small << ", ";
  if(source->full){
    std::cout << source->large;
  }
  std::cout << ") ";
}
