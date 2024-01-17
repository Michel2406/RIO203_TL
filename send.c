#include <stdio.h>
#include <curl/curl.h>

void performPostRequest(CURL *curl, const char *url, const char *postData);

int main(void) {
    CURL *curl;

    // Initialisation de libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Création de l'objet CURL
    curl = curl_easy_init();
    if(curl) {
        // Lecture du contenu du fichier data.json
        FILE *file = fopen("data.json", "r");
        if (!file) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier data.json\n");
            return 1;
        }

        // Obtention de la taille du fichier
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Allocation d'un tampon pour stocker le contenu du fichier
        char *postData = (char *)malloc(size + 1);
        if (!postData) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
            fclose(file);
            return 1;
        }

        // Lecture du contenu du fichier dans le tampon
        fread(postData, 1, size, file);
        postData[size] = '\0';  // Ajout d'un caractère de fin de chaîne

        // Fermeture du fichier
        fclose(file);

        // Appel de la fonction pour effectuer la requête POST
        performPostRequest(curl, "http://192.168.251.55:9090/api/v1/zEKH1U9te4RBoOeFwwUU/telemetry", postData);

        // Libération de la mémoire allouée pour le tampon
        free(postData);

        // Libération des ressources CURL
        curl_easy_cleanup(curl);
    }

    // Libération des ressources globales de libcurl
    curl_global_cleanup();

    return 0;
}

// Fonction pour effectuer une requête POST avec CURL
void performPostRequest(CURL *curl, const char *url, const char *postData) {
    CURLcode res;

    // URL de la requête POST
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Spécification du type de requête (POST)
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    // Spécification du contenu JSON
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);

    // En-tête Content-Type
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Exécution de la requête
    res = curl_easy_perform(curl);

    // Vérification des erreurs
    if(res != CURLE_OK)
        fprintf(stderr, "Erreur curl : %s\n", curl_easy_strerror(res));

    // Libération des en-têtes
    curl_slist_free_all(headers);
}
