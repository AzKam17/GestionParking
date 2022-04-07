#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include "../../headers/type_vehicule/identifierTypeVehicule.h"

int identifierTypeVehicule(MYSQL *conn, int typeVehicule){
	int idTypeVehicule = -1;
	char sql[500];

	if(typeVehicule == 1){
		idTypeVehicule = verifTypeVehicule(conn, "Moto");
		if (idTypeVehicule == -1)
		{
			idTypeVehicule = identifierTypeVehicule(conn, 2);
		}
	}else if(typeVehicule == 2){
		idTypeVehicule = verifTypeVehicule(conn, "Voiture");
		if (idTypeVehicule == -1)
		{
			idTypeVehicule = identifierTypeVehicule(conn, 3);
		}
	}else{
		idTypeVehicule = verifTypeVehicule(conn, "Camion");
	}
	return idTypeVehicule;
}

int verifTypeVehicule(MYSQL *conn, char* libTypeVehicule){
	char sql[500];
	sprintf(sql, "SELECT id, nbrDispo FROM type_vehicule WHERE lib = '%s'", libTypeVehicule);

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

	row = mysql_fetch_row(result);

	return atoi(row[1]) > 0 ? atoi(row[0]) : -1;
}