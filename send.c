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
        // Données JSON à envoyer
        const char *postData = {"temperature": "36","lumiere": "42"};

        // Appel de la fonction pour effectuer la requête POST
        performPostRequest(curl, "http://192.168.251.55:9090/api/v1/zEKH1U9te4RBoOeFwwUU/telemetry", postData);

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