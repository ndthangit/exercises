public class nhanVien {
    public static int soNhanVien = 0;
    private final String tenNhanVien;
    private final double luongCoBan;
    private double heSoLuong;

    private double LUONG_MAX;

    public nhanVien(String tenNhanVien, double luongCoBan, double heSoLuong, double LUONG_MAX) {
        this.tenNhanVien = tenNhanVien;
        this.luongCoBan = luongCoBan;
        this.heSoLuong = heSoLuong;
        this.LUONG_MAX = LUONG_MAX;
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

    public void setLUONG_MAX(double LUONG_MAX) {
        this.LUONG_MAX = LUONG_MAX;
    }

}
