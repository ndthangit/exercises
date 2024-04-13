public class Main {
    public static void main(String[] args) {

        try {
            PhongBan pb = new PhongBan("marketing", (byte) 3);
            nhanVien nv1 = new nhanVien("Nguyen Van A", 2.0);
            nhanVien nv2 = new nhanVien("Nguyen Van B", 3.0);
            nhanVien nv3 = new nhanVien("Nguyen Van C", 4.0);
            nhanVien nv4 = new nhanVien("Nguyen Van D", 5.0);
            pb.themNV(nv1);
            pb.themNV(nv2);
            pb.themNV(nv3);
            pb.themNV(nv4);
            pb.inTTin();
            System.out.println("Tong luong: " + pb.tongLuong());
            pb.xoaNV(nv1);
            pb.inTTin();
            System.out.println("Tong luong: " + pb.tongLuong());

            PhongBan pb2 = new PhongBan("Ke toan", (byte) 2);
            nhanVien nv5 = new nhanVien("Nguyen Van E", 2.0);
            nhanVien nv6 = new nhanVien("Nguyen Van F", 3.0);
            pb2.themNV(nv5);
            pb2.themNV(nv6);
            pb2.inTTin();
            System.out.println("Tong luong: " + pb2.tongLuong());
            pb2.xoaNV(nv5);
            pb2.inTTin();
            System.out.println("Tong luong: " + pb2.tongLuong());
//            TruongPhong b= new TruongPhong("Nguyen Van G", 5.0);

        } catch (Exception e) {
            System.out.println("Error");
        }
    }
}