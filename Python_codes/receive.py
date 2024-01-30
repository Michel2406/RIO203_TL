import mysql.connector
import time

# Paramètres de connexion à la base de données MySQL
conn_params = {
    'host': '192.168.96.55',
    'user': 'root',
    'password': 'rio203',
    'database': 'rio',
}

def check_attribute_value():
    # Connexion à la base de données
    conn = mysql.connector.connect(**conn_params)
    cursor = conn.cursor()

    # Commande SQL pour sélectionner la valeur de l'attribut de la ligne spécifique
    select_query = "SELECT * FROM User_Demand"
    cursor.execute(select_query)  # Remplacez 1 par l'ID de la ligne que vous souhaitez vérifier

    # Récupérer la valeur de l'attribut
    result = cursor.fetchone()
    if result:
        print(f"La valeur de l'attribut 'demand' est : {result[0]}")
    else:
        print("L'ID de la ligne spécifiée n'existe pas dans la table LED.")

    # Fermeture de la connexion
    cursor.close()
    conn.close()

# Boucle infinie pour vérifier périodiquement la valeur de l'attribut
while True:
    check_attribute_value()
    time.sleep(5)  # Pause de 5 secondes avant la prochaine vérification
