public class fd implements hoh{
    String s;
    fd a;
    public fd(String s) {
        this.s = s;
    }
    public static void main(String[] args) {
        fd a1 = new fd("first");
        fd a2 = new fd("second");
        a1.a = a2;
        a2.a = a1;
        System.out.print(a1.a.s);
        System.out.print(a2.a.s);
    }

    @Override
    public double sum(double a, double b) {
        return 0;
    }

    @Override
    public double sub(double a, double b) {
        return 0;
    }

    @Override
    public double mul(double a, double b) {
        return 0;
    }
}
