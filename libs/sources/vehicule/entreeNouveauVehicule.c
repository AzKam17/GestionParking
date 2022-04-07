#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include "../../headers/vehicule/entreeNouveauVehicule.h"
#include "../../headers/type_vehicule/identifierTypeVehicule.h"

void entreeNouveauVehicule(MYSQL *conn, int typeVehicule, char* plaqueImmat){
	char sql1[500];
	char sql2[500];
	int idTypeVehicule = -1;
	printf("\n\n=====> Enregistrement de voitre vehicule");
	printf("\n\n\n\n Vous avez choisi le type :  %d et la plaque d'immatriculation de votre véhicule est : %s", typeVehicule, plaqueImmat);

	idTypeVehicule = identifierTypeVehicule(conn, typeVehicule);

	//Insertion dans la table
	sprintf(
		sql1, 
		"INSERT INTO vehicule (immat, dateArrivee, dateFin, type_veh, type_stattionnement) VALUES ('%s', NOW(), NOW(), %d, %d);",
		plaqueImmat, typeVehicule, idTypeVehicule
	);

    mysql_query(conn, sql1);

	//Soustraction du nombre de places disponibles
	sprintf(
		sql2, 
		"UPDATE type_vehicule SET nbrDispo = nbrDispo - 1 WHERE id = %d;",
		idTypeVehicule
	);

    mysql_query(conn, sql2);
	printf("\n\n=====> Enregistrement réussi");
}