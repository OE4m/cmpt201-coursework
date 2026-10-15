#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
    uint64_t size;
    struct header *next;
    int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
    block->size = size;
    block->next = next;
    block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
    // TODO: Implement first fit
    while (free_list_ptr) {
        if (free_list_ptr->size >= size) {
            return free_list_ptr->id;
        }
        free_list_ptr = free_list_ptr->next;
    }
    return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
    int best_fit_id = -1;
    uint64_t best_fit_size = UINT64_MAX;
    // TODO: Implement best fit
    while (free_list_ptr) {
        if (free_list_ptr->size >= size && free_list_ptr->size < best_fit_size) {
            best_fit_size = free_list_ptr->size;
            best_fit_id = free_list_ptr->id;
        }
        free_list_ptr = free_list_ptr->next;
    }
    return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
    int worst_fit_id = -1;
    uint64_t worst_fit_size = 0;
    // TODO: Implement worst fit
    while (free_list_ptr) {
        if (free_list_ptr->size >= size && free_list_ptr->size > worst_fit_size) {
            worst_fit_size = free_list_ptr->size;
            worst_fit_id = free_list_ptr->id;
        }
        free_list_ptr = free_list_ptr->next;
    }
    return worst_fit_id;
}

int main(void) {

    struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
    struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
    struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
    struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
    struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

    initialize_block(free_block1, 6, free_block2, 1);
    initialize_block(free_block2, 12, free_block3, 2);
    initialize_block(free_block3, 24, free_block4, 3);
    initialize_block(free_block4, 8, free_block5, 4);
    initialize_block(free_block5, 4, NULL, 5);

    struct header *free_list_ptr = free_block1;

    int first_fit_id = find_first_fit(free_list_ptr, 7);
    int best_fit_id = find_best_fit(free_list_ptr, 7);
    int worst_fit_id = find_worst_fit(free_list_ptr, 7);

    printf("The ID for First-Fit algorithm is:   %d\n", first_fit_id);
    printf("The ID for Best-Fit algorithm is:    %d\n", best_fit_id);
    printf("The ID for Worst-Fit algorithm is:   %d\n", worst_fit_id);

    return 0;
}

/*
 * 1. end_z = start_z + size_z.
 *    merged_before = false.
 *    merged_after = false.
 *
 * 2. For each current block in the free list:
 *      end_current = start_current + size_current.
 *
 *      If end_current == start_z:
 *          Remove current from the free list.
 *          start_z = start_current.
 *          size_z += size_current.
 *          merged_before = true.
 *
 *      Else if end_z == start_current:
 *          Remove current from the free list.
 *          size_z += size_current.
 *          end_z = start_z + size_z.
 *          merged_after = true.
 *
 *      If merged_before AND merged_after:
 *          break.
 *
 * 3. Store size_z in the header at start_z.
 *    Insert the merged block into the free list.
 */