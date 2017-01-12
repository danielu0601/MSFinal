/***
 * This code .h file define size and struct used.
 */

#define FILE_SIZE       32
// only 26*n is support due to invert matrix function
// only 26 and 676 add to git
#define DICT_SIZE       26
#define FILE_PATH       "../doc/FILE0001.txt"
#define MATRIX_PATH     "../Matrix/Matrix26trans.txt"
#define MATRIXinv_PATH  "../Matrix/Matrix26inv.txt"
#define SK_PATH         "./SK.txt"

// struct of node
typedef struct tree_node {
    int ID; // node ID
    double D[2][DICT_SIZE]; // index data
//    double D[2][DICT_SIZE]; // index data
    struct tree_node *Pl; // pointer to left node
    struct tree_node *Pr; // pointer to right node
    int FID; // pointer to file, use file's ID here
} Node;

// max function
double max( double a, double b ){ return (a>b)?a:b; }

