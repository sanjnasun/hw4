#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int height(Node* given)
{
  if(given == nullptr)
  return 0;

    int leftH = height(given->left);
    int rightH = height(given->right);
    
    if(leftH > rightH) //adding 1--causing probs
    {
      return leftH + 1;
    }
    else
    {
      return rightH + 1;
    }
  
}

bool equalPaths(Node * root)
{
    // Add your code below
    if(root == nullptr)
    return true;

    //add case where a child only has one leaf but not another
    //in the case where the lh and rh have children// not equal to 0

    


    int lh = height(root->left);
    int rh = height(root->right);

    
    
    if(lh != rh && (root->left != nullptr) && (root->right != nullptr))
    {
      return false;
    }


    
    // else
    // {
    //   bool leqa = equalPaths(root->left);
    //   bool reqa = equalPaths(root->right);
    //   return (leqa && reqa);
    // }

    return equalPaths(root->left) && equalPaths(root->right);

    
}
