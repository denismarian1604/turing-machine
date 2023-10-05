build: 
	gcc turing_machine.c -std=c99 -Wall -Werror operatii.c aloc_dist.c mutari.c -o turing_machine
run:
	./tema1
clean:
	rm tema1
