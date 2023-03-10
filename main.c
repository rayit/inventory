#include <gtk/gtk.h>
#include <mysql/mysql.h>
#include "Model/person.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PWD "rayrayray"
#define DB_PORT 3306
#define DB_NAME "inventory"

GtkWidget *view;
GtkTreeModel *model;
GtkWidget *txtLastName;
GtkWidget *txtFirstName;

enum
{
    COL_FirstName = 0,
    COL_LastName = 1,
    NUM_COLS = 2
} ;


void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void save_button(GtkWidget* wid, gpointer ptr)
{
    // Use person Model to insert a Person
    char *r = insertPerson(gtk_entry_get_text(txtFirstName), gtk_entry_get_text(txtLastName));
    gtk_label_set_text(ptr, r);
    // Clear form
    gtk_entry_set_text(txtLastName, "");
    gtk_entry_set_text(txtFirstName, "");
}

void query(GtkWidget* wid, gpointer ptr)
{
    GtkListStore *store = queryPerson();
    model = gtk_tree_view_get_model(GTK_TREE_VIEW(view));
    g_object_ref(model); // Make sure the model stays with us after the tree view unrefs it 
    gtk_tree_view_set_model(GTK_TREE_VIEW(view), store); // Re-attach model to view 
}

static GtkTreeModel* create_and_fill_model(void)
{
    GtkListStore *store = gtk_list_store_new(NUM_COLS,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING);
    /* Append a row and fill in some data */
    GtkTreeIter iter;
    gtk_list_store_append (store, &iter);
    gtk_list_store_set (store, &iter,
                        COL_FirstName, "Raymond",
                        COL_LastName, "Marx",
                        -1);
    gtk_list_store_append (store, &iter);
    gtk_list_store_set (store, &iter,
                        COL_FirstName, "Nicole",
                        COL_LastName, "Marx",
                        -1);

    return GTK_TREE_MODEL (store);
}

static GtkWidget* create_view_and_model (void)
{
    view = gtk_tree_view_new();

    GtkCellRenderer  *renderer;
    // Column #1
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(
            GTK_TREE_VIEW (view),
            0,
            "FirstName",
            renderer,
            "text",
            COL_FirstName,
            NULL
            );
    // Column #2
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(
            GTK_TREE_VIEW(view),
            1,
            "LastName",
            renderer,
            "text",
            COL_LastName,
            NULL
            );

    model = create_and_fill_model ();

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

    /* The tree view has acquired its own reference to the
     *  model, so we can drop ours. That way the model will
     *  be freed automatically when the tree view is destroyed
     */
    g_object_unref (model);

    return view;
}

int main(int argc, char *argv[]) {
// USING Glade (for FUTURE)
//    gtk_init (&argc, &argv);
//    GtkBuilder *builder = gtk_builder_new_from_file (
//            "layout.glade");
//    GtkWidget *win = (GtkWidget *) gtk_builder_get_object (builder, "win");
//
//    GtkWidget *btn = (GtkWidget *) gtk_builder_get_object(builder, "btn");
//    g_signal_connect(btn, "clicked", G_CALLBACK(save_button), NULL);
//
//    gtk_widget_show_all (win);
//    gtk_main ();

    gtk_init (&argc, &argv);
    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_resize(win, 800, 600);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    // Add label
    GtkWidget *lbl = gtk_label_new("Last name:");
    GtkWidget *lblFirstName = gtk_label_new("First name:");
    GtkWidget *lblStatus = gtk_label_new("");

    // Btn1
    GtkWidget *btnSave = gtk_button_new_with_label("SAVE");
    g_signal_connect(btnSave, "clicked", G_CALLBACK(save_button), lblStatus);

    // Btn1
    GtkWidget *btnQuery = gtk_button_new_with_label("Query");
    g_signal_connect(btnQuery, "clicked", G_CALLBACK(query), lblStatus);

    // input
    txtLastName = gtk_entry_new();

    txtFirstName = gtk_entry_new();

    // GridView
    view = create_view_and_model();

    // Grid
    GtkWidget *grd = gtk_grid_new();

    gtk_widget_compute_expand(grd, GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_margin_top(grd, 30);
    gtk_widget_set_margin_start(grd, 30);
    gtk_widget_set_margin_end(grd, 30);
    gtk_widget_set_margin_bottom(grd, 30);
    gtk_grid_set_column_spacing(grd, 5);
    gtk_grid_set_row_spacing(grd, 5);
    gtk_widget_set_hexpand (txtFirstName, TRUE);
    gtk_widget_set_hexpand (txtLastName, TRUE);

    gtk_grid_attach(GTK_GRID(grd), lblFirstName, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grd), txtFirstName, 2 , 0, 4, 1);


    gtk_grid_attach(GTK_GRID(grd), lbl, 0, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grd), txtLastName, 2,1,4,1);

    gtk_grid_attach(GTK_GRID(grd), btnSave, 0, 2, 3,1);
    gtk_grid_attach(GTK_GRID(grd), btnQuery, 3, 2, 3,1);

    gtk_grid_attach(GTK_GRID(grd), lblStatus, 0, 3, 6, 1);
    gtk_grid_attach(GTK_GRID(grd), view, 0, 4, 6, 1);

    gtk_container_add(GTK_CONTAINER(win), grd);
    gtk_widget_show_all (win);
    gtk_main ();
    return 0;
}

