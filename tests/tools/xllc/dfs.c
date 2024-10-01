void *malloc(unsigned long);
void free(void *);
void *memset(void *, int, unsigned long);
int printf(const char *, ...);

int n, m;
int *adj;
int *target, *next;

void add_edge(int e, int u, int v) {
    target[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}

void visit(int v) {
    printf("%d\n", v);
}

int *visited;

void dfs(int u) {
    visit(u);
    visited[u] = 1;
    for (int e = adj[u]; e != -1; e = next[e]) {
        int v = target[e];
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main(void) {
    n = 9;
    m = 12;

    adj = malloc(n * sizeof(int));
    memset(adj, -1, n * sizeof(int));

    target = malloc(m * sizeof(int));
    next = malloc(m * sizeof(int));

    add_edge(0, 0, 1);
    add_edge(1, 1, 2);
    add_edge(2, 3, 4);
    add_edge(3, 4, 5);
    add_edge(4, 6, 7);
    add_edge(5, 7, 8);
    add_edge(6, 0, 3);
    add_edge(7, 1, 4);
    add_edge(8, 2, 5);
    add_edge(9, 3, 6);
    add_edge(10, 4, 7);
    add_edge(11, 5, 8);

    visited = malloc(n * sizeof(int));
    memset(visited, 0, n * sizeof(int));

    dfs(0);

    free(visited);

    free(next);
    free(target);

    free(adj);

    return 0;
}
