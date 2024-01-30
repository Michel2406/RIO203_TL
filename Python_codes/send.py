import mysql.connector
import json
# Paramètres de connexion à la base de données MySQL
conn_params = {
    'host': '192.168.96.55',
    'user': 'root',
    'password': 'rio203',
    'database': 'rio',

}

def read_json(nom_fichier):
    try:
        with open(nom_fichier, 'r') as fichier:
            donnees_json = json.load(fichier)
            return donnees_json
    except FileNotFoundError:
        print(f"Le fichier {nom_fichier} n'a pas été trouvé.")
        return None
    except json.JSONDecodeError:
        print(f"Erreur lors du décodage JSON dans le fichier {nom_fichier}.")
        return None


def insert_led_data(led_data):

    # Connexion à la base de données
    conn = mysql.connector.connect(**conn_params)
    cursor = conn.cursor()

    # Commande SQL pour insérer ou mettre à jour la ligne
    insert_query = """
        INSERT INTO LED (id,number, couleur)
        VALUES (%s,%s, %s)
        ON DUPLICATE KEY UPDATE id = VALUES(id)
    """
    cursor.execute(insert_query, (1,led_data['number'], led_data['couleur']))

    # Commit des modifications
    conn.commit()

    # Fermeture de la connexion
    cursor.close()
    conn.close()

# Exemple d'utilisation de la fonction avec un objet JSON

def insert_gps_leds_data(gps_leds_data):
    # Connexion à la base de données
    conn = mysql.connector.connect(**conn_params)
    cursor = conn.cursor()

    # Insertion de données dans la table "GPS_leds"
    insert_query = "INSERT INTO GPS_leds (latitude, longitude) VALUES (%s, %s)"
    cursor.execute(insert_query, (gps_leds_data['latitude'], gps_leds_data['longitude']))

    # Commit des modifications
    conn.commit()

    # Fermeture de la connexion
    cursor.close()
    conn.close()

