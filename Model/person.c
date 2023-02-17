#include "person.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PWD "rayrayray"
#define DB_PORT 3306
#define DB_NAME "inventory"

MYSQL_RES *res;
MYSQL_ROW row;
enum
{
    COL_FirstName = 0,
    COL_LastName = 1,
    NUM_COLS = 2
} ;

char* insertPerson(GtkWidget *FirstName, GtkWidget *LastName) {

    MYSQL* conn = mysql_init(NULL);
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PWD, DB_NAME, DB_PORT, NULL, 0))
    {
        char q[1000];
        sprintf(q, "INSERT INTO Persons (FirstName, LastName) VALUES (\"%s\", \"%s\");", FirstName,  LastName );
        if(mysql_query(conn, q) != 0)
        {
            return mysql_error(conn);
        } else {
            return "Inserted";
        }
    } else {
        return mysql_error(conn);
    }
    mysql_close(conn);
}

GtkWidget* queryPerson() {
    MYSQL* conn = mysql_init(NULL);

    if(mysql_real_connect(conn, DB_HOST, DB_USER, DB_PWD, DB_NAME, DB_PORT, NULL, 0))
    {
        char q[1000] = "SELECT * FROM Persons";
        if(mysql_query(conn, q) != 0) 
        {
            return mysql_error(conn);
        } else {
            res = mysql_store_result(conn);
            GtkListStore *store = gtk_list_store_new(NUM_COLS,
                                                 G_TYPE_STRING,
                                                 G_TYPE_STRING);

            while ( row = mysql_fetch_row(res))
            {
                g_print("%s\t%s\t%s\n",row[0], row[1], row[2]);
                GtkTreeIter iter;
                gtk_list_store_append (store, &iter);
                gtk_list_store_set (store, &iter,
                                COL_FirstName, row[1],
                                COL_LastName, row[2],
                                -1);
            }
            mysql_free_result(res);
            return store;
            // Howto do this??
            g_object_unref(store);
        }
    } else {
        return mysql_error(conn);    
    }
    mysql_close(conn);
}

