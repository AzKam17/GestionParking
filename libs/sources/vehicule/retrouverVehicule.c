#include <stdio.h>
#include <mysql.h>
#include <stdio.h>
#include <string.h>

#include "../../headers/vehicule/retrouverVehicule.h"

int retrouverVehicule(MYSQL *conn, char* immatVehicule, int presentDansLeParking){
    char sql[500];

    if(!presentDansLeParking){
	    sprintf(sql, 
	    	"SELECT vehicule.id, type_vehicule.lib, immat, dateArrivee, dateFin \
	    			FROM vehicule, type_vehicule \
	    			WHERE  type_vehicule.id = vehicule.type_veh AND immat = '%s' \
	    			ORDER BY id DESC LIMIT 1", 
	    	immatVehicule);
	
    }else{
	    sprintf(sql, 
	    	"SELECT vehicule.id, type_vehicule.lib, immat, dateArrivee, dateFin \
	    			FROM vehicule, type_vehicule \
	    			WHERE  type_vehicule.id = vehicule.type_veh AND dateFin = dateArrivee AND immat = '%s' \
	    			ORDER BY id DESC LIMIT 1", 
	    	immatVehicule);
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
	int i;
	while ((row = mysql_fetch_row(result)))
	{
        printf("\nVotre véhicule est un(e) %s, son numéro de plaque d'immatriculation est %s, enregistré le %s", row[1], row[2], row[3]);

        if(row[3] != row[4]){
        	printf(" et sorti le %s.\n", row[4]);
        }

        printf(".");

		return atoi(row[0]);
	}


}