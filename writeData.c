#include "writeData.h"
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

// Fonction pour mettre à jour la couleur du feu dans le fichier JSON
void updateColorData(FILE *file, const JsonData *jsonData) {
    fprintf(file, "{\"couleurFeu\":\"%s\"}\n", jsonData->couleurFeu);
}

// Fonction pour mettre à jour la localisation GPS dans le fichier JSON
void updateGPSData(FILE *file, const JsonData *jsonData) {
    fprintf(file, "{\"latitude\":%f,\"longitude\":%f}\n", jsonData->latitude, jsonData->longitude);
}

void writeData(const char *filename, const char *updateType, const JsonData *jsonData) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        // Initialisation de la structure de données JSON
        JsonData defaultData;
        memset(&defaultData, 0, sizeof(JsonData));

        // Utilisation des fonctions appropriées en fonction du type de mise à jour
        if (strcmp(updateType, "feu") == 0) {
            updateColorData(file, jsonData);
        } else if (strcmp(updateType, "gps") == 0) {
            updateGPSData(file, jsonData);
        } else {
            fprintf(stderr, "Type de mise à jour non reconnu.\n");
            // Utilisez la fonction appropriée pour une mise à jour par défaut
            updateGPSData(file, &defaultData);
        }

        fclose(file);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s pour écriture.\n", filename);
    }
}

