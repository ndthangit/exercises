package expandBT7;

public class TruongPhong extends NhanVienCoHuu{
    private double phuCap;
    private int soNamDuongChuc;

    public TruongPhong(String tenNhanVien, double LUONG_MAX, double luongCoBan, double heSoLuong, double phuCap, int soNamDuongChuc) {
        super(tenNhanVien, LUONG_MAX, luongCoBan, heSoLuong);
        this.phuCap = phuCap;
        this.soNamDuongChuc = soNamDuongChuc;

    }

    @Override
    public void inThongTin() {
        System.out.println("Tên nhân viên: " + getTenNhanVien());
        System.out.println("Lương max: " + getLUONG_MAX());
        System.out.println("Lương cơ bản: " + getLuongCoBan());
        System.out.println("Hệ số lương: " + getHeSoLuong());
        System.out.println("Phụ cấp: " + phuCap);
        System.out.println("Số năm đưọng chức: " + soNamDuongChuc);
    }

    @Override
    public double tinhLuong() {
        return this.getLuongCoBan()*this.getHeSoLuong()+ phuCap;
    }
}
