#include <iostream>
#include <time.h>
#include <math.h>
#include <string.h>
#include "graph.h"
using namespace std;


struct nodebt* insert(struct nodebt* root, int data) {
    if (root == NULL) {
        struct nodebt* new_node = (nodebt*)malloc(sizeof(struct nodebt));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    else if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    return root;
}

void traverse_inorder(struct nodebt* root, int* a, int* i) {
    if (root == NULL) {
        return;
    }
    traverse_inorder(root->left, a, i);
    a[(*i)++] = root->data;
    traverse_inorder(root->right, a, i);
}

int* tree_sort(int* a, int n) {
    struct nodebt* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, a[i]);
    }

    int* result = (int*)malloc(sizeof(int) * n);
    int j = 0;
    traverse_inorder(root, result, &j);

    free(root);
    return result;
}

struct node1* L_Stern(struct node1* current) { //создание левого левого
    struct node1* new_node = (struct node1*)malloc(sizeof(struct node1));
    new_node->num = current->leftp->num + current->num;
    new_node->den = current->leftp->den + current->den;
    new_node->leftp = current->leftp;
    new_node->rightp = current;
    return new_node;
}
struct node1* R_Stern(struct node1* current) { //создание правого ребенка
    struct node1* new_node = (struct node1*)malloc(sizeof(struct node1));
    new_node->num = current->rightp->num + current->num;
    new_node->den = current->rightp->den + current->den;
    new_node->leftp = current;
    new_node->rightp = current->rightp;
    return new_node;
}
void ALL_Stern(int n, struct node1* current) { //вывод всех элементов штерна до уровня n
    if (n > 0) {
        ALL_Stern(n - 1, L_Stern(current));
        cout << current->num << "/" << current->den << " ";
        ALL_Stern(n - 1, R_Stern(current));
    }
}
string search_Stern(int n, float number, struct node1* current, string way) {
    if (n > 0) {

        {

            if (number < (float(current->num) / current->den)) {
                way += 'L';
                return search_Stern(n - 1, number, L_Stern(current), way);


            }
            if (number > (float(current->num) / current->den))
            {
                way += 'R';
                return search_Stern(n - 1, number, R_Stern(current), way);

            }

        }
    }
    if ((number = (float(current->num) / current->den))) return way;
    if (n == 0) return way;
}
void PROGRAMM(struct node1* current) {
    cout << "Введите 1 чтобы вывести все дерево" << "\n";
    cout << "Введите 2 чтобы вывести приближение числа" << "\n";
    int programm;
    cin >> programm;
    if (programm == 1) {
        int n;
        cout << "Введите глубину дерева" << "\n";
        cin >> n;
        cout << "Дерево Штерна Брока\n";
        ALL_Stern(n, current);
        cout << "\n\n";
    }
    else if (programm == 2) {
        int n;
        float number;
        cout << "Введите глубину " << "\n";
        cin >> n;

        cout << "Введите число для поиска приближенного:" << "\n";
        cin >> number;
        cout << "Ближайший путь:\n" << search_Stern(n, number, current, "");
    }

}


graph* graph_init(int n) {
    graph* g = (graph*)malloc(sizeof(graph));
    g->count = n;
    g->adj_list = (list*)malloc(n * sizeof(list));
    for (int i = 0; i < n; i++) {
        g->adj_list[i].head = NULL;
    }
    return g;
}
void graph_print(graph* g) {
    for (int i = 0; i < g->count; i++) {
        node* cur = g->adj_list[i].head;
        cout << i << ": ";
        while (cur != NULL) {
            cout << cur->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }
}
void graph_free(graph* g) {
    for (int i = 0; i < g->count; ++i) {
        node* temp;
        while (g->adj_list[i].head != NULL) {
            temp = g->adj_list[i].head;
            g->adj_list[i].head = g->adj_list[i].head->next;
            free(temp);
        }
    }
    free(g->adj_list);
    free(g);
}
void add_arc(graph* g, int a, int b) {
    if (a < g->count && b < g->count) {
        node* current_node = g->adj_list[a].head;
        while (current_node) {
            if (current_node->val == b) {
                return;
            }
            current_node = current_node->next;
        }
        node* pNode = (node*)malloc(sizeof(node));
        pNode->val = b;
        pNode->next = g->adj_list[a].head;
        g->adj_list[a].head = pNode;
    }
}
void add_edge(graph* g, int a, int b) {
    add_arc(g, a, b);
    add_arc(g, b, a);
}
void del_arc(graph* g, int a, int b) {
    if (a < g->count && b < g->count) {
        node* prev = NULL;
        node* cur = g->adj_list[a].head;
        while (cur != NULL && cur->val != b) {
            prev = cur;
            cur = cur->next;
        }
        if (prev == NULL && cur != NULL) {
            g->adj_list[a].head = cur->next; // ??
        }
        else if (cur != NULL) {
            prev->next = cur->next;
        }
        free(cur);
    }
}


typedef struct queue {
    node* head;
    node* last;
} queue;

queue* get_queue(int elem) {
    queue* q = (queue*)malloc(sizeof(queue));

    node* new_node = (node*)malloc(sizeof(node)); // выделяем память для "новой вершины"
    new_node->val = elem; // присваиваем новой вершине значение стартовой
    new_node->next = NULL; // пока нет следующего
    q->head = new_node;
    q->last = new_node->next;
    return q;
}

void queue_free(queue* q) {
    node* cur = q->head;
    while (cur)
    {
        free(q->head);
        cur = cur->next;
    }
}

int queue_pop(queue* q) {
    int val = q->head->val;
    node* temp = q->head;
    q->head = q->head->next;
    free(temp);
    return val;
}

void queue_push(queue* q, int n)
{
    node* new_node = (node*)malloc(sizeof(node)); // выделяем память для "новой вершины"
    new_node->val = n; // присваиваем новой вершине значение стартовой
    new_node->next = NULL; // пока нет следующего
    if (q->last != NULL) {

        q->last->next = new_node;
        q->last = q->last->next;
    }
    else { q->last = new_node; }
}

int dfs(graph* g, int start, int* colours)
{
    node* cur = g->adj_list[start].head;// запустили dfs от вершины и берем ее список смежности
    while (cur) {// будем в цикле запускать dfs от смежны вершин по порядку
        int n = cur->val; // получаем номер вершины смежной со стартовой
        if (!colours[n]) // тк при создании массива все элементы автоматически заполняются нулями, для нас 0 в ячейке массива будет означать что вершина еще не была нами посещена
        {
            colours[n] = -colours[start]; // следуя логике нашего алгоритма будем красить смежную вершину в противоположный цвет стартовой
            if (dfs(g, n, colours) == 0) {
                ;// если обход в ширину вернул 0 значит граф не является двудольным 
                return 0;
            }
        }
        else if (colours[n] == colours[start])// если все таки вершина уже имела какой то цвет в нашем массиве, то нам надо понять, совпадает ли этот цвет с цветом стартовой вершины или нет, тк мы хотим чтобы вершины одного ребра 'имели разный цвет'
        {
            // если вдруг цвета совпали => граф не двудольный

            return EXIT_FAILURE;
        }
        cur = cur->next;
    }
    return EXIT_SUCCESS;
}

int bfs(graph* g, int start, int* colours)
{
    queue* q = get_queue(start);
    colours[start] = 1;
    while (q->head)
    {
        int n = queue_pop(q);
        for (node* temp = g->adj_list[n].head; temp; temp = temp->next)
        {
            int adjacent_vertex = temp->val;
            if (!colours[adjacent_vertex])
            {
                colours[adjacent_vertex] = -colours[n];
                queue_push(q, adjacent_vertex);
            }
            else if (colours[adjacent_vertex] == colours[n])
            {
                return EXIT_FAILURE;
            }
        }

    }
    return EXIT_SUCCESS;
}
int* is_bipartite(graph* g, int check_alg(graph*, int, int*)) {
    int* colours = (int*)calloc(g->count, sizeof(int)); // выделяем память для массива цветов вершин
    for (int i = 0; i < g->count; i++) {   // проходим по всем вершинам графа
        if (!colours[i]) {// если вершина еще не покрашена,
            colours[i] = 1;
            if (check_alg(g, i, colours) == 0) { // запускаем алгоритм для проверки двудольности
                free(colours);
                return NULL;
            }
        }
    }

    return colours;
}

bool dfs_acyclicity(graph* g, int start, int* colors1) {
    colors1[start] = 1;
    node* cur = g->adj_list[start].head;
    while (cur) {
        int u = cur->val;
        if (colors1[u] == 0)
            dfs_acyclicity(g, u, colors1);
        if (colors1[u] == 1)
            return 0;
        cur = cur->next;
    }
    colors1[start] = 2;
    return 1;
}
int acyclicity(graph* g) {
    int* colors1 = (int*)calloc(g->count, sizeof(int));
    for (int i = 0; i < g->count; i++) {
        if (!colors1[i])
            if (!(dfs_acyclicity(g, i, colors1))) {
                free(colors1);
                return 0;
            }
    }
    return 1;
}

void dfs_for_topsort(graph* g, int start, int* visited, int** res_pos) {
    visited[start] = 1;
    node* cur = g->adj_list[start].head;
    while (cur)
    {
        int n = cur->val;
        if (!visited[n])
        {
            dfs_for_topsort(g, n, visited, res_pos);
        }
        cur = cur->next;
    }
    **res_pos = start;
    (*res_pos)--;
}
int* dfs_time(graph* g)
{
    int* res = (int*)calloc(g->count, sizeof(int));
    int* visited = (int*)calloc(g->count, sizeof(int)); // выделяем память для массива цветов вершин
    int* res_pos = res + g->count - 1;
    for (int i = 0; i < g->count; i++) {   // проходим по всем вершинам графа
        if (!visited[i]) {// если вершина еще не покрашена,
            visited[i] = 1;
            dfs_for_topsort(g, i, visited, &res_pos);
        }
    }
    free(visited);
    return res;
}
graph* graph_transposition(graph* g)
{
    graph* gt = graph_init(g->count);
    for (int i = 0; i < gt->count; i++)
    {
        node* cur = g->adj_list[i].head;
        while (cur)
        {
            add_arc(gt, cur->val, i); // добавляем инцидентную вершину с инвертированным направлением ребра
            cur = cur->next;
        }

    }
    return gt;
}
void dfs_scc(graph* g, int start, bool* visited, int colour, int* colours) {
    visited[start] = 1;

    node* cur = g->adj_list[start].head;
    while (cur) {
        if (!visited[cur->val]) {

            dfs_scc(g, cur->val, visited, colour, colours);

        }
        cur = cur->next;
        if (colours[start] == 0)
        {
            colours[start] = colour;
        }
    }
}

int* graph_scc(graph* g)
{
    int colour = 1;
    int* colours = (int*)calloc(g->count, sizeof(int));
    bool* visited = (bool*)calloc(g->count, sizeof(bool));

    graph* gt = graph_transposition(g);
    int* res = dfs_time(gt);

    //graph_print(gt);

    for (int i = 0; i < g->count; i++) {
        if (!visited[res[i]])
        {
            dfs_scc(g, res[i], visited, colour, colours);
            colour++;
        }
    }
    graph_free(gt);
    free(visited);
    free(res);
    return colours;
}