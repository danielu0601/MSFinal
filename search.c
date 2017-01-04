#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define FILE_SIZE 20
#define DICT_SIZE 20

/***
 * This code read the tree from file and do search
 */

// struct of node
struct tree_node {
    int ID; // node ID
    double D[DICT_SIZE]; // index data
    struct tree_node *Pl; // pointer to left node
    struct tree_node *Pr; // pointer to right node
    int FID; // pointer to file, use file's ID here
};

// struct of queue
struct tree_node queue[FILE_SIZE*2];
int front = 0;
int rear = -1;
int itemCount = 0;
struct tree_node *insert(struct tree_node data) {
    if( itemCount != FILE_SIZE*2 ) {
        if( rear == FILE_SIZE*2-1 )
            rear = -1;
        queue[++rear] = data;
        itemCount++;
    }
    return &queue[rear];
}
struct tree_node *removeData() {
    struct tree_node *data = &queue[front++];
    if( front == FILE_SIZE*2 )
        front = 0;
    itemCount--;
    return data;
}

// read tree from file
struct tree_node *file2tree( FILE *fp ) {
    if( feof(fp) != 0 ) return NULL;
    int i, l, r;
    struct tree_node tn;
    // ID 
    fscanf(fp, "%d ", &tn.ID);
    // D
    for( i = 0; i < DICT_SIZE; i++ )
        fscanf(fp, "%lf ", &tn.D[i]);
    // pointer
    fscanf(fp, "%d %d ", &l, &r);
    // FID
    fscanf(fp, "%d ", &tn.FID);
    // recursive call
    tn.Pl = file2tree( fp );
    tn.Pr = file2tree( fp );
    // check left and right child's id
    if( (tn.Pl != NULL && l != tn.Pl->ID)
            || (tn.Pr != NULL && r != tn.Pr->ID ) ) {
        printf("Error at read File%03d from file\n", tn.ID);
    }
    return insert(tn);
}

int main( void ) {
    int i, j;
    double TF[FILE_SIZE][DICT_SIZE], IDF[DICT_SIZE];
    FILE *fp;
    struct tree_node *root;

    // read tree from file
    fp = fopen("tree.txt", "r");
    root = file2tree(fp);
    fclose(fp);

    // read IDF from file
    fp = fopen("IDF.txt", "r");
    for( i = 0; i < DICT_SIZE; i++ ) {
        fscanf(fp, "%lf ", &IDF[i]);
    }
    fclose(fp);
    puts("Finish reading from file.");

    // do search
    while( 1 ) {
        int wordindex = 0;
        char req[10];
        // read search request
        scanf("%s", req);
        // check req format
        for( i = 0; i < strlen(req); i++ ) {
            if( !islower(req[i]) ) {
                wordindex += DICT_SIZE;
                break;
            }
            wordindex *= 26;
            wordindex += req[i] - 'a';
        }
        printf("%d\n", wordindex);
        if( wordindex >= DICT_SIZE ) {
            puts("Input format Error");
            break;
        }
        // do something
        
    }

    return 0;
}
