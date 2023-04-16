public class conta {
    private String agencia;
    private String numero;
    private tipo tipo;
    private double saldoCorrente;
    private double saldoPoupanca;
    
    public conta(String a, String nu, tipo t, double s, double p) {
        agencia = a;
        numero = nu;
        tipo = t;
        saldoCorrente = s;
        saldoPoupanca = p;
    }

    //verifica a taxa para as transferencia bancária dependendo se for
    //conta preferncial ou comum, para esse método ser chamado significa
    //que o cliente tem conta corrente preferencial
    public double getTaxa (boolean especial) {
        if (especial && (saldoCorrente > 50000 || saldoPoupanca > 50000))
                return 0.01;
            else
                return 0.02;
    }

    public double getSaldoCorrente() {
        return saldoCorrente;
    }

    public double getSaldoPoupanca() {
        return saldoPoupanca;
    }

    //esse metodo processa a taxa e atualiza o saldo da 
    //conta corrente
    public void taxaConta(double quantia, boolean especial) {
        double taxa;
        double valor;
        taxa = getTaxa(especial);
        saldoCorrente -= quantia * taxa;
        valor = quantia * taxa;
        System.out.printf("Taxa: %.2f %n", taxa);
        System.out.printf("Valor taxa: %.2f %n", valor);
    }

    //deposita dinheiro na conta
    public void depositar(double quantia) {
        saldoCorrente += quantia;
    }

    //saca dinheiro da conta
    public void sacar(double quantia) {
        saldoCorrente -= quantia;
    }

    //transferencia entre conta corrente e conta poupanca, sendo 1 a
    //operação de conta corrnte para poupanca e 2 o contrário
    public void transferenciaInterna (double quantia, int operacao){
        if (operacao == 1 && quantia > 0 && quantia <= saldoCorrente){
            saldoPoupanca += quantia;
            saldoCorrente -= quantia;
        }
        else if (operacao == 2 && quantia > 0 && quantia <= saldoPoupanca){
            saldoCorrente += quantia;
            saldoPoupanca -= quantia;
        }
        else
            System.out.printf(" %nOperacao invalida! %n%n");
    }

    //verifica se o deposito é valido
    public boolean verificaDeposito (double quantia){
        if (quantia < 0)
            return false;
        
        return true;
    }

    //verifica se o sque é valido
    public boolean verificaSaque (double quantia){
        if (quantia < 0 || quantia >= saldoCorrente){
            System.out.printf(" %nOperacao invalida! %n%n");
            return false;
        }

        return true;
    }

    public void printSaldoCorrente() {
        System.out.printf("Saldo conta corrente: %.2f %n", saldoCorrente);
    }

    public void printSaldoPoupanca() {
        System.out.printf("Saldo poupanca: %.2f %n", saldoPoupanca);
    }

    public void printConta() {
        System.out.printf("Agencia: %s %nNumero: %s %nSaldo conta corrente: %.2f %n",
                                    agencia, numero, saldoCorrente);  
    }
}
