package expandBT7;

public class test {
    public static void main(String[] args) {
        try {
            NhanVienCoHuu nhanVienCoHuu = new NhanVienCoHuu("Nguyen Van A", 10000000, 50000, 2);
            nhanVienCoHuu.inThongTin();
            System.out.println("Lương nhân viên cơ hữu: " + nhanVienCoHuu.tinhLuong());
            nhanVienCoHuu.inThongTin();
            System.out.println("=====================================");

            NhanVienHopDong nhanVienHopDong = new NhanVienHopDong("Nguyen Van B", 10000000, 50000);
            nhanVienHopDong.inThongTin();
            System.out.println("Lương nhân viên hợp đồng: " + nhanVienHopDong.tinhLuong());
            System.out.println("=====================================");

            PhongBan phongBan = new PhongBan("Phòng marketing", 10000000, "Phong A", 0);
            phongBan.setSO_NHAN_VIEN_MAX(10);
            phongBan.themNhanVien(nhanVienCoHuu);
            phongBan.themNhanVien(nhanVienHopDong);
            phongBan.inThongTin();
            System.out.println("=====================================");
            System.out.println("Lương phòng ban: " + phongBan.tinhLuong());

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
