import mysql.connector
import json


def read_json(nom_fichier):
    try:
        with open(nom_fichier, 'r') as fichier:
            donnees_json = json.load(fichier)
            return donnees_json[0]
    except FileNotFoundError:
        print(f"Le fichier {nom_fichier} n'a pas été trouvé.")
        return None
    except json.JSONDecodeError:
        print(f"Erreur lors du décodage JSON dans le fichier {nom_fichier}.")
        return None

def insert_gps_user_data(gps_user_data):
    # Paramètres de connexion à la base de données MySQL
    conn_params = {
        'host': 'localhost',
        'user': 'root',
        'password': 'rio203',
        'database': 'rio',
        'auth_plugin': 'rio203'
    }

    # Connexion à la base de données
    conn = mysql.connector.connect(**conn_params)
    cursor = conn.cursor()

    # Insertion de données dans la table "GSP_user"
    insert_query = "INSERT INTO GSP_user ( latitude, longitude) VALUES (%s, %s)"
    cursor.execute(insert_query, ( gps_user_data['latitude'], gps_user_data['longitude']))

    # Commit des modifications
    conn.commit()

    # Fermeture de la connexion
    cursor.close()
    conn.close()


