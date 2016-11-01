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
    Sent = 0,
    The,
    NounP,
    VerbP,
    Noun,
    AdvSet,
    Adv,
    Verb,
    Adj,
    NUM_TYPES  // special val for array size; do not use!
} node_type;


/*
 * ast_type_data: Data about ast_node's type.
 * Index in array of type datas = type itself,
 * used in array to define a context-free grammar.
 */
typedef struct {
    bool printable;
    int num_poss_vals;
    char **poss_vals;
    int num_child_combs; // several possible sets of children, randomly chosen
    int *child_counts;      // counts of children in each set
    node_type **child_types;  // sets of child types, corresponds to child_counts
} ast_type_data;


typedef ast_type_data cf_grammar[NUM_TYPES];


struct str_ast_node;
typedef struct str_ast_node ast_node;


struct str_ast_node {
    ast_node *children;
    node_type *chosen_childtypes;  // chosen types for children
    int num_children;
    node_type type;
    char *val;
};


ast_node new_ast_node(node_type type, char *val, cf_grammar grammar);
void print_ast_node(ast_node node, cf_grammar grammar);
void gen_node_children(ast_node *node, cf_grammar grammar);
ast_node gen_node(node_type type, cf_grammar grammar);


/*
 * new_ast_node: Produce an empty ast_node.
 */
ast_node new_ast_node(node_type type, char *val, cf_grammar grammar) {
    ast_node new_node;
    new_node.val = val;
    new_node.type = type;
    if(grammar[type].num_child_combs > 0) {
        int chosen_child_comb = rand() % grammar[type].num_child_combs;
        new_node.num_children = grammar[type].child_counts[chosen_child_comb];
        new_node.children = malloc(sizeof(ast_node)*new_node.num_children);
        if(new_node.children == NULL) {
            printf("Failure: could not malloc ast node's children");
            exit(EXIT_FAILURE);
        }
        new_node.chosen_childtypes = grammar[type].child_types[chosen_child_comb];
    }
    return new_node;
}


/*
 * print_ast_node: Print an ast_node.
 */
void print_ast_node(ast_node node, cf_grammar grammar) {
    if(grammar[node.type].printable)
        printf("%s ", node.val);
    else {
        for(int i = 0; i < node.num_children; i++)
            print_ast_node(node.children[i], grammar);
    }
}


/*
 * gen_node_children: Generate an AST node's children.
 */
void gen_node_children(ast_node *node, cf_grammar grammar) {
    for(int i = 0; i < node->num_children; i++) {
        node->children[i] = gen_node(node->chosen_childtypes[i], grammar);
    }
}


/*
 * gen_node: Generate an AST node of a certain type, along with its children.
 */
ast_node gen_node(node_type type, cf_grammar grammar) {
    ast_node node;
    if(grammar[type].printable) {
        char *chosen_val = grammar[type].poss_vals[rand() % grammar[type].num_poss_vals];
        node = new_ast_node(
            type,
            chosen_val,
            grammar
        );
    } else {
        node = new_ast_node(
            type,
            NULL,
            grammar
        );
        gen_node_children(&node, grammar);
    }
    return node;
}


// An example grammar.

cf_grammar example_gram = {
    // Sent
    (ast_type_data) {
        .printable = false,
        .num_child_combs = 1,
        .child_counts = (int[]) {2},
        .child_types = (node_type *[]) {
          (node_type []) {NounP, VerbP}
        },
        .num_poss_vals = 0,
        .poss_vals = NULL
    },
    // The
    (ast_type_data) {
        .printable = true,
        .num_child_combs = 0,
        .child_counts = NULL,
        .child_types = NULL,
        .num_poss_vals = 1,
        .poss_vals = (char *[]) {"the"}
    },
    // NounP
    (ast_type_data) {
        .printable = false,
        .num_child_combs = 1,
        .child_counts = (int[]) {3},
        .child_types = (node_type *[]) {
          (node_type []) {The, AdvSet, Noun}
        },
        .num_poss_vals = 0,
        .poss_vals = NULL
    },
    // VerbP
    (ast_type_data) {
        .printable = false,
        .num_child_combs = 1,
        .child_counts = (int[]) {3},
        .child_types = (node_type *[]) {
          (node_type []) {Verb, NounP, Adj}
        },
        .num_poss_vals = 0,
        .poss_vals = NULL
    },
    // Noun
    (ast_type_data) {
        .printable = true,
        .num_child_combs = 0,
        .child_counts = NULL,
        .child_types = NULL,
        .num_poss_vals = 4,
        .poss_vals = (char *[]) {
          "eagle", "businessman", "cat", "dog"
        }
    },
    // AdvSet
    (ast_type_data) {
        .printable = false,
        .num_child_combs = 2,
        .child_counts = (int[]) {2, 1},
        .child_types = (node_type *[]) {
          (node_type []) {AdvSet, Adv},
          (node_type []) {Adv}
        },
        .num_poss_vals = 0,
        .poss_vals = NULL
    },
    // Adv
    (ast_type_data) {
        .printable = true,
        .num_child_combs = 0,
        .child_counts = NULL,
        .child_types = NULL,
        .num_poss_vals = 4,
        .poss_vals = (char *[]) {
          "quick", "small", "angry", "bald"
        }
    },
    // Verb
    (ast_type_data) {
        .printable = true,
        .num_child_combs = 0,
        .child_counts = NULL,
        .child_types = NULL,
        .num_poss_vals = 4,
        .poss_vals = (char *[]) {
          "fought", "attacked", "annoyed", "ate"
        }
    },
    // Adj
    (ast_type_data) {
        .printable = true,
        .num_child_combs = 0,
        .child_counts = NULL,
        .child_types = NULL,
        .num_poss_vals = 4,
        .poss_vals = (char *[]) {
          "quickly", "easily", "strongly", "viciously"
        }
    }
};


int main(int argc, char **argv) {
    srand(time(NULL));  // randomize the seed
    ast_node sentence = gen_node(Sent, example_gram);
    print_ast_node(sentence, example_gram);
    printf("\n");
    return 0;
}

