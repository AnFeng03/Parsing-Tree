#ifndef P2_RDP_H
#define P2_RDP_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "tree.h"

#define FAILED NULL


extern char *nextTerminal;

bool lookahead(char c);
bool match(char c);

TREE Expr(void);
TREE Atom(void);
TREE List(void);
TREE Elements(void);
TREE Rest(void);
TREE Word(void);
TREE WordT(void);
TREE Number(void);
TREE NumberT(void);
TREE Digit(void);
TREE Letter(void);


#endif //P2_RDP_H
