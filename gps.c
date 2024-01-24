#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "writeData.h"

#define GPS_SERIAL_PORT "/dev/ttyAMA0"  // Emplacement du port série UART sur la Raspberry Pi

int main(void) {
    // Initialisation de la bibliothèque WiringPi
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Erreur lors de l'initialisation de WiringPi.\n");
        return 1;
    }

    // Ouverture du port série pour le GPS
    int gpsSerial = serialOpen(GPS_SERIAL_PORT, 9600);
    if (gpsSerial == -1) {
        fprintf(stderr, "Erreur lors de l'ouverture du port série GPS.\n");
        return 1;
    }

    // Allocation dynamique pour la structure JsonData
    JsonData *gpsData = malloc(sizeof(JsonData));
    if (gpsData == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour JsonData.\n");
        return 1;
    }

    // Boucle pour lire les données GPS
    while (1) {
        // Attendre jusqu'à ce qu'il y ait des données disponibles sur le port série
        while (serialDataAvail(gpsSerial) == 0) {
            delay(100);
        }

        // Lire une ligne de données GPS depuis le port série
        char gpsBuffer[256];
        int bytesRead = serialGets(gpsSerial, gpsBuffer, sizeof(gpsBuffer));

        if (bytesRead > 0) {
            // Analyser les données GPS (à remplacer par votre propre logique d'analyse)
            sscanf(gpsBuffer, "$GPGGA,%lf,%lf", &gpsData->latitude, &gpsData->longitude);

            // Appel de la fonction pour écrire les données dans le fichier
            writeData("data.json", "gps", gpsData);
        }
    }

    // Libération de la mémoire allouée pour la structure JsonData (notez que cela ne sera jamais atteint dans la boucle infinie)
    free(gpsData);

    // Fermeture du port série
    serialClose(gpsSerial);

    return 0;
}
