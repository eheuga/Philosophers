#!/bin/bash
# Script de test pour philosophers
# Usage: ./test.sh

BIN=./philo
GREEN='\033[0;32m'; RED='\033[0;31m'; YEL='\033[1;33m'; NC='\033[0m'

run_timeout() {
    # $1 = durée max en secondes, $2... = args
    timeout "$@" 2>&1
}

echo "=== Tests philosophers ==="

# 1. Philo seul : doit mourir (1 fourchette)
echo -e "${YEL}[1] ./philo 1 800 200 200 (doit mourir ~800, s'arrêter)${NC}"
out=$(run_timeout 3 $BIN 1 800 200 200)
echo "$out" | tail -n 2
echo "$out" | grep -q "died" && echo -e "${GREEN}-> 'died' présent OK${NC}" || echo -e "${RED}-> pas de 'died' KO${NC}"

# 2. Personne ne meurt : doit tourner (timeout = normal)
echo -e "${YEL}[2] ./philo 4 410 200 200 (personne ne meurt, doit tourner 3s)${NC}"
out=$(run_timeout 3 $BIN 4 410 200 200)
echo "$out" | grep -q "died" && echo -e "${RED}-> 'died' inattendu KO${NC}" || echo -e "${GREEN}-> aucun 'died' OK (tourne bien)${NC}"

# 3. Mort attendue rapidement
echo -e "${YEL}[3] ./philo 4 310 200 100 (qqn doit mourir)${NC}"
out=$(run_timeout 3 $BIN 4 310 200 100)
echo "$out" | tail -n 1
last=$(echo "$out" | tail -n 1)
echo "$last" | grep -q "died" && echo -e "${GREEN}-> 'died' en dernière ligne OK${NC}" || echo -e "${RED}-> 'died' pas en dernière ligne KO${NC}"

# 4. Mort rapide, marge nulle (lancé 5x pour la concurrence)
echo -e "${YEL}[4] ./philo 5 100 100 100 x5 (died doit être la dernière ligne à chaque fois)${NC}"
for n in 1 2 3 4 5; do
    out=$(run_timeout 3 $BIN 5 100 100 100)
    last=$(echo "$out" | tail -n 1)
    if echo "$last" | grep -q "died"; then
        echo -e "  run $n: ${GREEN}OK${NC} ($last)"
    else
        echo -e "  run $n: ${RED}KO -> ligne après died !${NC} ($last)"
    fi
done

# 5. Quota de repas : doit s'arrêter SANS died
echo -e "${YEL}[5] ./philo 5 800 200 200 3 (tous mangent 3x, arrêt SANS died)${NC}"
out=$(run_timeout 5 $BIN 5 800 200 200 3)
echo "$out" | grep -q "died" && echo -e "${RED}-> 'died' inattendu KO${NC}" || echo -e "${GREEN}-> aucun 'died', arrêt propre OK${NC}"

# 6. Valgrind (fuites mémoire) - sur un cas qui se termine
echo -e "${YEL}[6] valgrind ./philo 4 310 200 100 (fuites mémoire)${NC}"
if command -v valgrind >/dev/null 2>&1; then
    vg=$(valgrind --leak-check=full --error-exitcode=42 timeout 3 $BIN 4 310 200 100 2>&1)
    echo "$vg" | grep -q "no leaks are possible\|All heap blocks were freed" && echo -e "${GREEN}-> pas de fuite OK${NC}" || echo -e "${RED}-> fuites détectées (voir détail) KO${NC}"
    echo "$vg" | grep "definitely lost\|indirectly lost" | head -n 3
else
    echo "valgrind non installé, test sauté"
fi

echo "=== Fin des tests ==="