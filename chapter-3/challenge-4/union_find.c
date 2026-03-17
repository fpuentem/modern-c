#include <stdio.h>
#include <stdlib.h>

/* * * make_set now initializes BOTH the parent array and a size array.
 */
void make_set(size_t n, size_t parent[static n], size_t size[static n]) {
    for (size_t i = 0; i < n; ++i) {
        parent[i] = i;
        size[i] = 1; // Initially, every set has a size of 1
    }
}

/* *
 * find_set with Path Halving.
 * Notice how one extra line flattens the data structure dynamically.
 */
size_t find_set(size_t n, size_t parent[static n], size_t i) {
    while (i != parent[i]) {
        // Make the node point to its grandparent
        parent[i] = parent[parent[i]];
        // Move up the tree
        i = parent[i];
    }
    return i;
}

/* *
 * union_sets with Union by Size.
 * Attaches the smaller tree to the larger one to keep the structure flat.
 */
void union_sets(size_t n, size_t parent[static n],
                size_t size[static n], size_t i, size_t j) {
    size_t root_i = find_set(n, parent, i);
    size_t root_j = find_set(n, parent, j);

    if (root_i != root_j) {
        // Compare sizes and merge smaller into larger
        if (size[root_i] < size[root_j]) {
            parent[root_i] = root_j;
            size[root_j] += size[root_i]; // Update the size of the new root
        } else {
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
        }
    }
}

int main(void) {
    size_t const n = 10;

    // We now need two arrays: one for the connections, one for the weights
    size_t parent[n];
    size_t size[n];

    make_set(n, parent, size);

    // Build some connections
    union_sets(n, parent, size, 0, 1);
    union_sets(n, parent, size, 2, 3);
    union_sets(n, parent, size, 0, 2);

    // Merge the groups
    union_sets(n, parent, size, 4, 5);
    union_sets(n, parent, size, 6, 7);
    union_sets(n, parent, size, 4, 6);
    union_sets(n, parent, size, 0, 4);

    // Check connectivity
    if (find_set(n, parent, 3) == find_set(n, parent, 7)) {
        printf("3 and 7 are connected in a highly optimized way!\n");
    }

    return EXIT_SUCCESS;
}
