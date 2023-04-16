//armazena o tipo de conta para cada cliente
public class tipo {
    private boolean correnteComum;
    private boolean correntePreferencial;
    private boolean poupanca;
    private boolean conjunta;
    private int conjuntaNum;
    private String conjuntaCom;

    public tipo(boolean cc, boolean cp, boolean po, boolean co, int conNum, String con){
        correnteComum = cc;
        correntePreferencial = cp;
        poupanca = po;
        conjunta = co;
        conjuntaNum = conNum;
        conjuntaCom = con;
    }

    public boolean getConjunta() {
        return conjunta;
    }

    public boolean getPoupanca() {
        return poupanca;
    }

    public boolean getPreferencial() {
        return correntePreferencial;
    }

    public String getConjuntaCom() {
        return conjuntaCom;
    }

    public int getConjuntaNum() {
        return conjuntaNum;
    }

    public void printTipo(int numero) {
        if (correnteComum && numero == 0)
            System.out.println("Conta corrente comum");
        
        if (correntePreferencial && numero == 1)
            System.out.println("Conta corrente preferncial");
        
        if (poupanca && numero == 2)
            System.out.println("Conta poupanca");
        
        if (conjunta && numero == 3)
            System.out.printf("Conta Conjunta com: %s %n", conjuntaCom);
        
    }
}
