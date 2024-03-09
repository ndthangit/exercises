import java.text.DecimalFormat;
import java.util.Scanner;

public class calculation {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("1. Solve a first-degree equation (linear equation) with one variable");
        System.out.println("2. Solve a system of first-degree equations (linear system) with two variables");
        System.out.println("3. Solve a second-degree equation with one variable");
        System.out.print("Choose an option (1, 2, or 3): ");
        int option = scanner.nextInt();

        switch (option) {
            case 1:
                solveFirstDegreeEquation(scanner);
                break;
            case 2:
                solveLinearSystem(scanner);
                break;
            case 3:
                solveSecondDegreeEquation(scanner);
                break;
            default:
                System.out.println("Invalid option!");
        }

        scanner.close();
    }

    public static void solveFirstDegreeEquation(Scanner scanner) {
        System.out.println("Enter the coefficients of the equation ax + b = 0:");

        System.out.print("Enter the value of a: ");
        double a = scanner.nextDouble();

        System.out.print("Enter the value of b: ");
        double b = scanner.nextDouble();

        if (a == 0 && b != 0) {
            System.out.println("The equation has no root.");
            return;
        }
        double x = -b / a;
        System.out.println("The root for the equation is: x = " + x);
    }

    public static void solveLinearSystem(Scanner scanner) {
        System.out.println("Enter the coefficients of the linear system:");
        System.out.println("For the system:\n α11*x1 + α12*x2 = b1 \n a21*x1 + a22*x2 = b2");

        System.out.print("Enter the value of α11: ");
        double a11 = scanner.nextDouble();

        System.out.print("Enter the value of α12: ");
        double a12 = scanner.nextDouble();

        System.out.print("Enter the value of b1: ");
        double b1 = scanner.nextDouble();

        System.out.print("Enter the value of α21: ");
        double a21 = scanner.nextDouble();

        System.out.print("Enter the value of α22: ");
        double a22 = scanner.nextDouble();

        System.out.print("Enter the value of b2: ");
        double b2 = scanner.nextDouble();

        double D = a11 * a22 - a12 * a21;
        double D1 = b1 * a22 - b2 * a12;
        double D2 = a11 * b2 - a21 * b1;

        if (D != 0) {
            double x1 = D1 / D;
            double x2 = D2 / D;
            System.out.println("The root for the system is: x1 = " + x1 + ", x2 = " + x2);
        } else {
            if (D1 == 0 && D2 == 0)
                System.out.println("The system has infinitely roots.");
            else
                System.out.println("The system has no root.");
        }
    }

    public static void solveSecondDegreeEquation(Scanner scanner) {
        System.out.println("Enter the coefficients of the second-degree equation ax^2 + bx + c = 0:");

        System.out.print("Enter the value of a: ");
        double a = scanner.nextDouble();

        if (a == 0) {
            System.out.println("Invalid input. 'a' cannot be zero.");
            return;
        }

        System.out.print("Enter the value of b: ");
        double b = scanner.nextDouble();

        System.out.print("Enter the value of c: ");
        double c = scanner.nextDouble();

        double discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            double root1 = (-b + Math.sqrt(discriminant)) / (2 * a);
            double root2 = (-b - Math.sqrt(discriminant)) / (2 * a);
            System.out.println("The roots of the equation are: " + root1 + " and " + root2);
        } else if (discriminant == 0) {
            double root = -b / (2 * a);
            System.out.println("The double root of the equation is: " + root);
        } else {
            double sqrt_discriminant = Math.sqrt(-discriminant);
            DecimalFormat df = new DecimalFormat("#.###");
            String formatted_sqrt_discriminant = df.format(sqrt_discriminant);
            System.out.println("The roots of the equation are: " + "(" + -b + "+" + formatted_sqrt_discriminant + "i)"
                    + "/" + 2 * a + " and " + "(" + -b + "-" + formatted_sqrt_discriminant + "i)" + "/" + 2 * a);

        }
    }
}
