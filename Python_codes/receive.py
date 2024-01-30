import mysql.connector
import time
import json

# Paramètres de connexion à la base de données MySQL
conn_params = {
    'host': '192.168.96.55',
    'user': 'root',
    'password': 'rio203',
    'database': 'rio',
}

def check_attribute_value_and_write_to_json():
    # Connexion à la base de données
    conn = mysql.connector.connect(**conn_params)
    cursor = conn.cursor()

    # Commande SQL pour sélectionner tous les attributs de toutes les lignes
    select_query = "SELECT * FROM User_Demand"
    cursor.execute(select_query)

    # Récupérer toutes les lignes
    results = cursor.fetchall()

    # Construire une liste de dictionnaires pour chaque ligne
    data_to_write = []
    for result in results:
        data_to_write.append({'ID': result[0], 'demand': result[1]})

    # Fermeture de la connexion
    cursor.close()
    conn.close()

    # Écrire les données dans un fichier JSON
    with open('output.json', 'w') as json_file:
        json.dump(data_to_write, json_file, indent=2)

# Boucle infinie pour vérifier périodiquement la valeur de l'attribut et écrire dans un fichier JSON
while True:
    check_attribute_value_and_write_to_json()
    time.sleep(5)  # Pause de 5 secondes avant la prochaine vérification
