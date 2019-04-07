make -C ..
g++ gen.cpp -o gen.out
g++ -std=c++11 timer.cpp -o timer.out
./timer.out 10 25 1 > times.txt
Rscript grafico.r
rm in.txt
rm timer.out
rm gen.out
rm times.txt
