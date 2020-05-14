clear: belote.exe
	del array.o
	del gamelogic.o
	del highscore.o
	del input.o
	del menu.o
	del main.o

belote.exe: main.o array.o gamelogic.o highscore.o input.o menu.o
	gcc -o belote.out main.o array.o gamelogic.o highscore.o input.o menu.o

main.o: main.c
	gcc -c main.c

array.o: array.c
	gcc -c array.c

gamelogic.o: gamelogic.c
	gcc -c gamelogic.c

highscore.o: highscore.c
	gcc -c highscore.c

input.o: input.c
	gcc -c input.c

menu.o: menu.c
	gcc -c menu.c