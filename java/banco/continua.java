import java.util.Scanner; 

//simples implementação de uma classes para ter um menu
//de continuar no programa
public class continua {
    public void cont() {
        Scanner sc = new Scanner(System.in);
  
        char c;
        String s;
        System.out.println();
        System.out.print("Continuar? (s/n): ");
        s = sc.next();
        c = s.charAt(0);
        
        if (c == 'n')
            System.exit(0);
    }
}
