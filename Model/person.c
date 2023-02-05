#include "person.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PWD "rayrayray"
#define DB_PORT 3306
#define DB_NAME "inventory"


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

