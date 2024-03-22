#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "rdp.h"
#include "tree.h"

char *nextTerminal;

bool lookahead(char c){
    return *nextTerminal == c;
}

bool match(char c){
    if (lookahead(c)){
        nextTerminal += 1;
        return true;
    } else {
        return false;
    }
}

TREE Expr(void) {
    if (lookahead('(')) {
        TREE t1 = List();
        if(t1) {
            return makeNode1('E', t1);
        }
    } else {
        TREE t2 = Atom();
        if(t2) {
            return makeNode1('E', t2);
        }
    }
    return NULL;
}

TREE Atom(void) {
    if (isdigit(*nextTerminal)) {
        TREE t1 = Number();
        if(t1) {
            return makeNode1('A', t1);
        }
    } else {
        TREE t2 = Word();
        if(t2) {
            return makeNode1('A', t2);
        }
    }
    return NULL;
}

TREE Word(void) {
    TREE t1 = Letter();
    if (t1) {
        TREE t2 = WordT();
        return makeNode2('W', t1, t2);
    }
        return NULL;
}

TREE WordT(void) {
    TREE t = Word();
    if (t) {
        return makeNode1('O',t);
    }
    return makeNode1('O', makeNode0('e'));  // epsilon node
}

TREE Letter(void) {
    if (isalpha(*nextTerminal) && islower(*nextTerminal)) {
        char c = *nextTerminal;
        match(c);
        return makeNode1('Z', makeNode0(c));
    }
    return NULL;
}

TREE Number(void) {
    TREE t1 = Digit();
    if (t1) {
        TREE t2 = NumberT();
        return makeNode2('N', t1, t2);
    }
    return NULL;
}

TREE NumberT(void) {
    TREE t = Number();
    if (t) {
        return makeNode1('T', t);
    }
    return makeNode1('T', makeNode0('e'));  // epsilon node
}

TREE Digit(void) {
    if (isdigit(*nextTerminal)) {
        char c = *nextTerminal;
        match(c);
        return makeNode1('D', makeNode0(c));
    }
    return NULL;
}

TREE List(void) {
    if (match('(')) {
        TREE t1 = Elements();
        if (match(')')) {
            return makeNode3('L', makeNode0('('), t1, makeNode0(')'));
        }
    }
    return NULL;
}


TREE Elements(void) {
    TREE t1 = Expr();
    if (t1) {
        TREE t2 = Rest();
        return makeNode2('Q', t1, t2);
    } else if (lookahead(')') || *nextTerminal == '\0') {
        return makeNode1('Q', makeNode0('e'));  // epsilon node for empty string or direct closing parenthesis
    }
    return NULL;
}



TREE Rest(void) {
    if (*nextTerminal == ')' || *nextTerminal == '\0') {
        return makeNode1('R', makeNode0('e'));  // epsilon node for empty string or direct closing parenthesis
    }

    if (lookahead(' ')) {
        match(' ');
    }

    TREE t1 = Expr();
    if (t1) {
        TREE t2 = Rest();
        return makeNode2('R', t1, t2);
    }

    return NULL;
}

