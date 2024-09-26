public class ok {

    public static void increase1(int[] arr) {
        for (int a : arr)
            a += 1;
    }

    public static void increase2(int[] arr) {
        for (int i = 0; i < arr.length; ++i)
            arr[i]++;
    }

    public static void main(String[] args) {
        int arr[] = {5, 6, 7};
        increase1(arr);
        increase2(arr);
        for (int a : arr)
            System.out.print(a + " ");

        int a1=10;
        double b1=10.0;
        if(a1==b1)
        {
            System.out.println("Equal");
        }
        else
        {
            System.out.println("Not Equal");
        }
    }


}
