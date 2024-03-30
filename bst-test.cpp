#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    AVLTree<int, int> at;
    at.insert(std::make_pair(10, 10));
    at.insert(std::make_pair(5,8));
    at.insert(std::make_pair(15,12));
    at.insert(std::make_pair(2,7));
    at.insert(std::make_pair(7,12));
    at.insert(std::make_pair(12,9));
    at.insert(std::make_pair(18,6));
    at.insert(std::make_pair(11,12));
    at.insert(std::make_pair(14,12));
    at.insert(std::make_pair(21,12));
    at.insert(std::make_pair(13,12));

    at.print();
    // Binary Search Tree tests
    //BinarySearchTree<char,int> bt;
    // bt.insert(std::make_pair('a',1));
    // bt.insert(std::make_pair('b',2));
    
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');

    // // AVL Tree Tests
    // AVLTree<char,int> at;
    // at.insert(std::make_pair('a',1));
    // at.insert(std::make_pair('b',2));

    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');

    // return 0;

  // BinarySearchTree<std::string, std::string> testTree;

	// testTree.remove("supercalifragilisticexpialodocious");

	// EXPECT_TRUE(verifyBST(testTree, {}));

}
