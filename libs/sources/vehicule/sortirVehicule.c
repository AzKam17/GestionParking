#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include "../../headers/vehicule/sortirVehicule.h"
#include "../../headers/type_vehicule/libererPlaceParking.h"

void sortirVehicule(MYSQL *conn, char* plaqueImmat){
	char sql[500];
	sprintf(
		sql, 
		"UPDATE vehicule SET dateFin = NOW() WHERE immat = '%s' \
		ORDER BY id DESC LIMIT 1;",
		plaqueImmat
	);

    mysql_query(conn, sql);

    libererPlaceParking(conn, plaqueImmat);
}