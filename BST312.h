
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOrder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;

//helper functions:
    void insertItem(TreeNode*& t, const ItemType& newItem); //tested
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const; //tested
    int countNodes(TreeNode* t) const; //tested
    void deleteNode(TreeNode*& node); //tested
    void makeEmpty(TreeNode*& t); //tested
    void deleteItem(TreeNode*& t, const ItemType& newItem); //tested
    void getPredecessor(TreeNode* t, ItemType& data); //tested
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const; //tested
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const; //tested
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);
    bool isItemInTree(TreeNode *t, const ItemType& item); //tested
};

/*******************************
//Function implementations
********************************/


//default constructor
template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

//copy constructor
template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

//destructor
template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();

}

//Functions: places contents of original tree into copy
//Pre-conditions: copy and originalTree initalized
//Post-conditions: contents of original tree placed into copy
template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}

//Function: Removes nodes from BST
//Preconditions: BST has been initialized.
//Postconditions: Nodes removed from BST.
template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}


template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    //YOUR CODE GOES HERE
    if (t == NULL)
        return;
    makeEmpty (t->left); //delete nodes from left subtree
    makeEmpty (t->right); //delete nodes from right subtree
    deleteNode (t);
}


/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(TreeNode *t, const ItemType& item)
{
    if (t == NULL)
        return false; //stops recursion when reachese a leaf
    else if (item < t->data)
    {
        return (isItemInTree (t-> left, item)); //searches left subtree
    }

    else if (item > t->data)
    {
        return (isItemInTree (t->right, item)); //searches right subtree
    }

    else
        return true; //if you reach a node that if equal to item

}


/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{

    //YOUR CODE GOES HERE
    TreeNode *currentNode = root;
    return (isItemInTree (currentNode, item));

}

template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{

    //YOUR CODE GOES HERE
    if (t == NULL) //once it reaches a spot in tree where newItem can be placed
    {
        t = new TreeNode (); 
        t -> data = newItem;
        t -> left = NULL;
        t -> right = NULL;
    }
    //making sure newItem goes in correct location in tree:
    else if (newItem < t->data)
        insertItem(t->left, newItem);
    else if (newItem > t->data)
        insertItem(t->right, newItem);

}

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    //YOUR CODE GOES HERE
    if (isFull ())
        return;
    else if (isItemInTree(newItem))
        return;
    else {
        insertItem(root, newItem);
    }
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    //YOUR CODE GOES HERE
    int totalNodes = 1; //incuding head of tree
    if (t->left != NULL) {
        totalNodes += countNodes (t->left); //including all nodes in left subtree 
    }
    if (t->right != NULL) {
        totalNodes += countNodes (t->right); //including all nodes in right subtree
    }
    return totalNodes;
}


/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    //YOUR CODE GOES HERE
    int totalNodes = 0;
    if (!isEmpty())
    {
        TreeNode *currentNode = root;
        totalNodes = countNodes (currentNode);
    }

    return totalNodes;
}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if (t != NULL)
    {
        result.push_back(t -> data); //node first
        preOrderTraversal(t->left, result); //left second
        preOrderTraversal(t->right, result); //right last
    }
}


/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector <ItemType> preOrder;
    if (isEmpty())
        return preOrder;
    else
    {
        TreeNode *currentNode = root;
        preOrderTraversal (currentNode, preOrder);
        return preOrder;
    }

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if (t != NULL)
    {
        inOrderTraversal (t->left, result); //left first
        result.push_back(t->data); //node second
        inOrderTraversal (t->right, result); //right last
    }

}

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector <ItemType> inOrder;
    if (isEmpty())
        return inOrder;
    else
    {
        TreeNode *currentNode = root;
        inOrderTraversal (currentNode, inOrder);
        return inOrder;
    }
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{

    //YOUR CODE GOES HERE
    if (t != NULL)
    {
        postOrderTraversal (t->left, result); //left first
        postOrderTraversal (t->right, result); //right second
        result.push_back(t->data); //node last
    }
}

/****************************
postOrderTraversal

Function: returns the postOrder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector <ItemType> postOrder;
    if (isEmpty())
        return postOrder;
    else
    {
        TreeNode *currentNode = root;
        postOrderTraversal (currentNode, postOrder);
        return postOrder;
    }
}


#endif

