#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <vector>
#include <cstring>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <limits>
#include <math.h>
#include <cmath>
#include "dsexceptions.h"
#include <iostream>    // For NULL
using namespace std;   


// BinarySearchTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

ofstream myfile;

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) :root( NULL )
    {
    }

    BinarySearchTree( const BinarySearchTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }
    
    //-------User-defined binary tree functions---------------
    
    void prettyprint()
    {
        if (root->right != NULL)
        {
            prettyprint(root->right, "", " /");
        }
        myfile << root->element << endl;
        if (root->left != NULL)
        {
            prettyprint(root->left, "", " \\");
        }
        return;
    }

    //--------------------------------------
    
    void reOrder()
    {
        reOrder(root);
    }
    
    void insertHyper( const Comparable & x )
    {
        BinaryNode *a = new BinaryNode(x, NULL, NULL);

        insert(a, root);
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException();
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException();
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == NULL;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    
    void insertAVL(const Comparable &x )
    {
        insertAVL ( x, root);
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    /**
     * Deep copy.
     */
    const BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }

  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height;
        int lsize;
        int rsize;
        
        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, int h = 0, int ls = 0, int rs = 0 )
            : element( theElement ), left( lt ), right( rt ) { }
    };

    BinaryNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == NULL )
            t = new BinaryNode( x, NULL, NULL );
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == NULL )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != NULL && t->right != NULL ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != NULL ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != NULL )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != NULL )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new BinaryNode( t->element, clone( t->left ), clone( t->right ) );
    }
    
    void prettyprint(BinaryNode *t, string linePrefix, string nodeTag)
    {
        string twoSpaces = "  ";
        string rightChild = " /";
        string leftChild = " \\";
        string temp = linePrefix;
        
        if (t->right != NULL)
        {
            if (nodeTag == " /")
            {
                temp  += twoSpaces;
            }
            else
            {
                temp += "| ";
            }
            prettyprint(t->right, temp, rightChild);
        }
        
        myfile << linePrefix << nodeTag << t->element << endl;
            
        temp = linePrefix;    
        if (t->left != NULL)
        {
            if (nodeTag == " /")
            {
                temp += "| ";
            }
            else
            {
                temp += twoSpaces;
            }
            prettyprint(t->left, temp, leftChild);
        }
    
    }
    
    int height( BinaryNode *t ) const
    {
        return t == NULL ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( BinaryNode * & k2 )
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( BinaryNode * & k1 )
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( BinaryNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( BinaryNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
    
    void insertAVL( const Comparable & x, BinaryNode * & t )
    {
        if( t == NULL )
            t = new BinaryNode( x, NULL, NULL );
        else if( x < t->element )
        {
            insertAVL( x, t->left );
            if( height( t->left ) - height( t->right ) == 2 )
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
        }
        else if( t->element < x )
        {
            insertAVL( x, t->right );
            if( height( t->right ) - height( t->left ) == 2 )
                if( t->right->element < x )
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
        }
        else
            ;  // Duplicate; do nothing
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    //-------------User defined HB Tree functions---------------
        
    void insert(BinaryNode * & x, BinaryNode * & t )
    {
        if( t == NULL )
        {
            t = new BinaryNode( x->element, NULL, NULL );
        }
        else if( x->element <= t->element )
        {
            t->lsize += 1;
            insert( x, t->left );
        }
        else if( t->element <= x->element )
        {
            t->rsize += 1;
            insert( x, t->right );
        }
            
            
        if (abs(t->lsize - t->rsize) >= 2)
        {
            rebalance(t);
        }
    }
    
    //------------------------------------------
    
    void rebalance( BinaryNode * & t )
    {
        Comparable temp = t->element;
        if (t->lsize = (t->rsize + 2))
        {
            BinaryNode *x = removeMax(t->left);
            t->element = x->element;
            x->element = temp;
            insert(x, t->right);
        }
        else if (t->lsize = (t->rsize - 2))
        {
            BinaryNode *x = removeMin(t->right);
            t->element = x->element;
            x->element = temp;
            insert(x, t->left);
        }
    }
    
    BinaryNode * removeMax( BinaryNode * & t )
    {
        BinaryNode *x = t;
        BinaryNode *p = NULL;
        
        if (x != NULL && x->right != NULL)
        {
            while (x->right != NULL)
            {
                p = x;
                x = x->right;
            }
            p->right = NULL;
        }
        if (p == NULL)
        {
            t = x->left;
            x->left = NULL;
        }
        
        
        reOrder(root);
        
        if (abs(t->lsize - t->rsize) >= 2)
        {
            rebalance(t);
        }
        
        return x;
    }
    
    BinaryNode * removeMin( BinaryNode * & t )
    {
        BinaryNode *x = t;
        BinaryNode *p = NULL;
        
        if (x != NULL && x->left != NULL)
        {
            while ( x->left != NULL)
            {
                p = x;
                x = x->left;
            }
            p->left = NULL;
        }
        if (p == NULL)
        {
            t = x->right;
            x->right = NULL;
        }
        
        reOrder(root);
        
        if (abs(t->lsize - t->rsize) >= 2)
        {
            rebalance(t);
        }
        
        return x;
    }
    
    int reOrder(BinaryNode * & t)
    {
        if (t == NULL)
        {
            return 0;
        }
        else
        {
            if (t->left != NULL)
            {
                t->lsize = reOrder(t->left) + reOrder(t->left->right) + 1;
            }
            else
            {
                t->lsize = reOrder(t->left) + 1;
            }
            if (t->right != NULL)
            {
                t->rsize = reOrder(t->right) + reOrder(t->right->left) + 1;
            }
            else
            {
                t->rsize = reOrder(t->right) + 1;
            }
        }
        
    }
    


};


//-------------------------------User-defined functions------------------------------

int main(int argc, char* argv[])
{
    BinarySearchTree<double> unb;
    BinarySearchTree<double> avl;
    BinarySearchTree<double> hyper;
    
    string temp = "";
    string file = argv[1];
    ifstream infile;
    int num = 1;
    
    infile.open(file.c_str());

    string output = "";
    
    for(int i=0; i < file.length(); ++i)
    {
        if(file.at(i) == '.')
        {
            break;
        }
        
        output += file.at(i);
    }
    output += ".out";
    
    myfile.open(output.c_str());
    
    while (getline(infile, temp))
    {
        istringstream iss(temp);
        double n;
        while (iss >> n)
        {
            unb.insert(n);
            avl.insertAVL(n);
            //hyper.insertHyper(n);
        }
    myfile << "TEST CASE: " << num << endl;
    myfile << endl << endl;
    myfile << "UNBALANCED TREE: " << endl;
    unb.prettyprint();
    myfile << endl;
    myfile << "AVL: " << endl;
    avl.prettyprint();
    myfile << endl << endl;
    myfile << "HYPER: " << endl;
    //hyper.prettyprint();
    myfile << endl;
    ++num;
    }

}



#endif