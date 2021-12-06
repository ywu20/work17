all:		main.o	write.o
	gcc	-o	main	main.o
	gcc	-o	write	write.o
main.o:	main.c	write.h
	gcc	-c	main.c
write.o:	write.c	write.h
	gcc	-c	write.c
