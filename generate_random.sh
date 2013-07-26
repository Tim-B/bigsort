FILE="bin/random.txt"

rm -f $FILE

for i in {1..50000} 
do
    echo $RANDOM >> $FILE
done