-- BTSQL2 BÀI 3
CREATE TABLE [Nhân viên] (
    MaNV CHAR(10) PRIMARY KEY,
    [Họ tên] NVARCHAR(100),
    [Ngày sinh] date,
    MaP CHAR(10),
    foreign key (MaP) references [Phòng](MaP)
);
go
CREATE TABLE [Phòng] (
    MaP CHAR(10) PRIMARY KEY,
    [Tên p] NVARCHAR(100),
    [Địa điểm] NVARCHAR(100),
    [Số ĐT] NVARCHAR(10),
);
go
CREATE TABLE [Dự án] (
    MaDA CHAR(10) primary key ,
    [Tên DA] CHAR(10),
    [Ngân sách] money,
);
go
CREATE TABLE [Tham gia] (
    MaNV CHAR(10),
    MaDA CHAR(10),
    [Số giờ tham gia] DATETIME,
    PRIMARY KEY (MaNV, MaDA),
    foreign key (MaNV) references [Nhân viên](MaNV),
    foreign key (MaDA) references [Dự án](MaDA)
);
go
-- a. Đưa ra tên của các dự án có ngân sách nằm trong khoảng từ 50,000 đến 100,000
select [Tên DA] from [Dự án]
where [Ngân sách] between 50000 and 100000
go;
-- b. Đưa ra họ tên của các nhân viên có tham gia làm dự án “Quản lý đào tạo”
select [Họ tên] from [Nhân viên]
where MaNV in (
    select MaNV from [Tham gia]
    where MaDA = (
        select MaDA from [Dự án]
        where [Tên DA] = N'Quản lý đào tạo'
    )
)
go
-- c. Đưa ra mã số của các nhân viên tham gia cả hai dự án “Quản lý đào taọ” và “Đào tạo từ xa”
select [MaNV] from [Tham gia]
join [Dự án] DA on [Tham gia].MaDA = DA.MaDA
where DA.MaDA = (
    select MaDA from [Dự án]
    where [Tên DA] = N'Quản lý đào tạo'
)
and MaNV in (
    select MaNV from [Tham gia]
    join [Dự án] DA on [Tham gia].MaDA = DA.MaDA
    where DA.MaDA = (
        select MaDA from [Dự án]
        where [Tên DA] = N'Đào tạo từ xa'
    )
)

-- d. Đưa ra mã số của các nhân viên tham gia dự án “Quản lý đào tạo” nhưng
-- không tham gia dự án “Đào tạo từ xa”
select [MaNV] from [Tham gia]
join [Dự án] DA on [Tham gia].MaDA = DA.MaDA
where DA.MaDA = (
    select MaDA from [Dự án]
    where [Tên DA] = N'Quản lý đào tạo'
)
and MaNV not in (
    select MaNV from [Tham gia]
    join [Dự án] DA on [Tham gia].MaDA = DA.MaDA
    where DA.MaDA = (
        select MaDA from [Dự án]
        where [Tên DA] = N'Đào tạo từ xa'
    )
)
go
-- e. Đưa ra mã số của phòng không có nhân viên nào tham gia dự án
select distinct MaP from [Nhân viên]
where MaNV not in (
    select MaNV from [Tham gia]
    )
go
-- f. Dự án nào có tất cả các nhân viên của phòng „NCKH‟ tham gia?
DECLARE @soNVpNCKh INT;
SET @soNVpNCKh = (SELECT COUNT(MaNV) FROM [Nhân viên] nv
WHERE nv.MaP = (
    SELECT Phòng.MaP FROM [Phòng]
    WHERE Phòng.MaP = 'NCKH'
    )
);
select distinct [Tên DA] from [Dự án]
join [Tham gia] on [Dự án].MaDA = [Tham gia].MaDA
join [Nhân viên] nv on [Tham gia].MaNV = nv.MaNV
join Phòng P on P.MaP = nv.MaP
where [Tên p] = 'NCKH'
group by [Tên DA]
having count(nv.MaNV)= @soNVpNCKh
go

-- g. Ngân sách trung bình của các dự án mà nhân viên có mã số NV001 tham gia là bao nhiểu?
select avg([Ngân sách]) from [Dự án]
where MaDA in (
    select MaDA from [Tham gia]
    where MaNV = 'NV001'
)
-- h. Có bao nhiêu nhân viên tham gia dự án Quản lý đào tạo?

select count(MaNV) from [Tham gia]
where MaDA = (
    select MaDA from [Dự án]
    where [Tên DA] = N'Quản lý đào tạo'
)
go
-- i. Hãy đưa ra tên của các dự án mà số nhân viên tham gia dự án đó < 10
select [Tên DA] from [Dự án]
join [Tham gia] on [Dự án].MaDA = [Tham gia].MaDA
group by [Tên DA]
having count([Tham gia].MaNV) < 10
go
-- j. Dự án nào có số nhân viên tham gia lớn nhất
select [Tên DA] from [Dự án]
join [Tham gia] on [Dự án].MaDA = [Tham gia].MaDA
group by [Tên DA]
having count([Tham gia].MaNV) = (
    select max(soNV) from (
        select count([Tham gia].MaNV) as soNV from [Dự án]
        join [Tham gia] on [Dự án].MaDA = [Tham gia].MaDA
        group by [Dự án].MaDA
    ) as soNV
)
go
