public class child extends mother{
    public child(String name) {
        super(name);
    }

    @Override
    public void print() {
        System.out.println("I am the child"+name);
    }
}
