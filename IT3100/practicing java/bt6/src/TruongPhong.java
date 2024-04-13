public class TruongPhong  extends  nhanVien{

    private double phuCap ;

    private double soNamDuongChuc;

    public double getPhuCap() {
        return phuCap;
    }

    public void setPhuCap(double phuCap) {
        this.phuCap = phuCap;
    }

    public double getSoNamDuongChuc() {
        return soNamDuongChuc;
    }

    public void setSoNamDuongChuc(double soNamDuongChuc) {
        this.soNamDuongChuc = soNamDuongChuc;
    }

    public TruongPhong(String tenNhanVien, double heSoLuong) {
        super(tenNhanVien, heSoLuong);
    }

    @Override
    public double tinhLuong() {
        return this.getLuongCoBan()*this.getHeSoLuong()+ this.getPhuCap();
    }

    @Override
    public void inTTin() {
        super.inTTin();
    }
}
