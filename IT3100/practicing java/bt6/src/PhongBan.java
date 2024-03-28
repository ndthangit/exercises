import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class PhongBan extends nhanVien {
    protected static String tenPhongBan;
    private byte soNhanVien = 0;
    private final byte SoNhanVienMax = 100 ;
    public ArrayList<nhanVien> listNV =new ArrayList<>();

    public PhongBan(String tenPhongBan, byte soNhanVien) {
        super(tenPhongBan, soNhanVien);
    }

    public void themNV(nhanVien nv){
        if (soNhanVien < SoNhanVienMax){
            listNV.add(nv);
            soNhanVien++;
        }
        else {
            System.out.println("Phong ban da day");
        }
    }

    public void xoaNV(nhanVien nv){
        if (soNhanVien > 0){
            listNV.remove(nv);
            soNhanVien--;
        }
        else {
            System.out.println("Phong ban rong");
        }
    }

    public void inTTin(){
        System.out.println("Ten phong ban: " + tenPhongBan);
        System.out.println("So nhan vien: " + soNhanVien);
        System.out.println("So nhan vien toi da: " + SoNhanVienMax);
        System.out.println("Danh sach nhan vien: ");
        for (nhanVien nv : listNV){
            nv.inTTin();
        }
    }

    public double tongLuong(){
        double tongLuong = 0;
        for (nhanVien nv : listNV){
            tongLuong += nv.tinhLuong();
        }
        return tongLuong;
    }
    public static String getTenPhongBan() {
        return tenPhongBan;
    }

    public static void setTenPhongBan(String tenPhongBan) {
        PhongBan.tenPhongBan = tenPhongBan;
    }

    public byte getSoNhanVien() {
        return soNhanVien;
    }

    public void setSoNhanVien(byte soNhanVien) {
        this.soNhanVien = soNhanVien;
    }

    public byte getSoNhanVienMax() {
        return SoNhanVienMax;
    }
}
