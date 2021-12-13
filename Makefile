all: bucket

bucket: bucket.c
	gcc bucket.c -o bucket