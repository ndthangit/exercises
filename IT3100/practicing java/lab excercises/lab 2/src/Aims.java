public class Aims {
    public static void main(String[] args){
        // print hello
        System.out.println("hello");

        DigitalVideoDisc dvd10 = new DigitalVideoDisc("title 1");

        DigitalVideoDisc dvd20 = new DigitalVideoDisc("title 2","category 2",100);

        DigitalVideoDisc dvd30 = new DigitalVideoDisc("title 3","category 3","director 3",100);

        DigitalVideoDisc dvd40 = new DigitalVideoDisc("title 4","category 4","director 4",100,100);

        Cart anOrder = new Cart();

        DigitalVideoDisc dvd1 = new DigitalVideoDisc("The Lion King","Animation","Roger Allers",87,19.95f);
        anOrder.addDigitalVideoDisc(dvd1);
        DigitalVideoDisc dvd2 = new DigitalVideoDisc("Star Wars","Science Fiction","George Lucas",87,24.95f);
        anOrder.addDigitalVideoDisc(dvd2);
        DigitalVideoDisc dvd3 = new DigitalVideoDisc("Aladin","Animation",18.99f);
        anOrder.addDigitalVideoDisc(dvd3);

        System.out.println("Total cost is: " + anOrder.totalCost());

        anOrder.removeDigitalVideoDisc(dvd1);
        anOrder.removeDigitalVideoDisc(dvd2);
        System.out.println("Total remaining cost is: " + anOrder.totalCost());
    }
}
