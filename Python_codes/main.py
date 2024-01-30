import time
import send

def main():
    while True:
        # Lire les données depuis les fichiers JSON
        gps_leds_data = send.read_json("../gps.json")
        led_data = send.read_json("../color.json")

        # Insérer les données dans la base de données
        if gps_leds_data:
            print(gps_leds_data)
            send.insert_gps_leds_data(gps_leds_data)
        if led_data:
            print(led_data)
            send.insert_led_data(led_data)

        # Attendre pendant un certain temps avant la prochaine itération
        time.sleep(3)  # Attendre 5 secondes (ajustez selon vos besoins)

if __name__ == "__main__":
    main()
