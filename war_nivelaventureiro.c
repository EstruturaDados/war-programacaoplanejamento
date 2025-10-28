#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território no jogo War
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n🛡️ Cadastro do território %d:\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n🌍 Territórios cadastrados:\n");
    for (int i = 0; i < total; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("⚠️ Não é permitido atacar um território da mesma cor!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Dados rolados:\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ Ataque bem-sucedido! O território %s foi conquistado.\n", defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("❌ Ataque falhou! O atacante perde uma tropa.\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// Função para liberar a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\n --- Memória liberada com sucesso. ---\n");
}

int main() {
    srand(time(NULL)); // Inicializa a aleatoriedade

    int total;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &total);

    // Alocação dinâmica de memória para os territórios
    Territorio* mapa = (Territorio*) calloc(total, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, total);
    exibirTerritorios(mapa, total);

    // Simulação de ataque
    int atacante, defensor;
    printf("\n⚔️ Escolha os territórios para o ataque:\n");
    printf("Número do território atacante (1 a %d): ", total);
    scanf("%d", &atacante);
    printf("Número do território defensor (1 a %d): ", total);
    scanf("%d", &defensor);

    // Validação de índices
    if (atacante < 1 || atacante > total || defensor < 1 || defensor > total) {
        printf("❌ Índices inválidos.\n");
    } else {
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
        exibirTerritorios(mapa, total);
    }

    liberarMemoria(mapa);
    return 0;
}
