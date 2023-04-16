public class cliente {
    private String nome;
    private String CPF;
    private String RG;
    private endereco endereco;
    private boolean especial;
    private conta conta;

    cliente(String n, String c, String r, endereco e, boolean es, conta a) {
      nome = n;
      CPF = c;
      RG = r;
      endereco = e;
      especial = es;
      conta = a;
    }
    
    public String getNome() {
      return nome;
    }

    public String getCPF() {
      return CPF;
    }

    public String getRG() {
      return RG;
    }

    public boolean getEspecial() {
      return especial;
    }

    public conta getConta() {
      return conta;
    }

    //imprime informações do cliente
    public void printCliente() {
      System.out.printf("Nome: %s %nCPF: %s %nRG: %s %n",
                          nome, CPF, RG);
      if (getEspecial())
        System.out.println("Cliente especial");
      else
        System.out.println("Cliente Comum");
    }
}






