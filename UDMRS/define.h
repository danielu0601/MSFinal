/***
 * This code .h file define size and struct used.
 */

#define FILE_SIZE 500
#define DICT_SIZE 650
#define FILE_PATH "../doc/FILE0001.txt"

// struct of node
typedef struct tree_node {
    int ID; // node ID
    double D[DICT_SIZE]; // index data
    struct tree_node *Pl; // pointer to left node
    struct tree_node *Pr; // pointer to right node
    int FID; // pointer to file, use file's ID here
} Node;

// max function
double max( double a, double b ){ return (a>b)?a:b; }

