#include <stdio.h>
#include <curl/curl.h>

size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userdata);

int main(void) {
    CURL *curl;

    // Initialisation de libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Création de l'objet CURL
    curl = curl_easy_init();
    if(curl) {
        // Ouverture du fichier data.json
        FILE *file = fopen("data.json", "r");
        if (!file) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier data.json\n");
            return 1;
        }

        // Appel de la fonction pour effectuer la requête POST avec le contenu du fichier
        performPostRequest(curl, "http://192.168.251.55:9090/api/v1/zEKH1U9te4RBoOeFwwUU/telemetry", file);

        // Fermeture du fichier
        fclose(file);

        // Libération des ressources CURL
        curl_easy_cleanup(curl);
    }

    // Libération des ressources globales de libcurl
    curl_global_cleanup();

    return 0;
}

// Fonction pour effectuer une requête POST avec CURL en utilisant le contenu du fichier
void performPostRequest(CURL *curl, const char *url, FILE *file) {
    CURLcode res;

    // URL de la requête POST
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Spécification du type de requête (POST)
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    // Spécification de la fonction de lecture du fichier
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, file);

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

// Fonction de rappel de lecture pour CURLOPT_READFUNCTION
size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    FILE *file = (FILE *)userdata;
    size_t retcode = fread(ptr, size, nmemb, file);
    return retcode;
}
