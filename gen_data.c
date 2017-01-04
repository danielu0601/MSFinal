#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define FILE_SIZE 20
#define DICT_SIZE 20

/***
 * This code generate the data used in search
 */

int main() {
    int i, j;
    FILE *fp;
    struct stat st = {0};

    // initial the random seed
    srand(time(NULL));
    // if no dir "doc", creat it
    if (stat("./doc", &st) == -1) {
        mkdir("./doc", 0700);
    }

    // for each file
    for( i = 0; i < FILE_SIZE; i++ ) {
        //initial file name
        char filename[] = "doc/FILE001.txt";
        sprintf(filename, "doc/FILE%03d.txt", i);
        fp = fopen(filename, "w");

        // for each keyword in file
        for( j = 0; j < DICT_SIZE; j++ ) {
            // initial keyword name
            char word[2];
            word[0] = 'a' + j / 26;
            word[1] = 'a' + j % 26;

            // generate keyword size, half set to 0
            int a = rand()%(DICT_SIZE*2) - DICT_SIZE;
            if( a < 0 ) a = 0;
            fprintf(fp, "%s %03d\n", word, a);
        }

        // close file
        fclose(fp);
    }

    return 0;
}