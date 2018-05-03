make clean time
rm ./data/*
rm ./graphs/*

# Resize off
./scale.sh 0 0
./scale.sh 1 0
./scale.sh 2 0
./scale.sh 3 0

# Resize on
./scale.sh 0 1
./scale.sh 1 1
./scale.sh 2 1
./scale.sh 3 1

python3 plot.py

echo "done!"
