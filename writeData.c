#include "writeData.h"
#include <stdio.h>
#include <string.h>

// Fonction pour mettre à jour la couleur du feu dans le fichier JSON
void updateColorData(const char *filename, const JsonData *jsonData) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s pour lecture.\n", filename);
        return;
    }

    // Lire le contenu actuel de data.json et stocker dans un buffer
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

    // Ouvrir le fichier en mode écriture (effacer son contenu)
    file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de %s pour écriture.\n", filename);
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
void updateGPSData(const char *filename, const JsonData *jsonData) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s pour lecture.\n", filename);
        return;
    }

    // Lire le contenu actuel de data.json et stocker dans un buffer
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

    // Ouvrir le fichier en mode écriture (effacer son contenu)
    file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de %s pour écriture.\n", filename);
        free(buffer);
        return;
    }

    // Écrire le contenu actuel du fichier dans le nouveau fichier
    fprintf(file, "%s", buffer);

    // Ajouter la nouvelle ligne de localisation GPS dans le fichier
    fprintf(file, "{\"latitude\":%f,\"longitude\":%f}\n", jsonData->latitude, jsonData->longitude);

    // Fermer le fichier et libérer le buffer
    fclose(file);
    free(buffer);
}


