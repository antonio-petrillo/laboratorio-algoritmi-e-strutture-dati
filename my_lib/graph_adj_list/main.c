#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

#define DEFAULT_SIZE 8

void menu();
int choice();
unsigned int take_vertex(char* str);
int take_weight();

int main(int argc, char** argv){
   	graph_t g = NULL;
	if(argc < 2){
		g = make_empty_graph(DEFAULT_SIZE);
	}else{
		FILE* fp = fopen(argv[1], "r");
		assert(fp != NULL);
		g = load_graph_from_file(fp);
		fclose(fp);
	}
    graph_t gt = NULL;
    int i=1;
    while(i){
        menu();
        switch (choice()){
        case 1:
            add_edge(g, take_vertex("src"), take_vertex("dest"), take_weight());
            break;
        case 2:
            remove_edge(g, take_vertex("src"), take_vertex("dest"));
            break;
        case 3:
            print_graph(g);
            break;
        case 4:
            gt = transpose(g);
            printf("print of transposed graph\n");
            print_graph(gt);
            drop_graph(gt);
            break;
        case 5:
            bfs(g, take_vertex("starting point"), take_vertex("end_point"));
            break;
        case 6:
            dijkstra(g, take_vertex("starting point"), take_vertex("end_point"));
            break;
        case 7:
            dfs(g);
            break;
        case 8:
            drop_graph_stack(ts(g));
            break;
        case 9:
            scc(g);
            break;
        case 10:
            drop_graph(g);
            i = 0;
            break;
        default:
            break;
        }
    }
    return 0;
}

void menu(){
    printf("1) add edge\n2) remove edge\n3) print graph\n");
    printf("4) make transpose & print it\n5) bfs\n");
    printf("6) dijkstra\n7) dfs\n8) topological sort\n9) strongly connected components\n");
    printf("10) drop & end\nAny other input will be ignored\n");
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
