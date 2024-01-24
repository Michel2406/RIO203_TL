#include "writeData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

// Fonction pour mettre à jour la couleur du feu dans le fichier JSON
void updateColorData(const char *filename, const JsonData *jsonData) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s pour lecture.\n", filename);
        return;
    }

    // Charger le contenu JSON du fichier
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le buffer.\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    // Fermer le fichier
    fclose(file);

    // Charger le contenu dans un objet cJSON
    cJSON *root = cJSON_Parse(buffer);
    free(buffer);

    if (root == NULL) {
        fprintf(stderr, "Erreur lors de l'analyse du fichier JSON.\n");
        return;
    }

    // Mettre à jour la couleur du feu
    cJSON *colorItem = cJSON_GetObjectItemCaseSensitive(root, "couleurFeu");
    if (colorItem == NULL) {
        fprintf(stderr, "Le fichier JSON ne contient pas de champ 'couleurFeu'.\n");
        cJSON_Delete(root);
        return;
    }

    cJSON_SetValuestring(colorItem, jsonData->color);

    // Ouvrir le fichier en mode écriture (effacer son contenu)
    file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de %s pour écriture.\n", filename);
        cJSON_Delete(root);
        return;
    }

    // Écrire le contenu mis à jour dans le fichier
    char *updatedContent = cJSON_Print(root);
    fprintf(file, "%s\n", updatedContent);

    // Fermer le fichier, libérer la mémoire et détruire l'objet cJSON
    fclose(file);
    free(updatedContent);
    cJSON_Delete(root);
}

// Fonction pour mettre à jour la localisation GPS dans le fichier JSON
void updateGPSData(const char *filename, const JsonData *jsonData) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s pour lecture.\n", filename);
        return;
    }

    // Charger le contenu JSON du fichier
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le buffer.\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    // Fermer le fichier
    fclose(file);

    // Charger le contenu dans un objet cJSON
    cJSON *root = cJSON_Parse(buffer);
    free(buffer);

    if (root == NULL) {
        fprintf(stderr, "Erreur lors de l'analyse du fichier JSON.\n");
        return;
    }

    // Mettre à jour la localisation GPS
    cJSON *latitudeItem = cJSON_GetObjectItemCaseSensitive(root, "latitude");
    cJSON *longitudeItem = cJSON_GetObjectItemCaseSensitive(root, "longitude");

    if (latitudeItem == NULL || longitudeItem == NULL) {
        fprintf(stderr, "Le fichier JSON ne contient pas les champs 'latitude' et 'longitude'.\n");
        cJSON_Delete(root);
        return;
    }

    cJSON_SetValueNumber(latitudeItem, jsonData->latitude);
    cJSON_SetValueNumber(longitudeItem, jsonData->longitude);

    // Ouvrir le fichier en mode écriture (effacer son contenu)
    file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de %s pour écriture.\n", filename);
        cJSON_Delete(root);
        return;
    }

    // Écrire le contenu mis à jour dans le fichier
    char *updatedContent = cJSON_Print(root);
    fprintf(file, "%s\n", updatedContent);

    // Fermer le fichier, libérer la mémoire et détruire l'objet cJSON
    fclose(file);
    free(updatedContent);
    cJSON_Delete(root);
}
