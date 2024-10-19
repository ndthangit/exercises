--a. Truy vấn cơ bản
--1. Cho biết thông tin (mã cầu thủ, họ tên, số áo, vị trí, ngày sinh, địa chỉ) của tất cả cáccầu thủ’.
select MACT,HOTEN,SO,VITRI,NGAYSINH,DIACHI from CAUTHU;

--2. Hiển thị thông tin tất cả các cầu thủ có số áo là 7 chơi ở vị trí Tiền vệ.
select * from CAUTHU
where VITRI = N'Tiền vệ';

--3. Cho biết tên, ngày sinh, địa chỉ, điện thoại của tất cả các huấn luyện viên.
select TENHLV,NGAYSINH,DIACHI,DIENTHOAI from HUANLUYENVIEN

--4. Hiển thi thông tin tất cả các cầu thủ có quốc tịch Việt Nam thuộc câu lạc bộ Becamex Bình Dương.
select * from CAUTHU
join QUOCGIA on QUOCGIA.MAQG= CAUTHU.MAQG
where TENQG =N'Việt Nam'

--5. Cho biết mã số, họ tên, ngày sinh, địa chỉ và vị trí của các cầu thủ thuộc đội bóng ‘SHB Đà Nẵng’ có quốc tịch
select SO, HOTEN,NGAYSINH,DIACHI,VITRI from CAUTHU
join CAULACBO on CAULACBO.MACLB= CAUTHU.MACLB
where TENCLB =N'SHB Đà Nẵng'

--6. Hiển thị thông tin tất cả các cầu thủ đang thi đấu trong câu lạc bộ có sân nhà là“Long An”.
select * from CAUTHU
join CAULACBO on CAULACBO.MACLB= CAUTHU.MACLB
join SANVD on SANVD.MASAN = CAULACBO.MASAN
where TENSAN =N'Sân Long An'

--7. Cho biết kết quả (MATRAN, NGAYTD, TENSAN, TENCLB1, TENCLB2, KETQUA) các trận đấu vòng 2 của mùa bóng năm 2009.
select * from TRANDAU
where VONG =2 and YEAR(NGAYTD) = 2009

--8. Cho biết mã huấn luyện viên, họ tên, ngày sinh, địa chỉ, vai trò và tên CLBđang làm việc của các huấn luyện viên có quốc tịch “ViệtNam”.
select HUANLUYENVIEN.MAHLV,TENHLV,NGAYSINH,DIACHI,VAITRO,TENCLB from CAULACBO
join HLV_CLB on HLV_CLB.MACLB= CAULACBO.MACLB
join HUANLUYENVIEN on  HUANLUYENVIEN.MAHLV=HLV_CLB.MAHLV 
join QUOCGIA on QUOCGIA.MAQG = HUANLUYENVIEN.MAQG
where TENQG =N'Việt Nam'

--9. Lấy tên 3 câu lạc bộ có điểm cao nhất sau vòng 3 năm 2009.
select top 3 * from CAULACBO
join BANGXH on BANGXH.MACLB= CAULACBO.MACLB
where NAM = 2009
order by DIEM desc

--10. Cho biết mã huấn luyện viên, họ tên, ngày sinh, địa chỉ, vai trò và tên CLB đang làm việcmà câu lạc bộ đó đóng ở tỉnh Binh Dương.
select * from CAULACBO
join TINH on TINH.MATINH = CAULACBO.MATINH
join HLV_CLB on HLV_CLB.MACLB =CAULACBO.MACLB

join HUANLUYENVIEN on  HUANLUYENVIEN.MAHLV= HLV_CLB.MAHLV
where TENTINH =N'Bình Dương'

--b. Các phép toán trên nhóm
--1. Thống kê số lượng cầu thủ của mỗi câu lạc bộ.
select TENCLB,count(TENCLB) as num_players from CAUTHU
join CAULACBO on CAULACBO.MACLB= CAUTHU.MACLB
group by TENCLB

--2. Thống kê số lượng cầu thủ nước ngoài (có quốc tịch khác Việt Nam) của mỗi câu lạc bộ
select TENQG, count(TENQG)as num_foreigners from CAUTHU
join CAULACBO on CAULACBO.MACLB= CAUTHU.MACLB
join QUOCGIA on QUOCGIA.MAQG = CAUTHU.MAQG
where TENQG != N'Việt Nam'
group by TENQG

--3. Cho biết mã câu lạc bộ, tên câu lạc bộ, tên sân vận động, địa chỉ và số lượng cầu
--thủ nước ngoài (có quốc tịch khác Việt Nam) tương ứng của các câu lạc bộ có nhiều
--hơn 2 cầu thủ nước ngoài.
select CAULACBO.MACLB, TENCLB,TENSAN,SANVD.DIACHI, count(TENQG) as num_foreigners from CAUTHU
join CAULACBO on CAULACBO.MACLB= CAUTHU.MACLB
join QUOCGIA on QUOCGIA.MAQG = CAUTHU.MAQG
join SANVD on SANVD.MASAN = CAULACBO.MASAN
where TENQG != N'Việt Nam'
group by CAULACBO.MACLB, TENCLB,TENSAN,SANVD.DIACHI
having  count(TENQG) > 2


--4. Cho biết tên tỉnh, số lượng cầu thủ đang thi đấu ở vị trí tiền đạo trong các câu lạc
--bộ thuộc địa bàn tỉnh đó quản lý.
select TENTINH, TENCLB, count(TENCLB) as num_players from CAUTHU
join CAULACBO on CAULACBO.MACLB= CAUTHU.MACLB
join QUOCGIA on QUOCGIA.MAQG = CAUTHU.MAQG
join SANVD on SANVD.MASAN = CAULACBO.MASAN
join Tinh on TINH.MATINH = CAULACBO.MATINH
where VITRI = N'Tiền Đạo'
group by TENTINH, TENCLB

--5. Cho biết tên câu lạc bộ, tên tỉnh mà CLB đang đóng nằm ở vị trí cao nhất của bảng
--xếp hạng vòng 3, năm 2009.

select top 1 TENCLB, TENTINH from CAULACBO
join TINH on TINH.MATINH = CAULACBO.MATINH
join BANGXH on BANGXH.MACLB = CAULACBO.MACLB
where vong =3  and NAM = 2009
order by  DIEM desc

--c. Các toán tử nâng cao
--1. Cho biết tên huấn luyện viên đang nắm giữ một vị trí trong một câu lạc bộ
--mà chưa có số điện thoại.
select TENHLV from CAULACBO
join HLV_CLB on HLV_CLB.MACLB =CAULACBO.MACLB
join HUANLUYENVIEN on HUANLUYENVIEN.MAHLV = HLV_CLB.MAHLV
where DIENTHOAI  IS NULL


--2. Liệt kê các huấn luyện viên thuộc quốc gia Việt Nam chưa làm công tác huấn luyện
--tại bất kỳ một câu lạc bộ nào.
select TENHLV from CAULACBO
join HLV_CLB on HLV_CLB.MACLB =CAULACBO.MACLB
right join HUANLUYENVIEN on HUANLUYENVIEN.MAHLV = HLV_CLB.MAHLV
where CAULACBO.MACLB is null

--3. Liệt kê các cầu thủ đang thi đấu trong các câu lạc bộ có thứ hạng ở vòng 3 năm 2009
--lớn hơn 6 hoặc nhỏ hơn 3.

select * from CAUTHU
where MACLB in (select top 2 MACLB from BANGXH where VONG=3 and NAM =2009 order by diem desc) 
or MACLB not in (select top 6 MACLB from BANGXH where VONG=3 and NAM =2009 order by diem desc)
go

--4. Cho biết danh sách các trận đấu (NGAYTD, TENSAN, TENCLB1, TENCLB2, KETQUA)
--của câu lạc bộ (CLB) đang xếp hạng cao nhất tính đến hết vòng 3 năm 2009
declare @MCLBTOP1 nvarchar(100)
set @MCLBTOP1 = (select top 1 MACLB from BANGXH where VONG=3 and NAM =2009 order by diem desc)

select * from TRANDAU
where (MACLB1 = @MCLBTOP1 or MACLB2 = @MCLBTOP1) and VONG < 4