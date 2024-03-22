#include "tree.h"
#include "rdp.h"
#include "tdp.h"
#include "queue.h"

TREE makeNode0(char x) {
    TREE root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1(char x, TREE t) {
    TREE root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}

TREE makeNode2(char x, TREE t1, TREE t2) {
    TREE root = makeNode1(x, t1);
    t1->rightSibling = t2;
    return root;
}

TREE makeNode3(char x, TREE t1, TREE t2, TREE t3) {
    TREE root = makeNode2(x, t1, t2);
    t2->rightSibling = t3;
    return root;
}


//For part 2:

void addChildToLeaf1(TREE root, char target, TREE child) {
    Queue q = {NULL, NULL};
    enqueue(&q, root);

    TREE lastFoundLeaf = NULL;

    while (!isEmpty(&q)) {
        TREE current = dequeue(&q);
        if (current->label == target && current->leftmostChild == NULL) {
            lastFoundLeaf = current;  // Save this leaf node, but don't break out yet.
        }

        for (TREE currChild = current->leftmostChild; currChild != NULL; currChild = currChild->rightSibling) {
            enqueue(&q, currChild);
        }
    }

    if (lastFoundLeaf != NULL) {
        lastFoundLeaf->leftmostChild = child;
    }
}

void addChildToLeaf2(TREE root, char target, TREE child1, TREE child2) {
    Queue q = {NULL, NULL};
    enqueue(&q, root);

    TREE lastFoundLeaf = NULL;

    while (!isEmpty(&q)) {
        TREE current = dequeue(&q);
        if (current->label == target && current->leftmostChild == NULL) {
            lastFoundLeaf = current;  // Save this leaf node, but don't break out yet.
        }

        for (TREE currChild = current->leftmostChild; currChild != NULL; currChild = currChild->rightSibling) {
            enqueue(&q, currChild);
        }
    }

    if (lastFoundLeaf != NULL) {
        lastFoundLeaf->leftmostChild = child1;
        child1->rightSibling = child2;
    }
}

void addChildToLeaf3(TREE root, char target, TREE child1, TREE child2, TREE child3) {
    Queue q = {NULL, NULL};
    enqueue(&q, root);

    TREE lastFoundLeaf = NULL;

    while (!isEmpty(&q)) {
        TREE current = dequeue(&q);
        if (current->label == target && current->leftmostChild == NULL) {
            lastFoundLeaf = current;  // Save this leaf node, but don't break out yet.
        }

        for (TREE currChild = current->leftmostChild; currChild != NULL; currChild = currChild->rightSibling) {
            enqueue(&q, currChild);
        }
    }

    if (lastFoundLeaf != NULL) {
        lastFoundLeaf->leftmostChild = child1;
        child1->rightSibling = child2;
        child2->rightSibling = child3;
    }
}


void printTree(TREE t, int depth) {
    if (t == NULL) return;

    // Print indentation
    for (int i = 0; i < depth; i++) {
        printf("  "); // 2 spaces for each depth level
    }

    // Print the node label
    printf("%c\n", t->label);

    // Print the leftmost child at a greater depth
    if (t->leftmostChild) {
        printTree(t->leftmostChild, depth + 1);
    }

    // Print the right sibling at the same depth
    if (t->rightSibling) {
        printTree(t->rightSibling, depth);
    }
}
