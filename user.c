#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cores.h"

#define MAXNOME 128
#define MAXPOST 128

void perfil(char *nome, char *nick){
    FILE *fr = fopen(nick, "r");
    if(fr == NULL){
        vermelho();
        printf("Nao foi possiver acessar seus dados...\n");
        padrao();
        return;
    }
    int tipo;
    fscanf(fr, "%d\n", &tipo);
    fgets(nome, MAXNOME, fr);
    int i;
    for(i = 0; nome[i] != '\0'; i++);
    nome[i - 1] = '\0';
    fgets(nick, MAXNOME, fr);
    for(i = 0; nick[i] != '\0'; i++);
    nick[i - 1] = '\0';
    int numseg;
    fscanf(fr, "%d\n", &numseg);
    int numpost;
    fscanf(fr, "%d\n", &numpost); 
    fclose(fr);
    while(1){
        printf("\tMENU\n1 - Voltar\n");
        printf("Nome: %s\n", nome);
        printf("Nickname: %s\n", nick);
        printf("Numero de Seguidores: %d\n", numseg);
        printf("Numero de Posts: %d\n", numpost);
        int escolha;
        setbuf(stdin, NULL);
        scanf("%d", &escolha);
        if(escolha == 1){
            break;
        }
    }
}

void posts(int tipo, char *nome, char *nick, int numseg, int numpost){
    int flag = 1;
    char *aux = (char *) malloc(MAXPOST * sizeof(char));
    if(aux == NULL){
        vermelho();
        printf("Erro de alocacao...\n");
        padrao();
        exit(1);
    }
    while(flag){
        int flag2 = 1;
        int flag3 = 1;
        FILE *fr = fopen(nick, "r");
        if(fr == NULL){
            vermelho();
            printf("Nao foi possivel abrir o arquivo %s.\n", nick);
            padrao();
            break;
        }
        fscanf(fr, "%d\n", &tipo);
        fgets(nome, MAXNOME, fr);
        fgets(nick, MAXNOME, fr);
        fscanf(fr, "%d\n", &numseg);
        fscanf(fr, "%d\n", &numpost);
        char **seg = (char **) malloc(numseg * sizeof(char *));
        if(seg == NULL){
            vermelho();
            printf("Erro de alocacao...\n");
            padrao();
            exit(1);
        }
        int i;
        for(i = 0; i < numseg; i++){
            seg[i] = (char *) malloc(MAXNOME * sizeof(char));
            if(seg[i] == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            fgets(seg[i], MAXNOME, fr);
        }
        char **post = (char **) malloc((numpost) * sizeof(char *));
        if(post == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
        }
        for(i = 0; i < numpost; i++){
            post[i] = (char *) malloc(MAXPOST * sizeof(char));
            if(post[i] == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            fgets(post[i], MAXPOST, fr);
        }
        fclose(fr);
        printf("\tMENU\n1 - Meus Posts\n2 - Novo Post\n3 - Excluir Post\n4 - Voltar\n");
        int escolha;
        setbuf(stdin, NULL);
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                if(numpost <= 5){
                    printf("\tPOSTAGENS PESSOAIS\n");
                    for(i = 0; i < numpost; i++){
                        printf("%d- %s", i + 1, post[i]);
                    }
                     break;
                }
                i = 0;
                do{
                   int j = i;
                   printf("\tPOSTAGENS PESSOAIS\n");
                   printf("\tMENU\n1 - Mais cinco\n2 - Voltar\n\n");
                   for(i; i < j + 5 && i != numpost; i++){
                       printf("%d: %s", i + 1, post[i]);
                   }
                   setbuf(stdin, NULL);
                   scanf("%d", &escolha);
                } while(escolha != 2 && i != numpost);
                break;
            case 2:
                setbuf(stdin, NULL);
                printf("Digite seu novo post (ate 127 caracteres): ");
                fgets(aux, MAXPOST, stdin);
                numpost++;
                flag2 = 0;
                break;
            case 3:
                printf("Digite o numero da postagem que deseja excluir: ");
                setbuf(stdin, NULL);
                scanf("%d", &escolha);
                if(escolha > numpost || escolha <= 0){
                    vermelho();
                    printf("Esse post nao existe...\n");
                    padrao();
                    break;
                }
                flag3 = 0;
                numpost--;      
                break;
            case 4:
                flag = 0;
                break;
            default:
                break;          
        }
        for(i = 0; nick[i] != '\0'; i++);
        nick[i - 1] = '\0';
        for(i = 0; nome[i] != '\0'; i++);
        nome[i - 1] = '\0';
        for(i = 0; i < numseg; i++){
            int j;
            for(j = 0; seg[i][j] != '\0'; j++);
            seg[i][j - 1] = '\0';
        }
        if(!flag2){
            for(i = 0; i < numpost - 1; i++){
                int j;
                for(j = 0; post[i][j] != '\0'; j++);
                post[i][j - 1] = '\0';
            }
        } else{
            if(!flag3){
                for(i = 0; i < numpost + 1; i++){
                    int j;
                    for(j = 0; post[i][j] != '\0'; j++);
                    post[i][j - 1] = '\0';
                }
            } else{
                for(i = 0; i < numpost; i++){
                    int j;
                    for(j = 0; post[i][j] != '\0'; j++);
                    post[i][j - 1] = '\0';
                }
            }
        }
        FILE *fw = fopen(nick, "w");
        if(fw == NULL){
            vermelho();
            printf("Erro ao criar o arquivo %s.\n", nick);
            padrao();
        }
        fprintf(fw, "%d\n", tipo);
        fprintf(fw, "%s\n",nome);
        fprintf(fw, "%s\n", nick);
        fprintf(fw, "%d\n", numseg);
        fprintf(fw, "%d\n", numpost);
        for(i = 0; i < numseg; i++){
            fprintf(fw, "%s\n", seg[i]);
            free(seg[i]);
        }
        free(seg);
        if(!flag2){
            for(i = 0; i < numpost - 1; i++){
                fprintf(fw, "%s\n", post[i]);
                free(post[i]);
            }
            free(post);
            fprintf(fw, "%s", aux);
        } else{
            if(!flag3){
                for(i = 0; i < numpost + 1; i++){
                    if(i != escolha - 1){
                        fprintf(fw, "%s\n", post[i]);
                    }
                    free(post[i]);
                }
                free(post);
            } else{
                for(i = 0; i < numpost; i++){
                    fprintf(fw, "%s\n", post[i]);
                    free(post[i]);
                }
                free(post);
            }  
        }
        fclose(fw);
    }
    free(aux);
}

void seguidores(int tipo, char *nome, char *nick, int numseg, int numpost){
    int flag = 1;
    char *aux = (char *) malloc(MAXNOME * sizeof(char));
    if(aux == NULL){
        vermelho();
        printf("Erro de alocacao...\n");
        padrao();
        exit(1);
    }
    while(flag){
        int flag2 = 1;
        int flag3 = 1;
        FILE *fr = fopen(nick, "r");
        if(fr == NULL){
            vermelho();
            printf("Nao foi possivel abrir o arquivo %s.\n", nick);
            padrao();
        }
        fscanf(fr, "%d\n", &tipo);
        fgets(nome, MAXNOME, fr);
        int i;
        for(i = 0; nome[i] != '\0'; i++);
        nome[i - 1] = '\0';
        fgets(nick, MAXNOME, fr);
        for(i = 0; nick[i] != '\0'; i++);
        nick[i - 1] = '\0';
        fscanf(fr, "%d\n", &numseg);
        fscanf(fr, "%d\n", &numpost);
        char **seg = (char **) malloc(numseg * sizeof(char *));
        if(seg == NULL){
            vermelho();
            printf("Erro de alocacao...\n");
            padrao();
            exit(1);
        }
        for(i = 0; i < numseg; i++){
            seg[i] = (char *) malloc(MAXNOME * sizeof(char));
            if(seg == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            fgets(seg[i], MAXNOME, fr);
        }
        char **post = (char **) malloc(numpost *sizeof(char *));
        if(post == NULL){
            vermelho();
            printf("Erro de alocacao...\n");
            padrao();
            exit(1);
        }
        for(i = 0; i < numpost; i++){
            post[i] = (char *) malloc(MAXPOST * sizeof(char));
            if(post[i] == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            fgets(post[i], MAXPOST, fr);
        }
        fclose(fr);
        FILE *fr2 = fopen("Usuarios", "r");
        if(fr2 == NULL){
            vermelho();
            printf("Nao foi possivel abrir o arquivo Usuarios.\n");
            padrao();
            flag = 0;
        }
        int num;
        fscanf(fr2, "%d\n", &num);
        char **users = (char **) malloc(num * sizeof(char*));
        if(users == NULL){
            vermelho();
            printf("Erro de alocacao...\n");
            padrao();
            exit(1);
        }
        for(i = 0; i < num; i++){
            users[i] = (char *) malloc(MAXNOME * sizeof(char));
            if(users[i] == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            fgets(users[i], MAXNOME, fr2);
        }
        fclose(fr2);
        printf("\tMENU\n1 - Listar Seguidores\n2 - Seguir\n3 - Deixar de Seguir\n4 - Voltar\n");
        int escolha;
        setbuf(stdin, NULL);
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                printf("\tLISTA DE SEGUIDORES\n");
                for(i = 0; i < numseg; i++){
                    printf("%d: %s", i + 1, seg[i]);
                }
                break;
            case 2:
                printf("\tLISTA DE CADASTRADOS\n");
                for(i = 1; i < num; i++){
                    printf("%s", users[i]);
                }
                printf("Digite o nome de quem deseja seguir: ");
                setbuf(stdin, NULL);
                fgets(aux, MAXNOME, stdin);
                for(i = 0; i < num; i++){
                    if(!strcmp(aux, users[i])){
                        flag2 = 0;
                        break;
                    }
                }
                if(flag2){
                    vermelho();
                    printf("Usuario inexistente...\n");
                    padrao();
                    break;
                }
                for(i = 0; i < numseg; i++){
                    if(!strcmp(aux, seg[i])){
                        vermelho();
                        printf("Voce ja segue esse usuario...\n");
                        padrao();
                        flag2 = 1;
                        break;
                    } 
                }
                break;
            case 3:
                printf("\tLISTA DE SEGUIDORES\n");
                for(i = 0; i < numseg; i++){
                    printf("%d: %s", i + 1, seg[i]);
                }
                printf("Digite o numero de quem deseja parar de seguir: ");
                setbuf(stdin, NULL);
                scanf("%d", &escolha);
                if(escolha > numseg || escolha <= 0){
                    vermelho();
                    printf("Seguidor inexistente...\n");
                    padrao();
                    break;
                }
                flag3 = 0; 
                break;
            case 4:
                flag = 0;
                break;
            default:
                break;
        }
        FILE *fw = fopen("Usuarios", "w");
        if(fw == NULL){
            vermelho();
            printf("Nao foi possivel criar o arquivo Usuarios...\n");
            padrao();
        }
        fprintf(fw, "%d\n", num);
        for(i = 0; i < num; i++){
            fprintf(fw, "%s", users[i]);
            free(users[i]);
        }
        free(users);
        fclose(fw);
        FILE *fw2 = fopen(nick, "w");
        fprintf(fw2, "%d\n", tipo);
        fprintf(fw2, "%s\n", nome);
        fprintf(fw2, "%s\n", nick);
        if(!flag2){
            fprintf(fw2, "%d\n", numseg + 1);
        } else{
            if(!flag3){
                fprintf(fw2, "%d\n", numseg - 1);
            }else{
                fprintf(fw2, "%d\n", numseg);
            }
        }
        fprintf(fw2, "%d\n", numpost);
        if(!flag2){
            for(i = 0; i < numseg; i++){
                fprintf(fw2, "%s", seg[i]);
            }
            fprintf(fw2, "%s", aux);
        } else{
            if(!flag3){
                for(i = 0; i < numseg; i++){
                    if(i != escolha - 1){
                        fprintf(fw2, "%s", seg[i]);
                    }
                }
            } else{
                for(i = 0; i < numseg; i++){
                    fprintf(fw2, "%s", seg[i]);
                }
            }
        }
        for(i = 0; i < numpost; i++){
            fprintf(fw2, "%s", post[i]);
        }

        for(i = 0; i < numseg; i++){
            free(seg[i]);
        }
        free(seg);
        for(i = 0; i < numpost; i++){
            free(post[i]);
        }
        free(post);
        fclose(fw2);
    }
    free(aux);
}

void timeline(int tipo, char *nome, char *nick, int numseg, int numpost){
    int flag = 1;
    int i;
    int escolha2;
    FILE *fr = fopen(nick, "r");
    if(fr == NULL){
        vermelho();
        printf("Nao foi possivel abrir o arquivo %s.\n", nick);
        padrao();
        return;
    }
    fscanf(fr, "%d\n", &tipo);
    fgets(nome, MAXNOME, fr);
    for(i = 0; nome[i] != '\0'; i++);
    nome[i - 1] = '\0';
    fgets(nick, MAXNOME, fr);
    for(i = 0; nick[i] != '\0'; i++);
    nick[i - 1] = '\0';
    fscanf(fr, "%d\n", &numseg);
    if(numseg == 0){
        vermelho();
        printf("Voce nao segue ninguem...\n");
        padrao();
        return;
    }
    fscanf(fr, "%d\n", &numpost);
    char **seg = (char **) malloc(numseg * sizeof(char *));
    if(seg == NULL){
        vermelho();
        printf("Erro de alocacao...\n");
        padrao();
        exit(1);
    }
    for(i = 0; i < numseg; i++){
        seg[i] = (char *) malloc(MAXNOME * sizeof(char));
        if(seg[i] == NULL){
            vermelho();
            printf("Erro de alocacao...\n");
            padrao();
            exit(1);
        }
        fgets(seg[i], MAXNOME, fr);
    }
    fclose(fr);
    while(flag){
        int flagdeuruim = 1;
        printf("\tLISTA DE SEGUIDORES\n");
        for(i = 0; i < numseg; i++){
            printf("%d: %s",i + 1, seg[i]);
        }
        printf("Digite o numero do usuario que deseja vizualizar: \n");
        int escolha;
        setbuf(stdin, NULL);
        scanf("%d", &escolha);
        if(escolha > 0 && escolha <= numseg){
            for(i = 0; seg[escolha - 1][i] != '\0'; i++);
            if(seg[escolha - 1][i - 1] == '\n'){
                seg[escolha - 1][i - 1] = '\0';
            }
            FILE *fr2 = fopen(seg[escolha - 1], "r");
            if(fr2 == NULL){
                vermelho();
                printf("Nao foi possivel abrir o arquivo %s.\n", seg[escolha - 1]);
                padrao();
                break;
            }
            int tipo2;
            fscanf(fr2, "%d\n", &tipo2);
            char nome2[MAXNOME];
            fgets(nome2, MAXNOME, fr2);
            char nick2[MAXNOME];
            fgets(nick2, MAXNOME, fr2);
            int numseg2;
            fscanf(fr2, "%d\n", &numseg2);
            int numpost2;
            fscanf(fr2, "%d\n", &numpost2);
            char **seg2 = (char **) malloc(numseg2 * sizeof(char *));
            if(seg2 == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            for(i = 0; i < numseg2; i++){
                seg2[i] = (char *) malloc(MAXNOME * sizeof(char));
                if(seg2[i] == NULL){
                    vermelho();
                    printf("Erro de alocacao...\n");
                    padrao();
                    exit(1);
                }
                fgets(seg2[i], MAXNOME, fr2);
            }
            char **post2 = (char **) malloc(numpost2 * sizeof(char *));
            if(post2 == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            for(i = 0; i < numpost2; i++){
                post2[i] = (char *) malloc(MAXNOME * sizeof(char));
                if(post2[i] == NULL){
                    vermelho();
                    printf("Erro de alocacao...\n");
                    padrao();
                    exit(1);
                }
                fgets(post2[i], MAXNOME, fr2);
            }
            fclose(fr2);
            if(numpost2 <= 5){
                    int flag2 = 1;
                    int escolha3;
                    while(flag2){
                        printf("\tPOSTAGENS DE %s.\n", seg[escolha - 1]);
                        for(i = 0; i < numpost2; i++){
                            printf("%d- %s", i + 1, post2[i]);
                        }
                        printf("\nVoltar(1)?: ");
                        setbuf(stdin, NULL);
                        scanf("%d", &escolha3);
                        if(escolha3 == 1){
                            flag2 = 0;
                            flag = 0;
                        }
                    }
            } else{
                i = 0;
                do{
                    int j = i;
                    printf("\tMENU\n1 - Mais cinco\n2 - voltar\n");
                    for(i;i < j + 5 && i != numpost2; i++){
                        printf("%d: %s", i + 1, post2[i]);
                    }
                    setbuf(stdin, NULL);
                    scanf("%d", &escolha2);
                } while(escolha2 != 2 && i != numpost2);
                flag = 0;
            }
            for(i = 0; i < numseg2; i++){
                free(seg2[i]);
            }
            free(seg2);
            for(i = 0; i < numpost2; i++){
                free(post2[i]);
            }
            free(post2); 
        } else{
            vermelho();
            printf("Este usuario nao existe...\n");
            padrao();
            flagdeuruim = 0;
        }
        for(i = 0; i < numseg; i++){
            free(seg[i]);
        }
        free(seg);
        if(!flagdeuruim){
        break;
        }
    }
    for(i = 0; nick[i] != '\0'; i++);
    if(nick[i - 1] == '\n'){
        nick[i - 1] = '\0';
    }
    for(i = 0; nome[i] != '\0'; i++);
    if(nome[i - 1] == '\n'){
        nome[i - 1] = '\0';
    }
}
