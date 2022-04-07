#include <stdio.h>
#include <mysql.h>
#include <stdio.h>
#include <string.h>

#include "../../headers/type_vehicule/afficherNombrePlacesDisponibles.h"

void afficherNombrePlacesDisponibles(MYSQL *conn){
	int resultat = 0;
    char sql[500];

   	strcpy(sql, "SELECT lib, nbrDispo FROM type_vehicule");

    if(mysql_query(conn, sql)){
        printf("Erreur: %s\r\n", mysql_error(conn));
    }

    MYSQL_RES *result = mysql_store_result(conn);
	if (result == NULL)
	{
		printf("error: %s\r\n", mysql_error(conn));
		mysql_close(conn);
		exit(1);
	}

	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	int i;
	while ((row = mysql_fetch_row(result)))
	{
		printf("Pour la catégorie %s, il y'a %s place(s) disponible(s).\n", row[0], row[1]);
	}

}