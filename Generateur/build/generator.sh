#!/bin/bash

for j in 2 4 20 70
do
    ./build/text_generator 500000 $j > ./Texts/text_$j.txt
    for i in 4 5 6 7 8 9 10 15 20 30 40 50
    do
        ./build/word_generator 100 $i $j > ./Texts/word_$i._$j.txt
    done
done