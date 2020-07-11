#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXNOME 128
#define MAXPOST 128

void cadastro(){
    setbuf(stdin, NULL);
    FILE *fr = fopen("Usuarios", "r");
    if(fr == NULL){
        printf("Não foi possivel abrir o arquivo Usuarios.\n");
        exit(1);
    }
    int pos;
    fseek(fr, 0, SEEK_END);
    pos = ftell(fr);
    char *aux = (char *) malloc(MAXNOME * sizeof(char));
    if(aux == NULL){
        printf("Erro de alocacao...\n");
        exit(1);
    }
    char *nome = (char *) malloc(MAXNOME * sizeof(char));
    if(nome == NULL){
        printf("Erro de alocacao...\n");
        exit(1);
    }
    char *nick = (char *) malloc(MAXNOME * sizeof(char));
    if(nick == NULL){
        printf("Erro de alocacao...\n");
        exit(1);
    }

    int i;
    int flag = 0;
    while(!flag){
        printf("Digite seu nome (Ate %d caracteres): ", MAXNOME - 1);
        fgets(nome, MAXNOME, stdin);
        for(i = 0; nome[i] != '\0'; i++);
        nome[i - 1] = '\0';
        printf("Digite seu nickname (Ate %d caracteres): ", MAXNOME - 1);
        fgets(nick, MAXNOME, stdin);
        for(i = 0; nick[i] != '\0'; i++);
        nick[i - 1] = '\0';
        fseek(fr, 0, SEEK_SET);
        while(ftell(fr) < pos){
            fgets(aux, MAXNOME, fr);
            for(i = 0; aux[i] != '\0'; i++);
            aux[i - 1] = '\0';
            if(!strcmp(aux, nick)){
                printf("Nickname em uso... tente novamente\n");
                flag = 0;
                break;
            } else {
                flag = 1;
            }
        }    
    }
    
    fr = fopen("Usuarios", "r");
    if(fr == NULL){
        printf("Não foi possivel abrir o arquivo Usuarios.\n");
        exit(1);
    }
    int num;
    fscanf(fr, "%d\n", &num);
    char **users = (char **) malloc(num * sizeof(char*));
    if(users == NULL){
        printf("Erro de alocacao...\n");
        exit(1);
    }
    for(i = 0; i < num; i++){
        users[i] = (char *) malloc(MAXNOME * sizeof(char));
        if(users[i] == NULL){
            printf("Erro de alocacao...\n");
            exit(1);
        }
        fgets(users[i], MAXNOME, fr);
    }
    fclose(fr);
    FILE *fw = fopen("Usuarios", "w");
    fprintf(fr, "%d\n", num + 1);
    for(i = 0; i < num; i++){
        int j;
        for(j = 0; users[i][j] != '\0'; j++);
        users[i][j - 1] = '\0';
        fprintf(fw, "%s\n", users[i]);
    }
    fprintf(fw, "%s\n", nick);
    for(i = 0; i < num; i++){
        free(users[i]);
    }
    free(users);
    fclose(fw);
    FILE *fw2 = fopen(nick, "w");
    int tipo = 0;
    int numseg = 1;
    int numpost = 1;
    fprintf(fw2, "%d\n", tipo);
    fprintf(fw2, "%s\n", nome);
    fprintf(fw2, "%s\n", nick);
    fprintf(fw2, "%d\n", numseg);
    fprintf(fw2, "%d\n", numpost);
    fprintf(fw2, "%s\n", nick);
    fprintf(fw2, "Ola, acabei de me cadastrar.\n");
    fclose(fw2);
    printf("\tCadastrado(a) com Sucesso!\n");
    free(aux);
    free(nome);
    free(nick);
}