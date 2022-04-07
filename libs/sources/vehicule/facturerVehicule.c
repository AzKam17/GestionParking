#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include "../../headers/vehicule/facturerVehicule.h"


#include "../../headers/vehicule/retrouverVehicule.h"
#include "../../headers/vehicule/calculPrixParking.h"
#include "../../headers/vehicule/sortirVehicule.h"

void facturerVehicule(MYSQL *conn, char* plaqueImmat){
	//Recherche du vehicule dans la base de donnees
	int vehiculeDansLeParking = retrouverVehicule(conn, plaqueImmat, 1);

	//Vehicule n'est pas dans le parking
	if(!vehiculeDansLeParking){
		printf("Votre vehicule n'est pas dans le parking !");
		return;
	}

	//Vehicule présent dans le parking on calcule le montant 
	int minutes, prixParking;

	calculPrixParking(conn, plaqueImmat, &prixParking, &minutes);

	printf(
		"\nMerci pour votre visite, vous devez payer %d FCFA pour vos %d minutes de stationnement.", 
		prixParking, minutes
	);
	
	//Faire sortir le véhicule du parking
	sortirVehicule(conn, plaqueImmat);

	//Message de remerciement
	printf("\n\nMerci au plaisir de vous revoir !");
}