#include "writeData.h"


void updateColorData(FILE *file, const JsonData *jsonData) {
    // Lire le contenu actuel de data.json et stocker dans un buffer
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le buffer.\n");
        return;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    // Fermer le fichier
    fclose(file);

    // Ouvrir le fichier en mode écriture (effacer son contenu)
    file = fopen("data.json", "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de data.json pour écriture.\n");
        free(buffer);
        return;
    }

    // Écrire le contenu actuel du fichier dans le nouveau fichier
    fprintf(file, "%s", buffer);

    // Ajouter la nouvelle ligne de couleur dans le fichier
    fprintf(file, "{\"couleurFeu\":\"%s\"}\n", jsonData->color);

    // Fermer le fichier et libérer le buffer
    fclose(file);
    free(buffer);
}

// Fonction pour mettre à jour la localisation GPS dans le fichier JSON
void updateGPSData(FILE *file, const JsonData *jsonData) {
    fprintf(file, "{\n\t\"latitude\":%f,\n\t\"longitude\":%f\n}", jsonData->latitude, jsonData->longitude);
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

