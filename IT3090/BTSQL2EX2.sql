-- BTSQL2 BÀI 2
CREATE TABLE dbo.NhanVien (
    MSNV CHAR(10) PRIMARY KEY,
    [Họ tên] NVARCHAR(100),
    [Tuổi] int,
    [Lương] MONEY
);
go
CREATE TABLE dbo.Phong (
    MSP CHAR(10) PRIMARY KEY,
    [Tên phòng] NVARCHAR(100),
    [Địa điểm] NVARCHAR(100),
    [Ngân quỹ] MONEY,
    [MS trưởng phòng] CHAR(10),
    FOREIGN KEY ([MS trưởng phòng]) REFERENCES NhanVien(MSNV)
);
go
CREATE TABLE dbo.LamViec (
    MSNV CHAR(10),
    MSP CHAR(10),
    [Thời gian] DATETIME,
    PRIMARY KEY (MSNV, MSP),
    FOREIGN KEY (MSNV) REFERENCES NhanVien(MSNV),
    FOREIGN KEY (MSP) REFERENCES Phong(MSP)
);
go
-- a. Đưa ra tên và tuổi của các nhân viên làm việc cho cả phòng Tổ chức và Kế hoạch
SELECT [Họ tên], [Tuổi] from LamViec
LEFT JOIN NhanVien NV on NV.MSNV = LamViec.MSNV
LEFT JOIN Phong on Phong.MSP = LamViec.MSP
WHERE Phong.[Tên phòng] IN (N'Tổ chức', N'Kế hoạch')
GO;
-- b. Với mỗi phòng với trên 20 nhân viên, hãy đưa ra mã số phong và số nhân viên làm trong phòng đó
SELECT MSP, COUNT(MSNV) as 'Số nhân viên' from LamViec
GROUP BY MSP
HAVING COUNT(MSNV) > 20
GO;
-- c. Đưa ra tên của các nhân viên mà lương của họ cao hơn cả ngân quỹ của tất cả các phòng mà nhân viên đó làm việc
SELECT NV.[Họ tên] from LamViec
JOIN NhanVien NV on NV.MSNV = LamViec.MSNV
JOIN Phong on Phong.MSP = LamViec.MSP
GROUP BY NV.[Họ tên], NV.[Lương]
having NV.[lương] > sum([Ngân quỹ])
GO;

-- d. Đưa ra mã số trưởng phòng của những người trưởng phòng mà các phòng họ
-- quản lý đều có ngân quỹ > 1,000,000
SELECT [MS trưởng phòng] from Phong
WHERE [Ngân quỹ] > 1000000
GO;
-- e. Đưa ra tên của người trưởng phòng mà phòng đó có ngân quỹ lớn nhất
SELECT NV.[Họ tên] from Phong
LEFT JOIN NhanVien NV on NV.MSNV = Phong.[MS trưởng phòng]
WHERE [Ngân quỹ] = (SELECT MAX([Ngân quỹ]) from Phong)
GO;
-- f. Nếu một người có thể quản lý nhiều phòng, người đó có quyền kiểm soát ngân
-- quỹ của tất cả các phòng đó. Hãy đưa ra mã số của người trưởng phòng mà
-- tổng số ngân quỹ được kiểm soát bởi người đó > 5,000,000

select [MS trưởng phòng] from Phong
group by [MS trưởng phòng]
having sum([Ngân quỹ]) > 5000000
go;