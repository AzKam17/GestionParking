#ifndef IDENTIFIER_TYPE_VEHICULE_LIB_H    
#define IDENTIFIER_TYPE_VEHICULE_LIB_H    

int identifierTypeVehicule(MYSQL *conn, int typeVehicule);
int verifTypeVehicule(MYSQL *conn, char* libTypeVehicule);

#endif 