import time
from write_data import read_json, insert_gps_leds_data, insert_led_data

def main():
    gps_leds_data_file = "gps_leds_data.json"
    led_data_file = "led_data.json"

    while True:
        # Lire les données depuis les fichiers JSON
        gps_leds_data = read_json(gps_leds_data_file)
        led_data = read_json(led_data_file)

        # Insérer les données dans la base de données
        if gps_leds_data:
            insert_gps_leds_data(gps_leds_data)
        if led_data:
            insert_led_data(led_data)

        # Attendre pendant un certain temps avant la prochaine itération
        time.sleep(5)  # Attendre 5 secondes (ajustez selon vos besoins)

if __name__ == "__main__":
    main()
