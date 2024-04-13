public class nhanVien {
    public static int soNhanVien = 0;
    private final String tenNhanVien;

    private final double luongCoBan =750000;
    private double heSoLuong;

    private final double LUONG_MAX= 20000000;

    public nhanVien(String tenNhanVien, double heSoLuong) {
        this.tenNhanVien = tenNhanVien;
        this.heSoLuong = heSoLuong;
        soNhanVien++;
    }

    public double tinhLuong() {
        return Math.min(luongCoBan * heSoLuong, LUONG_MAX);
    }

    public boolean tangLuong(double phanTang) {
        if (phanTang < 0 ) {
            return false;
        }
        if ((heSoLuong + phanTang) * luongCoBan > LUONG_MAX) {
            return false;
        }
        heSoLuong += phanTang;
        return true;
    }

    public void inTTin(){
        System.out.println("Ten nhan vien: " + tenNhanVien);
        System.out.println("Luong co ban: " + luongCoBan);
        System.out.println("He so luong: " + heSoLuong);
        System.out.println("Luong: " + tinhLuong());
    }

    public void setHeSoLuong(double heSoLuong) {
        this.heSoLuong = heSoLuong;
    }

    public String getTenNhanVien() {
        return tenNhanVien;
    }

    public double getLuongCoBan() {
        return luongCoBan;
    }

    public double getHeSoLuong() {
        return heSoLuong;
    }

    public double getLUONG_MAX() {
        return LUONG_MAX;
    }
}
