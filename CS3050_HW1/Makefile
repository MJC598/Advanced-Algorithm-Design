project1.exe: main.o vector.o
		 cc main.o vector.o -o project1

main.o: main.c vector.h input_error.h
		 cc -c main.c

vector.o: vector.c vector.h input_error.h
		 cc -c vector.c
clean:
		 rm main.o vector.o
