public class HangMayDien extends HangHoa {
    private int thoiGianBaoHanh;
    private String dienAp;
    private String congSuat;

    public HangMayDien(String maHang, String tenHang, String nhaSanXuat, double gia, int thoiGianBaoHanh, String dienAp, String congSuat) {
        this.setMaHang(maHang);
        this.setTenHang(tenHang);
        this.setNhaSanXuat(nhaSanXuat);
        this.setGia(gia);
        this.thoiGianBaoHanh = thoiGianBaoHanh;
        this.dienAp = dienAp;
        this.congSuat = congSuat;
    }


    @Override
    public void inThongTin() {
        System.out.println("Mã hàng: " + getMaHang());
        System.out.println("Tên hàng: " + getTenHang());
        System.out.println("Nhà sản xuất: " + getNhaSanXuat());
        System.out.println("Giá: " + getGia());
        System.out.println("Thời gian bảo hành: " + thoiGianBaoHanh);
        System.out.println("Điện áp: " + dienAp);
        System.out.println("Công suất: " + congSuat);
    }
}
