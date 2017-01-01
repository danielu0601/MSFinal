#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILE_SIZE 20
#define DICT_SIZE 20

struct tree_node {
    int ID; // node ID
    double D[DICT_SIZE]; // index data
    struct tree_node *Pl; // pointer to left node
    struct tree_node *Pr; // pointer to right node
    int FID; // pointer to file, use file's ID here
};

int main() {
    int i, j;
    int tmp1;
    char tmp2[10];
    int TF[FILE_SIZE][DICT_SIZE], IDF[DICT_SIZE];
    FILE *fp;
    struct tree_node root;

    // for each file
    for( i = 0; i < FILE_SIZE; i++ ) {
        //initial file name
        char filename[] = "doc/FILE001.txt";
        sprintf(filename, "doc/FILE%03d.txt", i);
        fp = fopen(filename, "w");

        // for each keyword in file
        for( j = 0; j < DICT_SIZE; j++ ) {
            // read data to array and count IDF
            fscanf(fp, "%s %d", tmp2, &tmp1);
            TF[i][j] = tmp1;
            if( TF[i][j] > 0 ) {
                IDF[j];
            }
        }

        // close file
        fclose(fp);
    }

    // make the tree
    for( i = 0; i < FILE_SIZE; i++ ) {
        
    }

    // search

    return 0;
}
