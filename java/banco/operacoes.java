import java.util.Scanner; 

public class operacoes {
    public static void main(String[] args) throws InterruptedException {
        int operacao = -1, numeroConjunta;
        int clienteNumero = 0, tipoTransferencia = 0, clienteTransferencia;
        double quantia;
        Scanner sc = new Scanner(System.in);

        tipo[] tipo;
        conta[] conta;
        endereco[] endereco;
        cliente[] cliente;
        continua cont = new continua();

        tipo = new tipo[4];
        conta = new conta[4];
        endereco = new endereco[4];
        cliente = new cliente[4];

        //cria instancia do cliente 1
        tipo[1] = new tipo(true, false, false, false, 0, "");
        conta[1] = new conta("9002-3", "3001-4", tipo[1], 0, 0);
        endereco[1] = new endereco("Rua Cidade de Maceió", "222", "Itapuera", "Aracruz", "ES");
        cliente[1] = new cliente("Luana Heloisa Sandra Rodrigues", "714.772.755-09", "21.560.396-5",
                                    endereco[1], false, conta[1]);

        //cria instancia do cliente 2
        tipo[2] = new tipo(true, false, true, true, 1, "Luana Heloisa Sandra Rodrigues");
        conta[2] = new conta("9002-3", "3001-5", tipo[2], 0, 0);
        endereco[2] = endereco[1];
        cliente[2] = new cliente("Osvaldo Rodrigo Bernardo Barros", "768.023.310-12", 
                                        "26.509.045-3", endereco[1], false, conta[2]);
        
        //cria instancia do cliente 3
        tipo[3] = new tipo(false, true, false, false, 0, "");
        conta[3] = new conta("9002-3", "3001-6", tipo[3], 0, 0);
        endereco[3] = new endereco("Rua Professor Eliomar da Luz Moura", "665", "Ipueiras", "Picos", "PI");
        cliente[3] = new cliente("Malu Josefa Isadora Santos", "608.728.426-57", 
                                    "29.593.414-1", endereco[3],true, conta[3]);
                                        
        
        while (operacao != 0){

            //usuario escolhe o cliente
            while (clienteNumero < 1 || clienteNumero > 3){
                System.out.printf("Escolha um cliente: %n" +
                                            "1 - Luana Heloisa Sandra Rodrigues %n" +
                                            "2 - Osvaldo Rodrigo Bernardo Barros %n" +
                                            "3 - Malu Josefa Isadora Santos %n" +
                                            "Cliente: ");
                clienteNumero = sc.nextInt();
                System.out.println();
            }

            if (operacao == 0){
                System.exit(0);
                sc.close();
            }

            //exibe o menu para o usuário, onde ele deve digitar o
            //numero da operação
            if (operacao == -1){
                System.out.printf("0 - Sair %n" +
                                    "1 - Depositar %n" +
                                    "2 - Sacar %n" +
                                    "3 - Verificar saldo %n" +
                                    "4 - Transferencia %n" +
                                    "5 - Detalhes da conta %n" +
                                    "6 - Escolher outro cliente %n" +
                                    "7 - Trasnferencia interna %n" +
                                    "Operacao: ");
                operacao = sc.nextInt();
                System.out.println();
            }

            //operação 1 é a operação de saque
            if (operacao == 1){
                tipoTransferencia = 1;

                //se for conta conjunta, um menu de escolha do tipo
                //de transferência é mostrado
                if (tipo[clienteNumero].getConjunta()){
                    System.out.printf("Tipo de transferencia: %n" +
                                        "1 - Conta pessoal %n" +
                                        "2 - Conta conjunta com %s %n" +
                                        "Tipo: ", tipo[clienteNumero].getConjuntaCom());
                    tipoTransferencia = sc.nextInt();
                    System.out.println();
                }
                
                System.out.print("Digite a quantia a ser depositada: ");
                quantia = sc.nextDouble();

                //verifica se a quantia é válida
                if (!conta[clienteNumero].verificaDeposito(quantia)){
                    operacao = -1;
                    continue;
                }

                //tipoTransferencia será 1 se for uma operação normal na própia
                //conta corrente, se não é feito um deposito na conta corrente 
                //da pessoa com conta conjunta
                if (tipoTransferencia == 1)
                    conta[clienteNumero].depositar(quantia);
                else {
                    numeroConjunta = tipo[clienteNumero].getConjuntaNum();
                    conta[numeroConjunta].depositar(quantia);
                    System.out.println("Saldo conta conjunta: ");

                    conta[numeroConjunta].printSaldoCorrente();

                    if (tipo[numeroConjunta].getPoupanca())
                        conta[numeroConjunta].printSaldoPoupanca();                      
                }
                    
                System.out.println();

                //exibe informações da transferência e saldo
                System.out.printf("Depositado: %.2f %n", quantia);
                conta[clienteNumero].taxaConta(quantia, tipo[clienteNumero].getPreferencial());

                conta[clienteNumero].printSaldoCorrente();

                //se a pessoa tiver poupança, é exibido o saldo da mesmo
                if (tipo[clienteNumero].getPoupanca())
                    conta[clienteNumero].printSaldoPoupanca();                      

                operacao = -1;
                cont.cont();
                System.out.println();
            }

            //operação 2 é a operação de saque
            if (operacao == 2){
                tipoTransferencia = 1;

                //se for conta conjunta, um menu de escolha do tipo
                //de transferência é mostrado
                if (tipo[clienteNumero].getConjunta()){
                    System.out.printf("Tipo de transferencia: %n" +
                                        "1 - Conta pessoal %n" +
                                        "2 - Conta conjunta com %s %n" +
                                        "Tipo: ", tipo[clienteNumero].getConjuntaCom());
                    tipoTransferencia = sc.nextInt();
                    System.out.println();
                }

                System.out.print("Digite a quantia a ser sacada: ");
                quantia = sc.nextDouble();

                //verifica validade so saque
                if (!conta[clienteNumero].verificaSaque(quantia)){
                    operacao = -1;
                    continue;
                }

                //tipoTransferencia será 1 se for uma operação normal na própia
                //conta corrente, se não é feito um deposito na conta corrente 
                //da pessoa com conta conjunta
                if (tipoTransferencia == 1)
                    conta[clienteNumero].sacar(quantia);
                else {
                    numeroConjunta = tipo[clienteNumero].getConjuntaNum();
                    conta[numeroConjunta].sacar(quantia);
                    System.out.println("Saldo conta conjunta: ");

                    conta[numeroConjunta].printSaldoCorrente();

                    if (tipo[numeroConjunta].getPoupanca())
                        conta[numeroConjunta].printSaldoPoupanca();
                }

                //exibe informações da transferência e saldo
                System.out.printf("Sacado: %.2f %n", quantia);
                conta[clienteNumero].taxaConta(quantia, tipo[clienteNumero].getPreferencial());
                conta[clienteNumero].printSaldoCorrente();

                //se a pessoa tiver poupança, é exibido o saldo da mesmo
                if (tipo[clienteNumero].getPoupanca())
                        conta[clienteNumero].printSaldoPoupanca();

                operacao = -1;
                cont.cont();
                System.out.println();
            }

            //a operação 3 é a operação de verifica o saldo da conta
            if (operacao == 3){
                System.out.println("Seus saldos sao: ");
                conta[clienteNumero].printSaldoCorrente();
                
                //se tiver poupança, exibe o saldo da mesma
                if (tipo[clienteNumero].getPoupanca())
                        conta[clienteNumero].printSaldoPoupanca();

                //se for conta conjunta, exibe, o saldo dessa conta também
                if (tipo[clienteNumero].getConjunta()){
                    numeroConjunta = tipo[clienteNumero].getConjuntaNum();

                    System.out.printf("%nSaldo da conta conjunta: %n");
                    conta[numeroConjunta].printSaldoCorrente();
                    
                    //verifica se a conta conjunta tem poupança tabém
                    if (tipo[numeroConjunta].getPoupanca())
                        conta[numeroConjunta].printSaldoPoupanca();
                }
                    
                operacao = -1;
                cont.cont();
                System.out.println();
            }

            //operação 4 é a operação de transferência externa
            if (operacao == 4){
                //exibe o menu de transferência para os outros clientes
                System.out.println("Para quem voce quer transferir?");
                for (int i = 1; i < 4; i++){
                    if (i != clienteNumero)
                        System.out.printf("%d - %s %n", i, cliente[i].getNome());
                }
                System.out.print("Numero: ");
                clienteTransferencia = sc.nextInt();

                System.out.println();

                System.out.print("Digite a quantia: ");
                quantia = sc.nextDouble();

                System.out.println();

                //verifica se a quantia é valida
                if (!conta[clienteNumero].verificaSaque(quantia)){
                    operacao = -1;
                    continue;
                }
                
                //deposita na conta do outro cliente e saca da própria conta
                conta[clienteTransferencia].depositar(quantia);
                conta[clienteNumero].sacar(quantia);

                //exibe informações da transferência
                System.out.printf("Transferido: %.2f %n", quantia);
                conta[clienteNumero].taxaConta(quantia, tipo[clienteNumero].getPreferencial());
                conta[clienteNumero].printSaldoCorrente();
                
                //verifica se o cliente tem poupança
                if (tipo[clienteNumero].getPoupanca())
                    conta[clienteNumero].printSaldoPoupanca();
            
                operacao = -1;
                cont.cont();
                System.out.println();
            }

            //a operação 5 exibe todos os detalhes da conta
            if (operacao == 5){
                System.out.println("Seus detalhes da conta sao: ");

                //dados do cliente
                cliente[clienteNumero].printCliente();

                //endereço do cliente
                endereco[clienteNumero].pirintEndereco();

                //tipo de conta
                for (int i = 0; i < 4; i++)
                    tipo[clienteNumero].printTipo(i);

                //detalhes da conta
                conta[clienteNumero].printConta();

                //saldo da poupança se tiver
                if (tipo[clienteNumero].getPoupanca())
                    conta[clienteNumero].printSaldoPoupanca();

                operacao = -1;
                cont.cont();
                System.out.println();
            }

            //operação 6 deixa o usuário escolher outro cliente
            //para ver suas operações
            if (operacao == 6){
                System.out.printf("Escolha um cliente: %n" +
                                            "1 - Luana Heloisa Sandra Rodrigues %n" +
                                            "2 - Osvaldo Rodrigo Bernardo Barros %n" +
                                            "3 - Malu Josefa Isadora Santos %n" +
                                            "Cliente: ");
                clienteNumero = sc.nextInt();

                operacao = -1;
                System.out.println();
            }

            //operaçõa 7 é de transferência interna
            if (operacao == 7){

                //verifica se o cliente tem conta poupança ou não
                //se não tiver não é possível fazer a transferência interna
                if (!tipo[clienteNumero].getPoupanca()){
                    System.out.println("Voce nao tem conta poupanca!");
                    operacao = -1;
                    cont.cont();
                    System.out.println();
                    continue;
                }

                //escolhe o tipo de operação
                System.out.printf("Escolha um tipo de operacao: %n" +
                                            "1 - Conta corrente para poupanca %n" +
                                            "2 - Poupanca para conta corrente %n" +
                                            "Operacao: ");
                tipoTransferencia = sc.nextInt();
                System.out.println();

                System.out.print("Digite a quantia: ");
                quantia = sc.nextDouble();

                //verifica a quantia dependendo do tipo de transferência
                //se tipoTransferência for 1, é uma operação de conta corrente
                //para poupança, se for 2, é o contrário
                if (!conta[clienteNumero].verificaDeposito(quantia) && tipoTransferencia == 1){
                    System.out.printf(" %nOperacao invalida! %n%n");
                    operacao = -1;
                    continue;
                }
                else if (!conta[clienteNumero].verificaDeposito(quantia) && tipoTransferencia == 2){
                    System.out.printf(" %nOperacao invalida! %n%n");
                    operacao = -1;
                    continue;
                }

                //executa a transferência
                conta[clienteNumero].transferenciaInterna(quantia, tipoTransferencia);

                //exibe saldo
                conta[clienteNumero].printSaldoCorrente();
                
                //exibe saldo se tiver poupança
                if (tipo[clienteNumero].getPoupanca())
                    conta[clienteNumero].printSaldoPoupanca();

                operacao = -1;
                cont.cont();
                System.out.println();
            }
        }
    }   
}
