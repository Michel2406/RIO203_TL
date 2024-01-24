#include "writeData.h"
#include <stdio.h>
#include <string.h>

//Fonction pour mettre à jour la couleur du feu
void updateColorData(FILE *file, const JsonData *jsonData) {
    // Ouvrir le fichier en mode lecture
    FILE *tempFile = fopen("temp.json", "w");

    if (tempFile == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier temporaire pour écriture.\n");
        return;
    }

    // Lire le fichier original et copier son contenu dans le fichier temporaire
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        fputs(buffer, tempFile);
    }

    // Rembobiner le fichier original à la position de début
    rewind(file);

    // Écrire la nouvelle ligne de couleur dans le fichier temporaire
    fprintf(tempFile, "{\"couleurFeu\":\"%s\"}\n", jsonData->color);

    // Copier le reste du fichier original après la nouvelle ligne
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        fputs(buffer, tempFile);
    }

    // Fermer les fichiers
    fclose(file);
    fclose(tempFile);

    // Renommer le fichier temporaire pour écraser l'original
    rename("temp.json", "data.json");
}

// Fonction pour mettre à jour la localisation GPS dans le fichier JSON
void updateGPSData(FILE *file, const JsonData *jsonData) {
    fprintf(file, "{\"latitude\":%f,\"longitude\":%f}\n", jsonData->latitude, jsonData->longitude);
}

void writeData(const char *filename, const char *updateType, JsonData *jsonData) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        // Initialisation de la structure de données JSON
        JsonData defaultData;
        memset(&defaultData, 0, sizeof(JsonData));

        // Utilisation des fonctions appropriées en fonction du type de mise à jour
        if (strcmp(updateType, "color") == 0) {
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

