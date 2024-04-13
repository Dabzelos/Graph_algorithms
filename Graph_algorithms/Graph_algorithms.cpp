#include <math.h>
#include "cstring"
#include <string.h>
#include "graph.h"

using namespace std;

//
//void test_poly() 
//{
//    const char* polynom1 = "x^2+763x^3-2";
//    const char* polynom2 = "x^2+763x^3-2";
//
//    poly* test_poly1 = poly_get(polynom1);
//    poly_print(test_poly1);
//
//    poly* test_poly2 = poly_get(polynom2);
//    poly_print(test_poly2);
//
//    poly* test_poly3 = poly_add(test_poly1, test_poly2);
//    poly_print(test_poly3);
//    poly* test_poly4 = poly_mul(test_poly1, test_poly2);
//    poly_print(test_poly4);
//    poly_print(test_poly1);
//
//
//
//    poly_free(test_poly1);
//    poly_free(test_poly2);
//    poly_free(test_poly3);
//    poly_free(test_poly4);
//}
void test_Shtern()
{

    node1 rootL, rootR; //создаем корни

    rootL.num = 0;
    rootL.den = 1;
    rootR.num = 1;
    rootR.den = 0;

    rootL.leftp = NULL;
    rootL.rightp = NULL;
    rootR.leftp = NULL;
    rootR.rightp = NULL;

    node1 root;
    root.leftp = &rootL;
    root.rightp = &rootR;
    root.num = 1;
    root.den = 1;

    struct node1* current = (struct node1*)malloc(sizeof(struct node1));
    current = &root;

    PROGRAMM(current);
}

void test_graph()
{
    int n, r;
    cout << "Количество вершин:";
    cin >> n;
    struct graph* g;
    g = graph_init(n);
    int a, b;
    cout << "Количество ребер:";
    cin >> r;
    cout << "Между какими вершинами ребра:";
    for (int i = 0; i < r; i++) {
        cin >> a >> b;
        add_arc(g, a, b);
    }
    graph_print(g);

    cout << "del";
    cin >> a >> b;
    del_arc(g, a, b);
    graph_print(g);

    cout << "add";
    cin >> a >> b;
    add_arc(g, a, b);
    graph_print(g);
    cout << endl;
    graph* gt = graph_transposition(g);
    graph_print(gt);
    graph_free(g);
    graph_free(gt);
}
void test_bipartite() {
    int n, r;
    cout << "Количество вершин:";
    cin >> n;
    struct graph* g;
    g = graph_init(n);
    int a, b;
    cout << "Количество ребер:";
    cin >> r;
    cout << "Между какими вершинами ребра:";
    for (int i = 0; i < r; i++) {
        cin >> a >> b;
        add_edge(g, a, b);
    }
    graph_print(g);

    if (is_bipartite(g, dfs)) {
        int* colours = is_bipartite(g, dfs);
        for (int j = 0; j < g->count; j++) {
            if (colours[j] == 1)
                cout << j << " " << "В первой доле" << endl;
            if (colours[j] == -1)
                cout << j << " " << "Во второй доле" << endl;
        }

    }
    else { cout << "Не двудольный"; }
    cout << endl;
    if (is_bipartite(g, bfs)) {
        int* colors = is_bipartite(g, bfs);
        for (int j = 0; j < g->count; j++) {
            if (colors[j] == 1)
                cout << j << " " << "В первой доле" << endl;
            if (colors[j] == -1)
                cout << j << " " << "Во второй доле" << endl;
        }
    }
    else { cout << "Не двудольный"; }
    graph_free(g);
}
void test_topsort() {
    int n, r;
    cout << "Количество вершин:";
    cin >> n;
    struct graph* g;
    g = graph_init(n);
    int a, b;
    cout << "Количество ребер:";
    cin >> r;
    cout << "Между какими вершинами ребра:";
    for (int i = 0; i < r; i++) {
        cin >> a >> b;
        add_arc(g, a, b);
    }
    graph_print(g);
    int* res_topsort = dfs_time(g);
    for (int i = 0; i < g->count; i++) { cout << res_topsort[i] << " "; }
    /*
    8
    12
   0 1
   5 1
   5 0
   0 4
   5 4
   1 2
   6 5
   2 3
   7 6
   3 6
   7 2
   3 7*/
}
void test_scc()
{
    int n, r;
    cout << "Количество вершин:";
    cin >> n;
    struct graph* g;
    g = graph_init(n);
    int a, b;
    cout << "Количество ребер:";
    cin >> r;
    cout << "Между какими вершинами ребра:";
    for (int i = 0; i < r; i++) {
        cin >> a >> b;
        add_arc(g, a, b);
    }
    graph_print(g);
    system("CLS");
    int* colours = graph_scc(g);
    int colour = 1;
    for (int i = 0; i < g->count; i++)
    {
        cout << colours[i] << " ";
    }
}



/*
           1 ---- 3 ---- 5
          /|      |
        0  |      |   vertex cover = 0 2 3
         \ |      |
           2 ---- 4    */

int main() {
    setlocale(LC_ALL, "rus");
    test_graph();
}







