-- create database BAITHUCHANHSO1;
-- go

create table CAUTHU(
	MACT int primary key identity(1,1),
	HOTEN nvarchar(100) not null,
	VITRI nvarchar(20) not null,
	NGAYSINH date,
	DIACHI nvarchar(200),
	MACLB varchar(5) not null,
	MAQG varchar(5) not null,
	SO int not null,

	foreign key (MACLB) references CAULACBO(MACLB),
	foreign key (MAQG) references QUOCGIA(MAQG)
)
go
create table QUOCGIA(
	MAQG varchar(5) primary key,
	TENQG nvarchar(60) not null,
)
go
create table TINH(
	MATINH varchar(5) primary key,
	TENTINH nvarchar(100) not null,
)
go


create table SANVD(
	MASAN varchar(5) primary key,
	TENSAN nvarchar(100) not null,
	DIACHI nvarchar(200)
)
go
create table CAULACBO(
	MACLB varchar(5) primary key,
	TENCLB nvarchar(100) not null,
	MASAN varchar(5) not null,
	MATINH varchar(5) not null,

	foreign key (MASAN) references SANVD(MASAN),
	foreign key (MATINH) references TINH(MATINH)
)
go
create table HUANLUYENVIEN(
	MAHLV varchar(5) primary key,
	TENHLV nvarchar(100) not null,
	NGAYSINH date,
	DIACHI nvarchar(200),
	DIENTHOAI nvarchar(20),
	MAQG varchar(5) not null,

	foreign key (MAQG) references QUOCGIA(MAQG),

)
go

create table HLV_CLB(
	MAHLV varchar(5) ,
	MACLB varchar(5) ,
	VAITRO varchar(100) not null,
	primary key (MAHLV, MACLB),

	foreign key (MAHLV) references HUANLUYENVIEN(MAHLV),
	foreign key (MACLB) references CAULACBO(MACLB),
)
go

create table TRANDAU(
	MATRAN int primary key identity(1,1),
	NAM int not null,
	VONG int not null,
	NGAYTD date not null,

	MACLB1 varchar(5) not null,
	MACLB2 varchar(5) not null,
	MASAN varchar(5) not null,
	KETQUA varchar(5) not null,

	foreign key (MACLB1) references CAULACBO(MACLB),
	foreign key (MACLB2) references CAULACBO(MACLB),
	foreign key (MASAN) references SANVD(MASAN),

)
go
create table BANGXH(
	MACLB varchar(5) not null,
	NAM int not null,
	VONG int not null,
	SOTRAN int not null,
	THANG int not null,
	HOA int not null,
	THUA int not null,
	HIEUSO varchar(5),
	DIEM int not null,
	HANG int not null
	foreign key (MACLB) references CAULACBO(MACLB),
)
go

insert into CAUTHU(HOTEN,VITRI,NGAYSINH,DIACHI,MACLB,MAQG,SO)
values
(N'Nguyễn Vũ Phong',N'TIền vệ','1990-02-20', null, 'BBD', 'VN',17)

go
INSERT INTO CAUTHU ( HOTEN, VITRI, NGAYSINH, DIACHI, MACLB, MAQG, SO)-- ok
VALUES
( N'Nguyễn Vũ Phong', N'Tiền vệ', '1990-02-20', NULL, 'BBD', 'VN', 17),
( N'Nguyễn Công Vinh', N'Tiền đạo', '1992-03-10', NULL, 'HAGL', 'VN', 9),
( N'Trần Tần Tài', N'Tiền vệ', '1989-11-12', NULL, 'BBD', 'VN', 8),
( N'Phan Hồng Sơn', N'Thủ môn', '1991-06-10', NULL, 'HAGL', 'VN', 1),
( N'Ronaldo', N'Tiền vệ', '1989-12-12', NULL, 'SDN', 'BRA', 7),
( N'Robinho', N'Tiền vệ', '1989-10-12', NULL, 'SDN', 'BRA', 8),
( N'Vidic', N'Hậu vệ', '1987-10-15', NULL, 'HAGL', 'ANH', 3),
( N'Trần Văn Santos', N'Thủ môn', '1990-10-21', NULL, 'BBD', 'BRA', 1),
( N'Nguyễn Trường Sơn', N'Hậu vệ', '1993-08-26', NULL, 'BBD', 'VN', 4);
go
select * from cauthu;
go
INSERT INTO QUOCGIA (MAQG, TENQG)
VALUES
('VN', N'Việt Nam'),
('ANH', N'Anh Quốc'),
('TBN', N'Tây Ban Nha'),
('BDN', N'Bồ Đào Nha'),
('BRA', N'Bra-xin'),
('ITA', N'Ý'),
('THA', N'Thái Lan');
go
select * from QUOCGIA;
go
INSERT INTO CAULACBO (MACLB, TENCLB, MASAN, MATINH) -- ok
VALUES
('BBD', N'BECAMEX BÌNH DƯƠNG', 'GD', 'BD'),
('HAGL', N'HOÀNG ANH GIA LAI', 'PL', 'GL'),
('SDN', N'SHB ĐÀ NĂNG', 'CL', 'DN'),
('KKH', N'KHATOCO KHÁNH HÒA', 'NT', 'KH'),
('TPY', N'THÉP PHÚ YÊN', 'TH', 'PY'),
('GDT', N'GẠCH ĐÔNG TÂM LONG AN', 'LA', 'LA');
go
delete from CAULACBO
where MACLB = 'THP'

go
INSERT INTO CAULACBO (MACLB, TENCLB, MASAN, MATINH) -- ok
VALUES
('TPY', N'THÉP PHÚ YÊN', 'TH', 'PY')
go
INSERT INTO TINH (MATINH, TENTINH)
VALUES
('BD', N'Bình Dương'),
('GL', N'Gia Lai'),
('DN', N'Đà Nẵng'),
('KH', N'Khánh Hòa'),
('PY', N'Phú Yên'),
('LA', N'Long An');
go
select * from Tinh;
go
delete from TINH;
go
INSERT INTO SANVD (MASAN, TENSAN, DIACHI)
VALUES
('GD', N'Gò Đậu', N'123 QL1, TX Thủ Dầu Một, Bình Dương'),
('PL', N'Pleiku', N'22 Hồ Tùng Mậu, Thống Nhất, Thị xã Pleiku, Gia Lai'),
('CL', N'Chi Lăng', N'127 Võ Văn Tần, Đà Nẵng'),
('NT', N'Nha Trang', N'128 Phan Chu Trinh, Nha Trang, Khánh Hòa'),
('TH', N'Tuy Hòa', N'57 Trường Chinh, Tuy Hòa, Phú Yên'),
('LA', N'Long An', N'102 Hùng Vương, Tp Tân An, Long An');
go
select * from SANVD;
go
INSERT INTO HUANLUYENVIEN (MAHLV, TENHLV, NGAYSINH, DIACHI, DIENTHOAI, MAQG)
VALUES
('HLV01', N'Vital', '1955-10-15', NULL, '0918011075', 'BDN'),
('HLV02', N'Lê Huỳnh Đức', '1972-05-20', NULL, '01223456789', 'VN'),
('HLV03', N'Kiatisuk', '1970-12-11', NULL, '01990123456', 'THA'),
('HLV04', N'Hoàng Anh Tuấn', '1970-06-10', NULL, '0989112233', 'VN'),
('HLV05', N'Trần Công Minh', '1973-07-07', NULL, '0909099990', 'VN'),
('HLV06', N'Trần Văn Phúc', '1965-02-03', NULL, '01650101234', 'VN');
go
select * from HUANLUYENVIEN;
go
INSERT INTO HLV_CLB (MAHLV, MACLB, VAITRO)
VALUES
('HLV01', 'BBD', N'HLV Chính'),
('HLV02', 'SDN', N'HLV Chính'),
('HLV03', 'HAGL', N'HLV Chính'),
('HLV04', 'KKH', N'HLV Chính'),
('HLV05', 'GDT', N'HLV Chính'),
('HLV06', 'BBD', N'HLV thủ môn');
go
select * from HLV_CLB;
go
INSERT INTO TRANDAU ( NAM, VONG, NGAYTD, MACLB1, MACLB2, MASAN, KETQUA)
VALUES

( 2009, 2, '2009-02-16', 'SDN', 'KKH', 'CL', '2-2'),
( 2009, 2, '2009-02-16', 'TPY', 'BBD', 'TH', '5-0'),
( 2009, 3, '2009-03-01', 'TPY', 'GDT', 'TH', '0-2'),
( 2009, 3, '2009-03-01', 'KKH', 'BBD', 'NT', '0-1'),
( 2009, 4, '2009-03-07', 'KKH', 'TPY', 'NT', '1-0')


go
select * from TRANDAU;
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
('SDN', 2009, 4, 2, 1, 1, 0, '2-5', 1, 5)