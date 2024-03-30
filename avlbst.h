#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char



};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here

   
    void rotateLeft(AVLNode<Key, Value>* node);
    void rotateRight(AVLNode<Key, Value>* node);
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node);
    void removeFix(AVLNode<Key, Value>* node, int diff);
    AVLNode<Key, Value>* find(const Key& key) const;
    //virtual AVLNode<Key, Value>* successor(AVLNode<Key, Value>* current) const;

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
// template<class Key, class Value>
// void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
// {
//     // TODO
//     //insert regularly. just go through and check if it's bigger or not. 
//     //after inserting regularly, then check 


 //   


template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    AVLNode<Key, Value>* new_node = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);

    if (this->empty()) {
        this->root_ = new_node;
        new_node->setBalance(0);
        return;
    }

    AVLNode<Key, Value>* parent = nullptr;
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);

    while(current != nullptr)
    {
        if(new_item.first == current->getKey())
        {
            current->setValue(new_item.second);
            return;
        }
       
       
       
       else if(new_item.first < current->getKey())
        {
            if (current->getLeft() == nullptr) {
                current->setLeft(new_node);
                new_node->setParent(current);
                break; 
            }
            else 
            {
                current = current->getLeft();
            }
        }
        else {
            if (current->getRight() == nullptr) {
                current->setRight(new_node);
                new_node->setParent(current);
                break; 
            } else {
                current = current->getRight();
            }
        }
    } 

    
    new_node->setBalance(0);

    parent = new_node->getParent();
    if (parent->getBalance() == 0) {
        if (new_node == parent->getLeft()) {
            parent->setBalance(-1);
        } else {
            parent->setBalance(1);
        }
        insertFix(parent, new_node);
    }
    else {
        parent->setBalance(0);
    }
}



template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node) {
    if (parent == nullptr || parent->getParent() == nullptr)
        return;

    // while (parent != nullptr) {
    AVLNode<Key, Value>* grandparent = parent->getParent();


    if (parent == grandparent->getLeft()) 
    {
      grandparent->updateBalance(-1);

      //when parent is elft
      if(grandparent->getBalance() == 0)
      {
        return;
      }
      else if( grandparent->getBalance() == -1)
      {
        insertFix(grandparent, parent);

      }
      else if( grandparent->getBalance() == -2)
      {
        if (node == parent->getLeft()) 
        { 
          rotateRight(grandparent);
          grandparent->setBalance(0);
          parent->setBalance(0);
        } 
        else 
        { 
          rotateLeft(parent);
          rotateRight(grandparent);
          
          if(node->getBalance() == -1)
          {
            parent->setBalance(0);
            grandparent->setBalance(1);
            node->setBalance(0);
          }
          
          else if(node->getBalance() == 0)
          {
            parent->setBalance(0);
            grandparent->setBalance(0);
            node->setBalance(0);
          }
          else if (node->getBalance() == 1)
          {
            parent->setBalance(-1);
            grandparent->setBalance(0);
            node->setBalance(0);
          }
        }
      }
    }

    else 
    {
      grandparent->updateBalance(1);

      //when parent is elft
      if(grandparent->getBalance() == 0)
      {
        return;
      }

      else if( grandparent->getBalance() == 1)
      {
        insertFix(grandparent, parent);
      }

      else if( grandparent->getBalance() == 2)
      {
        if (node == parent->getRight()) 
        {  
          rotateLeft(grandparent);
          grandparent->setBalance(0);
          parent->setBalance(0);
        } 
        else 
        {
          rotateRight(parent);
          rotateLeft(grandparent);
          if(node->getBalance() == 1)
          {
            parent->setBalance(0);
            grandparent->setBalance(-1);
            node->setBalance(0);
          }
          else if(node->getBalance() == 0)
          {
            parent->setBalance(0);
            grandparent->setBalance(0);
            node->setBalance(0);
          }
          else if(node->getBalance() == -1)
          {
            parent->setBalance(1);
            grandparent->setBalance(0);
            node->setBalance(0);
          }
        }
      }
    }






        // if (parent->getBalance() == 0) {
        //     break;  //for no imbal
        // } else if (parent->getBalance() == -1 || parent->getBalance() == 1) {
           

        //     if (grandparent == nullptr) {
        //         break;
        //     }
            
        //      else {
               

        //         if (node == parent->getRight()) 
        //         {
                    
        //             rotateLeft(grandparent);
        //         } else 
        //         {
                   
        //             rotateRight(parent);
        //             rotateLeft(grandparent);
        //         }
        //     }
        //     break;
        // } else {


         
        //     if (parent == grandparent->getLeft()) {

        //         parent->setBalance(parent->getBalance() - 1);

        //     } else {
        //         parent->setBalance(parent->getBalance() + 1);
        //     }
        // }

        
        // node = parent;
        // parent = grandparent;
    //}
}









template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key) {
   

  AVLNode<Key, Value>* node = find(key);
  //node null return 
   if (node == NULL) {
        return;
    }

    //AVLNode<Key, Value>* node = find(key);
       
    //check for two children 
    if (node->getLeft() != nullptr && node->getRight() != nullptr) {
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(node));
        nodeSwap(node, pred);
        //node = pred;
    }
    //create parent node 
    AVLNode<Key, Value>* p = node->getParent();
    int diff = 0;


    if(p != nullptr)
    {
        if(p->getLeft() == node)
        {
            diff = 1;
        }
        else if(p->getRight() == node)
        {
            diff = -1;
        }
    }
    
    //no children 
    if(node->getLeft() == nullptr && node->getRight() == nullptr)
    {
        if(p == NULL)
        {
            this->root_ = nullptr;
        }
        else
        {
            if(p->getLeft() == node)
            {
                p->setLeft(nullptr);
            }
            else{
                p->setRight(nullptr);
            }

        }
    }
  

  //  else if (node->getLeft() == nullptr || node->getRight() == nullptr) 
  //   {
  //       //  one child
  //       AVLNode<Key, Value>* child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight();
  //       if (node == this->root_) {
  //           this->root_ = child;
  //           child->setParent(nullptr);
  //       } else {
            
  //            AVLNode<Key, Value>* parent = node->getParent();
  //           if (parent->getLeft() == node) {
  //               parent->setLeft(child);
  //           } else {
  //               parent->setRight(child);
  //           }
  //           child->setParent(parent);
  //       }
        
  //       delete node;
  //   }  
   
   
      else if (node->getLeft() != nullptr && node->getRight() == nullptr) {
        if (p == nullptr) {
            this->root_ = node->getLeft();
        }
        else {
            if (p->getLeft() == node) {
                p->setLeft(node->getLeft());
            }
            else {
                p->setRight(node->getLeft());
            }
        }
        node->getLeft()->setParent(p);
    }

   
    else if (node->getLeft() == nullptr && node->getRight() != nullptr) {
        if (p == nullptr) {
            this->root_ = node->getRight();
        }
        else {
            if (p->getLeft() == node) {
                p->setLeft(node->getRight());
            }
            else {
                p->setRight(node->getRight());
            }
        }
        node->getRight()->setParent(p);
    }


    delete node;
    removeFix(p, diff);


}





template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* node, int diff) 

{

if(node == nullptr)
{
    return;
}

  AVLNode<Key, Value>* p = node->getParent();

int ndiff;


    if(p != nullptr)
    {
        if(p->getLeft() == node)
        {
            ndiff = 1;
        }
        else if(p->getRight() == node)
        {
            ndiff = -1;
        } 
    }


    if(node->getBalance() + diff == -2)
    {
        AVLNode<Key, Value>* c = node->getLeft();
        if(c->getBalance() == -1)
        {  
                rotateRight(node);
                node->setBalance(0);
                c->setBalance(0);

        }

        else if(c->getBalance() == 0)
        {
        
                rotateRight(node);
                node->setBalance(-1);
                c->setBalance(1);
        }


        else if(c->getBalance()  == 1)
        {
            AVLNode<Key, Value>* g = c->getRight();
            rotateLeft(c);
            rotateRight(node);

            if(g->getBalance() == 1)
            {
                node->setBalance(0);
                c->setBalance(-1);
                g->setBalance(0);
            }

            else if(g->getBalance() == 0)
            {
                node->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }
            
            else if(g->getBalance() == -1)
            {
                node->setBalance(-1);
                c->setBalance(1);
                g->setBalance(0);
            }

        }


    }

    else if(node->getBalance() + diff == -1)
    {
        node->setBalance(-1);
        return;
    }

    else if(node->getBalance() + diff == 0)
    {
        node->setBalance(0);
        removeFix(p, ndiff);
    }


    //------------------------------------------------------------//
        
        if(node->getBalance() + diff == 2)
    {
        AVLNode<Key, Value>* c = node->getRight();
        if(c->getBalance() == 1)
        {  
                rotateLeft(node);
                node->setBalance(0);
                c->setBalance(0);

        }

        else if(c->getBalance() == 0)
        {
        
                rotateLeft(node);
                node->setBalance(1);
                c->setBalance(-1);
        }


        else if(c->getBalance()  == -1)
        {
            AVLNode<Key, Value>* g = c->getLeft();
            rotateLeft(c);
            rotateRight(node);

            if(g->getBalance() == -1)
            {
                node->setBalance(0);
                c->setBalance(1);
                g->setBalance(0);
            }

            else if(g->getBalance() == 0)
            {
                node->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }
            
            else if(g->getBalance() == 1)
            {
                node->setBalance(1);
                c->setBalance(-1);
                g->setBalance(0);
            }

        }


    }

    else if(node->getBalance() + diff == -1)
    {
        node->setBalance(-1);
        return;
    }

    else if(node->getBalance() + diff == 0)
    {
        node->setBalance(0);
        removeFix(p, ndiff);
    }


}







template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::find(const Key& key) const {
    return static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
}




// template<class Key, class Value>
// AVLNode<Key, Value>* AVLTree<Key, Value>::successor(AVLNode<Key, Value>* current) const
// {
//     if (current == nullptr)
//         return nullptr;

//     if (current->getRight() != nullptr) {
//         AVLNode<Key, Value>* succ = current->getRight();
//         while (succ->getLeft() != nullptr) {
//             succ = succ->getLeft();
//         }
//         return succ;
//     }

//     AVLNode<Key, Value>* parent = current->getParent();
//     while (parent != nullptr && current == parent->getRight()) {
//         current = parent;
//         parent = parent->getParent();
//     }
//     return parent;
// }





template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node) {
   
    // if (node == nullptr || node->getRight() == nullptr)
    //     return;

    AVLNode<Key, Value>* pivot = node->getRight();
    node->setRight(pivot->getLeft());
   
    if (pivot->getLeft() != nullptr)
        pivot->getLeft()->setParent(node);
   
    pivot->setParent(node->getParent());
   
    if (node->getParent() == nullptr)
        this->root_ = pivot;
    
    else if (node == node->getParent()->getLeft())
        node->getParent()->setLeft(pivot);
    
    else
        node->getParent()->setRight(pivot);
    pivot->setLeft(node);
    node->setParent(pivot);
}






template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node) {
  


    AVLNode<Key, Value>* pivot = node->getLeft();
    
    node->setLeft(pivot->getRight());
   
    if (pivot->getRight() != nullptr)
        pivot->getRight()->setParent(node);
    pivot->setParent(node->getParent());
   
    if (node->getParent() == nullptr)
        this->root_ = pivot;
   
    else if (node == node->getParent()->getLeft())
        node->getParent()->setLeft(pivot);
   
    else
        node->getParent()->setRight(pivot);
    
    pivot->setRight(node);
    node->setParent(pivot);
}






















template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif