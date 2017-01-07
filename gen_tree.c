#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

#define FILE_SIZE 20
#define DICT_SIZE 20

/***
 * This code generate the tree base on the data generate by gen_data
 * and store the tree to file.
 */

// struct of node
struct tree_node {
    int ID; // node ID
    double D[DICT_SIZE]; // index data
    struct tree_node *Pl; // pointer to left node
    struct tree_node *Pr; // pointer to right node
    int FID; // pointer to file, use file's ID here
};

// max function
double max( double a, double b ){ return (a>b)?a:b; }

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

// write tree to file
void tree2file( FILE *fp, struct tree_node *root ) {
    if( root == NULL ) return ;
    int i;
    // ID 
    fprintf(fp, "%d ", root->ID);
    // D
    for( i = 0; i < DICT_SIZE; i++ )
        fprintf(fp, "%lf ", root->D[i]);
    // pointer
    if( root->Pl == NULL )
        fprintf(fp, "-1 ");
    else
        fprintf(fp, "%d ", root->Pl->ID);
    if( root->Pr == NULL )
        fprintf(fp, "-1 ");
    else
        fprintf(fp, "%d ", root->Pr->ID);
    // FID
    fprintf(fp, "%d\n", root->FID);
    // recursive call
    tree2file(fp, root->Pl);
    tree2file(fp, root->Pr);
    return ;
}

int main( void ) {
    int i, j, tmp1, ID = 1;
    char tmp2[10];
    int TFint[FILE_SIZE][DICT_SIZE], IDFint[DICT_SIZE];
    double TF[FILE_SIZE][DICT_SIZE], IDF[DICT_SIZE];
    FILE *fp;
    struct tree_node *root;

    // for each file
    for( i = 0; i < FILE_SIZE; i++ ) {
        //initial file name
        char filename[] = "doc/FILE001.txt";
        sprintf(filename, "doc/FILE%03d.txt", i);
        fp = fopen(filename, "r");

        // for each keyword in file
        for( j = 0; j < DICT_SIZE; j++ ) {
            // read data to array and count IDF
            fscanf(fp, "%s %d", tmp2, &tmp1);
            TFint[i][j] = tmp1;
            if( TFint[i][j] > 0 ) {
                IDFint[j]++;
            }
        }

        // close file
        fclose(fp);
    }

    // calculate normalized TF and IDF
    for( i = 0; i < FILE_SIZE; i++ ) {
        for( j = 0; j < DICT_SIZE; j++ ) {
            if( TFint[i][j] == 0 )
                TF[i][j] = 0;
            else
                TF[i][j] = 1 + log( TFint[i][j] );
        }
    }
    for( i = 0; i < DICT_SIZE; i++ ) {
        IDF[i] = log( 1.0 + (double)FILE_SIZE/IDFint[i] );
    }

    // build nodes and put into queue
    for( i = 0; i < FILE_SIZE; i++ ) {
        struct tree_node tp;
        double TFsum = 0;
        for( j = 0; j < DICT_SIZE; j++ ) {
            TFsum += TF[i][j] * TF[i][j];
        }
        if( TFsum == 0 ) {
            printf("Error : There is no keyword in FILE%03d\n", i);
            return -1;
        }

        tp.ID = ID; ID++;
        for( j = 0; j < DICT_SIZE; j++ ) {
            tp.D[j] = TF[i][j]/TFsum;
        }
        tp.Pl = NULL;
        tp.Pr = NULL;
        tp.FID = i;

        insert( tp );    
    }

    // build the tree
    while( itemCount > 1 ) {
        struct tree_node *tp1, *tp2;
        struct tree_node tp3;
        tp1 = removeData();
        tp2 = removeData();
        tp3.ID = ID; ID++;
        for( i = 0; i < DICT_SIZE; i++ ) {
            tp3.D[i] = max( tp1->D[i], tp2->D[i] );
        }
        tp3.Pl = tp1;
        tp3.Pr = tp2;
        tp3.FID = -1;

        insert( tp3 );
    }
    root = removeData();

    // write tree to file
    fp = fopen("tree.txt", "w");
    tree2file(fp, root);
    fclose(fp);

    // write IDF to file for trapdoor
    fp = fopen("IDF.txt", "w");
    for( i = 0; i < DICT_SIZE; i++ ) {
        fprintf(fp, "%lf ", IDF[i]);
    }
    fclose(fp);

    return 0;
}
