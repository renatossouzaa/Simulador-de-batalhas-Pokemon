#include <stdio.h>
#include <string.h>
#define MAX_POKEMON 100
#define MAX_NOME 50
typedef struct {
    int ataque;
    int defesa;
    int vida;
    char nome[MAX_NOME];
    char tipo[MAX_NOME];
} Pokemon;

float vantagens(Pokemon atacante, char *tipo_oponente) {
    if ((strcmp(atacante.tipo, "eletrico") == 0 && strcmp(tipo_oponente, "agua") == 0) ||
        (strcmp(atacante.tipo, "agua") == 0 && strcmp(tipo_oponente, "fogo") == 0) ||
        (strcmp(atacante.tipo, "fogo") == 0 && strcmp(tipo_oponente, "gelo") == 0) ||
        (strcmp(atacante.tipo, "gelo") == 0 && strcmp(tipo_oponente, "pedra") == 0) ||
        (strcmp(atacante.tipo, "pedra") == 0 && strcmp(tipo_oponente, "eletrico") == 0)) {
        return atacante.ataque * 1.2;
    } else if ((strcmp(atacante.tipo, "eletrico") == 0 && strcmp(tipo_oponente, "pedra") == 0) ||
               (strcmp(atacante.tipo, "agua") == 0 && strcmp(tipo_oponente, "eletrico") == 0) ||
               (strcmp(atacante.tipo, "fogo") == 0 && strcmp(tipo_oponente, "agua") == 0) ||
               (strcmp(atacante.tipo, "gelo") == 0 && strcmp(tipo_oponente, "fogo") == 0) ||
               (strcmp(atacante.tipo, "pedra") == 0 && strcmp(tipo_oponente, "gelo") == 0)) {
        return atacante.ataque * 0.8;
    }
    return atacante.ataque;
}

void batalha_pokemon(Pokemon jogador1[], int n1, Pokemon jogador2[], int n2) {
    int i1 = 0, i2 = 0;

    printf("\nResultados finais: \n");

    while (i1 < n1 && i2 < n2) {
        float ataque_ajustado = vantagens(jogador1[i1], jogador2[i2].tipo);

        if (ataque_ajustado > jogador2[i2].defesa) {
            jogador2[i2].vida -= (ataque_ajustado - jogador2[i2].defesa);
        } else {
            jogador2[i2].vida -= 1;
        }

        if (jogador2[i2].vida <= 0) {
            printf("%s venceu %s\n", jogador1[i1].nome, jogador2[i2].nome);
            i2++;
        } else {
            float ataque_oponente = vantagens(jogador2[i2], jogador1[i1].tipo);

            if (ataque_oponente > jogador1[i1].defesa) {
                jogador1[i1].vida -= (ataque_oponente - jogador1[i1].defesa);
            } else {
                jogador1[i1].vida -= 1;
            }

            if (jogador1[i1].vida <= 0) {
                printf("%s venceu %s\n", jogador2[i2].nome, jogador1[i1].nome);
                i1++;
            }
        }
    }

    if (i1 < n1) {
        printf("\nTreinador 1 Venceu!! \n\n");
        printf("Pokemon sobreviventes:\n");
        for (int i = i1; i < n1; i++) {
            printf("%s\n", jogador1[i].nome);
        }

        printf("\nPokemon derrotados:\n");
        for (int i = 0; i < i2; i++) {
            printf("%s\n", jogador2[i].nome);
        }
    } else {
        printf("\nTreinador 2 Venceu!! \n\n");
        printf("Pokemon sobreviventes:\n");
        for (int i = i2; i < n2; i++) {
            printf("%s\n", jogador2[i].nome);
        }

        printf("\nPokemon derrotados:\n");
        for (int i = 0; i < i1; i++) {
            printf("%s\n", jogador1[i].nome);
        }
    }
}

void carregar_dados(const char *arquivopokemon, Pokemon jogador1[], int *n1, Pokemon jogador2[], int *n2) {
    FILE *f = fopen(arquivopokemon, "r");
    if (!f) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fscanf(f, "%d %d", n1, n2);

    for (int i = 0; i < *n1; i++) {
        fscanf(f, "%s %d %d %d %s", jogador1[i].nome, &jogador1[i].ataque, &jogador1[i].defesa, &jogador1[i].vida, jogador1[i].tipo);
    }

    for (int i = 0; i < *n2; i++) {
        fscanf(f, "%s %d %d %d %s", jogador2[i].nome, &jogador2[i].ataque, &jogador2[i].defesa, &jogador2[i].vida, jogador2[i].tipo);
    }

    fclose(f);
}

int main() {
    Pokemon jogador1[MAX_POKEMON], jogador2[MAX_POKEMON];
    int n1, n2;

    carregar_dados("arquivopokemon.txt", jogador1, &n1, jogador2, &n2);

    printf("\nPokemons do Treinador 1:\n");
    for (int i = 0; i < n1; i++) {
        printf("%s %d %d %d %s\n", jogador1[i].nome, jogador1[i].ataque, jogador1[i].defesa, jogador1[i].vida, jogador1[i].tipo);
    }

    printf("\nPokemons do Treinador 2:\n");
    for (int i = 0; i < n2; i++) {
        printf("%s %d %d %d %s\n", jogador2[i].nome, jogador2[i].ataque, jogador2[i].defesa, jogador2[i].vida, jogador2[i].tipo);
    }

    batalha_pokemon(jogador1, n1, jogador2, n2);

    return 0;
}