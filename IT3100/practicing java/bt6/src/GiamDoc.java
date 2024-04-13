public class GiamDoc extends nhanVien implements QuanLy{


    private double phuCap ;

    private double loiNhuanCongTy;

    public GiamDoc(String tenNhanVien, double heSoLuong) {
        super(tenNhanVien, heSoLuong);
    }

    public double getPhuCap() {
        return phuCap;
    }

    public void setPhuCap(double phuCap) {
        this.phuCap = phuCap;
    }

    public double getLoiNhuanCongTy() {
        return loiNhuanCongTy;
    }

    public void setLoiNhuanCongTy(double loiNhuanCongTy) {
        this.loiNhuanCongTy = loiNhuanCongTy;
    }

    @Override
    public double tinhLuong() {
        return this.getLuongCoBan()*this.getHeSoLuong()+ this.getPhuCap()+this.tinhHoaHong();
    }

    @Override
    public void inTTin() {
        super.inTTin();
    }

    @Override
    public double tinhHoaHong() {
        return 0.05*this.loiNhuanCongTy;
    }
}
