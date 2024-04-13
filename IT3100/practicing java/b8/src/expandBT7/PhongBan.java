package expandBT7;

public class PhongBan extends Nhanvien{
    private String tenPhongBan;
    private int soNhanVien;

    private int SO_NHAN_VIEN_MAX ;

    public PhongBan(String trenNhanVien, double LUONG_MAX, String tenPhongBan, int soNhanVien) {
        super(trenNhanVien, LUONG_MAX);
        this.tenPhongBan = tenPhongBan;
        this.soNhanVien = soNhanVien;
    }

    public String getTenPhongBan() {
        return tenPhongBan;
    }

    public void setTenPhongBan(String tenPhongBan) {
        this.tenPhongBan = tenPhongBan;
    }

    public int getSoNhanVien() {
        return soNhanVien;
    }

    public void setSoNhanVien(int soNhanVien) {
        this.soNhanVien = soNhanVien;
    }

    public int getSO_NHAN_VIEN_MAX() {
        return SO_NHAN_VIEN_MAX;
    }

    public void setSO_NHAN_VIEN_MAX(int SO_NHAN_VIEN_MAX) {
        this.SO_NHAN_VIEN_MAX = SO_NHAN_VIEN_MAX;
    }

    @Override
    public void inThongTin() {
        System.out.println("Trên nhân viên: " + getTrenNhanVien());
        System.out.println("Lương max: " + getLUONG_MAX());
        System.out.println("Tên phòng ban: " + tenPhongBan);
        System.out.println("Số nhân viên: " + soNhanVien);
        System.out.println("Số nhân viên max: " + SO_NHAN_VIEN_MAX);
    }

    @Override
    public double tinhLuong() {
        return 0;
    }
}
