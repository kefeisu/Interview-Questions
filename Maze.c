//
//  Maze.c
//
//
//  Created by KeFei on 2017-04-09.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* Maze structure of bools: 1 indicates the block is a path
 *                          0 indicates the block is a wall
 *
 * example of a maze that is 3x3:
 * [1][1][1]
 * [0][1][0]
 * [0][1][1]
 *
 * we want to determine if there is a valid path
 * from index [0,0] to [x,y]
 */
struct maze {
    
    int x; // x-dimention of the maze
    int y; // y-dimention of the maze
    bool **array; //  2D array of bools
    
};

/* creates a random maze for us to search through */
struct maze * mazeCreate(int x, int y) {
    struct maze *m = malloc(sizeof(struct maze));
    m->x = x;
    m->y = y;
    m->array = malloc(y*sizeof(int*));
    
    for (int i = 0; i < y; ++i) {
        m->array[i] = malloc(x*sizeof(int));
    }
    
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++ j) {
            /* generate paths at a 67% rate */
            m->array[i][j] = ((random()%100) <= 67 );
        }
    }
    m->array[0][0] = true;
    m->array[x-1][y-1] = true;
    return m;
}


/* destroys a maze and free's it's memory */
void mazeDestroy(struct maze *m) {
    for (int i = 0; i < m->x; ++i){
        free(m->array[i]);
    }
    free(m->array);
    free(m);
    
}

/* print's out the maze */
void printMaze(struct maze *m) {
    
    for (int i = 0; i < m->x; ++i) {
        for (int j = 0; j < m->y-1; ++j) {
            printf("[%d]", m->array[i][j]);
        }
        printf("[%d]\n", m->array[i][m->x - 1]);
    }
}

/* a helper function to check if m[x][y] is valid */
bool isValid(struct maze *m, int xnode, int ynode) {
    bool a = xnode < m->x && 0 <= xnode;
    bool b = ynode < m->y && 0 <= ynode;
    if (!(a && b)){ return false; }
    else { return m->array[xnode][ynode]; }
}

/* DFS graph traversal */
bool DFS(struct maze *m, bool *visited, int xnode, int ynode) {
    
    bool result;
    
    /* already visited */
    int index = xnode*m->x + ynode;
    if(!isValid(m,xnode,ynode) || visited[index]) { return false; }
    else { visited[index] = true; }
    /* last node */
    if(xnode == m->x - 1 && ynode == m->y - 1) {
        printf("[%d,%d] ", ynode, xnode);
        return true;
    }
    
    /* down */
    result = DFS(m,visited,xnode,ynode+1);
    if (result) {
        printf("[%d,%d] ", ynode, xnode);
        return result;
    }
    /* right */
    result = DFS(m,visited,xnode+1,ynode);
    if (result) {
        printf("[%d,%d] ", ynode, xnode);
        return result;
    }
    /* up */
    result = DFS(m,visited,xnode,ynode-1);
    if (result) {
        printf("[%d,%d] ", ynode, xnode);
        return result;
    }
    /* left */
    result = DFS(m,visited,xnode-1,ynode);
    if (result) {
        printf("[%d,%d] ", ynode, xnode);
        return result;
    }

    
    return false;
}


/* prints a path from index 0,0 to x,y of a maze if it exists */
void printPath(struct maze *m) {
    int nodeAmount = m->x * m->y;
    bool *visited = malloc(nodeAmount*sizeof(int));
    for (int i = 0; i < nodeAmount; ++i) {
        visited[i] = false;
    }
    if(!DFS(m,visited,0,0)) { printf("no path exists\n"); }
    free(visited);
    
}

int main(void) {
    srand(time(NULL));
    struct maze *m = mazeCreate(4,5);
    printMaze(m);
    printPath(m);
    mazeDestroy(m);
    return 0;
}
