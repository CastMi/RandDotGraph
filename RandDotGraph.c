/*
 * This file is part of RandDotGraph.
 * 
 * RandDotGraph, to generate random dot graphs easily.
 * Copyright (C) 2013-2014 Michele Castellana <blacklion727@gmail.com>
 * 
 * RandDotGraph is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * RandDotGraph is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with RandDotGraph.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * @file RandDotGraph.c
 * @brief Generate random directed dot graphs easily.
 * 
 * @author Michele Castellana
 * @bug No known bugs.
 */

#define FILENAME "RandomGraph.txt"
#define ERRORMESSAGEBUFFER 100

#include "RandDotGraph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <getopt.h>
#include <ctype.h>
#ifdef DEBUG
#include <assert.h>
#endif

double randRange(const double min, const double max) {
#ifdef DEBUG
        assert(min <= max);
#endif
        if(min > max)
                return randRange(max, min);
        return rand() * (max - min) / RAND_MAX + min;
}

int numDigit(const int num) {
        if(num < 0)
                return numDigit(-num);
        if(num < 10)
                return 1;
        return 1 + numDigit(num / 10);
}

/**
 * @brief Append the string arg to the file named as fileName.
 * @param[in] arg The string.
 * @param[in] fileName The name of the file to open.
 * @return False if something wrong happened.
 *         True otherwise.
 */
static bool writeFile(const char *restrict const arg,
                      FILE * const fileName) {
#ifdef DEBUG
        assert(arg && fileName);
#endif
        if(!arg || !fileName)
                return false;
        fwrite(arg, sizeof(char), strlen(arg), fileName);
        return true;
}

/**
 * @brief Append a "\n" to the string arg.
 * @param[in] arg The string.
 * @param[in] fileName The name of the file to open.
 * @return False if something wrong happened.
 *         True otherwise.
 */
static bool writeFileNewLine(const char *restrict const arg,
                             FILE * const fileName) {
#ifdef DEBUG
        assert(arg && fileName);
#endif
        if(!arg || !fileName)
                return false;
        bool returnValue;
        char *restrict tmp;
        // add 2 more spaces for \n and the null terminator
        const size_t size = strlen(arg) + 2;
        errno = 0;
        tmp = (char *)malloc(size * sizeof(*tmp));
#ifdef DEBUG
        assert(tmp);
#endif
        if(checkErrors())
                return false;
        // - sizeof(char) to be sure it won't copy a random char
        memcpy(tmp, arg, size - sizeof(char));
        // + 1 to be sure that tmp will be null terminated
        strncat(tmp, "\n", size - sizeof(char) * (strlen(arg) + 1));

        returnValue = writeFile(tmp, fileName);
        // cleanup
        free(tmp);
        return returnValue;
}

/**
 * @brief Append a ";" to the string arg.
 * @param[in] arg The string.
 * @param[in] fileName The name of the file to open.
 * @return False if something wrong happened.
 *         True otherwise.
 */
static bool writeFileSemicolon(const char *restrict const arg,
                               FILE * const fileName) {
#ifdef DEBUG
        assert(arg && fileName);
#endif
        if(!arg || !fileName)
                return false;
        bool returnValue;
        char *restrict tmp;
        // add 2 more spaces for ; and the null terminator
        const size_t size = strlen(arg) + 2;
        errno = 0;
        tmp = (char *)malloc(size * sizeof(*tmp));
#ifdef DEBUG
        assert(tmp);
#endif
        if(checkErrors())
                return false;
        // - sizeof(char) to be sure it won't copy a random char
        memcpy(tmp, arg, size - sizeof(char));
        // + 1 to be sure that tmp will be null terminated
        strncat(tmp, ";", size - sizeof(char) * (strlen(arg) + 1));

        returnValue = writeFileNewLine(tmp, fileName);
        // cleanup
        free(tmp);
        return returnValue;
}

/**
 * @brief Clean file, if found.
 * @param[in] fileName The name of the file to clean.
 * @return Void.
 */
static void clean(const char *restrict const fileName) {
        FILE *fp;
        fp = fopen(fileName, "w");
        if(fp)
                fclose(fp);
}

static FILE * openFile(const char *restrict const fileName) {
        FILE * fp = fopen(fileName, "a+");
        if(fp) {
                return fp;
        } else
                return NULL;
}

bool writeDotFile(bool *const restrict *const restrict arg, const int n,
                  const char *restrict const fileName, const graph_prop gp) {
        int row, col;
        FILE *fp;
        char *restrict toWrite;
        size_t size;
        const char *restrict typeOfArc;

#ifdef DEBUG
        assert(arg && fileName && n >= 0);
#endif
        if(!arg || !fileName || n < 0) {
                errno = EINVAL;
                return false;
        }

        clean(fileName);
        errno = 0;
        fp = openFile(fileName);
        if(checkErrors())
                return false;
        writeFileNewLine("digraph G {", fp);
        size = 2 * numDigit(n) + 3;
        toWrite = (char *) malloc(size * sizeof(*toWrite));
#ifdef DEBUG
        assert(toWrite);
#endif
        if(gp & UNDIRECTED)
                typeOfArc = "--";
        else
                typeOfArc = "->";

        for(row = 0; row < n; row++) {
                snprintf(toWrite, size, "%d", row+1);
                writeFileSemicolon(toWrite, fp);
                // Check the lower triangular matrix
                for(col = 0; col <= row; col++) {
                        if(arg[row][col] == true) {
                                snprintf(toWrite, size, "%d%s%d",row+1,
                                         typeOfArc, col+1);
                                writeFileSemicolon(toWrite, fp);
                        }
                }
                // If it's a directed graph, check the rest of the columns
                // of the row.
                if(!(gp & UNDIRECTED))
                        for(; col < n; col++) {
                                if(arg[row][col] == true) {
                                        snprintf(toWrite, size, "%d%s%d", row+1,
                                                 typeOfArc, col+1);
                                        writeFileSemicolon(toWrite, fp);
                                }
                        }
        }
        writeFile("}", fp);
        fclose(fp);
        // cleanup
        free(toWrite);
        return true;
}

bool checkErrors(void) {
        if(errno != 0) {
                // used to restore the precall errno number
                const int oldErrno = errno;
                size_t size = ERRORMESSAGEBUFFER;
                char *buffer = (char *) malloc(size * sizeof(*buffer));
#ifdef DEBUG
                assert(buffer);
#endif
                if(!buffer) {
                        fprintf(stderr, "Something wrong happened but there is\
not enough memory to store the error message");
                } else {
                	/*
                	 * From string.h:
                	 * Reentrant version of `strerror'.
                         * There are 2 flavors of `strerror_r', GNU which
                         * returns the string and may or may not use the
                         * supplied temporary buffer and POSIX one which fills
                         * the string into the buffer. To use the POSIX
                         * version, -D_XOPEN_SOURCE=600 or
                         * -D_POSIX_C_SOURCE=200112L without -D_GNU_SOURCE is
                         * needed, otherwise the GNU version is preferred.
                         */
                        const int success = strerror_r(errno, buffer, size);
                        if(success != 0) {
                                fprintf(stderr, "Something wrong happened but \
a larger buffer for the error message is needed");
                        }
                        fprintf(stderr, "%s\n", buffer);
                        free(buffer);
                }
                // restore the precall errno number
                errno = oldErrno;
                return true;
        }
        return false;
}

/**
 * @brief It initializes the random number generator reading from urandom.
 * @return Void.
 */
static void randInitializer(void) {
        FILE *f;
        size_t bytes_read = 0;
        f = fopen("/dev/urandom", "r");
        if(f) {
                int randValue;
                bytes_read = fread(&randValue, sizeof(randValue), 1, f);
                fclose(f);
                if(bytes_read)
                	srand(randValue);
                else
                        srand(time(NULL));
        } else
                srand(time(NULL));
}

bool makeGraph(const int vertices, int edges, const graph_prop gp) {
        int row, col;
        
        // check for graph validity
#ifdef DEBUG
        assert(vertices >= 0 && edges >= 0);
        // the maximum number of edges is based on the property of the graph
        if(gp & UNDIRECTED) {
                if(gp & NOSELFLOOP)
                        assert(edges <= vertices * (vertices - 1) / 2);
                else
                        assert(edges <= vertices * (vertices + 1) / 2);
        } else
                assert(edges <= pow(vertices, 2));
#endif
        if(vertices < 0 || edges < 0 || edges > pow(vertices, 2)) {
                errno = EINVAL;
                return false;
        }
        /*
         * if UNDIRECTED and self loops are not allowed, then
         * the maximum number of edges is vertices*(vertices-1)/2
         * if UNDIRECTED and self loops are allowed, then
         * the maximum number of edges is vertices*(vertices+1)/2
         */
        if((gp & UNDIRECTED) &&
                   (((gp & NOSELFLOOP) &&
                     edges > vertices * (vertices - 1) / 2) ||
                    (!(gp & NOSELFLOOP) &&
                      edges > vertices * (vertices + 1) / 2))) {
                        errno = EINVAL;
                        return false;
        }
        // from now on, inputs are good
        errno = 0;
        // adjacency matrix
        bool **adj = (bool **) calloc(vertices, sizeof(*adj));
#ifdef DEBUG
        assert((vertices == 0 && !adj) || (vertices != 0 && adj));
#endif
        if(checkErrors())
                return false;

        for(row = 0; row < vertices; row++) {
                adj[row] = (bool *) calloc(vertices, sizeof(*adj[row]));
#ifdef DEBUG
                assert(adj[row]);
#endif
                if(checkErrors())
                        return false;
        }

        randInitializer();
        while(edges > 0) {
                row = randRange(0, vertices);
                col = randRange(0, vertices);
                /* 
                 * if NOSELFLOOP is set, row != col is mandatory.
                 * Therefore either NOSELFLOOP is not set or
                 * row != col
                 */
                if(adj[row][col] == false &&
                  (!(gp & NOSELFLOOP) || row != col)) {
#ifdef DEBUG
#if DEBUG > 2
                        fprintf(stderr, "(%d,%d)\n", row, col);
#endif
#endif
                        adj[row][col] = true;
                        if(gp & UNDIRECTED)
                                adj[col][row] = true;
                        edges--;
                }
        }
        writeDotFile(adj, vertices, FILENAME, gp);
        for(row = 0; row < vertices; row++) {
                free(adj[row]);
        }
        free(adj);
        return true;
}

/**
 * @brief It checks the bounds for the user input.
 * @param[in] toCheck The user input.
 * @return An integer i in the range 0<=i<=INT_MAX.
 */
static int filterInput(const char *restrict const toCheck) {
        long int temp;
        if(!toCheck)
                return 0;
        temp = strtol(toCheck, (char **)NULL, 10);
        if(temp > INT_MAX)
                return INT_MAX;
        else if(temp < 0)
                return 0;
        return temp;
}

/*
int exitWithErrMsg(const char *restrict errMsg, ...) {
        va_list arguments;
        va_start(arguments, errMsg);
        
        if(errMsg && errMsg != '\0')
                fprintf(stderr, "%s\n", errMsg);
        va_end(arguments);
        exit(EXIT_FAILURE);
}
*/

int main(int argc, char **argv) {
        int vertices = 0;
        int edges = 0;
        int c;
        graph_prop property = NOCONSTRAINT;
        static struct option long_options[] = {
                {"type",          required_argument, NULL,  't' },
                {"noselfloop",    no_argument,       NULL,  's' },
                {"vertices",      required_argument, NULL,  'v' },
                {"edges",         required_argument, NULL,  'e' },
                {0,               0,                 NULL,  0   }
        };
        
#ifdef DEBUG
        assert(argc >= 3);
#endif
        if(argc < 3) {
                fprintf(stderr, "Missing parameters\n");
                exit(EXIT_FAILURE);
        }

        while((c = getopt_long(argc, argv, "t:sv:e:", long_options,
                                NULL))
                != -1)
                switch(c) {
                        case 't':
                                if(optarg && !strncmp(optarg, "undirected",
                                                      sizeof(char)))
                                        property |= UNDIRECTED;
                                else if(optarg && strncmp(optarg, "directed",
                                                      sizeof(char))) {
                                        fprintf(stderr, "Unknown graph \
type\n");
                                        exit(EXIT_FAILURE);
                                }
#ifdef DEBUG
                                if(optarg)
                                        fprintf (stderr, "optarg variable: \
%s\n", optarg);
#endif
                                break;
                        case 's':
                                property |= NOSELFLOOP;
                                break;
                        case 'v':
                                // vertices
                                vertices = filterInput(optarg);
                                break;
                        case 'e':
                                // edges
                                edges = filterInput(optarg);
                                break;
                        case '?':
                        default :
                                // unknown option
                                if (isprint(optopt))
                                        fprintf(stderr, "Unknown option \
'-%c'\n", optopt);
                                else
                                        fprintf(stderr, "Unknown option \
character '\\x%x'\n", optopt);
                                exit(EXIT_FAILURE);
                }

        // trivial checks before starting the computation
        if(vertices < 0 || edges < 0) {
                fprintf(stderr, "Wrong parameters\n");
                exit(EXIT_FAILURE);
        }
        /*
         * if UNDIRECTED and self loops are not allowed, then
         * the maximum number of edges is vertices*(vertices-1)/2
         * if UNDIRECTED and self loops are allowed, then
         * the maximum number of edges is vertices*(vertices+1)/2
         */
        if((property & UNDIRECTED) &&
                   (((property & NOSELFLOOP) &&
                     edges > vertices * (vertices - 1) / 2) ||
                    (!(property & NOSELFLOOP) &&
                      edges > vertices * (vertices + 1) / 2))) {
                        fprintf(stderr, "Wrong parameters\n");
                        exit(EXIT_FAILURE);
        }
        /*
         * if DIRECTED and self loops are not allowed, then
         * the maximum number of edges is vertices*(vertices-1)
         * if DIRECTED and self loops are allowed, then
         * the maximum number of edges is vertices^2
         */
        if(!(property & UNDIRECTED) &&
                   ((((property & NOSELFLOOP) &&
                     edges > vertices * (vertices - 1)) ||
                    (!(property & NOSELFLOOP) &&
                      edges > pow(vertices, 2))))) {
                        fprintf(stderr, "Wrong parameters\n");
                        exit(EXIT_FAILURE);
        }

        makeGraph(vertices, edges, property);
        exit(EXIT_SUCCESS);
}
