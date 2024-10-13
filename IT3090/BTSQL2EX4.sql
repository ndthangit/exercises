-- BTSQL2 BÀI 4
CREATE TABLE [Sinh viên] (
    MSSV CHAR(10) PRIMARY KEY,
    [Họ tên] NVARCHAR(100),
    [Ngày sinh] date,
    [Quê quán] nvarchar(255)
);
go
CREATE TABLE [Môn học] (
    MSMH CHAR(10) PRIMARY KEY,
    [Tên MH] NVARCHAR(100),
    [Tên GV] NVARCHAR(100),
);
go
CREATE TABLE [Đăng ký] (
    MSMH CHAR(10),
    MSSV CHAR(10),
    [Điểm] int CHECK ([Điểm] >= 0 AND [Điểm] <= 10),
    PRIMARY KEY (MSMH, MSSV),
    FOREIGN KEY (MSMH) REFERENCES [Môn học](MSMH),
    FOREIGN KEY (MSSV) REFERENCES [Sinh viên](MSSV)
);
go
-- a. Đưa ra tên của các môn học
select [Tên MH] from [Môn học];
go

-- b. Đưa ra MS, Họtên, Ngày sinh của các sinh viên ở Hà nội
select MSSV, [Họ tên], [Ngày sinh]
from [Sinh viên]
where [Quê quán] = N'Hà Nội';
go
-- c. Đưa ra mã số của các sinh viên đăng ký học môn học có mã số M1 hoặc M2
select MSSV from [Đăng ký]
where MSMH in ('M1', 'M2');
go

-- d. Đưa ra tên của môn học mà sinh viên có mã số 20042325 học
select [Tên MH] from [Môn học]
where MSMH in (
    select MSMH
    from [Đăng ký]
    where MSSV = '20042325'
);
go

-- e. Đưa ra tên của các sinh viên đăng ký học ít nhất một môn do
-- giảng viên Lê Quân dạy
select distinct [Họ tên] from [Sinh viên]
where MSSV in (
    select MSSV from [Đăng ký]
    where MSMH in (
        select MSMH from [Môn học]
        where [Tên GV] = N'Lê Quân'
        )
    )
go

-- f. Đưa ra tên các môn mà sinh viên Nguyễn Văn A học và điểm tương ứng
-- của các môn đó cho sinh viên này
select [Tên MH], Điểm  from [Môn học]
join [Đăng ký] on [Môn học].MSMH = [Đăng ký].MSMH
where MSSV = (
    select MSSV from [Sinh viên]
    where [Họ tên] = N'Nguyễn Văn A'
    );
go

-- g. Đưa ra mã số của các sinh viên học tất cả các môn mà giảng viên Lê Quân
-- có dạy
select distinct MSSV from [Đăng ký]
join [Môn học] MH on [Đăng ký].MSMH = MH.MSMH
where [Tên GV] = N'Lê Quân'
go

-- h. Đưa ra tên của các môn học không được sinh viên nào đăng ký học
select [Tên MH] from [Môn học]
where MSMH not in (
    select MSMH from [Đăng ký]
);
go

-- i. Những sinh viên nào có đăng ký học từ 5 môn trở lên
select MSSV
from [Đăng ký]
group by MSSV
having count(MSMH) >= 5;
go

-- j. Điểm trung bình của sinh viên Nguyễn Văn A là bao nhiêu?
select AVG([Điểm]) as [Điểm trung bình]
from [Đăng ký]
where MSSV = (
    select MSSV from [Sinh viên]
    where [Họ tên] = N'Nguyễn Văn A'
    );
go
-- k. Sinh viên nào đạt điểm cao nhất cho môn CSDL
select top 1 [Họ tên] from [Sinh viên]
join [Đăng ký] DK on [Sinh viên].MSSV = DK.MSSV
where DK.MSMH = 'CSDL'
order by [Điểm] desc;
go
