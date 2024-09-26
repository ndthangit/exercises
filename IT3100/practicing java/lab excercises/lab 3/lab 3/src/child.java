public class child extends member {

    public child(String name) {
        super(name);
    }

    @Override
    protected void print() {
        super.print();
    }

    public String setName() {
        System.out.println("I am the child "+id);
        return name;
    }
}
