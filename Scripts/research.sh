#!/bin/bash
LANG=C
TIMEFORMAT=%R
result=result.txt
for j in 2 4 20 70
do
y=../Texts/texts_5000000_$j.txt
file=../Texts/words_100_5_15_$j.txt
echo "mat 5 15 $j:" >> $result
(time ac-matrice $file $y) 2>> $result

file=../Texts/words_100_15_30_$j.txt
echo "mat 15 30 $j :" >> $result
(time ac-matrice $file $y) 2>> $result

file=../Texts/words_100_30_60_$j.txt
echo "mat 30 60 $j :" >> $result
(time ac-matrice $file $y) 2>> $result

file=../Texts/words_100_5_15_$j.txt
echo "hash 5 15 $j:" >> $result
(time ac-hachage $file $y) 2>> $result

file=../Texts/words_100_15_30_$j.txt
echo "hash 15 30 $j :" >> $result
(time ac-hachage $file $y) 2>> $result

file=../Texts/words_100_30_60_$j.txt
echo "hash 30 60 $j :" >> $result
(time ac-hachage $file $y) 2>> $result


done