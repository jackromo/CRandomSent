/*
 * File: main.c
 *
 * Main entry point of program.
 *
 * Author: Jack Romo <sharrackor@gmail.com>
 */


#include <stdlib.h>
#include "sentgen.h"


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

