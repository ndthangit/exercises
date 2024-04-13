package expandBT7;

public abstract class Nhanvien {
    private String trenNhanVien;
    private double LUONG_MAX;

    public Nhanvien(String trenNhanVien, double LUONG_MAX) {
        this.trenNhanVien = trenNhanVien;
        this.LUONG_MAX = LUONG_MAX;
    }

    public String getTrenNhanVien() {
        return trenNhanVien;
    }

    public void setTrenNhanVien(String trenNhanVien) {
        this.trenNhanVien = trenNhanVien;
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
