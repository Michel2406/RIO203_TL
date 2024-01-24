#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "writeData.h"

int main(void) {
    // Initialisation des coordonnées GPS (valeurs fictives)
    double latitude = 37.7749;  // Exemple : San Francisco, CA
    double longitude = -122.4194;

    // Allocation dynamique pour la structure JsonData
    JsonData *gpsData = malloc(sizeof(JsonData));
    if (gpsData == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour JsonData.\n");
        return 1;
    }

    // Attribution des coordonnées GPS
    gpsData->latitude = latitude;
    gpsData->longitude = longitude;
    gpsData->color = NULL;  // Vous pouvez laisser color à NULL car il ne sera pas utilisé pour les coordonnées GPS

    // Appel de la fonction pour écrire les données dans le fichier
    writeData("data.json", "gps", gpsData);

    // Libération de la mémoire allouée pour la structure JsonData
    free(gpsData);

    return 0;
}
