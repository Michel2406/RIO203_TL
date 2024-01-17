#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int writeData(char *filename, char *data) {
    // Ouvrir un fichier en écriture (écraser le contenu existant)
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Écrire dans le fichier
    size_t bytes_ecrits = fwrite(data, 1, strlen(data), file);

    if (bytes_ecrits != strlen(data)) {
        printf("Erreur lors de l'écriture dans le fichier");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Fermer le fichier après l'écriture
    fclose(file);

    return 0;
}


