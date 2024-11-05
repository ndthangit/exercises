-- a. Xử lý chuỗi, ngày giờ
-- 1. Cho biết NGAYTD, TENCLB1, TENCLB2, KETQUA các trận đấu diễn ra vào tháng 3 trên sân
-- nhà mà không bị thủng lưới.
select NGAYTD,C1.TENCLB,C2.TENCLB,KETQUA from TRANDAU
join dbo.CAULACBO C1 on TRANDAU.MACLB1 = C1.MACLB
join dbo.CAULACBO C2 on TRANDAU.MACLB2 = C2.MACLB
where MONTH(NGAYTD) = 3 and KETQUA like '0-%';
go

-- 2. Cho biết mã số, họ tên, ngày sinh của những cầu thủ có họ lót là “Công”.

select MACT, HOTEN, NGAYSINH from CAUTHU where HOTEN  like N'% Công %';
go
-- 3. Cho biết mã số, họ tên, ngày sinh của những cầu thủ có họ không phải là họ “Nguyễn “.
select MACT, HOTEN, NGAYSINH from CAUTHU where HOTEN not like N'Nguyễn %';
go
-- 4. Cho biết mã huấn luyện viên, họ tên, ngày sinh, đ ịa chỉ của những huấn luyện viên Việt
-- Nam có tuổi nằm trong khoảng 35-40.

-- 5. Cho biết tên câu lạc bộ có huấn luyện viên trưởng sinh vào ngày 20 tháng 8 năm 2019.
select TENCLB from CAULACBO
where MACLB in (select MACLB from HUANLUYENVIEN
                join dbo.HLV_CLB HC on HUANLUYENVIEN.MAHLV = HC.MAHLV
                where NGAYSINH = '2019-08-20' and VAITRO = N'HLV Chính');
go
-- 6. Cho biết tên câu lạc bộ, tên tỉnh mà CLB đang đóng có số bàn thắng nhiều nhất tính đến hết vòng 3 năm 2009.

select top 1 TENCLB, TENTINH, CONVERT(INT, SUBSTRING(HIEUSO,1, CHARINDEX('-', HIEUSO)-1)) "Số bàn thắng" from CAULACBO
join dbo.TINH T on T.MATINH = CAULACBO.MATINH
join dbo.BANGXH B on CAULACBO.MACLB = B.MACLB
group by TENCLB, TENTINH, HIEUSO
order by "Số bàn thắng" desc;
go
-- b. Truy vấn con
-- 1. Cho biết mã câu lạc bộ, tên câu lạc bộ, tên sân vận động, địa chỉ và số lượng cầu thủ nước
-- ngoài (Có quốc tịch khác “Việt Nam”) tương ứng của các câu lạc bộ có nhiều hơn 2 cầu thủ nước ngoài.
select C.MACLB, TENCLB,TENSAN, S.DIACHI, COUNT(MACT) as "Số lượng cầu thủ nước ngoài" from CAULACBO
join dbo.SANVD S on CAULACBO.MASAN = S.MASAN
join dbo.CAUTHU C on CAULACBO.MACLB = C.MACLB
where MAQG != 'VN'
group by C.MACLB , TENCLB, TENSAN, S.DIACHI
having count(MACT)>2
go
-- 2. Cho biết tên câu lạc bộ, tên tỉnh mà CLB đang đóng có hiệu số bàn thắng bại cao nhất năm 2009.

select top 1 TENCLB, TENTINH, CONVERT(INT, SUBSTRING(HIEUSO,1, CHARINDEX('-', HIEUSO)-1)) - CONVERT(INT, SUBSTRING(HIEUSO, CHARINDEX('-', HIEUSO) + 1, LEN(HIEUSO))) "Hiệu số" from CAULACBO
join dbo.TINH T on T.MATINH = CAULACBO.MATINH
join dbo.BANGXH B on CAULACBO.MACLB = B.MACLB
where NAM= 2009
group by TENCLB, TENTINH, HIEUSO
order by "Hiệu số" desc;
go
-- 3. Cho biết danh sách các trận đấu ( NGAYTD, TENSAN, TENCLB1, TENCLB2, KETQUA) của
-- câu lạc bộ CLB có thứ hạng thấp nhất trong bảng xếp hạng vòng 3 năm 2009.

declare @Clb varchar(5)
set @Clb = (select top 1 MACLB from BANGXH
            where VONG =3 and NAM =2009
            order by HANG ASC )
select * from TRANDAU
where MACLB2 = @Clb or MACLB1 = @Clb
go
-- 4. Cho biết mã câu lạc bộ, tên câu lạc bộ đã tham gia thi đấu với tất cả các câu lạc bộ còn lại
-- (kể cả sân nhà và sân khách) trong mùa giải năm 2009.
select MACLB, TENCLB from CAULACBO
where MACLB in (select MACLB1
                 from TRANDAU
                 where NAM = 2009
                 group by MACLB1
                 having COUNT(DISTINCT MACLB2) = (select COUNT(MACLB) - 1 from CAULACBO)
                )
or MACLB in (select MACLB2
             from TRANDAU
             where NAM = 2009
             group by MACLB2
             having COUNT(DISTINCT MACLB1) = (select COUNT(MACLB) - 1 from CAULACBO)
            )
go

-- 5. Cho biết mã câu lạc bộ, tên câu lạc bộ đã tham gia thi đấu với tất cả các câu lạc bộ còn lại
-- ( chỉ tính sân nhà) tro ng mùa giải năm 2009.

select MACLB, TENCLB from CAULACBO
where MACLB in (select MACLB1
                 from TRANDAU
                 where NAM = 2009
                 group by MACLB1
                 having COUNT(DISTINCT MACLB2) = (select COUNT(MACLB) - 1 from CAULACBO)
                )
go
-- c. Bài tập về Rule
-- 1. Khi thêm cầu thủ mới, kiểm tra vị trí trên sân của cầu thủ chỉ thuộc một trong các vị
-- trí sau: Thủ môn, tiền đạo, tiền vệ, trung vệ, hậu vệ.
CREATE TRIGGER insert_cauthu
ON CAUTHU
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT *
        FROM INSERTED
        WHERE VITRI NOT IN (N'Thủ môn', N'Tiền đạo', N'Tiền vệ', N'Trung vệ', N'Hậu vệ')
    )
    BEGIN
        ROLLBACK TRANSACTION;
        RAISERROR(N'Vị trí cầu thủ không hợp lệ', 16, 1);
    END
END;

go
-- 2. Khi phân công huấn luyện viên, kiểm tra vai trò của huấn luyện vi ên chỉ thuộc một trong
-- các vai trò sau: HLV chính, HLV phụ, HLV thể lực, HLV thủ môn.

CREATE TRIGGER insert_hlv_clb
ON HLV_CLB
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT *
        FROM INSERTED
        WHERE VAITRO NOT IN (N'HLV chính', N'HLV phụ', N'HLV thể lực', N'THLV thủ môn')
    )
    BEGIN
        ROLLBACK TRANSACTION;
        RAISERROR(N'Vị trí huấn luyện viên không hợp lệ', 16, 1);
    END
END;
go
-- 3. Khi thêm cầu thủ mới, kiểm tra cầu thủ đó có tuổi phải đủ 18 trở lên (chỉ tính năm sinh)
CREATE TRIGGER insert_tuoicauthu
ON CAUTHU
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT *
        FROM INSERTED
        WHERE YEAR(GETDATE()) - YEAR(NGAYSINH) < 18
    )
    BEGIN
        ROLLBACK TRANSACTION;
        RAISERROR(N'Tuổi cầu thủ phải từ 18 trở lên', 16, 1);
    END
END;
-- 4. Kiểm tra kết quả trận đấu có dạng số_bàn_thắng- số_bàn_thua.
CREATE TRIGGER insert_ketqua
ON TRANDAU
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT *
        FROM INSERTED
        WHERE KETQUA NOT LIKE '[0-9]-[0-9]'
    )
    BEGIN
        ROLLBACK TRANSACTION;
        RAISERROR(N'Kết quả trận đấu không hợp lệ', 16, 1);
    END
END;

-- d. Bài tập về View
-- 1. Cho biết mã số, họ tên, ngày sinh, địa chỉ và vị trí của các cầu thủ thuộc đội bón g “SHB Đà Nẵng” có quốc tịch “Bra-xin”.
create view view_cauthu as
select MACT, HOTEN, NGAYSINH, DIACHI, VITRI from CAUTHU
where MACLB = (select MACLB from CAULACBO where TENCLB = N'SHB Đà Nẵng' and MAQG = 'BRA');
-- 2. Cho biết kết quả (MATRAN, NGAYTD, TENSAN, TENCLB1, TENCLB2, KETQUA) các trận đấu vòng 3 của mùa bóng năm 2009.
create view view_ketqua as
select MATRAN, NGAYTD,TENSAN,c1.TENCLB TENCLB1,c2.TENCLB TENCLB2,KETQUA from TRANDAU
join dbo.SANVD S on TRANDAU.MASAN = S.MASAN
join dbo.CAULACBO C1 on C1.MACLB = TRANDAU.MACLB1
join dbo.CAULACBO C2 on C2.MACLB = TRANDAU.MACLB1
where VONG =3 and NAM =2009

-- 3. Cho biết mã huấn luyện viên, họ tên, ngày sinh, địa chỉ, vai trò và tên CLB đang làm việc
-- của các huấn luyện viên có quốc tịch “Việt Nam”.
create view view_hlb as
select HUANLUYENVIEN.MAHLV,TENHLV, HUANLUYENVIEN.NGAYSINH,HUANLUYENVIEN.DIACHI, VAITRO from HUANLUYENVIEN
join dbo.HLV_CLB HC on HUANLUYENVIEN.MAHLV = HC.MAHLV
where HUANLUYENVIEN.MAQG = 'VN'
-- 4. Cho biết mã câu lạc bộ, tên câu lạc bộ, tên sân vận động, địa chỉ và số lượng cầu thủ
-- nước ngoài (có quốc tịch khác “Việt Nam”) tương ứng của các câu lạc bộ nhiều hơn
-- 2 cầu thủ nước ngoài.

create view view_foreigner as
select C.MACLB, TENCLB,TENSAN, S.DIACHI, COUNT(MACT) as "Số lượng cầu thủ nước ngoài" from CAULACBO
join dbo.SANVD S on CAULACBO.MASAN = S.MASAN
join dbo.CAUTHU C on CAULACBO.MACLB = C.MACLB
where MAQG != 'VN'
group by C.MACLB , TENCLB, TENSAN, S.DIACHI
having count(MACT)>2
-- 5. Cho biết tên tỉnh, số lượng câu thủ đang thi đấu ở vị trí tiền đạo trong các câu lạc
-- bộ thuộc địa bàn tỉnh đó quản lý.

create view view_tinh as
select TENTINH, TENCLB, count(TENCLB) as num_players from CAUTHU
join CAULACBO on CAULACBO.MACLB= CAUTHU.MACLB
join QUOCGIA on QUOCGIA.MAQG = CAUTHU.MAQG
join SANVD on SANVD.MASAN = CAULACBO.MASAN
join Tinh on TINH.MATINH = CAULACBO.MATINH
where VITRI = N'Tiền Đạo'
group by TENTINH, TENCLB

-- 6. Cho biết tên câu lạc bộ,tên tỉnh mà CLB đang đóng nằm ở vị trí cao nhất của bảng xếp
-- hạng của vòng 3 năm 2009.
create view view_top1clb as
select top 1 TENCLB, TENTINH from CAULACBO
join TINH on TINH.MATINH = CAULACBO.MATINH
join BANGXH on BANGXH.MACLB = CAULACBO.MACLB
where vong =3  and NAM = 2009
order by  DIEM desc

-- 7. Cho biết tên huấn luyện viên đang nắm giữ một vị trí trong 1 câu lạc bộ mà chưa có số điện thoại.
create view view_hlb_noPhone as
select TENHLV from CAULACBO
join HLV_CLB on HLV_CLB.MACLB =CAULACBO.MACLB
join HUANLUYENVIEN on HUANLUYENVIEN.MAHLV = HLV_CLB.MAHLV
where DIENTHOAI  IS NULL

-- 8. Liệt kê các huấn luyện viên thuộc quốc gia Việt Nam chưa làm công tác huấn luyện tại bất kỳ một câu lạc bộ
create view view_hlv_undeveloped as
select * from HUANLUYENVIEN
where HUANLUYENVIEN.MAQG ='VN'
and HUANLUYENVIEN.MAHLV not in ( select HLV_CLB.MAHLV from HLV_CLB);
-- 9. Cho biết kết quả các trận đấu đã diễn ra (MACLB1, MACLB2, NAM, VONG, SOBANTHANG,SOBANTHUA).
create view view_trandau as
select  MACLB1,MACLB2 , matran, nam, vong, CONVERT(INT, SUBSTRING(KETQUA,1, CHARINDEX('-', KETQUA)-1)) SOBANTHANG, CONVERT(INT, SUBSTRING(KETQUA, CHARINDEX('-', KETQUA) + 1, LEN(KETQUA))) SOBANTHUA  from TRANDAU
-- 10. Cho biết kết quả các trận đấu trên sân nhà (MACLB, NAM, VONG, SOBANTHANG, SOBANTHUA).
create view view_trandau1 as
select  MACLB1 , matran, nam, vong, CONVERT(INT, SUBSTRING(KETQUA,1, CHARINDEX('-', KETQUA)-1)) SOBANTHANG, CONVERT(INT, SUBSTRING(KETQUA, CHARINDEX('-', KETQUA) + 1, LEN(KETQUA))) SOBANTHUA  from TRANDAU

-- 11. Cho biết kết quả các trận đấu trên sân khách (MACLB, NAM, VONG, SOBANTHANG,SOBANTHUA).
create view view_trandau2 as
select  MACLB2 , matran, nam, vong, CONVERT(INT, SUBSTRING(KETQUA,1, CHARINDEX('-', KETQUA)-1)) SOBANTHANG, CONVERT(INT, SUBSTRING(KETQUA, CHARINDEX('-', KETQUA) + 1, LEN(KETQUA))) SOBANTHUA  from TRANDAU

-- 12. Cho biết danh sách các trận đấu (NGAYTD, TENSAN, TENCLB1, TENCLB2,KETQUA) của câu lạc bộ CLB đang xếp hạng cao nhất tính đến hết vòng 3 năm 2009.

create view view_trandau3 as
select * from TRANDAU
where MACLB1 in (select top 1 MACLB from BANGXH
            where VONG =3 and NAM =2009
            order by HANG desc )
or MACLB2 in (select top 1 MACLB from BANGXH
            where VONG =3 and NAM =2009
            order by HANG desc )

-- 13. Cho biết danh sách các trận đấu (NGAYTD, TENSAN, TENCLB1, TENCLB2, KETQUA)
-- của câu lạc bộ CLB có thứ hạng thấp nhất trong bảng xếp hạng vòng 3 năm 2009.
create view view_trandau4 as
select * from TRANDAU
where MACLB1 in (select top 1 MACLB from BANGXH
            where VONG =3 and NAM =2009
            order by HANG  )
or MACLB2 in (select top 1 MACLB from BANGXH
            where VONG =3 and NAM =2009
            order by HANG  )