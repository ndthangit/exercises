public class Circle extends Shape{

    private double radius;
    public Circle() {
        super();
        radius = 1.0;
    }

    public Circle(double radius) {
        super();
        this.radius = radius;
    }
    public Circle(String color, boolean filled) {
        super(color, filled);
    }

    public Circle(double radius, String color, boolean filled) {
        super(color, filled);
        this.radius = radius;
    }

    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    @Override
    public double getArea() {
        return this.getRadius()*this.getRadius()*Math.PI;
    }

    @Override
    public double getPerimeter() {
        return this.getRadius()*2*Math.PI;
    }
}
