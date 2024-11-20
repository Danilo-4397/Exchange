#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INVESTIDORES 100
#define MAX_CRIPTOMOEDAS 100

typedef struct {
    char nome[50];
    char cpf[12];
    char senha[20];
    double saldo;
    char extrato[500]; // Simplificado para registrar transações
} Investidor;

typedef struct {
    char nome[50];
    double cotacao_inicial;
    double taxa_compra;
    double taxa_venda;
} Criptomoeda;

// Variáveis globais
Investidor investidores[MAX_INVESTIDORES];
Criptomoeda criptomoedas[MAX_CRIPTOMOEDAS];
int totalInvestidores = 0;
int totalCriptomoedas = 0;

// Credenciais do administrador
char adminCpf[12] = "46802804840";
char adminSenha[20] = "439711";

// Funções auxiliares
int buscarInvestidor(char cpf[]) {
    for (int i = 0; i < totalInvestidores; i++) {
        if (strcmp(investidores[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarCriptomoeda(char nome[]) {
    for (int i = 0; i < totalCriptomoedas; i++) {
        if (strcmp(criptomoedas[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Opções do programa
void cadastrarInvestidor() {
    if (totalInvestidores >= MAX_INVESTIDORES) {
        printf("Limite máximo de investidores atingido!\n");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", investidores[totalInvestidores].nome);
    printf("CPF: ");
    scanf("%s", investidores[totalInvestidores].cpf);
    printf("Senha: ");
    scanf("%s", investidores[totalInvestidores].senha);
    investidores[totalInvestidores].saldo = 0.0;
    strcpy(investidores[totalInvestidores].extrato, "Extrato inicial\n");

    totalInvestidores++;
    printf("Investidor cadastrado com sucesso!\n");
}

void excluirInvestidor() {
    char cpf[12];
    printf("Informe o CPF do investidor a ser excluído: ");
    scanf("%s", cpf);

    int pos = buscarInvestidor(cpf);
    if (pos == -1) {
        printf("Investidor não encontrado!\n");
        return;
    }

    printf("Investidor encontrado: %s\n", investidores[pos].nome);
    printf("Deseja realmente excluir este investidor? (1-Sim / 0-Não): ");
    int confirmacao;
    scanf("%d", &confirmacao);

    if (confirmacao == 1) {
        for (int i = pos; i < totalInvestidores - 1; i++) {
            investidores[i] = investidores[i + 1];
        }
        totalInvestidores--;
        printf("Investidor excluído com sucesso!\n");
    } else {
        printf("Operação cancelada.\n");
    }
}

void cadastrarCriptomoeda() {
    if (totalCriptomoedas >= MAX_CRIPTOMOEDAS) {
        printf("Limite máximo de criptomoedas atingido!\n");
        return;
    }

    printf("Nome da criptomoeda: ");
    scanf(" %[^\n]", criptomoedas[totalCriptomoedas].nome);
    printf("Cotação inicial: ");
    scanf("%lf", &criptomoedas[totalCriptomoedas].cotacao_inicial);
    printf("Taxa de compra: ");
    scanf("%lf", &criptomoedas[totalCriptomoedas].taxa_compra);
    printf("Taxa de venda: ");
    scanf("%lf", &criptomoedas[totalCriptomoedas].taxa_venda);

    totalCriptomoedas++;
    printf("Criptomoeda cadastrada com sucesso!\n");
}

void excluirCriptomoeda() {
    char nome[50];
    printf("Informe o nome da criptomoeda a ser excluída: ");
    scanf(" %[^\n]", nome);

    int pos = buscarCriptomoeda(nome);
    if (pos == -1) {
        printf("Criptomoeda não encontrada!\n");
        return;
    }

    printf("Criptomoeda encontrada: %s\n", criptomoedas[pos].nome);
    printf("Deseja realmente excluir esta criptomoeda? (1-Sim / 0-Não): ");
    int confirmacao;
    scanf("%d", &confirmacao);

    if (confirmacao == 1) {
        for (int i = pos; i < totalCriptomoedas - 1; i++) {
            criptomoedas[i] = criptomoedas[i + 1];
        }
        totalCriptomoedas--;
        printf("Criptomoeda excluída com sucesso!\n");
    } else {
        printf("Operação cancelada.\n");
    }
}

void consultarSaldoInvestidor() {
    char cpf[12];
    printf("Informe o CPF do investidor: ");
    scanf("%s", cpf);

    int pos = buscarInvestidor(cpf);
    if (pos == -1) {
        printf("Investidor não encontrado!\n");
        return;
    }

    printf("Saldo do investidor %s: %.2f\n", investidores[pos].nome, investidores[pos].saldo);
}

void consultarExtratoInvestidor() {
    char cpf[12];
    printf("Informe o CPF do investidor: ");
    scanf("%s", cpf);

    int pos = buscarInvestidor(cpf);
    if (pos == -1) {
        printf("Investidor não encontrado!\n");
        return;
    }

    printf("Extrato do investidor %s:\n%s\n", investidores[pos].nome, investidores[pos].extrato);
}

void atualizarCotacao() {
    char nome[50];
    printf("Informe o nome da criptomoeda: ");
    scanf(" %[^\n]", nome);

    int pos = buscarCriptomoeda(nome);
    if (pos == -1) {
        printf("Criptomoeda não encontrada!\n");
        return;
    }

    printf("Cotação atual da criptomoeda %s: %.2f\n", criptomoedas[pos].nome, criptomoedas[pos].cotacao_inicial);
    printf("Informe a nova cotação: ");
    scanf("%lf", &criptomoedas[pos].cotacao_inicial);

    printf("Cotação atualizada com sucesso!\n");
}

int main() {
    char cpf[12], senha[20];
    printf("Login de Administrador\n");
    printf("CPF: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%s", senha);

    if (strcmp(cpf, adminCpf) == 0 && strcmp(senha, adminSenha) == 0) {
        int opcao;
        do {
            printf("\nMenu Principal:\n");
            printf("1. Cadastrar Investidor\n");
            printf("2. Excluir Investidor\n");
            printf("3. Cadastrar Criptomoeda\n");
            printf("4. Excluir Criptomoeda\n");
            printf("5. Consultar Saldo de Investidor\n");
            printf("6. Consultar Extrato de Investidor\n");
            printf("7. Atualizar Cotação de Criptomoeda\n");
            printf("0. Sair\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1: cadastrarInvestidor(); break;
                case 2: excluirInvestidor(); break;
                case 3: cadastrarCriptomoeda(); break;
                case 4: excluirCriptomoeda(); break;
                case 5: consultarSaldoInvestidor(); break;
                case 6: consultarExtratoInvestidor(); break;
                case 7: atualizarCotacao(); break;
                case 0: printf("Saindo...\n"); break;
                default: printf("Opção inválida!\n");
            }
        } while (opcao != 0);
    } else {
        printf("Login inválido!\n");
    }

    return 0;
}
