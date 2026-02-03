#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *helper function: mege
 * Uses 'const' to enforce that source arrays are read-only.
 * Uses 'static' inside [] to tell the compiler the arrays have at
 * least that size.
 */
void merge(size_t n_left, double const left[static n_left],
           size_t n_right, double const right[static n_right],
           double result[static n_left + n_right]) {

  size_t i = 0; // Index for left
  size_t j = 0; // Index for right
  size_t k = 0; // Index for result

  while (i < n_left && j < n_right) {
    if (left[i] <= right[j]) {
      result[k++] = left[i++];
    } else {
      result[k++] = right[j++];
    }
  }
  /* * Handle remaining elements.
   * memcpy is often optimized by hw/compiler.
   */
  if (i < n_left) {
    memcpy(result + k, left + i, (n_left - i) * sizeof(double));
  }
  if (j < n_right) {
    memcpy(result + k, right + j, (n_right - j) * sizeof(double));
  }
}

/*
 * merge_sort
 * Note the clean recursion using pointer arithmetic (A + mid).
 */
void merge_sort(size_t n, double A[static n]) {
  // Base case: 1 or 0 are already sorted
  if (n < 2)
    return;
  size_t mid = n / 2;
  // Recursively sort the two halfs
  // We treat 'A' as the start of the first half
  // We treat 'A + mid' as the start of the second half
  merge_sort(mid, A);
  merge_sort(n - mid, A + mid);

  /* Temporary buffer for the merge step.
   * In a heavy production env, you might allocate this once outside
   * the recursion to avoid repeated malloc calls, but this is
   * idiomatic self-contained logic.
   */
  double *tmp = malloc(n * sizeof(double));
  if (tmp) {
    merge(mid, A, n - mid, A + mid, tmp);
    // Copy sorted 'tmp' back into original 'A'
    memcpy(A, tmp, n * sizeof(double));
    free(tmp);
  } else {
    // Handle allocation failure (optional: print to stderr)
    fprintf(stderr, "Memory allocation failed!\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  double data[] = {3.5, 1.2, 9.9, 1.2, 5.0, 0.1};

  // Calculate size using sizeof (standard C idiom)
  size_t n = sizeof(data) / sizeof(data[0]);

  printf("Original:\n");
  for (size_t i = 0; i < n; ++i) {
    printf("%.1f ", data[i]);
  }
  printf("\n");

  merge_sort(n, data);

  printf("Sorted:\n");
  for (size_t i = 0; i < n; ++i) {
    printf("%.1f ", data[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
