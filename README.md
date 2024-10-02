# Exchange de Criptomoedas

Este é um programa simples para simular uma exchange de criptomoedas, onde é possível registrar investidores, realizar depósitos, saques e operações de compra e venda de criptomoedas como Bitcoin, Ethereum e Ripple.

## Funcionalidades

- Registrar novos investidores.
- Autenticar investidores existentes.
- Consultar saldo em reais e criptomoedas (Bitcoin, Ethereum e Ripple).
- Depositar e sacar valores.
- Comprar e vender criptomoedas com base nas cotações atuais.
- Exibir cotações atualizadas de Bitcoin, Ethereum e Ripple.

## Estrutura do Projeto

O projeto é dividido em várias funções para gerenciar o saldo dos investidores, registros de operações e funcionalidades de autenticação e transações:

- **`loading()`**: Exibe uma barra de carregamento.
- **`resgatarSaldo()`**: Recupera o saldo de um investidor a partir de um arquivo.
- **`salvarSaldo()`**: Salva o saldo atualizado do investidor em um arquivo.
- **`criarSaldo()`**: Cria um arquivo de saldo para um novo investidor.
- **`criarRegistro()`**: Cria um arquivo de registro para armazenar as transações de um investidor.
- **`lenRegistros()`**: Retorna o número de registros de transações de um investidor.
- **`salvarRegistro()`**: Salva um novo registro de transação.
- **`resgatarRegistros()`**: Exibe todos os registros de transações de um investidor.
- **`checkIsNumber()`**: Verifica se a string passada é um número.
- **`checkCpfExist()`**: Verifica se um CPF já está cadastrado.
- **`totalCpf()`**: Retorna o número total de CPFs registrados.
- **`registrarInvestidor()`**: Registra um novo investidor.
- **`autenticarInvestidor()`**: Autentica o login de um investidor.
- **`consultarsaldo()`**: Exibe o saldo do investidor em reais e criptomoedas.
- **`depositar()`**: Permite realizar um depósito em reais.
- **`sacar()`**: Permite realizar um saque em reais.
- **`exibirCotacao()`**: Exibe as cotações atuais de Bitcoin, Ethereum e Ripple.
- **`comprarcriptomoedas()`**: Permite ao investidor comprar criptomoedas com base no saldo em reais.
- **`vendercriptomoedas()`**: Permite ao investidor vender criptomoedas e receber reais.
- **`atualizarCotacao()`**: Atualiza aleatoriamente as cotações das criptomoedas.

## Como Executar

1. Clone o repositório ou baixe os arquivos.
2. Compile o arquivo `main.c`.
3. Execute o programa compilado.

```bash
gcc main.c -o Exchange-de-Criptomoedas
./Exchange-de-Criptomoedas
```
## Instruções de Uso

Após compilar e executar o programa, siga os passos abaixo para realizar operações básicas na exchange:

### 1. Registro de Investidor

Se você é um novo investidor, precisará se registrar primeiro. O programa solicitará:
- **Nome completo**
- **CPF** (número único para cada investidor)
- **Senha** (para autenticação)

Ao fornecer essas informações, seu saldo inicial será criado com 0 reais e 0 em criptomoedas.

### 2. Login

Caso já tenha se registrado, utilize seu CPF e senha para acessar sua conta.

### 3. Consultar Saldo

Após fazer login, você poderá consultar seu saldo em reais, Bitcoin, Ethereum e Ripple, escolhendo a opção "Consultar Saldo".

### 4. Depósito

Para adicionar fundos à sua conta em reais, escolha a opção "Depositar" e insira o valor desejado.

### 5. Saque

Se você deseja retirar dinheiro da sua conta em reais, escolha a opção "Sacar" e insira o valor que deseja sacar. O saldo em reais será atualizado.

### 6. Cotação de Criptomoedas

Escolha a opção "Exibir Cotações" para verificar o valor atual das criptomoedas (Bitcoin, Ethereum e Ripple) no mercado.

### 7. Comprar Criptomoedas

Com saldo em reais disponível, você pode comprar criptomoedas. Escolha a opção "Comprar Criptomoedas", selecione a criptomoeda desejada e insira o valor que deseja comprar com base na cotação atual.

### 8. Vender Criptomoedas

Caso queira vender suas criptomoedas e converter o valor para reais, escolha a opção "Vender Criptomoedas". Insira a quantidade de criptomoedas que deseja vender, e o valor será convertido para reais com base na cotação atual.

### 9. Histórico de Transações

Você pode visualizar o histórico de todas as suas transações (compra, venda, depósito, saque) escolhendo a opção "Exibir Registros de Transações".

### 10. Sair

Ao concluir suas operações, escolha a opção "Sair" para encerrar a sessão.

---

### Exemplo de Uso:

1. **Registro**: Insira seu nome, CPF e senha.
2. **Login**: Entre com o CPF e senha que você registrou.
3. **Depositar**: Adicione um valor de R$ 1.000 à sua conta.
4. **Consultar Saldo**: Verifique seu saldo atual (R$ 1.000 e 0 em criptomoedas).
5. **Comprar Bitcoin**: Compre R$ 500 em Bitcoin.
6. **Consultar Saldo**: Verifique seu novo saldo (R$ 500 em reais e a quantidade de Bitcoin comprada).
7. **Exibir Registros de Transações**: Veja seu histórico de depósito e compra.

---
