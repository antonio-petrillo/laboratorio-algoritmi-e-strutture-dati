#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

#define DEFAULT_SIZE 10

void menu();
int choice();
unsigned int take_vertex(char* str);
int take_weight();

int main(int argc, char** argv){
    graph_t g = NULL, gt = NULL;  
    if(argc == 2){
        FILE* fp = fopen(argv[1], "r");
        g = load_graph_from_file(fp);
        fclose(fp);
    }
    else{
        g = make_empty_graph(DEFAULT_SIZE);
    }
    int i=1;
    while(i){
        menu();
        switch (choice()){
        case 1:
            add_edge(g, take_weight(), take_vertex("dest"), take_vertex("src"));
            break;
        case 2:
            remove_edge(g, take_vertex("dest"), take_vertex("src"));
            break;
        case 3:
            print_graph(g);
            break;
        case 4:
            print_full_graph_matrix(g);
            break;
        case 5:
            add_vertex(g);
            break;
        case 6:
            remove_vertex(g, take_vertex("vertex to remove"));
            break;
        case 7:
            gt = transpose(g);
            printf("print of transposed graph\n");
            print_graph(gt);
            drop_graph(gt);
            break;
        case 8:
            bfs(g, take_vertex("end_point"), take_vertex("starting point"));
            break;
        case 9:
            dijkstra(g, take_vertex("end_point"), take_vertex("starting point"));
            break;
        case 10:
            dfs(g);
            break;
        case 11:
            free(ts(g));
            break;
        case 12:
            scc(g);
            break;
        case 13:
            drop_graph(g);
            i = 0;
            break;
        default:
            break;
        }
        fflush(stdin);
    }
    return 0;
}

void menu(){
    printf("1) add edge\n2) remove edge\n3) print graph\n");
    printf("4) print full adj matrix\n5) add vertex\n6) remove vertex\n");
    printf("7) make transpose & print it\n8) bfs\n9) dijkstra\n10) dfs\n11) topological sort\n12) strongly connected components\n13) drop & end\nAny other input will be ignored\n");
    return;
}


int choice(){
    int ret;
    printf("choice: ");
    scanf("%d", &ret);
    return ret;
}

unsigned int take_vertex(char* str){
    unsigned int ret;
    printf("insert the %s: ", str);
    scanf("%u", &ret);
    return ret;
}

int take_weight(){
    int ret;
    printf("insert the weight: ");
    scanf("%d", &ret);
    return ret;
}