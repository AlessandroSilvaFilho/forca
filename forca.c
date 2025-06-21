#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

char palsecret[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
void adicionapalavra(){

    char quer;
    printf("voce deseja adicionar uma nova palavra? s/n\n");
    scanf(" %c", &quer);
    if(quer == 's'){

        char novapalavra[TAMANHO_PALAVRA];
        printf("qual a nova palavra? ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0){

            printf("desculpe, banco de dados nao disponivel");
            exit(1);}
        
        int qtd;
        fscanf(f,"%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

void abertura (){

    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");

}

void chuta(){

    char chute;
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
    }

int jachutou(int letra){

    int achou = 0;

    for(int j = 0; j < chutesdados; j++){

        if(chutes[j] == letra){

            achou = 1;
            break;
        }
    }
    return achou;
}  

void imprpalavra(){

    int erros = chuteserrados();

//forca
    printf("  _______      \n");
    printf(" |/      |     \n");

    printf(" |      %c%c%c \n", (erros >= 1 ?'(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));

    printf(" |      %c%c%c \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));

    printf(" |       %c    \n", (erros >= 2 ? '|' : ' '));

    printf(" |      %c %c  \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palsecret); i++){

        int achou = jachutou(palsecret[i]);

            if(achou){

                printf("%c ", palsecret[i]);
            }      
            else {

                printf("_ ");}
    }
    printf("\n");
}

int chuteserrados(){

    int erros = 0;

    for(int i = 0; i < chutesdados; i++){

        int existe = 0;
        for (int j = 0; j < strlen(palsecret); j++){

            if(chutes[i] == palsecret[j]){

            existe = 1;
            break;
            }
        }

        if(!existe) erros++;
    }
    return erros;
}

int enforcou(){


    return  chuteserrados() >= 5;    
}

void gerapalavra(){
    FILE* f;

    f = fopen("palavras.txt", "r");
    if(f == 0){
        printf("desculpe, o banco de dados nao esta disponive");
        exit(1);
    }

    int qtdpalavras;
    fscanf(f , "%d", &qtdpalavras);

    srand(time(0));
    int nrandom = rand() % qtdpalavras;

    for(int i = 0; i <= nrandom; i++){

        fscanf(f , "%s", palsecret);
    }


   fclose(f);
}

int ganhou(){

        for(int i = 0; i < strlen(palsecret); i++){
            if(!jachutou(palsecret[i])){
                return 0;
            }
        }
        return 1;
}

int main(){
    
    gerapalavra();
    abertura();

    do{

        imprpalavra();
        chuta();

    } while(!ganhou() && !enforcou());

    if(ganhou()){

        printf("\nParabens, voce ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    } else{

        printf("voce foi enforcado, a palavra era * %s *\n\n", palsecret);
        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n\n");
    }
    adicionapalavra();
}