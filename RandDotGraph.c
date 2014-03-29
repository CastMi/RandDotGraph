/*
 * Copyright (C) 2013-2014 Michele Castellana <blacklion727[at]gmail[dot]com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

typedef enum { false, true } bool;
#define FILENAME "RandomGraph.txt"

/*
 * return a number i where i is min<=i<max
 */
double randRange(const double min, const double max){
#ifdef DEBUG
        assert(min <= max);
#endif
        return rand() * (max - min) / RAND_MAX + min;
}

int numDigit(const int num){
        if(num < 0)
                return numDigit(-num);
        if(num < 10)
                return 1;
        return 1 + numDigit(num / 10);
}

/*
 *
 */
void writeFile(const char *arg, const char *fileName) {
        if(arg == NULL)
                return;
        FILE *fp;
        fp = (fopen(fileName, "a+"));
        if (fp) {
                fwrite(arg, sizeof(char), strlen(arg), fp);
        } else {
                printf("Can't write in the file %s!", arg);
        }
        fclose(fp);
}

/*
 *
 */
void writeFileNewLine(const char *arg, const char *fileName) {
        if(arg == NULL)
                return;
        // add 2 more spaces for \n and terminator
        char *tmp = malloc(sizeof(char) * (strlen(arg) + 2));
#ifdef DEBUG
        assert(tmp != NULL);
#endif
        strcpy(tmp, arg);
        strcat(tmp,"\n");
        writeFile(tmp, fileName);
        // cleanup
        free(tmp);
}

/*
 *
 */
void writeFileSemicolon(char *arg, const char *fileName) {
        if(arg == NULL)
                return;
        // add 2 more spaces for ; and terminator
        char *tmp = malloc(sizeof(char) * (strlen(arg) + 2));
#ifdef DEBUG
        assert(tmp != NULL);
#endif
        strcpy(tmp, arg);
        strcat(tmp,";");
        writeFileNewLine(tmp, fileName);
        // cleanup
        free(tmp);
}

/*
 * clean file, if found
 */
void clean(const char *fileName) {
        FILE *fp;
        fp = fopen(fileName, "w");
        if (fp)
                fclose(fp);
}

/*
 *
 */
void writeDotFile(bool **arg, const int n, const char *fileName) {
        int i,j;
#ifdef DEBUG
        assert(arg != NULL);
#endif

        clean(FILENAME);
        char *toWrite;
        writeFileNewLine("digraph G {", fileName);
        for(i = 0; i < n; i++){
                toWrite = malloc(sizeof (int) * numDigit(i) + sizeof(char));
#ifdef DEBUG
                assert(toWrite != NULL);
#endif
                sprintf(toWrite,"%d",i+1);
                writeFileSemicolon(toWrite, fileName);
                free (toWrite);
                for(j = 0; j < n; j++) {
                        if(arg[i][j] == true){
                                toWrite = malloc(sizeof(int) * (numDigit(i) + numDigit(j)) + sizeof(char) * (strlen("->") + 1));
#ifdef DEBUG
                                assert(toWrite != NULL);
#endif
                                sprintf(toWrite,"%d->%d",i+1,j);
                                writeFileSemicolon(toWrite, fileName);
                                // cleanup
                                free (toWrite);
                        }
                }
        }
        writeFile("}", fileName);
}

void makegraph(const int vertices, int edges) {
        // adjacency matrix
        bool **adj = calloc(vertices, sizeof(*adj));
#ifdef DEBUG
        assert(adj != NULL);
#endif
        int temp1, temp2;
        int i,j;

        for(i = 0; i < vertices; i++){
                adj[i] = calloc(vertices, sizeof(*adj[i]));
#ifdef DEBUG
                assert(adj[i] != NULL);
#endif
        }

srand(time(NULL));

while(edges > 0){
        temp1 = randRange(0, vertices);
        temp2 = randRange(0, vertices);
        if(adj[temp1][temp2] == false){
#ifdef DEBUG
#if DEBUG > 2
                fprintf(stderr,"(%d,%d)\n",temp1,temp2);
#endif
#endif
                adj[temp1][temp2] = true;
                edges--;
        }
}

writeDotFile(adj, vertices, FILENAME);
free(adj);
}

int filterInput(char *toCheck) {
        const long int temp = strtol(toCheck, (char **)NULL, 10);
        if(temp > INT_MAX)
                return INT_MAX;
        else if(temp < 0)
                return 0;
        return temp;
}

int main(int argc, char **argv) {
        int vertices;
        int edges;
        long int temp;

        if (argc < 2) {
                fprintf(stderr,"Missing parameters\n");
                exit(EXIT_FAILURE);
        }

#ifdef DEBUG
        assert(argc >= 2 && argc <= 3);
#endif

        vertices = filterInput(argv[1]);
        edges = (argc < 3) ? 0 : filterInput(argv[2]);
        const double maxNumEdges = pow(vertices,2);
        if (edges > maxNumEdges) {
                edges = maxNumEdges;
        }

        makegraph(vertices,edges);
        exit(EXIT_SUCCESS);
}
