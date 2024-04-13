
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.Writer;
import java.rmi.server.LogStream;

public class Main {
    public static void main(String[] args) {
        System.out.println(System.out instanceof PrintStream); //true
        System.out.println(System.out instanceof OutputStream);//true
        System.out.println(System.out instanceof LogStream);//false
        System.out.println(System.out instanceof Object); //true

//        System.out.println(System.out instanceof Writer); //compile error
        //incompatible types: java.io.PrintStream cannot be converted to java.io.Writer
    }

}