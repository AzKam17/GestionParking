#include <stdio.h>
#include <mysql.h>

#include "../../headers/type_vehicule/nombreDePlacesDisponibles.h"

int nombresPlacesDispo(MYSQL *conn, int typeVehicule){
	int resultat = 0;
    char sql[500];

   	if(typeVehicule == 1){
   		strcpy(sql, "SELECT nbrDispo FROM type_vehicule WHERE lib='Moto'");
   	}else if(typeVehicule == 2){
   		strcpy(sql, "SELECT SUM(nbrDispo) FROM type_vehicule WHERE lib = 'Moto' or lib = 'Voiture'");
   	}else{
   		strcpy(sql, "SELECT SUM(nbrDispo) FROM type_vehicule");
   	}

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

	resultat = atoi(row[0]) > 0;
	

	//int res = atoi(row[0]);
	mysql_free_result(result);

	return resultat;

}