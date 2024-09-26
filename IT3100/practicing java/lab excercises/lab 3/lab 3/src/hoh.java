public interface hoh {
    public double sum(double a, double b);
    public abstract double sub(double a, double b);
    double mul(double a, double b);
    default double div(double a, double b) {
        System.out.println("I am the default method");
        return a/b;
    }
}
