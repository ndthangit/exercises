public class CanBoQuanLy extends nhanVien implements QuanLy{
    public CanBoQuanLy(String tenNhanVien, double heSoLuong) {
        super(tenNhanVien, heSoLuong);
    }

    @Override
    public double tinhHoaHong() {
        return 0;
    }
}
