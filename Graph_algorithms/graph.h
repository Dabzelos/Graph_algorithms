#pragma once



#include <iostream>
#include <time.h>
#include <math.h>
#include <string.h>

struct nodebt {
    int data;
    struct nodebt* left;
    struct nodebt* right;
};

struct nodebt* insert(struct nodebt* root, int data);
void traverse_inorder(struct nodebt* root, int* a, int* i);
int* tree_sort(int* a, int n);
struct node1
{
    int num; //numerator=числитель
    int den; //denominator=знаменатель
    struct node1* leftp; //left parent
    struct node1* rightp; //right parent
};
void PROGRAMM(struct node1* current);


//структура графа
typedef struct node {
    int val;
    struct node* next;
} node;
typedef struct list {
    node* head;
} list;
typedef struct graph {
    int count;
    list* adj_list;
} graph;




typedef struct variable {
    char name[3];
} variable;

typedef struct clause {
    variable* var1;
    variable* var2;
} clause;

typedef struct twosat {
    int num_vars;
    int num_clauses;
    clause* clauses;
} twosat;

//инициализация и простые действия над графом
graph* graph_init(int n);
void graph_print(graph* g);
void graph_free(graph* g);
void add_arc(graph* g, int a, int b);
void add_edge(graph* g, int a, int b);
void del_arc(graph* g, int a, int b);


//алгоритмы обхода и проверка на двудольность
int dfs(graph* g, int start, int* colours);
int bfs(graph* g, int start, int* colours);
int* is_bipartite(graph* g, int check_alg(graph*, int, int*));


//топологическая сортировка модификация DFS для топсорт, поиск компонент сильной связности, транспонирование графа
void dfs_for_topsort(graph* g, int start, int* visited, int num);
int* dfs_time(graph* g);
graph* graph_transposition(graph* g);
void dfs_scc(graph* g, int start, int colour, int* colours);
int* graph_scc(graph* g);

int* FPT_vertex_cover(graph* g, int k);
int* FPT_vertex_cover_2(graph* g, int k);
//2-SAT, структура для 2-SAT, 

twosat* get_2_sat_cnf_form(const char* bl_form);
void implication_graph(int* arr, twosat* two_sat, graph* g);
bool* result_twosat(int* comp, twosat* two_sat);