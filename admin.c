#include <stdio.h>
#include <string.h>
#include <windows.h>

void loading() {
    printf("\n");
    for (int i = 0; i <= 250; i++) {
        Sleep(12);
        printf(".");
    }
    printf("\n\n");
}
int totalCriptos();
int checkCriptoExist(char* sigla);
int totalCpf();
void criarSaldo(char* cpf);
void criarRegistro(char* cpf);
int checkIsNumber(char* str);
int checkCpfExist(char* cpf);
void efetuarLogin();
void cadastrarInvestidor();
void excluirInvestidor();
void cadastrarCriptomoeda();
void excluirCriptomoeda();
void consultarSaldo();
void consultarExtrato();
void atualizarCotacao();

int main() {
    int opcao = 1;
    char cpf[30], senha[30];

    printf("=== Sistema de Administrador ===\n");
    printf("Efetue login para continuar.\n");

    while (1) {
        printf("CPF: ");
        scanf("%s", cpf);
        getchar();

        printf("Senha: ");
        scanf("%s", senha);
        getchar();

        loading();
        if (strcmp(cpf, "admin") == 0 && strcmp(senha, "1234") == 0) {
            while (opcao) {        
                printf("\n=== Menu Principal ===\n\n");
                printf("1. Cadastro de novo investidor\n");
                printf("2. Excluir investidor\n");
                printf("3. Cadastro de criptomoeda\n");
                printf("4. Excluir criptomoeda\n");
                printf("5. Consultar saldo de um investidor\n");
                printf("6. Consultar extrato de um investidor\n");
                printf("7. Atualizar cotacao de criptomoedas\n");
                printf("0. Sair\n\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                getchar();
                
                loading();
                
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
            };
        } else {
            char opcao[20];
        
            printf("CPF ou senha incorreto!\n\n");
            printf("Deseja tentar novamente? (s para sim | enter para nao): ");
            
            scanf("%[^\n]", opcao);
            getchar();

            if (strcmp(opcao, "s") == 0) {
                continue;
            } else {
                printf("Saindo do sistema...\n");
                return 0;
            }
        }
    }
    return 0;
}

void cadastrarInvestidor() {
    char cpf[100];
    char nome[100];
    char senha[20];
    char opcao[10];

    printf("Digite o nome do investidor: ");
    scanf("%[^\n]", nome);
    getchar();

    printf("Digite o CPF do investidor: ");
    scanf("%[^\n]", cpf);
    getchar();

    printf("Digite a senha do investidor (4 digitos): ");
    scanf("%[^\n]", senha);
    getchar();

    if (totalCpf() >= 10) {
        printf("Numero maximo de investidores atingido!\n\n");
        return;
    }

    if (strlen(nome) == 0 || strlen(cpf) == 0 || strlen(senha) == 0) {
        printf("Nome, CPF ou senha invalidos!\n\n");
        loading();
        cadastrarInvestidor();
        return;
    }
    if (strlen(cpf) != 11 || !checkIsNumber(cpf)) {
        printf("CPF invalido!\n\n");
        loading();
        cadastrarInvestidor();
        return;
    }
    if (strlen(senha) < 4) 
    {
        printf("Senha invalida!\n\n");
        loading();
        cadastrarInvestidor();
        return;
    }
    if (checkCpfExist(cpf)) {
        printf("CPF ja cadastrado!\n\n");
        loading();
        cadastrarInvestidor();
        return;
    }

    FILE *file = fopen("investidores.txt", "a");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo investidores.txt");
        return;
    }

    fprintf(file, "%s\n%s\n%s\n", nome, cpf, senha);
    fclose(file);

    FILE *fileCpfs = fopen("cpfs.txt", "a");
    
    if (fileCpfs == NULL) {
        perror("Erro ao abrir o arquivo cpfs.txt");
        return;
    }

    fprintf(fileCpfs, "%s\n", cpf);
    fclose(fileCpfs);

    criarSaldo(cpf);
    criarRegistro(cpf);
    printf("Investidor registrado com sucesso!\n\n");
    
    printf("Deseja registrar outro investidor? (s para sim | enter para nao): ");
    scanf("%[^\n]", opcao);
    getchar();

    opcao[1] = '\0';

    if (strcmp(opcao, "s") == 0) {
        cadastrarInvestidor();
    }
    
    return;

}

void excluirInvestidor() {
    char cpf[100];

    printf("Digite o CPF do investidor que deseja excluir: ");
    scanf("%[^\n]", cpf);
    getchar();

    loading();

    if (!checkCpfExist(cpf)) {
        printf("CPF nao cadastrado!\n\n");
        return;
    }

    FILE *file = fopen("investidores.txt", "r");
    FILE *fileTemp = fopen("temp.txt", "w");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo investidores.txt");
        return;
    }
    if (fileTemp == NULL) {
        perror("Erro ao abrir o arquivo temp.txt");
        return;
    }

    char cpfCheck[100];
    char nome[100];
    char senha[20];

    while (1) {
        if (feof(file)) {
            break;
        }

        fscanf(file, "%[^\n]", nome);
        fgetc(file);
        fscanf(file, "%[^\n]", cpfCheck);
        fgetc(file);
        fscanf(file, "%[^\n]", senha);
        fgetc(file);

        if (strcmp(cpf, cpfCheck) == 0) {
            continue;
        }

        fprintf(fileTemp, "%s\n%s\n%s\n", nome, cpfCheck, senha);
    }
    fclose(file);
    fclose(fileTemp);

    remove("investidores.txt");
    rename("temp.txt", "investidores.txt");
    
    char arq[50];

    sprintf(arq, "registros/%s.txt", cpf);
    remove(arq);
    sprintf(arq, "saldo/%s.txt", cpf);
    remove(arq);

    printf("Investidor excluido com sucesso!\n\n");
    
    loading();
    return;
}

void cadastrarCriptomoeda() {
    char nome[100];
    char sigla[10];
    float cotacao;
    float txCompra;
    float txVenda;

    printf("Digite o nome da criptomoeda: ");
    scanf("%[^\n]", nome);
    getchar();

    printf("Digite a sigla da criptomoeda: ");
    scanf("%[^\n]", sigla);
    getchar();

    printf("Digite a cotacao atual da criptomoeda: ");
    scanf("%f", &cotacao);
    getchar();

    printf("Digite a taxa de compra da criptomoeda (1.0 = 100%%): ");
    scanf("%f", &txCompra);
    getchar();

    printf("Digite a taxa de venda da criptomoeda (1.0 = 100%%): ");
    scanf("%f", &txVenda);
    getchar();

    if(totalCriptos() >= 10) {
        printf("Numero maximo de criptomoedas atingido!\n\n");
        return;
    }

    if (checkCriptoExist(sigla)) {
        printf("Sigla ja cadastrada!\n\n");
        loading();
        cadastrarCriptomoeda();
        return;
    }

    if (strlen(nome) == 0 || strlen(sigla) == 0) {
        printf("Nome ou sigla invalidos!\n\n");
        loading();
        cadastrarCriptomoeda();
        return;
    }

    if (cotacao <= 0 || txCompra <= 0 || txVenda <= 0 || txCompra > 1 || txVenda > 1) {
        printf("Cotacao ou taxa invalida!\n\n");
        loading();
        cadastrarCriptomoeda();
        return;
    }

    FILE *file = fopen("criptos.txt", "a");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo criptos.txt");
        return;
    }

    fprintf(file, "%s\n", sigla);
    fclose(file);

    char arq[50];
    sprintf(arq, "cotacoes/%s.txt", sigla);
    file = fopen(arq, "w");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo cotacoes.txt");
        return;
    }

    fprintf(file, "%s\n%f\n%f\n%f\n", nome, cotacao, txCompra, txVenda);
    fclose(file);

    printf("Criptomoeda cadastrada com sucesso!\n\n");
    loading();
    return;
}

void excluirCriptomoeda() {
    char sigla[10];

    printf("Digite a sigla da criptomoeda que deseja excluir: ");
    scanf("%[^\n]", sigla);
    getchar();

    loading();

    if (!checkCriptoExist(sigla)) {
        printf("Sigla nao cadastrada!\n\n");
        return;
    }

    FILE *file = fopen("criptos.txt", "r");
    FILE *fileTemp = fopen("temp.txt", "w");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo criptos.txt");
        return;
    }
    if (fileTemp == NULL) {
        perror("Erro ao abrir o arquivo temp.txt");
        return;
    }

    char siglaCheck[10];

    while (1) {
        if (feof(file)) {
            break;
        }

        fscanf(file, "%[^\n]", siglaCheck);
        fgetc(file);

        if (strcmp(sigla, siglaCheck) == 0) {
            continue;
        }

        fprintf(fileTemp, "%s\n", siglaCheck);
    }
    fclose(file);
    fclose(fileTemp);

    remove("criptos.txt");
    rename("temp.txt", "criptos.txt");

    char arq[50];
    sprintf(arq, "cotacoes/%s.txt", sigla);
    remove(arq);
    
    printf("Criptomoeda excluida com sucesso!\n\n");
    loading();
    return;
}

void consultarSaldo() {
    printf("Funcao de consulta de saldo.\n");
}

void consultarExtrato() {
    printf("Funcao de consulta de extrato.\n");
}

void atualizarCotacao() {
    printf("Funcao de atualizacao de cotacao de criptomoedas.\n");
}

int totalCpf() {
    FILE *file = fopen("cpfs.txt", "r");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo cpfs.txt");
        return 0;
    }

    int i = 0;
    char c;

    // Loop para contar o número de linhas no arquivo
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            i++;
        }
    }

    fclose(file);
    return i;
}

void criarSaldo(char* cpf) {
    char arq[50];
    sprintf(arq, "saldo/%s.txt", cpf);
    
    FILE *file = fopen(arq, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo saldo.txt");
        return;
    }

    fprintf(file, "0.0\n");
    fprintf(file, "0.0\n");
    fprintf(file, "0.0\n");
    fprintf(file, "0.0\n");

    fclose(file);
}

void criarRegistro(char* cpf) {
    char arq[50];
    sprintf(arq, "registros/%s.txt", cpf);
    
    FILE *file = fopen(arq, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo registro.txt");
        return;
    }

    fclose(file);
}

int checkIsNumber(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int checkCpfExist(char* cpf) {
    char cpfCheck[20];
    FILE *file = fopen("cpfs.txt", "r");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo cpfs.txt");
        return 0;
    }

    int i = 0;
    while (1) {
        if (feof(file)) {
            break;
        }

        fscanf(file, "%[^\n]", cpfCheck);
        fgetc(file);

        if (strcmp(cpf, cpfCheck) == 0) {
            fclose(file);
            return 1;
        }
        i++;
    }
    fclose(file);
    return 0;
}

int totalCriptos() {
    FILE *file = fopen("criptos.txt", "r");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo criptos.txt");
        return 0;
    }

    int i = 0;
    char c;

    // Loop para contar o número de linhas no arquivo
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            i++;
        }
    }

    fclose(file);
    return i;
}

int checkCriptoExist(char* sigla) {
    char siglaCheck[10];
    FILE *file = fopen("criptos.txt", "r");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo criptos.txt");
        return 0;
    }

    int i = 0;
    while (1) {
        if (feof(file)) {
            break;
        }

        fscanf(file, "%[^\n]", siglaCheck);
        fgetc(file);

        if (strcmp(sigla, siglaCheck) == 0) {
            fclose(file);
            return 1;
        }
        i++;
    }
    fclose(file);
    return 0;
}