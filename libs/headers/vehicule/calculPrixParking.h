#ifndef CALCUL_PRIX_PARKING_LIB_H    
#define CALCUL_PRIX_PARKING_LIB_H  

int calculPrixParking(MYSQL *conn, char* plaqueImmat, int* prixParking, int* minutes);

#endif 