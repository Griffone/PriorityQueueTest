gcc -c -O3 linked-list.c -o linked-list.o && gcc -c -O3 heap.c -o heap.o && gcc -c -O3 bench.c -o bench.o && gcc -O3 bench.o linked-list.o heap.o -o bench
