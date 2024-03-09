import java.util.Scanner;

public class test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            System.out.print("Choose exercise (1 or 2 or 3): ");
            int option = Integer.parseInt(scanner.next());

            switch (option) {
                case 1:
                    // tests for exercise 1
                    double sideOfSquare, radiusOfCircle;

                    System.out.print("Enter the side of the square: ");
                    sideOfSquare = scanner.nextDouble();
                    System.out.print("Enter the radius of the circle: ");
                    radiusOfCircle = scanner.nextDouble();

                    // Assuming square and circle classes are defined elsewhere
                    square h1 = new square(sideOfSquare);
                    System.out.println("The area of the square h1: " + h1.getArea());
                    System.out.println("The perimeter of the square h1: " + h1.getPerimeter());

                    circle h2 = new circle(radiusOfCircle);
                    System.out.println("The area of the circle h2: " + h2.getArea());
                    System.out.println("The perimeter of the circle h2: " + h2.getPerimeter());

                    break;
                case 2:
                    // tests for exercise 2
                    double x1, x2, y1, y2, y3, z1, z2;
                    // input variables from keyboard
                    System.out.print("Enter the component of the vector1: ");
                    x1 = scanner.nextDouble();
                    y1 = scanner.nextDouble();
                    z1 = scanner.nextDouble();

                    System.out.print("Enter the component of the vector2: ");
                    x2 = scanner.nextDouble();
                    y2 = scanner.nextDouble();
                    z2 = scanner.nextDouble();

                    vecto v1 = new vecto(x1, y1, z1);
                    vecto v2 = new vecto(x2, y2, z2);

                    vecto sum = v1.add(v2);
                    //System.out.println();

                    System.out.println("the summary vector:"+sum.getX()+" "+sum.getY()+" "+sum.getZ());

                    vecto sub = v1.sub(v2);
                    System.out.println("the subtraction vector:"+sub.getX()+" "+sub.getY()+" "+sub.getZ());

                    double dot = v1.dot(v2);
                    System.out.println("the dot product:"+dot);

                    vecto cross = v1.cross(v2);
                    System.out.println("the cross product:"+cross.getX()+" "+cross.getY()+" "+cross.getZ());

                    break;
                case 3:
                    // Code for exercise 3
                    // input variables from keyboard
                    String tenNhanVien;
                    double luongCoBan, heSoLuong, LUONG_MAX;
                    System.out.print("Enter the name of the employee: ");
                    tenNhanVien = scanner.nextLine();
                    scanner.nextLine();


                    System.out.print("Enter the basic salary: ");
                    luongCoBan = scanner.nextDouble();
                    System.out.print("Enter the salary coefficient: ");
                    heSoLuong = scanner.nextDouble();
                    System.out.print("Enter the maximum salary: ");
                    LUONG_MAX = scanner.nextDouble();

                    // declare and initialize an object of nhanVien class
                    nhanVien nv = new nhanVien(tenNhanVien, luongCoBan, heSoLuong, LUONG_MAX);
                    nv.inTTin();
                    double phanTang;
                    System.out.print("Enter the raise: ");
                    phanTang = scanner.nextDouble();
                    nv.tangLuong(phanTang);
                    nv.inTTin();

                    break;
                default:
                    System.out.println("Invalid exercise number");
                    break;
            }
        } catch (Exception e) {
            System.out.println("Invalid input");
        }
    }
}
