Main: src/Main.c src/Tela.c src/Kernel.c src/Processador.c src/Disco.c src/Timer.c src/ControladorInterrupcoes.c src/Memoria.c src/Console.c src/Util/String.c
	gcc -Wall -o Main src/Main.c src/Tela.c src/Kernel.c src/Processador.c src/Disco.c src/Timer.c src/ControladorInterrupcoes.c src/Memoria.c src/Console.c src/Util/String.c -lncurses -pthread -lrt
