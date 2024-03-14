public class vecto {
    private double x, y, z;

    public vecto(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public vecto add(vecto v) {
        
        return new vecto(this.x + v.x, this.y + v.y, this.z + v.z);
    }

    public vecto sub(vecto v) {
        return new vecto(this.x - v.x, this.y - v.y, this.z - v.z);
    }

    public double dot(vecto v) {
        return this.x * v.x + this.y * v.y + this.z * v.z;
    }

    public vecto cross(vecto v) {
        return new vecto(this.y * v.z - this.z * v.y, this.z * v.x - this.x * v.z, this.x * v.y - this.y * v.x);
    }

    public vecto scale(double s) {
        return new vecto(this.x * s, this.y * s, this.z * s);
    }
    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getZ() {
        return z;
    }

//    public void printComponents() {
//        System.out.print("x: " + x);
//        System.out.print("y: " + y);
//        System.out.print("z: " + z);
//    }

}
