public class member {
    int id;
    String name;
    public member(String name){
        this.name = name;
    }
     void print(){
        System.out.println("I am the member "+ name);
    }
    public void setName(String name) {
        this.name = name;
    }
}
