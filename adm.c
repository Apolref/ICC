#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"cadastro.h"
#include"login.h"
#include"cores.h"

#define MAXNOME 128
#define MAXPOST 128


void adm_remover_user(){
    int num_users;
    while(1){
        FILE *fr = fopen("Usuarios", "r");
        if(fr == NULL){
            vermelho();
            printf("nao foi possivel abrir o arquivo :v\n");
            padrao();
            return;
        }
        fscanf(fr, "%d\n", &num_users);
        if(num_users == 2){
            vermelho();
            printf("Nao ha usuarios para remover\n");
            padrao();
            fclose(fr);
            return;
        }
        char **users = (char **) malloc(num_users * sizeof(char *));
        if(users == NULL){
            vermelho();
            printf("Erro de alocacao...\n");
            padrao();
            exit(1);
        }
        for(int i = 0; i < num_users; i++){
            users[i] = (char *) malloc(MAXNOME * sizeof(char));
            if(users[i] == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            fgets(users[i], MAXNOME, fr);
            int j;
            for(j = 0; users[i][j] != '\0'; j++);
            users[i][j - 1] = '\0';
        }
        fclose(fr);
        printf("\tLISTA DE CADASTRADOS\n");
        int i;
        for(i = 1; i < num_users; i++){
            printf("%d: %s\n", i, users[i]);
        }
        int thanos;
        while(1){
            printf("Digite o numero do perfil para remove-lo: ");
            setbuf(stdin, NULL);
            scanf("%d", &thanos);
            if(thanos <= 0 || thanos > num_users - 1){
                vermelho();
                printf("Entrada Invalida...\n");
                padrao();
            } else{
                break;
            }
        }
        if(!strcmp("Ades", users[thanos]))   {
            vermelho();
            printf("Esse usuario nao pode ser removido\n");
            padrao();
            for(i = 0; i < num_users; i++){
                free(users[i]);
            }
            free(users);
            continue;
        }    
        remove(users[thanos]);
        FILE *fw = fopen("Usuarios","w");
        if(fw == NULL){
            vermelho();
            printf("nao foi possivel abrir o arquivo :v\n");
            padrao();
            return;
        }
        fprintf(fw, "%d\n", num_users - 1);
        for(i = 0; i < num_users; i++){
            if(i != thanos){
                fprintf(fw, "%s\n", users[i]);
            }
        }
        fclose(fw);
        for(i = 0; i < num_users; i++){
            free(users[i]);
        }
        free(users);
        break;
    }
}
void adm_consultar_user(){
    int flag = 1;
    while(flag){
        int tipo;
        char *nome = (char *) malloc(MAXNOME * sizeof(char));
        if(nome == NULL){
            vermelho();
            printf("Erro de Alocacao...\n");
            padrao();
            exit(1);
        }
        char *nick = (char *) malloc(MAXNOME * sizeof(char));
        if(nick == NULL){
            vermelho();
            printf("Erro de Alocacao...\n");
            padrao();
            exit(1);
        }
        int numseg;
        int numpost;
        int flaginf = 1;
        int flagadm= 1;
        int flaglog = 1;
        int se_adm = 0;
        printf("\tMENU\n1 - Informacoes\n2 - Tornar Adm\n3 - Fazer Login Como\n4 - Voltar\n");
        int escolha2;
        scanf("%d", &escolha2);
        switch(escolha2){
            case 1:
                flaginf = 0;
                break;
            case 2:
                flagadm = 0;
                break;
            case 3:
                se_adm = 1;
                flaglog = 0;
                break;
            case 4:
                flag = 0;
                break;
            default:
                break;
        }
        if(flag == 0){
            break;
        }
        FILE *fr = fopen("Usuarios", "r");
        if(fr == NULL){
            vermelho();
            printf("Nao foi possivel abrir o arquivo Usuarios...\n");
            padrao();
            exit(1);
        }
        int numu;
        fscanf(fr, "%d\n", &numu);
        char **users = (char**) malloc(numu * sizeof(char*));
        if(users == NULL){
            vermelho();
            printf("Erro de Alocacao...\n");
            padrao();
            exit(1);
        }
        int i;
        for(i = 0; i < numu; i++){
            users[i] = (char *) malloc(MAXNOME * sizeof(char));
            if(users[i] == NULL){
                vermelho();
                printf("Erro de Alocacao...\n");
                padrao();
                exit(1);
            }
            fgets(users[i], MAXNOME, fr);
            int j;
            for(j = 0; users[i][j] != '\0'; j++);
            users[i][j - 1] = '\0';
        }
        fclose(fr);
        printf("\tLISTA DE USUARIOS\n");
        for(i = 1; i < numu; i++){
            printf("%d: %s\n", i, users[i]);
        }
        int escolha;
        while(1){
            printf("Digite o numero do usuario: ");
            setbuf(stdin, NULL);
            scanf("%d", &escolha);
            if(escolha > 0 && escolha <= numu){
               break;
            }
            vermelho();
            printf("Entrada invalida...\n");
            padrao();
        }
        FILE *fr2 = fopen(users[escolha], "r");
        if(fr2 == NULL){
            vermelho();
            printf("Nao foi possiver acessar seus dados...\n");
            padrao();
            return;
        }
        fscanf(fr2, "%d\n", &tipo);
        fgets(nome, MAXNOME, fr2);
        for(i = 0; nome[i] != '\0'; i++);
        nome[i - 1] = '\0';
        fgets(nick, MAXNOME, fr2);
        for(i = 0; nick[i] != '\0'; i++);
        nick[i - 1] = '\0';
        fscanf(fr2, "%d\n", &numseg);
        fscanf(fr2, "%d\n", &numpost);
        char **seg = (char **) malloc(numseg * sizeof(char *));
        if(seg == NULL){
            vermelho();
            printf("Erro de Alocacao...\n");
            padrao();
            exit(1);
        }
        for(i = 0; i < numseg; i++){
            seg[i] = (char *) malloc(MAXNOME * sizeof(char));
            if(seg[i] == NULL){
                vermelho();
                printf("Erro de Alocacao...\n");
                padrao();
                exit(1);
            }
            fgets(seg[i], MAXNOME, fr2);
        }
        char **posts = (char **) malloc(numpost * sizeof(char *));
        if(posts == NULL){
            vermelho();
            printf("Erro de Alocacao...\n");
            padrao();
            exit(1);
        }
        for(i = 0; i < numpost; i++){
            posts[i] = (char *) malloc(MAXNOME * sizeof(char));
            if(posts[i] == NULL){
                vermelho();
                printf("Erro de Alocacao...\n");
                padrao();
                exit(1);
            }
            fgets(posts[i], MAXNOME, fr2);
        }
        fclose(fr2);
        if(!flaginf){
            printf("Nome: %s\n", nome);
            printf("Nickname: %s\n", nick);
            printf("Numero de Seguidores: %d\n", numseg);
            printf("Numero de Posts: %d\n", numpost);
        }
        if(!flagadm && !tipo){
            FILE *fw = fopen(users[escolha], "w");
            fprintf(fw, "%d\n", 1);
            fprintf(fw, "%s\n", nome);
            fprintf(fw, "%s\n", nick);
            fprintf(fw, "%d\n", numseg);
            fprintf(fw, "%d\n", numpost);
            for(i = 0; i < numseg; i++){
                fprintf(fw, "%s", seg[i]);
            }
            for(i = 0; i < numpost; i++){
                fprintf(fw, "%s", posts[i]);
            }
            fclose(fw);
        } else{
            if(tipo && !flagadm){
                vermelho();
                printf("O usuario ja e um adm\n");
                padrao();
            }
        }
        if(!flaglog){
            login_normal(tipo, nome, nick, numseg, numpost, se_adm);
        }
        free(nick);
        free(nome);
        for(i = 0; i < numu; i++){
            free(users[i]);
        }       
        free(users);
        for(i = 0; i < numseg; i++){
            free(seg[i]);
        }
        free(seg);
        for(i = 0; i < numpost; i++){
            free(posts[i]);
        }
        free(posts);
    }
}

void adm_usuarios(){
    int flag=1;
    while(flag){
        printf("\tMENU ADM\n1 - Criar Usuario\n2 - Excluir Usuario existente\n3 - Consultar Usuario\n4 - Voltar\n");
        int escolha;
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                cadastro();
                break;
            case 2:
                adm_remover_user();
                break;
            case 3:
                adm_consultar_user();
                break;
            case 4:
                flag = 0;
                break;
            default:
                break;
        }
    }
}

void adm_infrede(){
    int escolha;
    int flag = 1;
    int num_users;
    while(flag){
        int flagnumu = 1;
        int flagnump = 1;
        int flagpm = 1;
        setbuf(stdin, NULL);
        printf("\tMENU\n1 - Numero de Usuarios\n2 - Numero de Posts\n3 - Pessoa com Mais postagens\n4 - Voltar\n");
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                flagnumu = 0;
                break;
            case 2:
                flagnump = 0;
                break;
            case 3:
                flagpm = 0;
                break;
            case 4:
                flag = 0;
                break;
            default:
                break;
        }
        if(!flagnumu){
            FILE *fr = fopen("Usuarios", "r");
            if(fr == NULL){
                vermelho();
                printf("nao foi possivel abrir o arquivo :v\n");
                padrao();
                return;
            }
            fscanf(fr, "%d\n", &num_users);
            printf("Numero de usuarios: %d\n",num_users - 1);
            fclose(fr);
        }
        if(!flagnump){
            int contador = 0;
            FILE *fr = fopen("Usuarios", "r");
            if(fr == NULL){
                vermelho();
                printf("nao foi possivel abrir o arquivo :v\n");
                padrao();
                return;
            }
            fscanf(fr, "%d\n", &num_users);
            char **users = (char **) malloc(num_users * sizeof(char *));
            if(users == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            for(int i = 0; i < num_users; i++){
                users[i] = (char *) malloc(MAXNOME * sizeof(char));
                if(users[i] == NULL){
                    vermelho();
                    printf("Erro de alocacao...\n");
                    padrao();
                    exit(1);
                }
                fgets(users[i], MAXNOME, fr);
                int j;
                for(j = 0; users[i][j] != '\0'; j++);
                users[i][j - 1] = '\0';
            }
            fclose(fr);
            for(int i = 1; i < num_users; i++){
                FILE *fr2 = fopen(users[i], "r");
                if(fr2 == NULL){
                    vermelho();
                    printf("nao foi possivel abrir o arquivo :v\n");
                    padrao();
                    return;
                }
                int postagens;
                char efemero[MAXNOME];
                fscanf(fr2, "%d\n", &postagens);
                fgets(efemero, MAXNOME, fr2);
                fgets(efemero, MAXNOME, fr2);
                fscanf(fr2, "%d\n", &postagens);
                fscanf(fr2, "%d\n", &postagens);
                contador+=postagens;
                fclose(fr2);
            }
            printf("Numero de Postagens: %d\n", contador);
            int i;
            for(i = 0; i < num_users; i++){
                free(users[i]);
            }
            free(users);
        }
        if(!flagpm){
            FILE *fr = fopen("Usuarios", "r");
            if(fr == NULL){
                vermelho();
                printf("nao foi possivel abrir o arquivo :v\n");
                padrao();
                return;
            }
            fscanf(fr, "%d\n", &num_users);
            char **users = (char **) malloc(num_users * sizeof(char *));
            if(users == NULL){
                vermelho();
                printf("Erro de alocacao...\n");
                padrao();
                exit(1);
            }
            int i;
            for(i = 0; i < num_users; i++){
                users[i] = (char *) malloc(MAXNOME * sizeof(char));
                if(users[i] == NULL){
                    vermelho();
                    printf("Erro de alocacao...\n");
                    padrao();
                    exit(1);
                }
                fgets(users[i], MAXNOME, fr);
                int j;
                for(j = 0; users[i][j] != '\0'; j++);
                users[i][j - 1] = '\0';
            }
            fclose(fr);
            int maior_nump = 0;
            for(i = 1; i < num_users; i++){
                FILE *fr2 = fopen(users[i], "r");
                if(fr2 == NULL){
                    vermelho();
                    printf("Erro de alocacao...\n");
                    padrao();
                    exit(1);
                }
                int postagens;
                char efemero[MAXNOME];
                fscanf(fr2, "%d\n", &postagens);
                fgets(efemero, MAXNOME, fr2);
                fgets(efemero, MAXNOME, fr2);
                fscanf(fr2, "%d\n", &postagens);
                fscanf(fr2, "%d\n", &postagens);
                if(postagens > maior_nump){
                    maior_nump = postagens;
                }
                fclose(fr2);
            }
            printf("O(s) Usuario(s) com mais postagens sao:\n");
            for(i = 1; i < num_users; i++){
                FILE *fr3 = fopen(users[i], "r");
                if(fr3 == NULL){
                    vermelho();
                    printf("Erro de alocacao...\n");
                    padrao();
                    exit(1);
                }
                int postagens;
                char efemero[MAXNOME];
                fscanf(fr3, "%d\n", &postagens);
                fgets(efemero, MAXNOME, fr3);
                fgets(efemero, MAXNOME, fr3);
                fscanf(fr3, "%d\n", &postagens);
                fscanf(fr3, "%d\n", &postagens);
                if(postagens == maior_nump){
                    printf("%s- %d\n", users[i], postagens);
                }
                fclose(fr3);
            }
            for(i = 0; i < num_users; i++){
                free(users[i]);
            }
            free(users);
        }
        
    }
}

void adm_reset(){
    int flag=1;
    while (flag){
        printf("\tVOCE DESEJA APAGAR TODOS OS DADOS DA REDE SOCIAL? \n\n1 - Sim, resetar a rede social\n2 - Nao, retornar a pagina anterior\n");
        int escolha, i, numu, j;
        setbuf(stdin, NULL);
        scanf("%d", &escolha);
        int thanos = 1;
        switch(escolha){
            case 1:
                thanos = 0;
                break;
            case 2:
                flag=0;
                break;
            default:
                break;
        }
        if(!thanos){
            FILE *fr = fopen("Usuarios", "r");
            if(fr == NULL){
                vermelho();
                printf("Nao foi possivel abrir o arquivo Usuarios...\n");
                padrao();
                exit(1);
            }
            fscanf(fr, "%d\n", &numu);
            char **users = (char**) malloc(numu * sizeof(char*));
            if(users == NULL){
                vermelho();
                printf("Erro de Alocacao...\n");
                padrao();
                exit(1);
            }
            for(i = 0; i < numu; i++){
                users[i] = (char *) malloc(MAXNOME * sizeof(char));
                if(users[i] == NULL){
                    vermelho();
                    printf("Erro de Alocacao...\n");
                    padrao();
                    exit(1);
                }
                fgets(users[i], MAXNOME, fr);
                for(j = 0; users[i][j] != '\0'; j++);
                users[i][j - 1] = '\0';
            }
            fclose(fr);
            for (i = 2;i < numu; i++){
                remove(users[i]);
            }
            FILE *fr2 = fopen("Usuarios", "w");
            if(fr2 == NULL){
                vermelho();
                printf("Nao foi possivel abrir o arquivo usuarios...\n");
                padrao();
                exit(1);
            }
            fprintf(fr2,"2\nUsuarios\nAdes\n");
            fclose(fr2);
            for(i = 0; i < numu; i++){
                free(users[i]);
            }
            free(users);
            remove("Ades");
            FILE *fw = fopen("Ades", "w");
            if(fw == NULL){
                printf("Erro ao criar o arquivo Ades...\n");
                exit(1);
            }
            fprintf(fw, "1\nAdenilso\nAdes\n1\n1\nAdes\nOla, acabei de me cadastrar.\n");
            fclose(fw);
            printf("\n\nREDE SOCIAL RESETADA COM SUCESSO, FECHANDO O PROGRAMA...\n\n");
            exit(1);
            flag=0;
        }
    }
}

void adm(){
    int flag = 1;
    while(flag){
        printf("\tMENU ADM\n1 - Informacoes da Rede Social\n2 - Administrar Usuarios\n3 - Apagar todos os dados\n4 - Voltar\n");
        int escolha;
        setbuf(stdin, NULL);
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                adm_infrede();
                break;
            case 2:
                adm_usuarios();
                break;
            case 3:
                adm_reset();
                break;
            case 4:
                flag = 0;
                break;
            default:
                break;
        }
    }
}
