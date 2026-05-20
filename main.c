#include <gtk/gtk.h>
#include <stdio.h>

#define MAX_NODES 20

// ================= GRAPH =================
int graph[MAX_NODES][MAX_NODES];
int n; // number of nodes

// positions (fixed layout for simplicity)
int pos[MAX_NODES][2] = {
    {100,100},{200,80},{300,120},{400,100},
    {150,200},{250,220},{350,200},{450,220},
    {100,300},{200,320},{300,300},{400,320}
};

// ================= TARJAN =================
int index_counter;
int stack[MAX_NODES], top;
int onStack[MAX_NODES];

int ids[MAX_NODES], low[MAX_NODES];
int scc_id[MAX_NODES];
int scc_count;

void push(int v) {
    stack[++top] = v;
    onStack[v] = 1;
}

int pop_node() {
    int v = stack[top--];
    onStack[v] = 0;
    return v;
}

void tarjanDFS(int at) {
    ids[at] = low[at] = index_counter++;
    push(at);

    for (int to = 0; to < n; to++) {
        if (graph[at][to]) {
            if (ids[to] == -1) {
                tarjanDFS(to);
                low[at] = (low[at] < low[to]) ? low[at] : low[to];
            } else if (onStack[to]) {
                low[at] = (low[at] < ids[to]) ? low[at] : ids[to];
            }
        }
    }

    if (ids[at] == low[at]) {
        while (1) {
            int node = pop_node();
            scc_id[node] = scc_count;
            if (node == at) break;
        }
        scc_count++;
    }
}

void findSCCs() {
    for (int i = 0; i < n; i++) {
        ids[i] = -1;
        onStack[i] = 0;
    }

    index_counter = 0;
    top = -1;
    scc_count = 0;

    for (int i = 0; i < n; i++) {
        if (ids[i] == -1)
            tarjanDFS(i);
    }
}

// ================= GTK =================
GtkWidget *drawing_area;
int computed = 0;

double colors[6][3] = {
    {1,0,0},{0,1,0},{0,0,1},
    {1,1,0},{1,0,1},{0,1,1}
};

// draw graph
static void draw(GtkDrawingArea *area, cairo_t *cr, int w, int h, gpointer data) {

    // draw edges
    cairo_set_source_rgb(cr, 0, 0, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) {
                cairo_move_to(cr, pos[i][0], pos[i][1]);
                cairo_line_to(cr, pos[j][0], pos[j][1]);
                cairo_stroke(cr);
            }
        }
    }

    // draw nodes
    for (int i = 0; i < n; i++) {

        if (computed) {
            int c = scc_id[i] % 6;
            cairo_set_source_rgb(cr, colors[c][0], colors[c][1], colors[c][2]);
        } else {
            cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
        }

        cairo_arc(cr, pos[i][0], pos[i][1], 15, 0, 2 * G_PI);
        cairo_fill(cr);

        // draw node label
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, pos[i][0]-5, pos[i][1]+5);
        char label[5];
        sprintf(label, "%d", i);
        cairo_show_text(cr, label);
    }
}

// button
void run_tarjan(GtkWidget *btn, gpointer data) {
    findSCCs();
    computed = 1;

    printf("\n--- SCC OUTPUT ---\n");
    for (int i = 0; i < n; i++) {
        printf("Node %d -> SCC %d\n", i, scc_id[i]);
    }

    gtk_widget_queue_draw(drawing_area);
}

// ================= INPUT =================
void init_graph() {

    int edges;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // clear graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
    }
}

// ================= GTK =================
static void activate(GtkApplication *app, gpointer user_data) {

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Tarjan SCC Simulation");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), box);

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 600, 350);
    gtk_box_append(GTK_BOX(box), drawing_area);

    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw, NULL, NULL);

    GtkWidget *btn = gtk_button_new_with_label("Find SCCs");
    gtk_box_append(GTK_BOX(box), btn);

    g_signal_connect(btn, "clicked", G_CALLBACK(run_tarjan), NULL);

    gtk_window_present(GTK_WINDOW(window));
}

// ================= MAIN =================
int main(int argc, char **argv) {

    init_graph();  // TAKE INPUT FIRST

    GtkApplication *app = gtk_application_new("com.example.tarjan", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    return g_application_run(G_APPLICATION(app), argc, argv);
}