import java.lang.reflect.Array;
import java.net.SocketOption;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        ArrayList<nhanVien> ds = new ArrayList<>();


        try {
            System.out.print("Choose exercise (1 or 2 or 3): ");
            int option = Integer.parseInt(scanner.nextLine());
            switch (option) {
                case 1:
                    // Code for exercise 1
                    ds.clear();
                    System.out.print("Enter the number of employees: ");
                    int number = scanner.nextInt();
                    scanner.nextLine();

                    for (int i = 0; i < number; i++) {
                        String tenNhanVien;
                        double luongCoBan, heSoLuong, LUONG_MAX;

                        System.out.print("Enter the name of the employee: ");
                        tenNhanVien = scanner.nextLine();
                        System.out.print("Enter the basic salary: ");
                        luongCoBan = Double.parseDouble(scanner.nextLine());
                        System.out.print("Enter the salary coefficient: ");
                        heSoLuong = Double.parseDouble(scanner.nextLine());
                        System.out.print("Enter the maximum salary: ");
                        LUONG_MAX = Double.parseDouble(scanner.nextLine());

                        nhanVien nv = new nhanVien(tenNhanVien, luongCoBan, heSoLuong, LUONG_MAX);
                        ds.add(nv);
                    }

                    System.out.println("The number of employees: " + nhanVien.soNhanVien);
                    break;
                case 2:
                    // Code for exercise 2
                    ds.clear();
                    System.out.print("Enter the number of employees: ");
                    number = scanner.nextInt();
                    scanner.nextLine();
                    for (int i = 0; i < number; i++) {
                        String tenNhanVien;
                        double luongCoBan, heSoLuong, LUONG_MAX;

                        System.out.print("Enter the name of the employee: ");
                        tenNhanVien = scanner.nextLine();
                        System.out.print("Enter the basic salary: ");
                        luongCoBan = Double.parseDouble(scanner.nextLine());
                        System.out.print("Enter the salary coefficient: ");
                        heSoLuong = Double.parseDouble(scanner.nextLine());
                        System.out.print("Enter the maximum salary: ");
                        LUONG_MAX = Double.parseDouble(scanner.nextLine());

                        nhanVien nv = new nhanVien(tenNhanVien, luongCoBan, heSoLuong, LUONG_MAX);
                        ds.add(nv);
                    }

                    int tongLuong = 0;
                    for (nhanVien nv : ds) {
                        tongLuong += nv.tinhLuong();
                    }
                    System.out.println("Total salary: " + tongLuong);

                    break;
                case 3:
                    // Code for exercise 2
                    int iterations = 100000;
                    double startTime, endTime;

                    // Using String concatenation
                    startTime = System.currentTimeMillis();
                    String resultString = "";
                    for (int i = 0; i < iterations; i++) {
                        resultString += "String";
                    }
                    endTime = System.currentTimeMillis();
                    System.out.println("Time taken with String concatenation: " + (endTime - startTime) + " milliseconds");

                    // Using StringBuffer
                    startTime = System.currentTimeMillis();
                    StringBuffer stringBuffer = new StringBuffer();
                    for (int i = 0; i < iterations; i++) {
                        stringBuffer.append("String");
                    }
                    String resultBuffer = stringBuffer.toString();
                    endTime = System.currentTimeMillis();
                    System.out.println("Time taken with StringBuffer: " + (endTime - startTime) + " milliseconds");



                    break;
                default:
                    System.out.println("Invalid exercise number");
                    break;
            }
        } catch (Exception e) {
            System.out.println("Invalid input");
        } finally {
            scanner.close();
        }

    }

}