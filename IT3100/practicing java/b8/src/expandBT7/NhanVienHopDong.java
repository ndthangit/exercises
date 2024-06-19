package expandBT7;

public class NhanVienHopDong extends NhanVien{
    private double luongHopDong;

    public NhanVienHopDong(String tenNhanVien, double LUONG_MAX, double luongHopDong) {
        super(tenNhanVien, LUONG_MAX);
        this.luongHopDong = luongHopDong;

    }

    public double getLuongHopDong() {
        return luongHopDong;
    }

    public void setLuongHopDong(double luongHopDong) {
        this.luongHopDong = luongHopDong;
    }

    @Override
    public void inThongTin() {
        System.out.println("Trên nhân viên: " + getTenNhanVien());
        System.out.println("Lương max: " + getLUONG_MAX());
        System.out.println("Lương hợp đồng: " + luongHopDong);
    }

    @Override
    public double tinhLuong() {
        return luongHopDong;
    }
}
