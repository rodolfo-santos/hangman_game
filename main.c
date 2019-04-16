#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

int tentativas;
char chutadas[26];

int enforcou = 0;
int chances;
int ganhou = 0;

char palavra_secreta[20];

char escolhe_dificuldade(){
    char tecla;
    printf("Aperte a tecla ( F ) para jogar no Fácil\n");
    printf("Aperte a tecla ( M ) para jogar no Médio\n");
    printf("Aperte a tecla ( D ) para jogar no Difícil\n");

    void dificuldade(){
    tecla = toupper(getch());
        switch(tecla){
        case 'F' : printf("\nVocê escolheu Fácil\n");
            break;
        case 'M' : printf("\nVocê escolheu Medio\n");
            break;
        case 'D' : printf("\nVocê escolheu Dificil\n");
            break;
        default: dificuldade();
        }
    }

    dificuldade();
    printf("\nPressione Enter para continuar...");
    getch();
    system("cls");

    return tecla;
}

void configura_dificuldade(escolha){
    switch(escolha){
        case 'F': chances = 20;
            break;
        case 'M': chances = 10;
            break;
        case 'D': chances = 5;
            break;
    }
}

void apresentacao(){
    printf("#####################");
    printf("\n### JOGO DA FORCA ###");
    printf("\n#####################\n");
}

void escolhe_palavra(){
    sprintf(palavra_secreta, "MELANCIA");
}

int chuta_letra(){
    char chute;
    printf("Tecle uma letra: ");
    chute = getch();

    chute = toupper(chute);

    errou(chute);

    return chute;
}

void errou(chute){
    int achou = 0;
    for(int i = 0; i<strlen(palavra_secreta); i++){
        if(chute == palavra_secreta[i]){
            achou = 1;
            break;
        }
    }
    if(!achou){
        chances--;
    }
}

void desenha_forca(){
    for(int i = 0; i < strlen(palavra_secreta); i++){
        int achou = 0;
        for(int j = 0; j < tentativas ; j++){
            if(chutadas[j] == palavra_secreta[i]){
                achou = 1;
                break;
            }
        }
        if(achou){
            printf("%c ", palavra_secreta[i]);
        }else{
            printf("_ ");
        }

    }
    printf("\n\n");
}

void armazena_chute(){
    chutadas[tentativas] = chuta_letra();
    tentativas++;
}

int ganhou_o_jogo(){
    int correta = 0;
    for(int a = 0; a<strlen(palavra_secreta); a++){
        for(int b = 0; b <= strlen(chutadas) ; b++){
            if(palavra_secreta[a] == chutadas[b]){
                correta++;
                break;
            }
        }
    }
    if(correta == strlen(palavra_secreta)){
        printf("Parabéns Você Ganhou!");
        return 1;
    }
    else{
        return 0;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    char escolha = escolhe_dificuldade();
    configura_dificuldade(escolha);
    apresentacao();
    escolhe_palavra();

    do {
        printf("Você tem %i chances!\n", chances);
        desenha_forca();
        armazena_chute();

        system("cls");
        printf("\n");

        if(chances == 0){
            printf("INFELIZMENTE VOCÊ PERDEU!! :C \n\n");
            scanf("%c", &palavra_secreta);
            enforcou = 1;

        }
    }while(!ganhou_o_jogo() && !enforcou);
}
