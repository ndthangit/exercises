import java.util.Calendar;
import java.util.Date;

public class testTime {
    public static void main(String args[]){
        mother m = new mother("Mum");
        mother c = new child("Child");
        c=m;
        c.setName("Mum2");
        m.print();
        c.print();
    }
}
