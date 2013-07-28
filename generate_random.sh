FILE="bin/random.txt"

rm -f $FILE

for i in {1..1000000} 
do
    echo $RANDOM >> $FILE
done