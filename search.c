#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILE_SIZE 20
#define DICT_SIZE 20

int main() {
    int i, j;
    int tmp1;
    char tmp2[10];
    char filedata[FILE_SIZE][DICT_SIZE];
    FILE *fp;

    // for each file
    for( i = 0; i < FILE_SIZE; i++ ) {
        //initial file name
        char filename[] = "doc/FILE001.txt";
        sprintf(filename, "doc/FILE%03d.txt", i);
        fp = fopen(filename, "w");

        // for each keyword in file
        for( j = 0; j < DICT_SIZE; j++ ) {
            // read the data to array
            fscanf("%s %d", tmp2, &tmp1);
            filedata[i][j] = tmp1;
        }

        // close file
        fclose(fp);
    }

    // analyse the data

    // make the tree

    // search

    return 0;
}
