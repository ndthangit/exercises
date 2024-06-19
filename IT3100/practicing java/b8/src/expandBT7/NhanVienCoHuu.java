package expandBT7;

public class NhanVienCoHuu extends NhanVien{
    private double luongCoBan;
    private double heSoLuong;

    public NhanVienCoHuu(String tenNhanVien, double LUONG_MAX, double luongCoBan, double heSoLuong) {
        super(tenNhanVien, LUONG_MAX);
        this.luongCoBan = luongCoBan;
        this.heSoLuong = heSoLuong;
    }

    public double tangHeSoLuong() {
        return heSoLuong += 0.1;
    }


    public double getLuongCoBan() {
        return luongCoBan;
    }

    public void setLuongCoBan(double luongCoBan) {
        this.luongCoBan = luongCoBan;
    }

    public double getHeSoLuong() {
        return heSoLuong;
    }

    public void setHeSoLuong(double heSoLuong) {
        this.heSoLuong = heSoLuong;
    }

    @Override
    public void inThongTin() {
        System.out.println("Tên nhân viên: " + getTenNhanVien());
        System.out.println("Lương max: " + getLUONG_MAX());
        System.out.println("Lương cơ bản: " + luongCoBan);
        System.out.println("Hệ số lương: " + heSoLuong);


    }


    @Override
    public double tinhLuong() {
        return Math.min(luongCoBan * heSoLuong, this.getLUONG_MAX());
    }
}
