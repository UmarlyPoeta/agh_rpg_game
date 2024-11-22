#!/bin/zsh

# Ścieżki do plików
SOURCE_FILE="/home/umarly-poeta/projects/agh_rpg/main.cpp"
OUTPUT_FILE="/home/umarly-poeta/projects/agh_rpg/main"

# Kompilacja
echo "Kompilowanie pliku $SOURCE_FILE..."
g++ -o $OUTPUT_FILE $SOURCE_FILE -lsfml-graphics -lsfml-window -lsfml-system

# Sprawdzenie, czy kompilacja się powiodła
if [ $? -eq 0 ]; then
    echo "Kompilacja zakończona sukcesem."
    echo "Uruchamianie programu..."
    $OUTPUT_FILE
else
    echo "Błąd podczas kompilacji."
fi