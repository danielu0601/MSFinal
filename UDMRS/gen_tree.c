#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include "define.h"

/***
 * This code generate the tree base on the data generate by gen_data
 * and store the tree to file.
 */

// File data tmp
double TF[FILE_SIZE][DICT_SIZE], IDF[DICT_SIZE];

// struct of queue
Node queue[FILE_SIZE*2];
int front = 0, rear = -1, itemCount = 0;
Node *insert(Node *data) {
    if( itemCount != FILE_SIZE*2 ) {
        if( rear == FILE_SIZE*2-1 )
            rear = -1;
        queue[++rear] = *data;
        itemCount++;
    }
    return &queue[rear];
}
Node *removeData() {
    Node *data = &queue[front++];
    if( front == FILE_SIZE*2 )
        front = 0;
    itemCount--;
    return data;
}

// write tree to file
void tree2file( FILE *fp, Node *root ) {
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
    char tmp2[8];
    FILE *fp;
    Node *root;

    // for each file
    for( i = 0; i < FILE_SIZE; i++ ) {
        //initial file name
        char filename[] = FILE_PATH;
        char *ptr = strstr(filename, "FILE");
        sprintf(ptr, "FILE%04d.txt", i+1);
        fp = fopen(filename, "r");

        // for each keyword in file
        for( j = 0; j < DICT_SIZE; j++ ) {
            // read data to array and count IDF
            fscanf(fp, "%s %d", tmp2, &tmp1);
            TF[i][j] = tmp1;
            if( TF[i][j] > 0 ) {
                IDF[j]++;
            }
        }

        // close file
        fclose(fp);
    }

    // calculate normalized TF and IDF
    for( i = 0; i < FILE_SIZE; i++ ) {
        for( j = 0; j < DICT_SIZE; j++ ) {
            if( TF[i][j] > 0 )
                TF[i][j] = 1 + log( TF[i][j] );
        }
    }
    for( i = 0; i < DICT_SIZE; i++ ) {
        IDF[i] = log( 1.0 + (double)FILE_SIZE/IDF[i] );
    }

    // build nodes and put into queue
    for( i = 0; i < FILE_SIZE; i++ ) {
        Node tp;
        double TFsum = 0;
        for( j = 0; j < DICT_SIZE; j++ )
            TFsum += TF[i][j] * TF[i][j];
        TFsum = sqrt(TFsum);
        if( TFsum == 0 ) {
            printf("Error : There is no keyword in FILE%04d\n", i);
            return -1;
        }

        tp.ID = ID;
        ID++;
        for( j = 0; j < DICT_SIZE; j++ ) {
            tp.D[j] = TF[i][j]/TFsum;
        }
        tp.Pl = NULL;
        tp.Pr = NULL;
        tp.FID = i+1;

        insert( &tp );
    }

    // build the tree
    while( itemCount > 1 ) {
        Node *tp1, *tp2;
        Node tp3;
        tp1 = removeData();
        tp2 = removeData();
        tp3.ID = ID;
        ID++;
        for( i = 0; i < DICT_SIZE; i++ ) {
            tp3.D[i] = max( tp1->D[i], tp2->D[i] );
        }
        tp3.Pl = tp1;
        tp3.Pr = tp2;
        tp3.FID = -1;

        insert( &tp3 );
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
