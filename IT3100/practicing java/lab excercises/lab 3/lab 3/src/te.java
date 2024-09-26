import java.io.IOException;

public class te {

    public void check1 (int n) throws Exception {
        if (n <= 0)
            throw new Exception("Number should be greater than 0");
    }
    public void check2 (int n) throws IOException {
        if (n == 5)
            throw new IOException("Number should not be 5");
    }
    public void check3 (int n) throws Exception, IOException {
        check1(n);
        check2(n);
    }
    public void test() throws Exception {
        int n = 4;
        check1(n);
        check2(n);
        check3(n);
        System.out.println("End of test");
    }
    //Phương thức test bị lỗi ở những đâu
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
        new te().test();
    }
}
