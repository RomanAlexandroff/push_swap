#include "push_swap.h"

double  compute_disorder(t_node *a, int nodes_count)
{
    t_node  *j; 
    long total_pairs;
    long mistakes;
    double  disorder;

    if (!a || nodes_count <= 1)
        return (0.0);
    mistakes = 0;
    total_pairs = 0;
    while (a)
    {
        j = a->node_after;
        while (j)
        {
            if (a->value > j->value)
                mistakes++;
            total_pairs++;
            j = j->node_after;
        }
        a = a->node_after;
    }
    disorder = (double)mistakes / total_pairs;
    return (disorder);
}
