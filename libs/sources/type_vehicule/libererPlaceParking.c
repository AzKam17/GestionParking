#include <stdio.h>
#include <mysql.h>
#include <stdio.h>
#include <string.h>

#include "../../headers/type_vehicule/libererPlaceParking.h"

void libererPlaceParking(MYSQL *conn, char* plaqueImmat){
	char sql[500];
	char sql2[500];

	sprintf(
		sql,
		"SELECT type_stattionnement \
		FROM vehicule \
		WHERE immat = '%s' \
		ORDER BY id DESC LIMIT 1;",
		plaqueImmat
	);

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
	while ((row = mysql_fetch_row(result)))
	{
	  	sprintf(
			sql2,
			"UPDATE type_vehicule \
			SET nbrDispo = nbrDispo + 1 \
			WHERE id = %d",
			atoi(row[0])
		);
		mysql_query(conn, sql2);
	}	
}