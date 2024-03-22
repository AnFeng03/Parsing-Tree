#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "rdp.h"
#include "stack.h"
#include "tdp.h"
#include "tree.h"
#include "queue.h"

//---------------------------------------------------
//Indexes of syntactic categories (rows of parse table)
//<E> : 0
//<A> : 1
//<W> : 2
//<LETTER> : 3
//<WT> : 4
//<N> : 5
//<D> : 6
//<NT> : 7
//<LIST> : 8
//<ELEMENTS> : 9
//<REST> : 10
//---------------------------------------------------
//Productions to be stored as entries in parse Table
//<E> -> A | L : 1,2
//<A> -> W | N : 3,4
//<W> -> L WT : 5
//<L> -> a | ... | z : 6
//<WT> -> epsilon | W : 7,8
//<N> -> D NT : 9
//<D> -> 0 | ... | 10 : 10
//<NT> -> epsilon | N : 11,12
//<LIST> -> (ELEMENT) : 13
//<ELEMENTS> -> epsilon | EXPR REST : 14,15
//<REST> -> epsilon | ' ' EXPR REST : 16,17
//--------------------------------------------
//          '\0'  a-z  0-9  (   )  ' '
//-------------------------------------
// <E>0      0    1    1    2   0   0
// <A>1      0    3    4    0   0   0
// <W>2      0    5    0    0   0   0
// <Z>3      0    6    0    0   0   0
// <O>4      7    8    0    0   7   7
// <N>5      0    0    9    0   0   0
// <D>6      0    0   10    0   0   0
// <T>7     11    0   12    0  11  11
// <L>8      0    0    0   13   0   0
// <Q>9      0   15   15   15  14   0
// <R>10     0    0    0    0  16  17
//-------------------------------------

int** makeTable(int rows, int columns) {
    int** table = (int**) malloc(rows * sizeof(int*));
    if (table == NULL) {
        // Error handling
        exit(1);
    }
    for(int i = 0; i < rows; i++) {
        table[i] = (int*) malloc(columns * sizeof(int));
        if (table[i] == NULL) {
            // Error handling
            exit(1);
        }
        // Initialize each column in the current row to -1
        for(int j = 0; j < columns; j++) {
            table[i][j] = 0;
        }
    }

    table[0][1] = 1;
    table[0][2] = 1;
    table[0][3] = 2;

    table[1][1] = 3;
    table[1][2] = 4;

    table[2][1] = 5;

    table[3][1] = 6;

    table[4][0] = 7;
    table[4][1] = 8;
    table[4][4] = 7;
    table[4][5] = 7;

    table[5][2] = 9;

    table[6][2] = 10;

    table[7][0] = 11;
    table[7][2] = 12;
    table[7][4] = 11;
    table[7][5] = 11;

    table[8][3] = 13;

    table[9][1] = 15;
    table[9][2] = 15;
    table[9][3] = 15;
    table[9][4] = 14;

    table[10][4] = 16;
    table[10][5] = 17;

    return table;
}

int getProduction(int** table, char symbol, char nonTerminal){
    int column;
    int row;
    switch (nonTerminal) {
        case 'E':
            row = 0; break;
        case 'A':
            row = 1;break;
        case 'W':
            row = 2; break;
        case 'Z':
            row = 3; break;
        case 'O':
            row = 4; break;
        case 'N':
            row = 5; break;
        case 'D':
            row = 6; break;
        case 'T':
            row = 7; break;
        case 'L':
            row = 8; break;
        case 'Q':
            row = 9; break;
        case 'R':
            row = 10; break;
        default:
            row = 0;
    }

    if(symbol == '\0'){
        column = 0;
    } else if (isalpha(symbol) && islower(symbol)){
        column = 1;
    } else if (isdigit(symbol)){
        column = 2;
    } else if (symbol == '('){
        column = 3;
    } else if (symbol == ')'){
        column = 4;
    } else if (symbol == ' '){
        column = 5;
    } else{
        column = 0;
    }

    return table[row][column];
}

bool isTerminal(char symbol){
    if(symbol == '\0'){
        return true;
    } else if (isalpha(symbol) && islower(symbol)){
        return true;
    } else if (isdigit(symbol)){
        return true;    }
    else if (symbol == '('){
        return true;
    } else if (symbol == ')'){
        return true;
    } else if (symbol == ' '){
        return true;
    } else{
        return false;
    }
}


TREE tdp_Parse(char *input, int** parseTable){
    nextTerminal = input;
    Stack* s =stack_create();
    stack_push(s, 'E');
    TREE tdpParseTree = makeNode0('E');

    while(!stack_is_empty(s)) {
        if (isTerminal(stack_peek(s)) && *nextTerminal == stack_peek(s) && !isalpha(stack_peek(s))) {
            stack_pop(s);
            nextTerminal += 1;
        }

        if (!stack_is_empty(s)) {
            int production = getProduction(parseTable, *nextTerminal, stack_peek(s));

            switch (production) {

                case 1: {
                    stack_pop(s);
                    stack_push(s, 'A');

                    TREE t1 = makeNode0('A');
                    addChildToLeaf1(tdpParseTree, 'E', t1);
                    break;
                }

                case 2: {
                    stack_pop(s);
                    stack_push(s, 'L');
                    TREE t1 = makeNode0('L');
                    addChildToLeaf1(tdpParseTree,'E', t1);
                    break;
                }

                case 3: {
                    stack_pop(s);
                    stack_push(s, 'W');
                    TREE t1 = makeNode0('W');
                    addChildToLeaf1(tdpParseTree, 'A', t1);
                    break;
                }
                case 4: {
                    stack_pop(s);
                    stack_push(s, 'N');
                    TREE t1 = makeNode0('N');
                    addChildToLeaf1(tdpParseTree, 'A', t1);
                    break;
                }
                case 5: {
                    stack_pop(s);
                    stack_push(s, 'O');
                    stack_push(s, 'Z');
                    TREE t1 = makeNode0('Z');
                    TREE t2 = makeNode0('O');
                    addChildToLeaf2(tdpParseTree,'W', t1, t2);
                    break;
                }

                case 6: {
                    stack_pop(s);
                    char c = *nextTerminal;
                    nextTerminal += 1;

                    TREE t1 = makeNode0(c);
                    addChildToLeaf1(tdpParseTree, 'Z', t1);
                    break;
                }

                case 7: { //epsilon
                    stack_pop(s);

                    TREE t1 = makeNode0('e');
                    addChildToLeaf1(tdpParseTree,'O', t1);
                    break;
                }


                case 8: {
                    stack_pop(s);
                    stack_push(s, 'W');

                    TREE t1 = makeNode0('W');
                    addChildToLeaf1(tdpParseTree,'O', t1); //change
                    break;
                }

                case 9: {
                    stack_pop(s);
                    stack_push(s, 'T');
                    stack_push(s, 'D');

                    TREE t1 = makeNode0('D');
                    TREE t2 = makeNode0('T');
                    addChildToLeaf2(tdpParseTree, 'N', t1, t2);

                    break;
                }

                case 10: {
                    stack_pop(s);
                    char c = *nextTerminal;
                    nextTerminal += 1;

                    TREE t1 = makeNode0(c);
                    addChildToLeaf1(tdpParseTree, 'D', t1);
                    break;
                }

                case 11: { //epsilon
                    stack_pop(s);

                    TREE t1 = makeNode0('e');
                    addChildToLeaf1(tdpParseTree,'T', t1);
                    break;
                }

                case 12: {
                    stack_pop(s);
                    stack_push(s, 'N');

                    TREE t1 = makeNode0('N');
                    addChildToLeaf1(tdpParseTree,'T', t1); //changed
                    break;
                }

                case 13: {
                    stack_pop(s);
                    stack_push(s, ')');
                    stack_push(s, 'Q');
                    stack_push(s, '(');

                    TREE t1 = makeNode0('(');
                    TREE t2 = makeNode0('Q');
                    TREE t3 = makeNode0(')');
                    addChildToLeaf3(tdpParseTree, 'L', t1, t2, t3);
                    break;
                }

                case 14: { //epslion
                    stack_pop(s);

                    TREE t1 = makeNode0('e');
                    addChildToLeaf1(tdpParseTree,'Q', t1);
                    break;
                }

                case 15: {
                    stack_pop(s);
                    stack_push(s, 'R');
                    stack_push(s, 'E');

                    TREE t1 = makeNode0('E');
                    TREE t2 = makeNode0('R');
                    addChildToLeaf2(tdpParseTree, 'Q', t1, t2);

                    break;
                }

                case 16: { //epsilon
                    stack_pop(s);

                    TREE t1 = makeNode0('e');
                    addChildToLeaf1(tdpParseTree,'R', t1);
                    break;
                }

                case 17: {
                    stack_pop(s);

                    stack_push(s, 'R');
                    stack_push(s, 'E');
                    stack_push(s, ' ');

                    TREE t1 = makeNode0(' ');
                    TREE t2 = makeNode0('E');
                    TREE t3 = makeNode0('R');
                    addChildToLeaf3(tdpParseTree, 'R', t1, t2, t3);

                    break;
                }

                default:
                    return NULL;
            }

            //printf("Production %d \n", production);
            //stack_print(s);

        }
    }
    return tdpParseTree;
}


