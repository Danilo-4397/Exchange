# Exchange de Criptomoedas Investidor

## Objetivo do Projeto
Este projeto consiste em uma aplicação de console desenvolvida em C para gerenciar uma Exchange de criptomoedas. A Exchange permite que usuários realizem operações com três tipos de criptomoedas: Bitcoin, Ethereum e Ripple. O sistema inclui funcionalidades de login, consulta de saldo, extrato de operações, depósitos, saques, compra e venda de criptomoedas, além da atualização de cotações.

## Funcionalidades
A aplicação oferece as seguintes operações para o usuário investidor:

1. **Login**:
   - Efetuar login usando CPF e senha. O menu principal é acessível apenas se as informações estiverem corretas.

2. **Consultar Saldo**:
   - Exibir saldo de reais, bitcoin, ethereum e ripple da carteira de investimentos.

3. **Consultar Extrato**:
   - Salvar em arquivo texto os dados do usuário e informações de todas as transações realizadas (data, valores e taxas).

4. **Depositar Reais**:
   - Permitir que o usuário deposite reais na carteira de investimento.

5. **Sacar Reais**:
   - Permitir que o usuário saque reais, validando a senha antes da transação.

6. **Comprar Criptomoedas**:
   - Permitir a compra de criptomoedas, informando o valor e validando a senha. Exibir informações da compra, incluindo a taxa cobrada, e solicitar confirmação do usuário.

7. **Vender Criptomoedas**:
   - Permitir a venda de criptomoedas, exibindo informações da venda e taxa cobrada, além de solicitar confirmação do usuário.

8. **Atualizar Cotação**:
   - Atualizar as cotações das criptomoedas usando valores aleatórios, com variações de no máximo 5% e mínimo -5%.

## Taxas
- **Bitcoin**:
  - Taxa de 2% na compra
  - Taxa de 3% na venda
- **Ethereum**:
  - Taxa de 1% na compra
  - Taxa de 2% na venda
- **Ripple**:
  - Taxa de 1% na compra
  - Taxa de 1% na venda

## Armazenamento de Dados
- O programa armazena dados de até 10 usuários e o histórico das últimas 100 transações realizadas por cada usuário.
- Utiliza arquivos binários para garantir a persistência dos dados das carteiras dos usuários.

## Compilação e Execução
Para compilar e executar o projeto, siga os passos abaixo:

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/Danilo-4397/Exchange.git
   cd Exchange

**Nome do integrante**:
Danilo Cassiano de Souza RA:22.124.090-6

# # Exchange de Criptomoedas ADMINISTRADOR 

Este projeto é um sistema em linguagem C que permite o gerenciamento de investidores e criptomoedas, destinado a um administrador. O sistema oferece funcionalidades para cadastrar, excluir, consultar e atualizar informações sobre investidores e criptomoedas.

---

## Funcionalidades

### Investidor
1. **Cadastrar Investidor**: Permite o registro de novos investidores com nome, CPF e senha.
2. **Excluir Investidor**: Remove investidores cadastrados no sistema usando o CPF.
3. **Consultar Saldo**: Exibe o saldo atual de um investidor.
4. **Consultar Extrato**: Mostra o extrato de transações de um investidor.

### Criptomoedas
1. **Cadastrar Criptomoeda**: Adiciona uma nova criptomoeda com informações como cotação inicial, taxa de compra e taxa de venda.
2. **Excluir Criptomoeda**: Remove uma criptomoeda cadastrada pelo nome.
3. **Atualizar Cotação**: Atualiza a cotação de uma criptomoeda existente.

---

## Requisitos

1. **Compilador GCC**: O código foi testado utilizando o compilador GCC.
2. **Sistema Operacional**: O programa pode ser executado em sistemas Windows, Linux ou MacOS com suporte a GCC.
3. **Editor de Texto**: Para editar ou visualizar o código (exemplo: VSCode, Sublime Text ou Notepad++).

---

## Como Compilar o Programa

1. Certifique-se de que o GCC está instalado. Para verificar, use:
   ```bash
   gcc --version
