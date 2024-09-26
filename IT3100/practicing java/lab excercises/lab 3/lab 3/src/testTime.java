import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
class A {
    int i = 200;
}
class B extends A {
    int i = 100;
}
class C extends A {
    int i = 300;
}
public class testTime {
    public static void swap(int a, int b){
        int temp = a;
        a=b;
        b=temp;
    }
    public int sum (double a, double b){
        return (int)a+(int)b;
    }
    public double sum (int a, double b){
        return a+b;
    }
    public void check1 (int n) throws Exception {
        if (n <= 0)
            throw new Exception("Number should be greater than 0");
    }
    public void check2 (int n) throws RuntimeException {
        if (n == 5)
            throw new RuntimeException("Number should not be 5");
    }
    public void check3 (int n) throws Exception, RuntimeException {
        check1(n);
        check2(n);
    }
    public void test() throws Exception {
        int n = 4;
        check1(n);
        check2(n);
        check3(n);
    }
    public static void main(String args[])  {

        B b = new B();
        System.out.println("End of main"+ b.i);
        try {
            int a = 0;
            int c = 5 / a;
            System.out.println("ok");
        } catch (ArithmeticException e) {
            System.out.println("Arithmetic Exception");
        } catch (Exception e) {
            System.out.println("Exception");
        } finally {
            System.out.println("Finally");
        }
        ArrayList<B> list = new ArrayList<B>();
        ArrayList<? extends A> list1 = new ArrayList<B>();
        B b1 = new B();
        list.add(b1);
//        list1.add();
        mother m = new mother("Mum");
        member c = new child("Child");
//        m.print();
        c.print();
//        c=m;
//        c.setName("Mum2");
//        m.print();
//        c.print();
//        int a=4;
//        int b=2;
//        swap(a,b);
////        System.out.println(a);
////        System.out.println(b);
//        member k = new member("Mum");
//        child c = new child("Child");
//        mother m = new mother("Mum");
//        c.setName();
//        child g=(child) k;
//        g.print();
//        intej: for (int i = 0; i < 5; i++) {
//            out:
//            for (int j = 0; j < 7; j++) {
//                if (j == 3) {
//                    continue intej;
//                }
//                System.out.println(j);
//            }
//
//            System.out.println(i);
//        }
//        c.setName("Child2");
//        System.out.println(c.setName());
//        c.print();
    }
}
