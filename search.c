#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILE_SIZE 20
#define DICT_SIZE 20

/***
 * This code read the tree from file and do search
 */

struct tree_node {
    int ID; // node ID
    double D[DICT_SIZE]; // index data
    struct tree_node *parent; // record parent for easy using
    struct tree_node *Pl; // pointer to left node
    struct tree_node *Pr; // pointer to right node
    int FID; // pointer to file, use file's ID here
};

void readTree( FILE *fp, struct tree_node *root ) {

    return ;
}

int main() {
    int i, j;
    int TF[FILE_SIZE][DICT_SIZE], IDF[DICT_SIZE];
    FILE *fp;
    struct tree_node *root;

    // read the tree from file
    fp = fopen("tree.txt", "r");
    readTree(fp, root);
    fclose(fp);

    // search

    return 0;
}
