#include <stdio.h>
#include <string.h>

// Definindo a estrutura Territorio
// Cada território possui um nome, uma cor de exército e uma quantidade de tropas
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Vetor para armazenar 5 territórios
    Territorio territorios[5];

    // Laço para entrada dos dados dos territórios
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastrando Território %d ---\n", i + 1);

        // Entrada do nome do território
        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);

        // Entrada da cor do exército
        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor);

        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n🌍 Territórios cadastrados:\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
