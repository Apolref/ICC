#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"adm.h"
#include"cadastro.h"
#include"checagem.h"
#include"cores.h"
#include"login.h"
#include"user.h"

#define MAXNOME 128
#define MAXPOST 128

int main(int argc, char  *argv[]){
    checagem();
    int tipo;
    char *nome = (char *) malloc(MAXNOME * sizeof(char));
    if(nome == NULL){
        vermelho();
        printf("Erro de alocacao...\n");
        padrao();
        exit(1);
    }
    char *nick = (char *) malloc(MAXNOME * sizeof(char));
    if(nick == NULL){
        vermelho();
        printf("Erro de alocacao...\n");
        padrao();
        exit(1);
    }
    int numseg = 0;
    int numpost = 0;

    int escolha;
    int flag = 1;
    while(flag){
        vermelho();
        negrito();
        sublinhado();
        printf("BEM-VINDO AO YACULT\n");
        padrao();
        printf("\tMENU\n1 - Login\n2 - Cadastro\n3 - Sair\n");
        setbuf(stdin, NULL);
        scanf("%d", &escolha);
        switch (escolha){
            case 1:
                login(&tipo, nome, nick, &numseg, &numpost);
                break;
            case 2:
                cadastro();
                tipo = -1;
                break;
            case 3:
                flag = 0;
                tipo = -1;
                break;
            default:
                tipo = -1;
                break;
        }
    
        if (escolha==1 && tipo==0){
            int se_adm = 0;
            login_normal(tipo, nome, nick, numseg, numpost, se_adm);
        }
        if (escolha==1 && tipo==1){
            login_adm(tipo, nome, nick, numseg, numpost);
        }
    }
    free(nome);
    free(nick);
} 