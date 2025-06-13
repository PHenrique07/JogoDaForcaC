#include <stdio.h>
#include <string.h> // Biblioteca para manipulação de strings
#include "forca.h"
#include <stdlib.h>
#include <time.h> // Biblioteca para manipulação de tempo



// Variáveis globais para armazenar a palavra secreta, os chutes e o número de chutes dados
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0; // Substituído de "tentativas" para "chutesdados"

// Função que exibe a abertura do jogo
void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

// Função que solicita ao jogador uma letra e armazena no array de chutes
void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute); // Adicionado espaço antes de %c para evitar problemas com caracteres residuais no buffer

    chutes[chutesdados] = chute; // Armazena o chute no array de chutes
    chutesdados++; // Incrementa o número de chutes dados
}

// Função que verifica se uma letra já foi chutada
int jachutou(char letra) {
    for (int j = 0; j < chutesdados; j++) {
        if (chutes[j] == letra) { // Verifica se a letra já foi chutada
            return 1; // Retorna 1 se a letra foi encontrada
        }
    }
    return 0; // Retorna 0 se a letra não foi encontrada
}

// Função que desenha a forca e exibe o progresso do jogador
void desenhaforca() {
    printf("Voce ja deu %d chutes\n", chutesdados); // Exibe o número de chutes dados

    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if (jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]); // Mostra a letra se já foi chutada
        } else {
            printf("_ "); // Mostra "_" para letras ainda não descobertas
        }
    }
    printf("\n");
}

int chuteserrados() {
    
}

// Função que escolhe a palavra secreta
void escolhepalavra() {
    FILE* f; // Declara um ponteiro para o arquivo
    f = fopen("palavras.txt", "r"); // Abre o arquivo de palavras e r de read
    if (f == 0) { // Verifica se o arquivo foi aberto corretamente
        printf("Desculpe, não consegui abrir o arquivo\n");
        exit(1); // Encerra o programa se o arquivo não puder ser aberto
    }
    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras); // Lê o número de palavras do arquivo

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for (int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta); // Lê a palavra secreta do arquivo
    }

    fclose(f); // Fecha o arquivo
}

int acertou() {
    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if (!jachutou(palavrasecreta[i])) { // Verifica se todas as letras foram chutadas
            return 0; // Retorna 0 se ainda houver letras não chutadas
        }
    }
    return 1; // Retorna 1 se o jogador ganhou
}

int enforcou() {
    int erros = 0; // Inicializa o número de erros
    for (int i = 0; i < chutesdados; i++) {
        int existe = 0;
        for (int j = 0; j < strlen(palavrasecreta); j++) { // strlen retorna o tamanho da string
            if (chutes[i] == palavrasecreta[j]) {
                existe = 1; // Retorna 0 se o jogador ainda não perdeu
                break;
            }
        }
        if (!existe) erros++; // Incrementa o número de erros se a letra não estiver na palavra secreta
    }
    return erros >= 5; // Retorna 1 se o jogador perdeu (5 erros)
}

void adicionapalavra() {
    char quer;
    printf("Voce deseja adicionar uma nova palavra? (S/N)\n");
    scanf(" %c", &quer); 

    if (quer == 'S' || quer == 's') {
        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra?\n");
        scanf("%s", novapalavra);

        // Primeiro, lemos a quantidade atual
        FILE* f = fopen("palavras.txt", "r");
        if (f == 0) {
            printf("Desculpe, não consegui abrir o arquivo\n");
            exit(1);
        }
        
        int qtd;
        fscanf(f, "%d", &qtd);
        fclose(f);
        
        // Agora abrimos para adicionar no final
        f = fopen("palavras.txt", "a");  // Modo append (adiciona no final)
        if (f == 0) {
            printf("Desculpe, não consegui abrir o arquivo\n");
            exit(1);
        }
        
        fprintf(f, "\n%s", novapalavra);
        fclose(f);
        
        // Atualizamos a contagem no início do arquivo
        f = fopen("palavras.txt", "r+");
        if (f == 0) {
            printf("Desculpe, não consegui abrir o arquivo\n");
            exit(1);
        }
        
        fprintf(f, "%d", qtd + 1);
        fclose(f);
        
        printf("Palavra adicionada com sucesso!\n");
    }
}

//*********************************************************************************************************************************** */

int main() {
    abertura(); // Chama a função de abertura do jogo
    escolhepalavra(); // Chama a função para escolher a palavra secreta

    do {
        desenhaforca(); // Exibe o estado atual da forca
        chuta(); // Solicita um chute ao jogador
    } while (!acertou() && !enforcou()); // Continua o jogo enquanto o jogador não acertar ou não perder

    printf("Fim de jogo!\n"); // Mensagem final do jogo
    adicionapalavra();
    return 0;
}