public class myMethod {
    public static int myMethod(int x) {
        int sum = 0;
        outer: for (int i = 0; i < x; i++) {
            inner: for (int j = i; j < x; j++) {
                sum++;
                // System.out.println(sum);
                if (j == 1)
                    continue;
                if (j == 2)
                    continue outer;
                if (i == 3)
                    break;
                if (j == 4)
                    break outer;
            }
        }
        return sum;
    }
    public static void main(String[] args) {
        System.out.println(myMethod(3));
    }
}
