#include "types.h"
#include "constants.h"

ladel_int ladel_nonzero_pattern_of_row_in_L(ladel_sparse_matrix *M, 
                                                ladel_symbolics *sym,
                                                ladel_int row)
{
    ladel_int start = M->ncol, index, next_node, nb_marked_nodes;
    ladel_int *etree = sym->etree, *pattern = sym->pattern, *nodes = sym->nodes;
    MARK(nodes,row);
    for (index = M->p[row]; index < M->p[row+1]; index++)
    {
        next_node = M->i[index];
        nb_marked_nodes = 0;
        /* mark all the nodes found by traversing the etree */
        while (!IS_MARKED(nodes, next_node))
        {
            MARK(nodes, next_node);
            pattern[nb_marked_nodes] = next_node;
            nb_marked_nodes++;
            next_node = etree[next_node];
        }
        /*append the newly marked nodes to pattern (which goes from ncol-1 to 0)*/
        while (nb_marked_nodes > 0)
        {
            start--;
            nb_marked_nodes--;
            pattern[start] = pattern[nb_marked_nodes];
        }
    }
    /* unmark all the nodes to prepare for finding the pattern of the next row */
    for (index = start; index < M->ncol; index++) UNMARK(nodes, pattern[index]);
    UNMARK(nodes, row);

    return start;
}