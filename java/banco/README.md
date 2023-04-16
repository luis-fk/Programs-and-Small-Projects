###Simulador de banco

A implementacao desse simulador de banco foi feita através da encapsulação e não pelo método de polymorfiso. Isso porque eu tinha dúvidas em como implementar esse programa do jeito pedido no enunciado e achei que seria mais fácil implementar desse jeito.

A implementação acabou ficando bastante bagunçada na minha opinião, por isso não sei se será fácil de entender o código, mas aqui vão algumas descrições de como o código funciona:


## operações.java
- O arquivo operacoes.java é onde está a main, nela são declarados arrays das classes e então essas classes são instanciadas. Eu fiz isso pois achei que seria mais fácil de chamar funções das classes desse jeito, apenas usando seu index.

- O primeiro cliente tem uma conta corrente normal. O segundo cliente é casado com a cliente 1, por isso uma shallow copy do endereço dela é feito com o endereço do cliente 2, ele também tem conta conjunta com a cliente 1. O cliente 3 tem uma conta corrente preferencial e então pode ter descontos nas taxas de transferência.

- Após isso o usuário se depara com um menu e vários tipos de operações que podem ser escolhidos, como saque, deposito, verificação de saldo, transferência externa e interna, trocar de conta e exibir informações da conta. Esse obviamente não seria um menu de um banco real, já que você pode trocar para um conta de outra pessoa, mas já que não estou usando SQL ou outro banco de dados, esse é o melhor jeito para verificar saldos e informações de outras contas.

- Vários teste básicos são feitos durante a execução do programa. Como por exemplo, não é possível sacar nem depositar números negativos, ou sacar mais dinheiro que você tem na conta. Caso você tente fazer alguma dessas operações uma mensagem de erro aparecerá. O programa também faz verificações se o cliente tem conta conjunta ou conta poupança, para exibir os tipos de menus apropriados.

## cliente.java
- Esse arquivo guarda as informações pessoais do cliente, como Nome, CPF, RG, endereço, tipo de cliente e detalhes da conta. Esse arquivo consiste basicamente de getters e um print das informações.

## conta.java
- uma das classes mais importantes, que guarda agencia, numero da agencia, tipo da conta e saldos. Essa classes é responsável pelas transferências externas e internas e faz todas as verificações antes da transferência ser feita.

## continua.java
É uma classes simples que implementei para deixar o menu mais bonitinho, deixando o usuário escolher se ele quer continuar e fazer mais operações ou simplesmente fechar e menu.

## endereco.java
Essa classes armazena todas as informações do endereço do cliente e apenas server para printar todas elas.

## tipo.java
Essa classe é responsável por guardar o tipo de conta entre corrente comum ou especial, poupanca e conjunta. Ela armazena também o número do cliente se a conta for conjunta e seu nome, sendo esse nome a único informação duplicada na memória.

