/*
 * File: sentgen.c
 *
 * Contains function definitions for generating/printing sentences.
 *
 * Author: Jack Romo <sharrackor@gmail.com>
 */


#include "sentgen.h"


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
