#! /bin/bash

echo "Heurística"
for test in $(seq 1 10); do
    echo "---------------------------------------------------"
    echo "entrada$test"
    time ./tp3h < ./samples/TesteHeuristica/entrada${test}.txt > /dev/null
    diff ./rodada.txt ./samples/TesteHeuristica/rodada${test}.txt
    echo "---------------------------------------------------"
    echo ""
done

echo "Força bruta"
for test in $(seq 1 26); do
    echo "---------------------------------------------------"
    echo "exemplo $test"
    time ./tp3fb < ./samples/exemplos/entrada/entrada${test}.txt > /dev/null
    diff ./rodada.txt ./samples/exemplos/saida/rodada${test}.txt
    echo "---------------------------------------------------"
    echo ""
done