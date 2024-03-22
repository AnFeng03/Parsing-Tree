#ifndef P2_TREE_H
#define P2_TREE_H

typedef struct NODE *TREE;
struct NODE {
    char label;
    TREE leftmostChild, rightSibling;
};

TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2(char x, TREE t1, TREE t2);
TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);

void printTree(TREE t, int depth);

void addChildToLeaf1(TREE root, char target, TREE child);
void addChildToLeaf2(TREE root, char target, TREE child1, TREE child2);
void addChildToLeaf3(TREE root, char target, TREE child1, TREE child2, TREE child3);

#endif //P2_TREE_H
