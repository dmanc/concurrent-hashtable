NAME1=./data/coarse$1$2.txt
NAME2=./data/stm$1$2.txt
NAME3=./data/fine$1$2.txt

rm ./data/coarse$1$2.txt
rm ./data/stm$1$2.txt
rm ./data/fine$1$2.txt

c=$(($1+3))
echo $c

norm1=$(./bin/time --resize=$2 --amount=500000 | grep -A5 "Sequential" | sed "$c,$c!d" | awk '{print $NF}';)

echo $norm1

for x in {1,2,4,8,16}; do
    echo "$x threads"
    total=$(./bin/time --resize=$2 --workers=$x --amount=500000 | grep -A5 "Coarse" | sed "$c,$c!d" | awk '{print $NF}';)
    val=$(echo "scale=2 ; $norm1 / $total" | bc)
    echo "$val" >> $NAME1
    echo "$val"

    total=$(./bin/time --resize=$2 --workers=$x --amount=500000 | grep -A5 "STM" | sed "$c,$c!d" | awk '{print $NF}';)
    val=$(echo "scale=2 ; $norm1 / $total" | bc)
    echo "$val" >> $NAME2

    echo "$val"
    total=$(./bin/time --resize=$2 --workers=$x --amount=500000 | grep -A5 "Fine" | sed "$c,$c!d" | awk '{print $NF}';)
    val=$(echo "scale=2 ; $norm1 / $total" | bc)
    echo "$val" >> $NAME3
    echo "$val"
done
