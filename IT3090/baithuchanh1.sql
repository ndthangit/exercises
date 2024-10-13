create trigger so_cau_thu_ngoai on dbo.CAULACBO
instead of insert
as
    begin
        if exists (
        select *
        from inserted i
        join dbo.CAUTHU c on i.MACLB = c.MACLB
        where c.MAQG != 'VN'
        having count(*) > 8
    )
    begin
        rollback transaction
        raiserror('Cannot have more than 8 foreign players in a club', 16, 1)
        return
    end

    insert into dbo.CAULACBO
    select * from inserted
end
go

create table dbo.CAUTHU
(
    MACT numeric IDENTITY (1,1) primary key,
    HOTEN nvarchar(100) not null ,
    VITRI nvarchar(20) not null check (VITRI in ('THU MON', 'HAU VE', 'TIEN VE', 'TIEN DAO', 'TRUNG VE')),
    NGAYSINH date,
    DIACHI nvarchar(200),
    MACLB varchar(5) not null,
    MAQG varchar(5) not null,
    SO int not null ,
)
go
create table dbo.QUOCGIA
(
    MAQG varchar(5) primary key,
    TENQG nvarchar(60) not null,
)
go
create table dbo.CAULACBO
(
    MACLB varchar(5) primary key,
    TENCLB nvarchar(100) not null,
    MASAN varchar(5) not null,
    MATINH varchar(5) not null,

)
go
create table dbo.TINH
(
    MATINH varchar(5) primary key,
    TENTINH nvarchar(100) not null,
)
go
create table dbo.SANVD
(
    MASAN varchar(5) primary key,
    TENSAN nvarchar(100) not null,
    DIACHI nvarchar(200),
)
go
create table dbo.HUANLUYENVIEN
(
    MAHLV varchar(5) primary key,
    HOTEN nvarchar(100) not null,
    NGAYSINH date,
    DIACHI nvarchar(200),
    DIENTHOAI varchar(15),
    MAQG varchar(5) not null,
)
go
create table dbo.HLVCLB
(
    MACLB varchar(5) not null,
    MAHLV varchar(5) not null,
    primary key (MACLB, MAHLV),
    VAITRO nvarchar(100) not null,
)
go
create table dbo.TRANDAU
(
    MATRAN numeric IDENTITY(1,1) primary key,
    NAM int not null,
    VONG int not null,
    NGAYTD date not null,
    MACLB1 varchar(5) not null,
    MACLB2 varchar(5) not null,
    MASAN varchar(5) not null,
    KETQUA varchar(5),
)
go
create table dbo.BANGXH
(
    MACLB varchar(5) not null,
    NAM int not null,
    VONG int not null,
    SOTRAN int not null,
    THANG int not null,
    HOA int not null,
    THUA int not null,
    HIEUSO varchar(5) not null,
    DIEM int not null,
    HANG int not null,
    primary key (MACLB, NAM ,VONG),
)
go
create trigger so_cau_thu_ngoai on dbo.CAULACBO
instead of insert
as
    begin
        if exists (
        select * from inserted i
        join dbo.CAUTHU c on i.MACLB = c.MACLB and c.MAQG != dbo.QUOCGIA.MAQG
        having count(*) > 8
    )
    begin
        rollback transaction
        raiserror('Cannot have more than 8 foreign players in a club', 16, 1)
        return
    end

    insert into dbo.CAULACBO
    select * from inserted
end
go
INSERT INTO dbo.CAUTHU (HOTEN, VITRI, NGAYSINH, DIACHI, MACLB, MAQG, SO)
VALUES
(N'Nguyễn Vũ Phong', 'TIEN VE', '1990-02-20', NULL, 'BBD', 'VN', 17),
(N'Nguyễn Công Vinh', 'TIEN DAO', '1992-03-10', NULL, 'HAGL', 'VN', 9),
(N'Trần Tấn Tài', 'TIEN VE', '1989-11-21', NULL, 'BBD', 'VN', 8),
(N'Phan Hồng Sơn', 'THU MON', '1991-06-10', NULL, 'HAGL', 'VN', 2),
(N'Ronaldo', 'TIEN VE', '1989-12-12', NULL, 'SDN', 'BRA', 7),
(N'Robinho', 'TIEN VE', '1989-10-12', NULL, 'SDN', 'BRA', 8),
(N'Vidic', 'HAU VE', '1987-10-15', NULL, 'HAGL', 'ANH', 3),
(N'Trần Văn Santos', 'THU MON', '1990-10-21', NULL, 'BBD', 'BRA', 1),
(N'Nguyễn Trường Sơn', 'HAU VE', '1993-08-26', NULL, 'BBD', 'VN', 4);

go
TRUNCATE TABLE dbo.CAUTHU;
go
INSERT INTO dbo.QUOCGIA (MAQG, TENQG)
VALUES
('VN', N'Việt Nam'),
('ANH', N'Anh Quốc'),
('TBN', N'Tây Ban Nha'),
('BDN', N'Bồ Đào Nha'),
('BRA', N'Bra-xin'),
('ITA', N'Ý'),
('THA', N'Thái Lan');
go
truncate table dbo.QUOCGIA;

go
INSERT INTO dbo.CAULACBO (MACLB, TENCLB, MASAN, MATINH)
VALUES
('BBD', N'BECAMEX BÌNH DƯƠNG', 'GD', 'BD'),
('HAGL', N'HOÀNG ANH GIA LAI', 'PL', 'GL'),
('SDN', N'SHB ĐÀ NĂNG', 'CL', 'DN'),
('KKH', N'KHATOCO KHÁNH HÒA', 'NT', 'KH'),
('ΤΡΥ', N'THÉP PHÚ YÊN', 'TH', 'PY'),
('GDT', N'GẠCH ĐÔNG TÂM LONG AN', 'LA', 'LA');
go
insert into dbo.TINH (MATINH, TENTINH)
values
('BD', N'Bình Dương'),
('GL', N'Gia Lai'),
('DN', N'Đà Nẵng'),
('KH', N'Khánh Hòa'),
('PY', N'Phú Yên'),
('LA', N'Long An');
go
INSERT INTO SANVD (MASAN, TENSAN, DIACHI)
VALUES
  ('GD', N'Gò Đậu', N'123 QL 1, TX Thủ Dầu Một, Bình Dương'),
  ('PL', N'Động Pleiku', N'22 Hồ Tùng Mậu, Thống Nhất, Pleiku, Gia Lai'),
  ('CL', N'Chi Lăng', N'127 Võ Văn Tần, Đà Nẵng, Gia Lai'),
  ('NT', N'Nha Trang', N'128 Phan Chu Trinh, Nha Trang, Khánh Hòa'),
  ('TH', N'Thống Nhất', N'57 Trường Chinh, Tuy Hòa, Phú Yên'),
  ('LA', N'Long An', N'102 Hùng Vương, Tp Tân An, Long An');
go
INSERT INTO dbo.HUANLUYENVIEN (MAHLV, HOTEN, NGAYSINH, DIACHI, DIENTHOAI, MAQG)
VALUES
  ('HLV01', N'Vital', N'1955-10-15', NULL, N'0918011075', 'BDN'),
  ('HLV02', N'Lê Huỳnh Đức', N'1972-05-20', NULL, N'01223456789', 'VN'),
  ('HLV03', N'Kiatisuk', N'1970-12-11', NULL, N'01990123456', 'THA'),
  ('HLV04', N'Hoàng Anh Tuần', N'1970-06-10', NULL, N'0989112233', 'VN'),
  ('HLV05', N'Trần Công Minh', N'1973-07-07', NULL, N'0909099990', 'VN'),
  ('HLV06', N'Trần Văn Phúc', N'1965-03-02', NULL, N'01650101234', 'VN');
go
insert into dbo.HLVCLB (MACLB, MAHLV, VAITRO)
values
('BBD', 'HLV01', N'HLV Chính'),
('HAGL', 'HLV02', N'HLV Chính'),
('SDN', 'HLV03', N'HLV Chính'),
('KKH', 'HLV04', N'HLV Chính'),
('ΤΡΥ', 'HLV05', N'HLV Chính'),
('GDT', 'HLV06', N'HLV thủ môn');
go
INSERT INTO dbo.TRANDAU (NAM, VONG, NGAYTD, MACLB1, MACLB2, MASAN, KETQUA)
VALUES
  (2009, 1, '2009-07-02', 'BBD', 'SDN', 'GD', '3-0'),
  (2009, 1, '2009-07-02', 'KKH', 'GDT', 'NT', '1-1'),
  (2009, 2, '2009-02-16', 'SDN', 'KKH', 'CL', '2-2'),
  (2009, 2, '2009-02-16', 'TPY', 'BBD', 'TH', '5-0'),
  (2009, 3, '2009-03-01', 'TPY', 'GDT', 'TH', '0-2'),
  (2009, 3, '2009-03-01', 'KKH', 'BBD', 'NT', '0-1'),
  (2009, 4, '2009-03-07', 'KKH', 'TPY', 'NT', '1-0'),
  (2009, 4, '2009-03-07', 'BBD', 'GDT', 'GD', '2-2');
go
truncate table dbo.TRANDAU;

go
INSERT INTO dbo.BANGXH (MACLB, NAM, VONG, SOTRAN, THANG, HOA, THUA, HIEUSO, DIEM, HANG)
VALUES
  ('BBD', 2009, 1, 1, 1, 0, 0, '3-0', 3, 1),
  ('KKH', 2009, 1, 1, 0, 1, 0, '1-1', 1, 2),
  ('GDT', 2009, 1, 1, 0, 1, 0, '1-1', 1, 3),
  ('TPY', 2009, 1, 0, 0, 0, 0, '0-0', 0, 4),
  ('SDN', 2009, 1, 1, 0, 0, 1, '0-3', 0, 5),
  ('TPY', 2009, 2, 1, 1, 0, 0, '5-0', 3, 1),
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
go