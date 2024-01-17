#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int writeData(char * filename, char * data) {
    // Ouvrir un fichier en écriture
    int file_descriptor = open(filename, O_CREAT | O_WRONLY |O_APPEND | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    // Écrire dans le fichier
    ssize_t bytes_ecrits = write(file_descriptor, data, strlen(data));

    if (bytes_ecrits == -1) {
        perror("Erreur lors de l'écriture dans le fichier");
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }
    // Fermer le fichier après l'écriture
    close(file_descriptor);

    return 0;
}
