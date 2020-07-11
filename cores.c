#include<stdio.h>

void padrao(){
    printf("\033[0m");
}

void negrito(){
    printf("\033[1m");
}

void italico(){
    printf("\033[3m");
}

void sublinhado(){
    printf("\033[4m");
}

void preto(){
    printf("\033[0;30m");
}
void vermelho(){
    printf("\033[0;31m");
}
void laranja(){
    printf("\033[0;33m");
}
void verde(){
    printf("\033[0;32m");
}
void azul(){
    printf("\033[0;34m");
}
void roxo(){
    printf("\033[0;35m");
}
void azul_claro(){
    printf("\033[0;36m");
}
void cinza(){
    printf("\033[0;37m");
}
//[0m Normal
//[1m Negrito
//[2m Muda a cor do texto (dentro)
//[3m Italico
//[4m Sublinhado

//[X;30m [X;30m === [X;37m [X;37m MUDA A COR DO texto
/*
0 preto
1 vermelho/rosa
2 verde
3 laranja
4 azul
5 roxo
6 azul agua
7 cinza
*/


//[X;40m [X;40m === [X;47m [X;47m MUDA A COR DO FUNDO
/*
0 preto
1 vermelho/rosa
2 verde
3 laranja
4 azul
5 roxo
6 azul agua
7 cinza
*/
