/*
 * File: sentgen.h
 *
 * Header for all sentence generation code.
 *
 * Author: Jack Romo <sharrackor@gmail.com>
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


/*
 * node_type: Type of token a node represents.
 * Each type has a unique integer value,
 * which can be overlayed with a homebrew enum.
 *
 * NB: Can only support number of types equal to
 * max range of int.
 */
typedef int node_type;


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


typedef ast_type_data cf_grammar[];


struct str_ast_node;
typedef struct str_ast_node ast_node;


struct str_ast_node {
    ast_node *children;
    node_type *chosen_childtypes;  // chosen types for children
    int num_children;
    node_type type;
    char *val;
};


// Function declarations
ast_node new_ast_node(node_type type, char *val, cf_grammar grammar);
void print_ast_node(ast_node node, cf_grammar grammar);
void gen_node_children(ast_node *node, cf_grammar grammar);
ast_node gen_node(node_type type, cf_grammar grammar);


