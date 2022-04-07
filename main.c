#include <stdio.h>
#include <mysql.h>

#include "./libs/headers/menu.h"
#include "./libs/headers/dbConnect.h"

int main(int argc, char **argv)
{
	//Initialisation de l'objet de connexion
	MYSQL *conn = mysql_init(NULL);
	//COnnexion à la base de données
	connectToDatabase(conn);

	menu(conn);
}