import java.util.Scanner;
import java.util.Arrays;
public class array {
    public static void main(String[] args) 
    {
        int quantity, sum = 0;
        float average;
        
        @SuppressWarnings("resource")
        Scanner s = new Scanner(System.in);
        System.out.print("Enter no. of elements you want in array:");
        quantity = s.nextInt();
        int a[] = new int[quantity];
        System.out.println("Enter all the elements:");
        for(int i = 0; i < quantity ; i++)
        {
            a[i] = s.nextInt();
            sum = sum + a[i];
        }
        Arrays.sort(a);
        System.out.print("The sorted array: ");
        for (int i : a) {
            System.out.print(i +" ");
        }
        System.out.println("\nSum: "+sum);
        average = (float)sum / quantity;
        System.out.println("Average: "+average);
    }
}
