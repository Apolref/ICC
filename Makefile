redesocial:	main.o	adm.o	cadastro.o	checagem.o	cores.o	login.o	user.o
	gcc	-o	redesocial	main.o	adm.o	cadastro.o	checagem.o	cores.o	login.o	user.o

main.o:	main.c
	gcc	-o	main.o	-c	main.c

adm.o:	adm.c
	gcc	-o	adm.o	-c	adm.c

cadastro.o:	cadastro.c
	gcc	-o	cadastro.o	-c	cadastro.c

checagem.o:	checagem.c
	gcc	-o	checagem.o	-c	checagem.c

cores.o:	cores.c
	gcc	-o	cores.o	-c	cores.c

login.o:	login.c
	gcc	-o	login.o	-c	login.c

user.o:	user.c
	gcc	-o	user.o	-c	user.c

all:	redesocial

run:	all
	./redesocial

clean:
	rm redesocial *.o

#clean:
#	rm main main.o adm.o cadastro.o checagem.o cores.o login.o	user.o

#run:	redesocial
#	./redesocial
