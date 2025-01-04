#!/bin/bash

#SBATCH --partition=rome
#SBATCH --ntasks-per-node=128
#SBATCH --nodes=1
#SBATCH --time=2:00:00

module load gcc/9.2.0 openmpi/3.1.3

cd /home/c/charisim/bitonic

make clean
make

rm ./test/results.txt
touch ./test/results.txt

for p in {1..7};
do
  echo -e "WHEN p = $p\n\n" >> ./test/results.txt
  for q in {20..27};
  do
    echo -e "q = $q\n" >> ./test/results.txt
    make P=$p Q= $q run >> ./test/results.txt
  done
done

make clean
