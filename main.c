#include <gtk/gtk.h>
#include <mariadb/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PWD "rayrayray"
#define DB_PORT 3306
#define DB_NAME "rayit"

int count = 0;
GtkWidget *txt;

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void count_button(GtkWidget* wid, gpointer ptr)
{
    char buffer[30];
    count++;
    sprintf(buffer, "Button pressed %d times", count);
    gtk_label_set_text(GTK_LABEL(ptr), buffer);
}

void save_button(GtkWidget* wid, gpointer ptr)
{
    MYSQL* conn = mysql_init(NULL);
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PWD, DB_NAME, DB_PORT, NULL, 0))
    {
        gtk_label_set_text(ptr, "Connection success");
        char q[1000];
        sprintf(q, "INSERT INTO Persons (LastName) VALUES (\"Marx\");" );
        if(mysql_query(conn, q) != 0)
        {
            gtk_label_set_text(ptr, mysql_error(conn));
        }
    } else {
        gtk_label_set_text(ptr, mysql_error(conn));
    }
    mysql_close(conn);
}

void copy_text (GtkWidget* wid, gpointer ptr)
{
    const char* input = gtk_entry_get_text(GTK_ENTRY(txt));
    gtk_label_set_text(GTK_LABEL(ptr), input);
}

int main(int argc, char *argv[]) {
    printf("Hello, World!\n");

    // USING Glade
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
    GtkWidget *btn = gtk_button_new_with_label ("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    // Add label
    GtkWidget *lbl = gtk_label_new("My label");

    // Btn2
    GtkWidget *btn2 = gtk_button_new_with_label("Count button");
    g_signal_connect(btn2, "clicked", G_CALLBACK(count_button), lbl);

    // Btn3
    GtkWidget *btn3 = gtk_button_new_with_label("SAVE button");
    g_signal_connect(btn3, "clicked", G_CALLBACK(save_button), lbl);

    // input
    txt = gtk_entry_new();

    // Grid
    GtkWidget *grd = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grd), lbl, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), btn, 1, 0, 1,1);
    gtk_grid_attach(GTK_GRID(grd), btn2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), btn3, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), txt, 1,1,1,1);
    gtk_container_add(GTK_CONTAINER(win), grd);
    gtk_widget_show_all (win);
    gtk_main ();
    return 0;
}
