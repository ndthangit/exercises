package expandBT7;

public abstract class NhanVien {
    private String tenNhanVien;
    private double LUONG_MAX;

    public NhanVien(String tenNhanVien, double LUONG_MAX) {
        this.tenNhanVien = tenNhanVien;
        this.LUONG_MAX = LUONG_MAX;
    }

    public String getTenNhanVien() {
        return tenNhanVien;
    }

    public void setTenNhanVien(String trenNhanVien) {
        this.tenNhanVien = tenNhanVien;
    }

    public double getLUONG_MAX() {
        return LUONG_MAX;
    }

    public void setLUONG_MAX(double LUONG_MAX) {
        this.LUONG_MAX = LUONG_MAX;
    }

    public abstract void inThongTin();
    public abstract double tinhLuong();

}
