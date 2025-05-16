#!/bin/bash

# Vérifie qu’un argument est fourni
if [ -z "$1" ]; then
    echo "Usage: $0 <nombre_de_tests> [taille_de_la_pile (défaut: 50)]"
    exit 1
fi

# Vérifie que c’est un entier strictement positif
if ! [[ "$1" =~ ^[0-9]+$ && "$1" -gt 0 ]]; then
    echo "Erreur : '$1' n’est pas un entier positif."
    exit 1
fi

N=$1
PILE_SIZE=${2:-50} # Par défaut 50 si pas précisé
MAX_VAL=700        # Plage de nombres aléatoires : 0 à MAX_VAL

# Vérifie que la taille de la pile est un entier positif <= MAX_VAL + 1
if ! [[ "$PILE_SIZE" =~ ^[0-9]+$ && "$PILE_SIZE" -gt 0 && "$PILE_SIZE" -le $((MAX_VAL + 1)) ]]; then
    echo "Erreur : la taille de la pile doit être un entier entre 1 et $((MAX_VAL + 1))."
    exit 1
fi

total=0
tests_done=0

make all

for ((i = 1; i <= N; i++)); do
    echo "===== Test $i/$N (taille: $PILE_SIZE) ====="

    # Génère des nombres aléatoires uniques
    ARG=$(shuf -i 0-$MAX_VAL -n $PILE_SIZE | tr '\n' ' ')
    echo $ARG > tmp

    # Exécute push_swap
    CMD=$(./push_swap $ARG)

    # Vérifie avec checker
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

