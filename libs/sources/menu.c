#include <stdio.h>
#include <mysql.h>


#include <Rinternals.h>
#include <Rembedded.h>

#include "../headers/menu.h"
#include "../headers/vehicule/facturerVehicule.h"
#include "../headers/vehicule/retrouverVehicule.h"
#include "../headers/vehicule/entreeNouveauVehicule.h"
#include "../headers/type_vehicule/recupListeTypeVehicule.h"
#include "../headers/type_vehicule/nombreDePlacesDisponibles.h"
#include "../headers/type_vehicule/afficherNombrePlacesDisponibles.h"


#include "../headers/R/tauxOccupation.h"

int menu(MYSQL *conn){

    

    // Intialize the R environment.
    int r_argc = 2;
    char *r_argv[] = { "R", "--silent" };
    Rf_initEmbeddedR(r_argc, r_argv);
    

    int choix;                                  

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("----------------------------------------------------------------\n\n");
    printf("                === BIENVENUE AU PARKING        ===             \n\n");

    while (1)
    {

        printf("----------------------------------------------------------------\n\n");
        printf("=> Veuillez choisir une option parmi les suivantes : \n\n");
        printf("=====> 1 - Enregistrer un nouveau véhicule \n");
        printf("=====> 2 - Voir les places disponibles \n");
        printf("=====> 3 - Retrouver un véhicule enregistré \n");
        printf("=====> 4 - Facturer un véhicule \n");
        printf("=====> 5 - Statistiques \n\n");
        printf("=====> 6 - Sortir de l'application \n\n");

        printf("=====> Choix : ");
        scanf("%d", &choix);

        if(choix == 1){
            menuNouveauVehicule(conn);
            continue;
        }else if(choix == 2){
            afficherNombrePlacesDisponibles(conn);
            continue;
        }else if(choix == 3){
            char immatVehicule[100];
            printf("Veuillez entrer votre numéro de plaque d'immatriculation : ");
            scanf("%s", &immatVehicule);
            retrouverVehicule(conn, immatVehicule, 0);
            continue;
        }else if(choix == 4){
            char immatVehicule[100];
            printf("Veuillez entrer votre numéro de plaque d'immatriculation : ");
            scanf("%s", &immatVehicule);
            facturerVehicule(conn, immatVehicule);
            continue;
        }else if(choix == 5){
            PrincR(conn);
            continue;
        }

        return 2;
    }
}

int menuNouveauVehicule(MYSQL *conn){
    //Permission de stationnement
    int permissionStationnement = 0;
    //Id du type de véhicule
    int typeVehicule = -1;
    //Plaque d'immatriculation
    char plaqueImmat[100];
    //Vérifier si des places sont disponibles
    int isPlacesDispo = 0;

    printf("\n\n =====> Enregistrer nouveau véhicule \n");
    printf("Voici les types de véhicules que nous prenons en charge : \n\n");

    //Affichage des types de véhicules présents en base de données
    listVehiculePrisEnCharge(conn);

    while (1)
    {
        printf("\nVeuiller choisir un type de véhicule en fonction de son numéro : ");
        scanf("%d", &typeVehicule);

        if(typeVehicule == 1 || typeVehicule == 2 || typeVehicule == 3){
            break;
        }else{
            printf("\n Veuillez faire un choix correct.");
        }
    }

    isPlacesDispo = nombresPlacesDispo(conn, typeVehicule);
    if(isPlacesDispo){
        printf("\n=====> Des places sont disponibles !");
    }else{
        printf("\n====> Aucune place disponible pour votre véhicule");
    }
    
    printf("\nVeuillez renseinger la plaque d'immatriculation de votre véhicule : ");
    scanf("%s", &plaqueImmat);

    entreeNouveauVehicule(conn, typeVehicule, plaqueImmat);

    return 0;
}