import java.util.Scanner;

public class Test {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            System.out.print("Choose exercise (1 or 2): ");
            int option = Integer.parseInt(scanner.nextLine());

            switch (option) {
                case 1:
                    // Code for exercise 1
                    System.out.print("Nhap so SV: ");
                    int N = Integer.parseInt(scanner.nextLine());
                    Student[] cls = new Student[N];
                    for (int i = 0; i < N; ++i) {
                        System.out.println("Nhap SV thu " + (i + 1));
                        System.out.print("Name: ");
                        String name = scanner.nextLine();
                        System.out.print("Year: ");
                        int year = Integer.parseInt(scanner.nextLine());
                        cls[i] = new Student(year, name);
                    }
                    int total = 0;
                    System.out.println("Danh sach lop: ");
                    for (int i = 0; i < N; ++i) {
                        total += 2012 - cls[i].getYear();
                        System.out.println(cls[i].getName());
                    }
                    System.out.println("Tong so tuoi: " + total);
                    break;
                case 2:
                    // Code for exercise 2
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
                    nv.inTTin();

                    double phanTang;
                    System.out.print("Enter the raise: ");
                    phanTang = Double.parseDouble(scanner.nextLine());
                    nv.tangLuong(phanTang);
                    nv.inTTin();

                    System.out.print("number: "+ nhanVien.soNhanVien);
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
