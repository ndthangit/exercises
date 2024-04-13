public class Main {
    public static void main(String[] args) {
//        System.out.println("Hello world!");

        Circle c = new Circle();
        System.out.println(c);

        c = new Circle(3.5);
        System.out.println(c);

        c = new Circle(3.5, "indigo", false);
        System.out.println(c);

        Rectangle r = new Rectangle();
        System.out.println(r);

        r = new Rectangle(2.3, 5.8);
        System.out.println(r);

        r = new Rectangle(2.5, 3.8, "orange", true);
        System.out.println(r);

        Square s = new Square();
        System.out.println(s);

        s = new Square(5.5);
        System.out.println(s);

        s = new Square(5.5, "yellow", false);
        System.out.println(s);
    }
}