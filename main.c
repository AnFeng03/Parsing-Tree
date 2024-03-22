#include <stdio.h>
#include <string.h>
#include "rdp.h"
#include "tdp.h"
#include "tree.h"

void rdpREPL(void) {
    char input[256];
    printf("Enter an expression (or 'quit' to exit):\n");
    while (true) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        if (strncmp(input, "quit", 4) == 0) {
            break;
        }
        nextTerminal = input;
        TREE result = Expr();
        if (result && (*nextTerminal == '\n' || *nextTerminal == '\0')) {
            printf("Parsed successfully!\n");
            printTree(result, 0);
        } else {
            printf("Parsing failed.\n");
        }
    }
}


void tdpREPL(void) {
    char input[256];

    int synCat = 11;
    int terminal = 6;

    // Create the parse table
    int** parseTable = makeTable(synCat, terminal);

    printf("Enter an expression (or 'quit' to exit):\n");
    while (true) {
        printf("> ");
        fgets(input, sizeof(input), stdin);

        // Remove newline character from input
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        if (strncmp(input, "quit", 4) == 0) {
            for (int i = 0; i < synCat; i++) {
                free(parseTable[i]);
            }
            free(parseTable);
            break;
        }

        TREE result = tdp_Parse(input, parseTable);
        if (result && (*nextTerminal == '\n' || *nextTerminal == '\0')) {
            printf("Parsed successfully!\n");
            printTree(result, 0);
        } else {
            printf("Parsing failed.\n");
        }
    }
}

int main(void) {
    printf("Testing for recursive descent parser:\n");
    rdpREPL();
    printf("Testing for table driven parser:\n");
    tdpREPL();
    return 0;
}

