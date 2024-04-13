public class HangthucPham extends HangHoa {

    private long ngaySanXuat;
    private long hanSuDung;

    public HangthucPham(String maHang, String tenHang, String nhaSanXuat, double gia, long ngaySanXuat, long hanSuDung) {
        this.setMaHang(maHang);
        this.setTenHang(tenHang);
        this.setNhaSanXuat(nhaSanXuat);
        this.setGia(gia);
        this.ngaySanXuat = ngaySanXuat;
        this.hanSuDung = hanSuDung;
    }

    @Override
    public void inThongTin() {
        System.out.println("Mã hàng: " + getMaHang());
        System.out.println("Tên hàng: " + getTenHang());
        System.out.println("Nhà sản xuất: " + getNhaSanXuat());
        System.out.println("Giá: " + getGia());
        System.out.println("Ngày sản xuất: " + ngaySanXuat);
        System.out.println("Hạn sử dụng: " + hanSuDung);
    }
}
