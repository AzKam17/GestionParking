
cmake_minimum_required(VERSION 3.10.2)
project(GestionParking2 C)

set(CMAKE_C_STANDARD 99)
include(FindPkgConfig)


find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})


find_package(PkgConfig REQUIRED)
pkg_check_modules(R REQUIRED libR)
include_directories(${R_INCLUDE_DIRS})
link_directories(${R_LIBRARY_DIRS})
add_definitions(${R_CFLAGS_OTHER})

pkg_check_modules(LIBMYSQLCLIENT REQUIRED mysqlclient)

foreach(FLAG ${LIBMYSQLCLIENT_CFLAGS_OTHER})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
endforeach()

link_directories(${LIBMYSQLCLIENT_LIBRARY_DIRS})

set(SOURCES 
    libs/sources/menu.c 
    libs/sources/dbConnect.c
    libs/sources/type_vehicule/libererPlaceParking.c
    libs/sources/type_vehicule/identifierTypeVehicule.c
    libs/sources/type_vehicule/recupListeTypeVehicule.c
    libs/sources/type_vehicule/nombreDePlacesDisponibles.c
    libs/sources/type_vehicule/afficherNombrePlacesDisponibles.c
    
    libs/sources/vehicule/facturerVehicule.c
    libs/sources/vehicule/retrouverVehicule.c
    libs/sources/vehicule/calculPrixParking.c
    libs/sources/vehicule/sortirVehicule.c
    libs/sources/vehicule/entreeNouveauVehicule.c


    libs/sources/R/tauxOccupation.c
)
add_executable(GestionParking2 main.c ${SOURCES})
target_include_directories(GestionParking2 PRIVATE ${YOUR_DIRECTORY})
target_include_directories(GestionParking2 PRIVATE ${LIBMYSQLCLIENT_INCLUDE_DIRS})
target_link_libraries(GestionParking2 PRIVATE ${LIBMYSQLCLIENT_LIBRARIES} ${GTK3_LIBRARIES} ${R_LIBRARIES})
