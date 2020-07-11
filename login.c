#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cores.h"

#include"adm.h"
#include"user.h"

#define MAXNOME 128
#define MAXPOST 128

void login(int *tipo, char *nome, char *nick, int *numseg, int *numpost){
    setbuf(stdin, NULL);
    printf("Informe seu nickname: ");
    fgets(nick, MAXNOME, stdin);
    int i;
    for(i = 0; nick[i] != '\0'; i++);
    nick[i - 1] = '\0';
    FILE *fr = fopen(nick, "r");
    if(fr == NULL){
        vermelho();
        printf("Usuario nao Cadastrado...\n");
        padrao();
        *tipo = -1;
        return;
    }
    int auxnum;
    fscanf(fr, "%d\n", &auxnum);
    *tipo = auxnum;
    fgets(nome, MAXNOME, fr);
    fgets(nick, MAXNOME, fr);
    for(i = 0; nick[i] != '\0'; i++);
    nick[i - 1] = '\0';
    for(i = 0; nome[i] != '\0'; i++);
    nome[i - 1] = '\0';
    fscanf(fr, "%d", &auxnum);
    *numseg = auxnum;
    fscanf(fr, "%d", &auxnum);
    *numpost = auxnum;
    fclose(fr);
}

void login_normal(int tipo, char *nome, char *nick, int numseg, int numpost, int se_adm){
    if(se_adm){
        printf("Login como %s\n", nick);
    }
    printf("\tBem-Vindo(a)\n");
    int escolha;
    int flag1 = 1;
    while(flag1){
        if(se_adm){
            printf("\tMENU\n1 - Perfil\n2 - Minhas Postagens\n3 - Seguidores\n4 - Timeline\n5 - Voltar para o ADM\n");
        }else{
            printf("\tMENU\n1 - Perfil\n2 - Minhas Postagens\n3 - Seguidores\n4 - Timeline\n5 - Logout\n");
        }
        setbuf(stdin, NULL);
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                perfil(nome, nick);
                break;
            case 2:
                posts(tipo, nome, nick, numseg, numpost);
                break;
            case 3:
                seguidores(tipo, nome, nick, numseg, numpost);
                break;
            case 4:
                timeline(tipo, nome, nick, numseg, numpost);
                break;
            case 5:
                flag1 = 0;
                break;
            default:
                break;
        }
    }
}

void login_adm(int tipo, char *nome, char *nick, int numseg, int numpost){
    int flag2 = 1;
    int escolha;
    while(flag2){
        printf("\tMENU\n1 - Perfil\n2 - Minhas Postagens\n3 - Seguidores\n4 - Timeline\n5 - Modo Administrador\n6 - Logout\n");
        setbuf(stdin, NULL);
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                perfil(nome, nick);
                break;
            case 2:
                posts(tipo, nome, nick, numseg, numpost);
                break;
            case 3:
                seguidores(tipo, nome, nick, numseg, numpost);
                break;
            case 4:
                timeline(tipo, nome, nick, numseg, numpost);
                break;
            case 5:
                adm();
                break;
            case 6:
                flag2 = 0;
                break;
            default:
                break;
        }
    }
}