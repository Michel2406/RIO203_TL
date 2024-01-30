#include "writeData.h"
#include <stdio.h>
#include <stdlib.h>

void updateColorData(const char *filename, const JsonData *jsonData) {
    // Ouvrir le fichier en mode écriture
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de %s pour écriture.\n", filename);
        return;
    }

    // Écrire le contenu JSON dans le fichier
    fprintf(file, "{\n");
    fprintf(file, "  \"couleur\": \"%s\",\n", jsonData->color);
    fprintf(file, "  \"number\": \"%d\"\n", jsonData->tl_ID);
    fprintf(file, "}\n");

    // Fermer le fichier
    fclose(file);
}

void updateGPSData(const char *filename, const JsonData *jsonData) {
    // Ouvrir le fichier en mode écriture
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de %s pour écriture.\n", filename);
        return;
    }

    // Écrire le contenu JSON dans le fichier
    fprintf(file, "{\n");
    fprintf(file, "  \"latitude\": %f,\n", jsonData->latitude);
    fprintf(file, "  \"longitude\": %f\n", jsonData->longitude);
    fprintf(file, "}\n");

    // Fermer le fichier
    fclose(file);
}

