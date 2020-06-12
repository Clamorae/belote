clear: belote.out
	rm array.o
	rm gamelogic.o
	rm highscore.o
	rm input.o
	rm menu.o
	rm main.o
	rm IA.o
	rm display.o

belote.out: main.o array.o gamelogic.o highscore.o input.o menu.o IA.o display.o
	gcc -o belote.out main.o array.o gamelogic.o highscore.o input.o menu.o IA.o display.o

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

IA.o: IA.c
	gcc -c IA.c
display.o: display.c
	gcc -c display.c
