#!/bin/bash

touch ./results.txt
cd ..

make clean
make

for q in {21..27}
do
    echo -e "Q = $q\n" >> ./test/results.txt
    make run Q=$q >> ./test/results.txt
    echo -e "\n" >> ./test/results.txt
    echo "Done with Q = $q"
done

make clean