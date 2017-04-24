// linked binary tree using nodes of type binaryTreeNode
// derives from the abstract class binaryTree

#ifndef linkedBinaryTree_
#define linkedBinaryTree_

#include <iostream>
#include "binaryTree.h"
#include "arrayQueue.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"

using namespace std;

template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E> > {
public:
    linkedBinaryTree() {
        root = NULL;
        treeSize = 0;
    }

    linkedBinaryTree(const linkedBinaryTree<E> &theTree);

    ~linkedBinaryTree() {
        erase();
    }

    bool empty() const {
        return treeSize == 0;
    }

    int size() const {
        return treeSize;
    }

    E *rootElement() const;

    void makeTree(const E &element, linkedBinaryTree<E> &, linkedBinaryTree<E> &);

    linkedBinaryTree<E> removeLeftSubtree();

    linkedBinaryTree<E> removeRightSubtree();

    void preOrder(void (*theVisit)(binaryTreeNode<E> *)) {
        visit = theVisit;
        preOrder(root);
    }

    void inOrder(void (*theVisit)(binaryTreeNode<E> *)) {
        visit = theVisit;
        inOrder(root);
    }

    void postOrder(void (*theVisit)(binaryTreeNode<E> *)) {
        visit = theVisit;
        postOrder(root);
    }

    void levelOrder(void (*)(binaryTreeNode<E> *));

    void preOrderOutput() {
        preOrder(output);
        cout << endl;
    }

    void inOrderOutput() {
        inOrder(output);
        cout << endl;
    }

    void postOrderOutput() {
        postOrder(output);
        cout << endl;
    }

    void levelOrderOutput() {
        levelOrder(output);
        cout << endl;
    }

    void erase() {
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }

    int height() const {
        return height(root);
    }

    E *search(E element);

    linkedBinaryTree<E> &operator=(const linkedBinaryTree<E> &rightHand);

    bool compare(const linkedBinaryTree<E> &x);

    int leafNode() const {
        return countLeafNodes(root);
    }

    void invert() {
        invert(root);
    }

    bool isHBLT() {
        if (!root)
            return true;
        else
            return isHBLT(root->leftChild, root->rightChild);
    }

protected:
    binaryTreeNode<E> *root;                // pointer to root
    int treeSize;                           // number of nodes in tree
    static void (*visit)(binaryTreeNode<E> *);      // visit function
    static int count;         // used to count nodes in a subtree
    static void preOrder(binaryTreeNode<E> *t);

    static void inOrder(binaryTreeNode<E> *t);

    static void postOrder(binaryTreeNode<E> *t);

    static void countNodes(binaryTreeNode<E> *t) {
        visit = addToCount;
        count = 0;
        preOrder(t);
    }

    static void dispose(binaryTreeNode<E> *t) {
        delete t;
    }

    static void output(binaryTreeNode<E> *t) {
        cout << t->element << ' ';
    }

    static void addToCount(binaryTreeNode<E> *t) {
        count++;
    }

    static int height(binaryTreeNode<E> *t);

    E *search(E element, binaryTreeNode<E> *t);

    binaryTreeNode<E> *copy(binaryTreeNode<E> *t);

    bool compare(binaryTreeNode<E> *t, binaryTreeNode<E> *u);

    static int countLeafNodes(binaryTreeNode<E> *t);

    void invert(binaryTreeNode<E> *&t);

    bool isHBLT(binaryTreeNode<E> *&l, binaryTreeNode<E> *&r);

    int s(binaryTreeNode<E> *&t);

};

// the following should work but gives an internal compiler error
template<class E>
void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E> *);

template<class E>
int linkedBinaryTree<E>::count;

template<class E>
linkedBinaryTree<E>::linkedBinaryTree(const linkedBinaryTree<E> &theTree) {
    root = copy(theTree.root);
    treeSize = theTree.treeSize;
}

template<class E>
linkedBinaryTree<E> &linkedBinaryTree<E>::operator=(const linkedBinaryTree<E> &rightHand) {
    erase();
    root = copy(rightHand.root);
    treeSize = rightHand.treeSize;

    return *this;
}

template<class E>
binaryTreeNode<E> *linkedBinaryTree<E>::copy(binaryTreeNode<E> *t) {
    if (!t) {
        return NULL;
    }
    binaryTreeNode<E> *left, *right;
    left = copy(t->leftChild);
    right = copy(t->rightChild);
    return new binaryTreeNode<E>(t->element, left, right);
}

template<class E>
bool linkedBinaryTree<E>::compare(const linkedBinaryTree<E> &x) {
    if (treeSize != x.treeSize) {
        return false;
    }
    return compare(root, x.root);
}

template<class E>
bool linkedBinaryTree<E>::compare(binaryTreeNode<E> *t, binaryTreeNode<E> *u) {
    if (!t && !u) {
        return true;
    }
    if (t->element != u->element) {
        return false;
    }
    return compare(t->leftChild, u->leftChild)
            && compare(t->rightChild, u->rightChild);
}

template<class E>
E *linkedBinaryTree<E>::search(E element) {
    return search(element, root);
}

template<class E>
E *linkedBinaryTree<E>::search(E element, binaryTreeNode<E> *t) {
    if (!t) {
        return NULL;
    }
    if (t->element == element) {
        return &t->element;
    }
    E *p;
    p = search(element, t->leftChild);
    if (p) {
        return p;
    }
    return search(element, t->rightChild);
}

template<class E>
E *linkedBinaryTree<E>::rootElement() const {
    // Return NULL if no root. Otherwise, return pointer to root element.
    if (treeSize == 0) {
        return NULL;  // no root
    } else {
        return &root->element;
    }
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E &element, linkedBinaryTree<E> &left, linkedBinaryTree<E> &right) {
    // Combine left, right, and element to make new tree.
    // left, right, and this must be different trees.
    // create combined tree
    root = new binaryTreeNode<E>(element, left.root, right.root);
    treeSize = left.treeSize + right.treeSize + 1;

    // deny access from trees left and right
    left.root = right.root = NULL;
    left.treeSize = right.treeSize = 0;
}

template<class E>
linkedBinaryTree<E> linkedBinaryTree<E>::removeLeftSubtree() {   // Remove and return the left subtree.
// check if empty
    if (treeSize == 0)
        throw emptyTree();

    // detach left subtree and save in leftSubtree
    linkedBinaryTree<E> leftSubtree;
    leftSubtree.root = root->leftChild;
    count = 0;
    countNodes(leftSubtree.root);
    leftSubtree.treeSize = count;

    root->leftChild = NULL;
    treeSize -= leftSubtree.treeSize;

    return leftSubtree;
}

template<class E>
linkedBinaryTree<E> linkedBinaryTree<E>::removeRightSubtree() {   // Remove and return the right subtree.
// check if empty
    if (treeSize == 0)
        throw emptyTree();

    // detach right subtree and save in rightSubtree
    linkedBinaryTree<E> rightSubtree;
    rightSubtree.root = root->rightChild;
    count = 0;
    //rightSubtree.treeSize = countNodes(rightSubtree.root);
    countNodes(rightSubtree.root);
    rightSubtree.treeSize = count;
    root->rightChild = NULL;
    treeSize -= rightSubtree.treeSize;

    return rightSubtree;
}

template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t) {   // Preorder traversal.
    if (t != NULL) {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t) {   // Inorder traversal.
    if (t != NULL) {
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t) {   // Postorder traversal.
    if (t != NULL) {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

template<class E>
void linkedBinaryTree<E>::levelOrder(void (*theVisit)(binaryTreeNode<E> *)) {   // Level-order traversal.
    arrayQueue<binaryTreeNode<E> *> q;
    binaryTreeNode<E> *t = root;
    while (t != NULL) {
        theVisit(t);  // visit t

        // put t's children on queue
        if (t->leftChild != NULL)
            q.push(t->leftChild);
        if (t->rightChild != NULL)
            q.push(t->rightChild);

        // get next node to visit
        try {
            t = q.front();
        } catch (const queueEmpty &) {
            return;
        }
        q.pop();
    }
}

template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t) {
    // Return height of tree rooted at *t.
    if (t == NULL) {    // empty tree
        return 0;
    }
    int hl = height(t->leftChild);  // height of left
    int hr = height(t->rightChild); // height of right
    if (hl > hr) {
        return ++hl;
    } else {
        return ++hr;
    }
}

template<class E>
int linkedBinaryTree<E>::countLeafNodes(binaryTreeNode<E> *t) {
    if (!t) {
        return 0;
    }
    binaryTreeNode<E> *left = t->leftChild, *right = t->rightChild;
    return (!left && !right) ? 1 : countLeafNodes(left) + countLeafNodes(right);
}

template<class E>
void linkedBinaryTree<E>::invert(binaryTreeNode<E> *&t) {
    if (t) {
        invert(t->leftChild);
        invert(t->rightChild);
        binaryTreeNode<E> *temp = t->leftChild;
        t->leftChild = t->rightChild;
        t->rightChild = temp;
    }
}

template<class E>
bool linkedBinaryTree<E>::isHBLT(binaryTreeNode<E> *&l, binaryTreeNode<E> *&r) {
    if (!l && !r) {
        return true;
    } else if (l && !r) {
        return isHBLT(l->leftChild, l->rightChild);
    } else if (!l) {
        return false;
    }

    if (s(l) < s(r)) {
        return false;
    } else {
        return isHBLT(l->leftChild, l->rightChild) && isHBLT(r->leftChild, r->rightChild);
    }
}

template<class E>
int linkedBinaryTree<E>::s(binaryTreeNode<E> *&t) {
    if (!t) {
        return 0;
    }
    int sl = s(t->leftChild);
    int sr = s(t->rightChild);
    if (sl > sr) {
        return ++sr;
    } else {
        return ++sl;
    }
}

#endif

