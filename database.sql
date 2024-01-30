-- Table pour "rio203"
CREATE TABLE rio203 (
    id INT PRIMARY KEY,
    latitude DECIMAL(10, 8),
    longitude DECIMAL(11, 8)
);

-- Table pour "GPS_leds"
CREATE TABLE GPS_leds (
    id INT PRIMARY KEY,
    latitude DECIMAL(10, 8),
    longitude DECIMAL(11, 8)
);

-- Table pour "GSP_user"
CREATE TABLE GSP_user (
    id INT PRIMARY KEY,
    latitude DECIMAL(10, 8),
    longitude DECIMAL(11, 8)
);

-- Table pour "LED"
CREATE TABLE LED (
    id INT PRIMARY KEY,
    couleur VARCHAR(255),
    etat VARCHAR(255)
);

-- Table pour "Users"
CREATE TABLE Users (
    id INT PRIMARY KEY,
    name VARCHAR(255),
    firstname VARCHAR(255),
    password VARCHAR(255)
);
