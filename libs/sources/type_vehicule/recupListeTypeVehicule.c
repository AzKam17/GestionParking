#include <stdio.h>
#include <mysql.h>

#include "../../headers/type_vehicule/recupListeTypeVehicule.h"

void listVehiculePrisEnCharge(MYSQL *conn){
    if(mysql_query(conn, "SELECT id, lib FROM type_vehicule")){
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
	  for(i = 0; i < num_fields; i++)
	  {
		  printf("%s%s", row[i] ? row[i] : "NULL", i == (num_fields - 1) ? "" : " - ");
	  }
	  printf("\r\n");
	}

	mysql_free_result(result);
}