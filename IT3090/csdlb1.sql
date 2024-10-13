create database CSDLB1;
go

CREATE TABLE CAUTHU (
    STT INT PRIMARY KEY IDENTITY(1,1), -- Assuming STT is an auto-incrementing primary key
    HOTEN NVARCHAR(100) NOT NULL,
    VITRI NVARCHAR(20) NOT NULL,
    NGAYSINH DATETIME,
    DIACHI NVARCHAR(200),
    MACLB VARCHAR(5) NOT NULL,
    MAQG VARCHAR(5) NOT NULL,
    SO INT NOT NULL
);
go
CREATE TABLE QUOCGIA (
    MAQG VARCHAR(5) PRIMARY KEY,
    TENQG NVARCHAR(60) NOT NULL
);
go
CREATE TABLE CAULACBO (
    MACLB VARCHAR(5) PRIMARY KEY,
    TENCLB NVARCHAR(100) NOT NULL,
    MASAN VARCHAR(5) NOT NULL,
    MATINH VARCHAR(5) NOT NULL
);
go
CREATE TABLE MATINH (
    MATINH VARCHAR(5) PRIMARY KEY,
    TENTINH NVARCHAR(100) NOT NULL
);
go
CREATE TABLE SANVD (
    MASAN VARCHAR(5) PRIMARY KEY,
    TENSAN NVARCHAR(100) NOT NULL,
    DIACHI NVARCHAR(200)
);
go
CREATE TABLE HUANLUYENVIEN (
    MAHLV VARCHAR(5) PRIMARY KEY,
    TENHLV NVARCHAR(100) NOT NULL,
    NGAYSINH DATETIME,
    DIACHI NVARCHAR(200),
    DIENTHOAI NVARCHAR(20),
    MAQG VARCHAR(5) NOT NULL
);
go
CREATE TABLE HLV_CLB (
    MAHLV VARCHAR(5) PRIMARY KEY,
    MACLB VARCHAR(5) PRIMARY KEY,
    VAITRO NVARCHAR(100) NOT NULL
);
go
CREATE TABLE TRANDAU (
    MATRAN NUMERIC IDENTITY(1,1) PRIMARY KEY,
    NAM INT NOT NULL,
    VONG INT NOT NULL,
    NGAYTD DATETIME NOT NULL,
    MACLB1 VARCHAR(5) NOT NULL,
    MACLB2 VARCHAR(5) NOT NULL,
    MASAN VARCHAR(5) NOT NULL,
    KETQUA VARCHAR(5) NOT NULL
);
go
CREATE TABLE BANGXH (
    MACLB VARCHAR(5),
    NAM INT,
    VONG INT,
    SOTRAN INT NOT NULL,
    THANG INT NOT NULL,
    HOA INT NOT NULL,
    THUA INT NOT NULL,
    HIEUSO VARCHAR(5) NOT NULL,
    DIEM INT NOT NULL,
    HANG INT NOT NULL,
    CONSTRAINT PK_TRANDAU PRIMARY KEY (MACLB, NAM, VONG)
);
go
INSERT INTO CAUTHU (MACT, HOTEN, VITRI, NGAYSINH, DIACHI, MACLB, MAQG, SO)
VALUES
(1, 'Nguyễn Vũ Phong', 'Tiền vệ', '20/02/1990', NULL, 'BBD', 'VN', 17),
(2, 'Nguyễn Công Vinh', 'Tiền đạo', '10/03/1992', NULL, 'HAGL', 'VN', 9),
(4, 'Trần Tần Tài', 'Tiền vệ', '12/11/1989', NULL, 'BBD', 'VN', 8),
(5, 'Phan Hồng Sơn', 'Thủ môn', '10/06/1991', NULL, 'HAGL', 'VN', 1),
(6, 'Ronaldo', 'Tiền vệ', '12/12/1989', NULL, 'SDN', 'BRA', 7),
(7, 'Robinho', 'Tiền vệ', '12/10/1989', NULL, 'SDN', 'BRA', 8),
(8, 'Vidic', 'Hậu vệ', '15/10/1987', NULL, 'HAGL', 'ANH', 3),
(9, 'Trần Văn Santos', 'Thủ môn', '21/10/1990', NULL, 'BBD', 'BRA', 1),
(10, 'Nguyễn Trường Sơn', 'Hậu vệ', '26/08/1993', NULL, 'BBD', 'VN', 4);
go
INSERT INTO QUOCGIA (MAQG, TENQG)
VALUES
('VN', 'Việt Nam'),
('ANH', 'Anh Quốc'),
('TBN', 'Tây Ban Nha'),
('BDN', 'Bồ Đào Nha'),
('BRA', 'Bra-xin'),
('ITA', 'Ý'),
('THA', 'Thái Lan');
go
INSERT INTO CAULACBO (MACLB, TENCLB, MASAN, MATINH)
VALUES
('BBD', 'BECAMEX BÌNH DƯƠNG', 'GD', 'BD'),
('HAGL', 'HOÀNG ANH GIA LAI', 'PL', 'GL'),
('SDN', 'SHB ĐÀ NĂNG', 'CL', 'DN'),
('KKH', 'KHATOCO KHÁNH HÒA', 'NT', 'KH'),
('THP', 'THÉP PHÚ YÊN', 'TH', 'PY'),
('GDT', 'GẠCH ĐÔNG TÂM LONG AN', 'LA', 'LA');
go
INSERT INTO TINH (MATINH, TENTINH)
VALUES
('BD', 'Bình Dương'),
('GL', 'Gia Lai'),
('DN', 'Đà Nẵng'),
('KH', 'Khánh Hòa'),
('PY', 'Phú Yên'),
('LA', 'Long An');
go
INSERT INTO SANVD (MASAN, TENSAN, DIACHI)
VALUES
('GD', 'Gò Đậu', '123 QL1, TX Thủ Dầu Một, Bình Dương'),
('PL', 'Pleiku', '22 Hồ Tùng Mậu, Thống Nhất, Thị xã Pleiku, Gia Lai'),
('CL', 'Chi Lăng', '127 Võ Văn Tần, Đà Nẵng'),
('NT', 'Nha Trang', '128 Phan Chu Trinh, Nha Trang, Khánh Hòa'),
('TH', 'Tuy Hòa', '57 Trường Chinh, Tuy Hòa, Phú Yên'),
('LA', 'Long An', '102 Hùng Vương, Tp Tân An, Long An');
go
INSERT INTO HUANLUYENVIEN (MAHLV, TENHLV, NGAYSINH, DIACHI, DIENTHOAI, MAQG)
VALUES
('HLV01', 'Vital', '1955-10-15', NULL, '0918011075', 'BDN'),
('HLV02', 'Lê Huỳnh Đức', '1972-05-20', NULL, '01223456789', 'VN'),
('HLV03', 'Kiatisuk', '1970-12-11', NULL, '01990123456', 'THA'),
('HLV04', 'Hoàng Anh Tuấn', '1970-06-10', NULL, '0989112233', 'VN'),
('HLV05', 'Trần Công Minh', '1973-07-07', NULL, '0909099990', 'VN'),
('HLV06', 'Trần Văn Phúc', '1965-02-03', NULL, '01650101234', 'VN');
go
INSERT INTO HLV_CLB (MAHLV, MACLB, VAITRO)
VALUES
('HLV01', 'BBD', 'HLV Chính'),
('HLV02', 'SDN', 'HLV Chính'),
('HLV03', 'HAGL', 'HLV Chính'),
('HLV04', 'KKH', 'HLV Chính'),
('HLV05', 'GDT', 'HLV Chính'),
('HLV06', 'BBD', 'HLV thủ môn');
go
INSERT INTO TRANDAU (MATRAN, NAM, VONG, NGAYTD, MACLB1, MACLB2, MASAN, KETQUA)
VALUES
(1, 2009, 1, '7/2/2009', 'BBD', 'SDN', 'GD', '3-0'),
(2, 2009, 1, '7/2/2009', 'KKH', 'GDT', 'NT', '1-1'),
(3, 2009, 2, '16/2/2009', 'SDN', 'KKH', 'CL', '2-2'),
(4, 2009, 2, '16/2/2009', 'TPY', 'BBD', 'TH', '5-0'),
(5, 2009, 3, '1/3/2009', 'TPY', 'GDT', 'TH', '0-2'),
(6, 2009, 3, '1/3/2009', 'KKH', 'BBD', 'NT', '0-1'),
(7, 2009, 4, '7/3/2009', 'KKH', 'TPY', 'NT', '1-0'),
(8, 2009, 4, '7/3/2009', 'BBD', 'GDT', 'GD', '2-2');
go
INSERT INTO BANGXH (MACLB, NAM, VONG, SOTRAN, THANG, HOA, THUA, HIEUSO, DIEM, HANG)
VALUES
('BBD', 2009, 1, 1, 1, 0, 0, '3-0', 3, 1),
('KKH', 2009, 1, 1, 0, 1, 0, '1-1', 1, 2),
('GDT', 2009, 1, 1, 0, 1, 0, '1-1', 1, 3),
('TPY', 2009, 1, 1, 0, 0, 1, '0-3', 0, 4),
('SDN', 2009, 1, 1, 0, 0, 1, '0-3', 0, 5),
('BBD', 2009, 2, 2, 1, 0, 1, '3-5', 3, 2),
('KKH', 2009, 2, 2, 0, 2, 0, '3-3', 2, 3),
('GDT', 2009, 2, 1, 0, 1, 0, '1-1', 1, 4),
('SDN', 2009, 2, 2, 1, 1, 0, '2-5', 1, 5),
('BBD', 2009, 3, 3, 2, 0, 1, '4-5', 6, 1),
('GDT', 2009, 3, 2, 1, 1, 0, '3-1', 4, 2),
('TPY', 2009, 3, 2, 1, 0, 1, '5-2', 3, 3),
('KKH', 2009, 3, 3, 0, 2, 1, '3-4', 2, 4),
('SDN', 2009, 3, 2, 1, 1, 0, '2-5', 1, 5),
('BBD', 2009, 4, 4, 2, 1, 1, '6-7', 7, 1),
('GDT', 2009, 4, 3, 1, 2, 0, '5-1', 5, 2),
('KKH', 2009, 4, 4, 1, 2, 1, '4-4', 5, 3),
('TPY', 2009, 4, 3, 1, 0, 2, '5-3', 3, 4),
('SDN', 2009, 4, 2, 1, 1, 1, 0, '2-5', 1, 5);