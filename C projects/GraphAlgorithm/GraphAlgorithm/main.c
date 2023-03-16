#define  _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

int maxlen = -1;

struct Edge;
typedef struct Vertex
{
    struct Vertex* next;
    struct Edge* firstEdge;
    int name;
    int mark;

}Vertex;

typedef struct Edge
{
    struct Edge* next;
    Vertex* vertexTo;
    int length;
}Edge;

int** creatememory(int N)
{
    int** arr;
    arr = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; ++i)
    {
        arr[i] = (int*)malloc(N * sizeof(int));
    }
    return arr;
}

char* getstring()
{
    char* result;
    int index = 0, capacity = 2;
    result = malloc(sizeof(char) * capacity);
    do
    {
        scanf("%c", &result[0]);
    } while (result[0] == '\n');
    do
    {
        index++;
        if (index == capacity)
        {
            capacity *= 2;
            result = realloc(result, capacity * sizeof(char));
        }
        scanf("%c", &result[index]);
    } while (result[index] != '\n');
    result[index] = 0;
    result = realloc(result, sizeof(char) * (index + 1));
    return result;
}

Vertex* Existence(Vertex* G, int v_name)
{
    Vertex* cur;
    for (cur = G; cur; cur = cur->next)
    {
        if (cur->name == v_name)
        {
            return cur;
        }
    }
    return 0;
}

void Print(Vertex* G)
{
    Vertex* cur;
    Edge* e;
    if (G)
    {
        for (cur = G; cur; cur = cur->next)
        {
            printf("%d (", cur->name);
            if (cur->firstEdge)
            {
                printf("%d: %d", cur->firstEdge->vertexTo->name, cur->firstEdge->length);

                for (e = cur->firstEdge->next; e; e = e->next)
                {
                    printf(", %d: %d", e->vertexTo->name, e->length);
                }
            }
            printf(")\n");
        }
    }
    else printf("graph is empty");
}

void Print_arr(int** arr, int str)
{
    for (int i = 0; i < str; ++i)
    {
        printf("%d| ", i);
        for (int j = 0; j < str; ++j)
        {
            printf("%d ", -arr[i][j]);
        }
        printf("\n");
    }
}

int menu(char* desc, int N, ...)
{
    char** A, k;
    int answer = 0, i;
    A = (char**)(&N + 1);
    do
    {
        system("cls");
        printf("%s\n", desc);
        for (i = 0; i < N; ++i)
        {
            if (answer == i) printf(">");
            else printf(" ");
            printf("%d. %s\n", i + 1, A[i]);

        }
        k = _getch();
        if ((k == 0 || k == -32) && _kbhit())
        {
            k = _getch();
            if (k == 72)
            {
                answer--;
                if (answer < 0) answer = N - 1;

            }
            if (k == 80)
            {
                answer++;
                if (answer == N) answer = 0;
            }
        }

    } while (k != 13);
    return answer;
}

void remove_vertex(Vertex* G)
{
    Vertex* v1 = 0, * curVertex;
    Edge* curEdge, * dE;
    char* name1;
    if (G)
    {
        name1 = getstring();
        if (strcmp(G->name, name1) == 0)
        {
            v1 = G;
            G = G->next;
        }
        else for (curVertex = G; curVertex->next; curVertex = curVertex->next)
            if (strcmp(curVertex->next->name, name1) == 0)
            {
                v1 = curVertex->next;
                curVertex->next = v1->next;
                break;
            }
        if (v1)
        {

            for (curVertex = G; curVertex; curVertex = curVertex->next)
                if (curVertex->firstEdge)
                {
                    if (curVertex->firstEdge->vertexTo == v1)
                    {
                        curEdge = curVertex->firstEdge;
                        curVertex->firstEdge = curEdge->next;
                        free(curEdge);
                    }
                    else
                    {
                        for (curEdge = curVertex->firstEdge; curEdge->next; curEdge = curEdge->next)
                            if (curEdge->next->vertexTo == v1)
                                break;
                        if (curEdge->next)
                        {
                            Edge* temp = curEdge->next;
                            curEdge->next = temp->next;
                            free(temp);
                        }
                    }
                }
            while (v1->firstEdge)
            {
                dE = v1->firstEdge;
                v1->firstEdge = dE->next;
                free(dE);
            }
            free(v1->name);
            free(v1);
            printf("Done!\n");
        }
        else printf("Vertex with name %s doesn't exist\n", name1);
        free(name1);
    }
    else printf("There is nothing to remove: graph is empty.\n");
}

void remove_edge(Vertex* G)
{
    char* name1, * name2;
    name1 = getstring();
    name2 = getstring();
    Vertex* v1, * v2;
    Edge* curEdge;
    for (v1 = G; v1; v1 = v1->next)
        if (strcmp(v1->name, name1) == 0)break;
    for (v2 = G; v2; v2 = v2->next)
        if (strcmp(v2->name, name2) == 0)break;
    if (v1 && v2)
    {
        if (v1->firstEdge != 0)
        {
            if (v1->firstEdge->vertexTo == v2)
            {
                curEdge = v1->firstEdge;
                v1->firstEdge = curEdge->next;
                free(curEdge);
                printf("Done!\n");
            }
            else
            {
                for (curEdge = v1->firstEdge; curEdge->next; curEdge = curEdge->next)
                    if (curEdge->next->vertexTo == v2)break;
                if (curEdge->next)
                {
                    Edge* temp = curEdge->next;
                    curEdge->next = temp->next;
                    free(temp);
                    printf("Done!\n");
                }
                else printf("There is no edge from vertex %s to vertex %s\n", name1, name2);
            }
        }
        else printf("There is no any edge from vertex %s\n", name1);
    }
    else printf("At least one of the vertices (%s, %s) doesn't exist\n", name1, name2);

    free(name1);
    free(name2);
}

void create_vertex(Vertex* G, int vertex)
{
    Vertex* ver, * cur;
    ver = malloc(sizeof(Vertex));
    ver->name = vertex;
    ver->firstEdge = 0;
    ver->next = 0;
    for (cur = G; cur->next; cur = cur->next);
    cur->next = ver;
}

void create_edge(Vertex* G, int vertex_from, int vertex_to, int count)
{
    Vertex* from = Existence(G, vertex_from);
    Vertex* to = Existence(G, vertex_to);
    // if this vertex exist 
    if (from && to && count)
    {
        if (from->firstEdge == 0)
        {
            from->firstEdge = malloc(sizeof(Edge));
            from->firstEdge->vertexTo = to;
            from->firstEdge->next = 0;
            from->firstEdge->length = count;
        }
        else
        {
            Edge* edge;
            Edge* e;
            edge = malloc(sizeof(Edge));
            edge->vertexTo = to;
            edge->next = 0;
            edge->length = count;
            for (e = from->firstEdge; e->next; e = e->next);
            e->next = edge;
        }
    }
}

Vertex* input_from_file(FILE* my_file)
{
    Vertex* cur;
    cur = malloc(sizeof(Vertex));
    cur->name = 0;
    cur->next = 0;
    cur->firstEdge = 0;
    Edge* e;
    int count, ** arr, str;
    printf("input number of vertex ");
    scanf("%d", &str);
    arr = creatememory(str);

    for (int i = 0; i < str; ++i)
    {
        for (int j = 0; j < str; ++j)
        {
            fscanf(my_file, "%d", &arr[i][j]);
        }
    }

    for (int i = 1; i < str; ++i)
    {
        create_vertex(cur, i);
    }

    for (int i = 0; i < str; ++i)
    {
        for (int j = 0; j < str; ++j)
        {
            create_edge(cur, i, j, arr[i][j]);
        }
    }
    return cur;
}

//every marks = 0 
void zeros(Vertex* G)
{
    Vertex* cur;
    for (cur = G; cur; cur = cur->next) cur->mark = 0;
}

int all_mark(Vertex* G)
{
    Vertex* cur;
    int mark_count = 0, count = 0;
    for (cur = G; cur; cur = cur->next)
    {
        count++;
        if (cur->mark) mark_count++;
    }
    // return 0 if all vertexes are traversed and marked
    return count - mark_count;
}

// in this function i find longest path to vertex
void new_dfs(Vertex* ver, int v_to, int count)
{
    Edge* chosen_edge = ver->firstEdge;
    if (ver->name != v_to)
    {
        for (chosen_edge; chosen_edge; chosen_edge = chosen_edge->next)
        {
            if (!chosen_edge->vertexTo->mark)
            {
                ver->mark = 1;
                new_dfs(chosen_edge->vertexTo, v_to, count + chosen_edge->length);
                ver->mark = 0;
            }
        }
    }
    else
    {
        if (count > maxlen) maxlen = count;
    }
    printf("count = %d\n", count);
    _getch();
}

int main()
{
    int k, ver_to;
    Vertex* G = 0;
    FILE* myfile = fopen("matrix2.txt", "r");

    do
    {
        k = menu("What do u want", 5, "Create graph", "Print", "Find max path", "Answer", "Exit");
        switch (k)
        {
        case 0:
            G = input_from_file(myfile);
            _getch();
            break;
        case 1:
            zeros(G);
            Print(G);
            _getch();
            break;
        case 2:
            zeros(G);
            maxlen = -1;
            printf("input vertex");
            scanf("%d", &ver_to);
            new_dfs(G, ver_to, 0);
            _getch();
            break;
        case 3:
            printf("answer: %d", maxlen);
            _getch();
            break;
        case 4:
            k = 1000;
            break;
        }
    } while (k != 1000);
    printf("max length = %d", maxlen);
}
