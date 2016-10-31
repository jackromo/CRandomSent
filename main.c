/*
 * File: main.c
 *
 * Main entry point of program.
 *
 * Author: Jack Romo <sharrackor@gmail.com>
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


typedef enum {
    Sent,
    The,
    NounP,
    VerbP,
    Noun,
    AdvSet,
    Adv,
    Verb,
    Adj
} node_type;


struct str_ast_node;
typedef struct str_ast_node ast_node;


struct str_ast_node {
    ast_node *children;
    int num_children;
    node_type type;
    bool printable;
    char *val;
};


ast_node new_ast_node(node_type type, char *val, int num_children);
void print_ast_node(ast_node node);
void gen_node_children(ast_node *node);
ast_node gen_node(node_type type);


/*
 * new_ast_node: Produce an empty ast_node.
 */
ast_node new_ast_node(node_type type, char *val, int num_children) {
    ast_node new_node;
    new_node.num_children = num_children;
    new_node.children = malloc(sizeof(ast_node)*num_children);
    if(new_node.children == NULL) {
        printf("Failure: could not malloc ast node's children");
        exit(EXIT_FAILURE);
    }
    new_node.type = type;
    switch(type) {
        case Adv:
        case Verb:
        case Noun:
        case The:
        case Adj:
            new_node.printable = true;
            break;
        default:
            new_node.printable = false;
    }
    if(new_node.printable)
        new_node.val = val;
    return new_node;
}


/*
 * print_ast_node: Print an ast_node.
 */
void print_ast_node(ast_node node) {
    if(node.printable)
        printf("%s ", node.val);
    else {
        for(int i = 0; i < node.num_children; i++)
            print_ast_node(node.children[i]);
    }
}


/*
 * gen_node_children: Generate an AST node's children.
 */
void gen_node_children(ast_node *node) {
    switch(node->type) {
        case Sent:
            node->children[0] = gen_node(NounP);
            node->children[1] = gen_node(VerbP);
            break;
        case NounP:
            node->children[0] = gen_node(The);
            node->children[1] = gen_node(AdvSet);
            node->children[2] = gen_node(Noun);
            break;
        case VerbP:
            node->children[0] = gen_node(Verb);
            node->children[1] = gen_node(NounP);
            node->children[2] = gen_node(Adj);
            break;
        case Noun:
            break;
        case AdvSet:
            for(int i = 0; i < node->num_children; i++) {
                node->children[i] = gen_node(Adv);
            }
            break;
        case Adv:
            break;
        case Verb:
            break;
        case Adj:
            break;
        case The:
            break;
        default:
            break;
    }
}


// All possible terminal node values.

char * nouns[] = {"cat", "dog", "businessman", "eagle"};
#define NUM_NOUNS 4
char * adverbs[] = {"quick", "small", "angry", "bald", "strong", "mean"};
#define NUM_ADVERBS 6
char * verbs[] = {"attacked", "fought", "ate", "annoyed"};
#define NUM_VERBS 4
char * adjectives[] = {"strongly", "easily", "angrily"};
#define NUM_ADJECTIVES 3


/*
 * gen_node: Generate an AST node of a certain type, along with its children.
 */
ast_node gen_node(node_type type) {
    ast_node node;
    switch(type) {
        case Sent:
            node = new_ast_node(type, NULL, 2);
            break;
        case NounP:
            node = new_ast_node(type, NULL, 3);
            break;
        case VerbP:
            node = new_ast_node(type, NULL, 4);
            break;
        case Noun:
            node = new_ast_node(type, nouns[rand() % NUM_NOUNS], 0);
            break;
        case AdvSet:
            node = new_ast_node(type, NULL, rand() % 4);
            break;
        case Adv:
            node = new_ast_node(type, adverbs[rand() % NUM_ADVERBS], 0);
            break;
        case Verb:
            node = new_ast_node(type, verbs[rand() % NUM_VERBS], 0);  // TODO
            break;
        case Adj:
            node = new_ast_node(type, adjectives[rand() % NUM_ADJECTIVES], 0);  // TODO
            break;
        case The:
            node = new_ast_node(type, "the", 0);  // TODO
            break;
        default:
            break;
    }
    gen_node_children(&node);
    return node;
}



int main(int argc, char **argv) {
    srand(time(NULL));  // randomize the seed
    ast_node sentence = gen_node(Sent);
    print_ast_node(sentence);
    printf("\n");
    return 0;
}

