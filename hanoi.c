#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #define DEBUG 0
#define ERROR 1
#define SUCCESS 0

#define RINGS 407 

void move(int start, int end); 
int get_top_ring(int rod); 
void remove_top_ring(int rod); 
void place_ring(int ring, int rod);
void hanoi(int args[3]); 
int get_other_rod(int ring_one, int ring_two); 

void print_layer(int layer);
void print_rods(void); 
void print_icon(int layer, int ring); 
void print_thin(void);
void print_ring(int size); 

int rods[3][RINGS] = { {0}, {0}, {0} };
int moves = 0;

int main(void) {
        for (int i = 0; i < RINGS; i++) {
                rods[0][i] = i + 1;
        }
        print_rods();

        int args[3] = { RINGS, 1, 3 };
        hanoi(args);

        print_rods();

        printf("Finished! Moves: %d\n", moves);
        return 0;
}

// Move top ring from start rod to top of end rod
void move(int start, int end) {

        moves++;

        #ifdef DEBUG 
        printf("%d'th move: %d, %d\n", moves, start, end); 
        #endif         

        int ring;
        int target_ring;
        ring = get_top_ring(start);
        target_ring = get_top_ring(end);

        if (ring == 0) {
                #ifdef DEBUG
                printf("Error: called 'move' on empty rod\n");
                #endif /* ifdef DEBUG */
                exit(1);
        }

        if (ring <= target_ring) {
                #ifdef DEBUG
                printf("Error: destination ring %d is smaller than %d\n", target_ring, ring); 
                #endif /* ifdef DEBUG */
                exit(1);
        }

        remove_top_ring(start);
        place_ring(ring, end);
}

// Get top ring from rod
int get_top_ring(int rod) {
        int top_ring = 0;
        for (int i = RINGS - 1; i >= 0; i--) {
                if (rods[rod][i] != 0) {
                        top_ring = rods[rod][i];
                        break;
                }
        }

        return top_ring;
}

// Removes top ring of rod
void remove_top_ring(int rod) {
        for (int i = RINGS - 1; i >= 0; i--) {
                if (rods[rod][i] != 0) {
                        rods[rod][i] = 0;
                        break;
                }
        }
}

// Place ring at top of rod
// Crashes if illegal move
void place_ring(int ring, int rod) {
        int i = RINGS - 1;
        while (i >= 0 && rods[rod][i] == 0) {
                i--;
        }

        #ifdef DEBUG
        if (i == RINGS - 1) {
                printf("Error: destination is full\n");
                exit(1);
        }
        #endif

        rods[rod][i + 1] = ring;
}

void hanoi(int args[3]) {

        #ifdef  DEBUG
        print_rods();
        #endif

        #ifdef DEBUG
        printf("Currently Executing: f(%d, %d, %d)\n", args[0], args[1], args[2]);        
        #endif /* ifdef DEBUG */

        if (args[0] == 1) {
                move(args[1] - 1, args[2] - 1);
                #ifdef DEBUG
                print_rods();
                #endif
        } else {
                int other = get_other_rod(args[1], args[2]);
                int new_args[3] = { args[0] - 1, args[1], other };
                hanoi(new_args);

                move(args[1] - 1, args[2] - 1);

                int newer_args[3] = { args[0] - 1, other, args[2] };
                hanoi(newer_args);
        }
}

// Trust me this works
int get_other_rod(int ring_one, int ring_two) {
        return 6 - ring_one - ring_two;
}
        

// ==========HELPER FUNCTIONS===========

// Print helper functions
void print_layer(int layer) {
        for (int i = 0; i < 3; i++) {
                print_icon(i, layer);
        }
        printf("\n");
}

// Prints state
void print_rods(void) {
        for (int i = RINGS - 1; i >= 0; i--) {
                print_layer(i);
        }
        printf("\n");
}

// Prints the correct icon for a ring
void print_icon(int layer, int ring) {
        if (rods[layer][ring] == 0) {
                print_thin();
        } else {
                print_ring(rods[layer][ring]);
        }
}

// Prints empty slot
void print_thin(void) {
        for (int i = 0; i < RINGS; i++) {
                printf(" ");
        }
        printf("| |");
        for (int i = 0; i < RINGS; i++) {
                printf(" ");
        }
}

// Prints ring
void print_ring(int size) {
        size = RINGS - size + 1;
        for (int i = 0; i <= RINGS - size; i++) {
                printf(" ");
        }
        for (int i = 0; i < 2 * (size + 1); i++) {
                printf("█");
        }
        for (int i = 0; i < RINGS - size; i++) {
                printf(" ");
        }
}
