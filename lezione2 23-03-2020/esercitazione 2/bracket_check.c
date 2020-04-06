#include <stdio.h>
#include <string.h>
#include "stack.h"

int bracket_check(char* string, unsigned int dim);
int bracket_check_rec(Stack s, char* string, unsigned int index);

int main(int argc, char** argv){
    char* string_cor = "{[()]}{}[]()";
    unsigned int dim1 = strlen(string_cor) + 1;
    char* string_uncor = "{[()]}{]}[]()";
    unsigned int dim2 = strlen(string_uncor) + 1;
    printf("stringa 1: %s\nE' bilanciata ? := %s\n", string_cor, (bracket_check(string_cor, dim1))? "true" : "false");
    printf("stringa 2: %s\nE' bilanciata ? := %s\n", string_uncor, (bracket_check(string_uncor, dim2))? "true" : "false");
    return 0; 
}

int bracket_check(char* string, unsigned int dim){
    Stack s;
    makestack(&s);
    int res = bracket_check_rec(s, string, 0);
    freestack(&s);
    return res;
}

int bracket_check_rec(Stack s, char* string, unsigned int index){
    if(string[index] == '\0') return is_empty(s); // se lo stack e' vuoto la stringa e'ben bilanciata
    else{
        int err, tmp;
        int select = string[index];
        switch(select){
            case '{':
                push(s, select, &err);
                return bracket_check_rec(s, string, index+1);
                break;
            case '[':
                push(s, select, &err);
                return bracket_check_rec(s, string, index+1);
                break;
            case '(':
                push(s, select, &err);
                return bracket_check_rec(s, string, index+1);
                break;
            case '}':
                tmp = pop(s, &err);
                if(tmp != '{') return 0;
                else return bracket_check_rec(s, string, index+1);
                break;
            case ']':
                tmp = pop(s, &err);
                if(tmp != '[') return 0;
                else return bracket_check_rec(s, string, index+1);
                break;
            case ')':
                tmp = pop(s, &err);
                if(tmp != '(') return 0;
                else return bracket_check_rec(s, string, index+1);
                break;
            default:// se c'e' un carattere che non e' una parentesi lo ignoro
                return bracket_check_rec(s, string, index+1);
                break;
        }
    }
}