#!/bin/bash

for j in 2 4 20 70
do
    ../Gen/genere-texte 500000 $j > ../Texts/texts_500000_$j.txt
    ../Gen/genere-mots 100 5 15 $j > ../Texts/words_100_5_15_$j.txt
    ../Gen/genere-mots 100 15 30 $j > ../Texts/words_100_15_30_$j.txt
    ../Gen/genere-mots 100 30 60 $j > ../Texts/words_100_30_60_$j.txt
done