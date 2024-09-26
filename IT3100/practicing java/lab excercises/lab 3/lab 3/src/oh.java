import java.lang.reflect.Array;
import java.util.ArrayList;

class Person1 {
    private int age;

    public Person1(int age) {
        this.age = age;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}
public class oh {
    public static void increaseAge(Person1 p) {
        p.setAge(p.getAge() + 1);
    }

    public static void swap( Person1 p1, Person1 p2,int[] a) {
        int tempAge = p1.getAge();
        p1.setAge(p2.getAge());
        p2.setAge(tempAge);
    }

    public static void main(String[] args) {
//        Person1 p1 = new Person1(15);
//        Person1 p2 = new Person1(20);
//        new Person1(25);
//        int[] a = new int[10];
//        increaseAge(p1);
//        swap(p1, p2);
//
//        System.out.print(p1.getAge() + " ");
//        System.out.print(p2.getAge() + " ");
        try {
            int i, sum;
            sum = 10;
            for (i = -1; i < 3 ;++i)
                sum = (sum / i);
        } catch (ArithmeticException e) {
            System.out.println("0");
        } //System.out.println(sum);
    }
}
