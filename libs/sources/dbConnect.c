#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include "../headers/dbConnect.h"

void connectToDatabase(MYSQL *conn)
{
    static char *host = "localhost";
    static char *dbname = "esatic";
    static char *user = "root";
    static char *pass = "";

    if (conn == NULL)
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        exit(0);
    }

    if(mysql_real_connect(conn, host, user, pass, dbname,0,NULL,0) == NULL)
    {
        fprintf(stderr,"%s\n",mysql_error(conn));
        mysql_close(conn);
        exit(0);
    }
    else
    {
        printf("\n");

    }
    
}