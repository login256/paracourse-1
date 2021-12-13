all: bucket bucket-para

bucket: bucket.c
	gcc bucket.c -o bucket

bucket-para: bucket-para.c
	mpicc -openmp bucket-para.c -o bucket-para -lomp

data: datamaker
	./datamaker 100000

datamaker: datamaker.cpp
	g++ datamaker.cpp -o datamaker -std=c++17