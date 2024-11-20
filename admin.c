// Funções auxiliares (a implementar)
void efetuarLogin();
void cadastrarInvestidor();
void excluirInvestidor();
void cadastrarCriptomoeda();
void excluirCriptomoeda();
void consultarSaldo();
void consultarExtrato();
void atualizarCotacao();

int main() {
    int opcao;
    char cpf[12], senha[20];

    printf("=== Sistema de Administrador ===\n");
    printf("Efetue login para continuar.\n");
    printf("CPF: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%s", senha);

    // Simulação de validação de login (implementar lógica)
    if (strcmp(cpf, "admin") == 0 && strcmp(senha, "1234") == 0) {
        do {
            printf("\n=== Menu Principal ===\n");
            printf("1. Cadastro de novo investidor\n");
            printf("2. Excluir investidor\n");
            printf("3. Cadastro de criptomoeda\n");
            printf("4. Excluir criptomoeda\n");
            printf("5. Consultar saldo de um investidor\n");
            printf("6. Consultar extrato de um investidor\n");
            printf("7. Atualizar cotação de criptomoedas\n");
            printf("0. Sair\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    cadastrarInvestidor();
                    break;
                case 2:
                    excluirInvestidor();
                    break;
                case 3:
                    cadastrarCriptomoeda();
                    break;
                case 4:
                    excluirCriptomoeda();
                    break;
                case 5:
                    consultarSaldo();
                    break;
                case 6:
                    consultarExtrato();
                    break;
                case 7:
                    atualizarCotacao();
                    break;
                case 0:
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    printf("Opcao invalida! Tente novamente.\n");
            }
        } while (opcao != 0);
    } else {
        printf("Login invalido! Encerrando o programa.\n");
    }

    return 0;
}

// Funções vazias para implementação
void cadastrarInvestidor() {
    printf("Funcao de cadastro de investidor.\n");
    // lógica de cadastro
}

void excluirInvestidor() {
    printf("Funcao de exclusao de investidor.\n");
    //  lógica de exclusão
}

void cadastrarCriptomoeda() {
    printf("Funcao de cadastro de criptomoeda.\n");
    // lógica de cadastro
}

void excluirCriptomoeda() {
    printf("Funcao de exclusao de criptomoeda.\n");
    //  lógica de exclusão
}

void consultarSaldo() {
    printf("Funcao de consulta de saldo.\n");
    //lógica de consulta
}

void consultarExtrato() {
    printf("Funcao de consulta de extrato.\n");
    // lógica de consulta
}

void atualizarCotacao() {
    printf("Funcao de atualizacao de cotacao de criptomoedas.\n");
    //lógica de atualização
}
