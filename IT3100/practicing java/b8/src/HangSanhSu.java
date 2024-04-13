public class HangSanhSu extends HangHoa{
    private String loaiNguyenLieu;

    public HangSanhSu(String maHang, String tenHang, String nhaSanXuat, double gia, String loaiNguyenLieu) {
        this.setMaHang(maHang);
        this.setTenHang(tenHang);
        this.setNhaSanXuat(nhaSanXuat);
        this.setGia(gia);
        this.loaiNguyenLieu = loaiNguyenLieu;
    }

    @Override
    public void inThongTin() {
        System.out.println("Mã hàng: " + getMaHang());
        System.out.println("Tên hàng: " + getTenHang());
        System.out.println("Nhà sản xuất: " + getNhaSanXuat());
        System.out.println("Giá: " + getGia());
        System.out.println("Loại nguyên liệu: " + loaiNguyenLieu);
    }
}
