public class square implements geometry {
    private double side;
    public square(double side){
        this.side = side;
    }
    public double getArea(){
        return side*side;
    }
    public double getPerimeter(){
        return side*4;
    }
}
