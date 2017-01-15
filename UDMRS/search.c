#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include "define.h"

/***
 * This code read the tree from file and do search.
 */

double TF[FILE_SIZE][DICT_SIZE], IDF[DICT_SIZE];
double query[DICT_SIZE], RList[FILE_SIZE][2];

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

// read tree from file
Node *file2tree( FILE *fp ) {
    if( feof(fp) != 0 ) return NULL;
    int i, l, r;
    Node tn;
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
    if( l != -1 )
        tn.Pl = file2tree( fp );
    else
        tn.Pl = NULL;
    if( r != -1 )
        tn.Pr = file2tree( fp );
    else
        tn.Pr = NULL;
    // check left and right child's id
    if( (tn.Pl != NULL && l != tn.Pl->ID)
            || (tn.Pr != NULL && r != tn.Pr->ID ) ) {
        printf("Error at reading Node %3d from file\n", tn.ID);
    }
    return insert(&tn);
}

// search function
void search(Node *root, double RList[FILE_SIZE][2], int k) {
    int i;
    double result = 0.0;
    // do dot
    for (i = 0; i < DICT_SIZE; i++) {
        result += query[i] * root->D[i];
    }
    // divide by node type
    if( root->FID != -1 ) { // leaf node
        if( result > RList[k-1][1] ) {
            // put into RList
            RList[k-1][0] = root->FID;
            RList[k-1][1] = result;
            for( i = k-2; i >= 0; i-- ) {
                if( RList[i][1] < RList[i+1][1] ) {
                    double tmp;
                    tmp           = RList[i  ][0];
                    RList[i  ][0] = RList[i+1][0];
                    RList[i+1][0] = tmp;
                    tmp           = RList[i  ][1];
                    RList[i  ][1] = RList[i+1][1];
                    RList[i+1][1] = tmp;
                }
            }
        }
    } else { // internal node
        if( result > RList[k-1][1] ) {
            search(root->Pl, RList, k);
            search(root->Pr, RList, k);
        }
    }
    return ;
}

int main( void ) {
    int i, j, k, n, wordindex;
    double sum;
    char req[10];
    FILE *fp;
    Node *root;

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
    puts("\n\n*** Finish reading from file. ***\n\n");

    // do search
    while( 1 ) {
        memset(query, 0, sizeof(query));
        memset(RList, 0, sizeof(RList));
        puts("Usage : 'k-top' 'keyword number' 'keyword1' 'keyword2' ...");
        puts("Example :  5           3             aa         ac      ae");

        // read search request
        scanf("%d %d ", &k, &n);
        for( i = 0; i < n; i++ ) {
            scanf("%s", req);
            // check req format
            wordindex = 0;
            for( j = 0; j < strlen(req); j++ ) {
                if( !islower(req[j]) ) {
                    wordindex += DICT_SIZE;
                    break;
                }
                wordindex *= 26;
                wordindex += req[j] - 'a';
            }
            printf("\tInput %d = '%s'\tindex = %d\n", i, req, wordindex);
            if( wordindex >= DICT_SIZE ) {
                puts("Input format Error");
                break;
            }
            query[ wordindex ] = IDF[ wordindex ];
        }
        // normalize query vector
        sum = 0;
        for( i = 0; i < DICT_SIZE; i++ ) {
            sum += query[i] * query[i];
        }
        sum = sqrt( sum );
        for( i = 0; i < DICT_SIZE; i++ ) {
            query[i] /= sum;
        }
        // really do search
        search(root, RList, k);
        puts("\n\nResults = ");
        for( i = 0; i < k; i++ ) {
            if( RList[i][1] > 0 )
                printf("\tRank%3d = File%4d Score = %lf\n", i+1, (int)RList[i][0], RList[i][1]);
            else {
                puts("No more result");
                break;
            }
        }
        puts("\n\n\n\n");
    }

    return 0;
}
