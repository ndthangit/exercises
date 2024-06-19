package expandBT7;

import java.util.ArrayList;

public class PhongBan extends NhanVien {
    private String tenPhongBan;
    private int soNhanVien = 0;

    private int SO_NHAN_VIEN_MAX;
    public ArrayList<NhanVienCoHuu> listNVCH = new ArrayList<>();
    public ArrayList<NhanVienHopDong> listNVHD = new ArrayList<>();


    public PhongBan(String tenNhanVien, double LUONG_MAX, String tenPhongBan, int soNhanVien) {
        super(tenNhanVien, LUONG_MAX);
        this.tenPhongBan = tenPhongBan;
        this.soNhanVien = soNhanVien;
    }

    public String getTenPhongBan() {
        return tenPhongBan;
    }

    public void setTenPhongBan(String tenPhongBan) {
        this.tenPhongBan = tenPhongBan;
    }

    public int getSoNhanVien() {
        return soNhanVien;
    }

    public void setSoNhanVien(int soNhanVien) {
        this.soNhanVien = soNhanVien;
    }

    public int getSO_NHAN_VIEN_MAX() {
        return SO_NHAN_VIEN_MAX;
    }

    public void setSO_NHAN_VIEN_MAX(int SO_NHAN_VIEN_MAX) {
        this.SO_NHAN_VIEN_MAX = SO_NHAN_VIEN_MAX;
    }

    public boolean themNhanVien(NhanVienCoHuu nhanVienCoHuu) {
        if (soNhanVien < SO_NHAN_VIEN_MAX) {
            soNhanVien++;
            listNVCH.add(nhanVienCoHuu);
            return true;
        }
        return false;
    }

    public boolean themNhanVien(NhanVienHopDong nhanVienHopDong) {
        if (soNhanVien < SO_NHAN_VIEN_MAX) {
            soNhanVien++;
            listNVHD.add(nhanVienHopDong);
            return true;
        }
        return false;
    }

    public NhanVienCoHuu xoaNhanVien(NhanVienCoHuu nhanVienCoHuu) {
        if (soNhanVien > 0) {

            for (int i = 0; i < listNVCH.size(); i++) {
                if (listNVCH.get(i).equals(nhanVienCoHuu)) {
                    listNVCH.remove(i);
                }
            }
            soNhanVien--;
            return nhanVienCoHuu;
        }
        return null;
    }

    public NhanVienHopDong xoaNhanVien(NhanVienHopDong nhanVienHopDong) {
        if (soNhanVien > 0) {

            for (int i = 0; i < listNVHD.size(); i++) {
                if (listNVHD.get(i).equals(nhanVienHopDong)) {
                    listNVHD.remove(i);
                }
            }
            soNhanVien--;
            return nhanVienHopDong;
        }
        return null;
    }



    @Override
    public void inThongTin() {
        System.out.println("Tên phòng ban: " + tenPhongBan);
        System.out.println("Số nhân viên: " + soNhanVien);
        System.out.println("Số nhân viên max: " + SO_NHAN_VIEN_MAX);
    }

    @Override
    public double tinhLuong() {
        double tongLuong = 0;
        for (NhanVien nv : listNVCH) {
            tongLuong += nv.tinhLuong();
        }

        for (NhanVien nv : listNVHD) {
            tongLuong += nv.tinhLuong();
        }
        return tongLuong;
    }
}
