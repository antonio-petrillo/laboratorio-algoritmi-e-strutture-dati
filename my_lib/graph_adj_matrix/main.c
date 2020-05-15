#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

int main(int argc, char** argv){
    FILE* fp = fopen(argv[1], "r");
    graph_t g = load_graph_from_file(fp);
    fclose(fp);
    print_graph(g);
    drop_graph(g);
    return 0;
}