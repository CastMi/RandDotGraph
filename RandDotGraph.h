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
 * @file RandDotGraph.h
 * @brief Generate random directed dot graphs easily.
 * 
 * @author Michele Castellana
 */

#ifndef RANDDOTGRAPH_H_
#define RANDDOTGRAPH_H_

// Graph properties
typedef unsigned short graph_prop;
// Flags
#define NOCONSTRAINT 0x00 // directed, with self loop
#define UNDIRECTED 0x01
#define NOSELFLOOP 0x02

#include <stdbool.h>

/**
 * @brief Returns a number i in the range min <= i < max.
 * @param[in] min The min of the range.
 * @param[in] max The max of the range.
 * @return A number i such that min <= i < max.
 */
double randRange(double min, double max);

/**
 * @brief Counts the number of digit of an integer.
 * @param[in] num The integer.
 * @return The number of digit.
 */
int numDigit(int num);

/**
 * @brief Uses the adjacency matrix to write the graph in dot format.
 * 
 * errno is set to EINVAL if n < 0.
 * errno is set to EINVAL if arg or fileName are NULL.
 * errno is only modified on failure.
 * 
 * @param[in] arg The adjacency matrix.
 * @param[in] n The dimension of the matrix.
 * @param[in] fileName The name of the file to use.
 * @param[in] gp The property that the resulting graph needs to satisfy.
 * @see <a href="http://linux.die.net/man/3/malloc">malloc</a> for further
 *      possible errors.
 * @return False if something bad happened.
 *         True otherwise.
 */
bool writeDotFile(bool *const restrict *restrict arg, int n,
      const char *restrict fileName, graph_prop gp);

/**
 * @brief Checks if an error occurred.
 * 
 * Check if the integer variable "errno" is different from 0.
 * If so, It tries to print a significant message.
 * Otherwise nothing is done.
 * The errno number won't be modified in any case.
 * 
 * @see <a href="http://linux.die.net/man/3/malloc">malloc</a> for further
 *      possible errors.
 * @see <a href="http://linux.die.net/man/3/strerror_r">strerror_r</a> for
 *      further possible errors.
 * @warning It assumes that errno had been set to 0!
 * @warning From string.h:
 *          Reentrant version of `strerror'.
 *          There are 2 flavors of `strerror_r', GNU which returns the string
 *          and may or may not use the supplied temporary buffer and POSIX one
 *          which fills the string into the buffer.
 *          To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
 *          without -D_GNU_SOURCE is needed, otherwise the GNU version is
 *          preferred.
 * @return True if errno is different from 0.
 *         False otherwise.
 */
bool checkErrors(void);

/**
 * @brief Allocates an adjacency matrix, fill it in and call the
 *        writeDotFile function.
 *
 * errno is set to EINVAL if vertices or edges are < 0.
 * errno is only modified on failure.
 *
 * @param[in] vertices The number of vertices.
 * @param[in] edges The number of edges.
 * @param[in] gp The property that the resulting graph needs to satisfy.
 * @see <a href="http://linux.die.net/man/3/calloc">calloc</a> for further
 *       possible errors.
 * @see writeDotFile function for further possible errors.
 * @return False if something bad happened.
 *         True otherwise.
 */
bool makeGraph(int vertices, int edges, graph_prop gp);

#endif
