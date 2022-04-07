
#include <stdio.h>
#include <string.h>
#include <mysql.h>

#include <Rinternals.h>
#include <Rembedded.h>

#include "../../headers/R/tauxOccupation.h"

void source(const char *name)
{
    SEXP e;

    PROTECT(e = lang2(install("source"), mkString(name)));
    R_tryEval(e, R_GlobalEnv, NULL);
    UNPROTECT(1);
}


void R_tauxOccupation(int alen, int a[])
{
    // Allocate an R vector and copy the C array into it.
    SEXP arg;
    PROTECT(arg = allocVector(INTSXP, alen));
    memcpy(INTEGER(arg), a, alen * sizeof(int));

    // Setup a call to the R function
    SEXP add1_call;
    PROTECT(add1_call = lang2(install("tauxOccupation"), arg));

    // Execute the function
    int errorOccurred;
    SEXP ret = R_tryEval(add1_call, R_GlobalEnv, &errorOccurred);

    if (!errorOccurred)
    {
        double *val = REAL(ret);
        printf("Le pourcentage d'occupation des place est de %0.1f %;", val[0]);
    }
    else
    {
        printf("Error occurred calling R\n");
    }
    
    UNPROTECT(2);
}

void PrincR(MYSQL *conn)
{
    //Récuperation du nombre de places au total
    char sql[500] = "SELECT SUM(nbrDispo) FROM type_vehicule;";

    //SQL nombre de places occupees
    char sql1[200] = "SELECT COUNT(id) FROM vehicule WHERE dateArrivee = dateFin;";
    
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
    int nombresPlacesTotal = atoi(row[0]);

    /* --------------------------------------------- */

    if(mysql_query(conn, sql1)){
        printf("Erreur: %s\r\n", mysql_error(conn));
    }
    result = mysql_store_result(conn);
    if (result == NULL)
    {
        printf("error: %s\r\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    num_fields = mysql_num_fields(result);
    row = mysql_fetch_row(result);
    int nombresPlacesEnUsage = atoi(row[0]);


    int arg[] = { nombresPlacesEnUsage, 100};

    // Invoke a function in R
    source("calculOcc.R");
    R_tauxOccupation(2, arg);

    // Release R environment
    Rf_endEmbeddedR(0);
    return(0);
}
