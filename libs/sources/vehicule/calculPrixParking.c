#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include "../../headers/vehicule/calculPrixParking.h"

int calculPrixParking(MYSQL *conn, char* plaqueImmat, int* prixParking, int* minutes){
	char sql[500];

   	sprintf(
   		sql, 
   		"SELECT MINUTE(TIMEDIFF(NOW(), dateArrivee)) * type_vehicule.prixHoraire, MINUTE(TIMEDIFF(NOW(), dateArrivee)) \
   		FROM vehicule, type_vehicule \
   		WHERE vehicule.type_veh = type_vehicule.id AND vehicule.immat = '%s' \
   		ORDER BY vehicule.id DESC LIMIT 1;", 
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
	int i;
	while ((row = mysql_fetch_row(result)))
	{
		*prixParking = atoi(row[0]);
		*minutes = atoi(row[1]);
	}
}