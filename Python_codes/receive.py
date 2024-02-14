import mysql.connector
import time
import json

# Paramètres de connexion à la base de données MySQL
conn_params = {
    'host': '192.168.126.55',
    'user': 'root',
    'password': 'rio203',
    'database': 'rio',
}

def check_attribute_value_and_write_to_json():
    # Connexion à la base de données
    print("Connection a la base de donnee...")
    conn = mysql.connector.connect(**conn_params)
    cursor = conn.cursor()
    print("Connection reussie")


    # Commande SQL pour sélectionner tous les attributs de toutes les lignes
    select_query = "SELECT * FROM User_Demand"
    cursor.execute(select_query)

    # Récupérer toutes les lignes
    result = cursor.fetchall()

    # Fermeture de la connexion
    cursor.close()
    conn.close()

    print("Ecriture dans le fichier output.txt")
    print(result)
    # Écrire les données dans un fichier JSON
    with open('../output.txt', 'w') as file:
        if result:
            file.write(str(result[len(result) - 1][0]))
        else:
            file.write("L'ID de la ligne n'existe pas")
        

# Boucle infinie pour vérifier périodiquement la valeur de l'attribut et écrire dans un fichier JSON
while True:
    check_attribute_value_and_write_to_json()
    time.sleep(5)  # Pause de 5 secondes avant la prochaine vérification
