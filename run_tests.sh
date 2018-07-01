#! /bin/bash

make

for i in $(seq 1 100); do
	echo ""
    echo ""
	echo "input${i}.txt";
	echo ""
	echo "tp3fb"
	./tp3fb < ./samples/generated/input${i}.txt > ./out_tp3fb.txt
	echo ""
	echo "tp3h"
	./tp3h < ./samples/generated/input${i}.txt > ./out_tp3h.txt
	echo ""
    diff <(head -1 ./out_tp3fb.txt) <(head -1 ./out_tp3h.txt)
    echo ""
done
