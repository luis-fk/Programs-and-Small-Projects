public class endereco {
    private String rua;
    private String numero;
    private String bairro;
    private String cidade;
    private String estado;

    public endereco (String ru, String num, String ba, String ci, String es){
        rua = ru;
        numero = num;
        bairro = ba;
        cidade = ci;
        estado = es;
    }

    public void pirintEndereco() {
        System.out.printf("Endereco: %s, %s, %s, %s, %s %n", rua, numero, bairro, cidade, estado);
    }
}


