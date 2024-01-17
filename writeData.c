#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "writeData.h"

// Structure pour représenter les données à écrire dans le fichier JSON
typedef struct {
    double latitude;
    double longitude;
    char couleurFeu[20];  // Choisir la taille en fonction de vos besoins
} JsonData;

void writeData(const char *filename, const char *updateType, const JsonData *jsonData) {
    // Ouverture du fichier en mode d'écriture
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        // Détermination du type de mise à jour
        if (strcmp(updateType, "feu") == 0) {
            // Écriture des données pour la mise à jour de la couleur du feu
            fprintf(file, "{\"couleurFeu\":\"%s\"}\n", jsonData->couleurFeu);
        } else if (strcmp(updateType, "gps") == 0) {
            // Écriture des données pour la mise à jour de la localisation GPS
            fprintf(file, "{\"latitude\":%f,\"longitude\":%f}\n", jsonData->latitude, jsonData->longitude);
        } else {
            fprintf(stderr, "Type de mise à jour non reconnu.\n");
        }

        // Fermeture du fichier
        fclose(file);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s pour écriture.\n", filename);
    }
}

