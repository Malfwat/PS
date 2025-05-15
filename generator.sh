#!/bin/bash

# Vérifie qu’un argument est fourni
if [ -z "$1" ]; then
    echo "Usage: $0 <nombre_de_tests>"
    exit 1
fi

# Vérifie que c’est un entier strictement positif
if ! [[ "$1" =~ ^[0-9]+$ && "$1" -gt 0 ]]; then
    echo "Erreur : '$1' n’est pas un entier positif."
    exit 1
fi

N=$1
total=0
tests_done=0

make all

for ((i = 1; i <= N; i++)); do
    echo "===== Test $i/$N ====="

    # Génère 500 nombres aléatoires uniques entre 0 et 700
    ARG=$(shuf -i 0-700 -n 50 | tr '\n' ' ')
	echo $ARG > tmp
    # Exécute push_swap
    CMD=$(./push_swap $ARG)

    # Vérifie avec checker_linux
    RESULTT=$(echo "$CMD" | ./checker $ARG)
    echo "$RESULTT <- checker"

    RESULT=$(echo "$CMD" | ./checker_linux $ARG)
    echo "$RESULT <- checker_linux"

    if [[ "$RESULT" == "KO" ]]; then
        echo "❌ Erreur : push_swap n’a pas correctement trié la liste."
        echo "Arrêt du test."
        exit 1
    fi

    VALUE=$(echo "$CMD" | wc -l)
    echo "Nombre d'opérations : $VALUE"
    ((total += VALUE))
    ((tests_done++))
    echo
done

echo "===== Résultat final ====="
echo "Tests réussis : $tests_done/$N"
echo "Total des opérations : $total"
echo "Moyenne des opérations : $((total / tests_done))"

