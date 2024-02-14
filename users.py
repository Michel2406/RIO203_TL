import mysql.connector

# Paramètres de connexion à la base de données MySQL
conn_params = {
    'host': '192.168.126.55',
    'user': 'root',
    'password': 'rio203',
    'database': 'rio',
}

def get_user_data():
    try:
        # Connexion à la base de données
        print("Connexion à la base de données...")
        conn = mysql.connector.connect(**conn_params)
        cursor = conn.cursor()
        print("Connexion réussie")

        # Commande SQL pour sélectionner des données d'un utilisateur spécifique
        select_query = "SELECT longitude, firstname FROM State WHERE id = %s"
        user_id = int(input("Entrez l'ID de l'utilisateur : "))
        cursor.execute(select_query, (user_id,))

        # Récupérer les données de l'utilisateur
        user_data = cursor.fetchone()

        if user_data:
            print(f"Données de l'utilisateur : {user_data}")
        else:
            print(f"L'utilisateur avec l'ID {user_id} n'a pas été trouvé.")

    except mysql.connector.Error as err:
        print(f"Erreur MySQL : {err}")
    finally:
        # Fermeture de la connexion
        if 'conn' in locals() and conn.is_connected():
            cursor.close()
            conn.close()
            print("Connexion fermée")

# Exécute la fonction pour récupérer les données de l'utilisateur
while(True):
    get_user_data()

