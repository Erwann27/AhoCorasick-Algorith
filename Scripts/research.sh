#!/bin/bash
LANG=C
TIMEFORMAT=%R
result=result.txt
for j in 2 4 20 70
do
y=../Texts/texts_5000000_$j.txt
file=../Texts/words_100_5_15_$j.txt
echo "mat :" >> $result
(time ../ac-matrice $file $y) 2>> $result

done