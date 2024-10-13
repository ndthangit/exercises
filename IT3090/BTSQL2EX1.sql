-- BTSQL2 BÀI 1
CREATE TABLE dbo.NCC (
    MSNCC CHAR(10) PRIMARY KEY,
    [Ten NCC] NVARCHAR(100),
    [Địa chỉ] NVARCHAR(255)
);
go
CREATE TABLE dbo.MatHang (
    MSMH CHAR(10) PRIMARY KEY,
    [Tên mặt hàng] NVARCHAR(100),
    [Màu sắc] NVARCHAR(50)
);
go
CREATE TABLE CungCap (
    MSNCC CHAR(10),
    MSMH CHAR(10),
    [Giá tiền] MONEY,
    PRIMARY KEY (MSNCC, MSMH),
    FOREIGN KEY (MSNCC) REFERENCES NCC(MSNCC),
    FOREIGN KEY (MSMH) REFERENCES MatHang(MSMH)
);
go
--a. Đưa ra tên của những hãng có cung ứng ít nhất 1 mặt hàng màu đỏ
SELECT distinct NCC.[Ten NCC]
FROM NCC
JOIN CungCap ON NCC.MSNCC = CungCap.MSNCC
JOIN MatHang ON CungCap.MSMH = MatHang.MSMH
WHERE MatHang.[Màu sắc] = N'Đỏ';
go
--b. Đưa ra mã số của các hãng có cung ứng ít nhất 1 mặt hàng màu đỏ hoặc 1 mặt hàng màu xanh
SELECT DISTINCT NCC.[MSNCC]
FROM NCC
JOIN CungCap ON NCC.MSNCC = CungCap.MSNCC
JOIN MatHang ON CungCap.MSMH = MatHang.MSMH
WHERE MatHang.[Màu sắc] IN (N'Đỏ', N'Xanh');

GO
--c. Đưa ra mã số của hãng có cung ứng ít nhất 1 mặt hàng màu đỏ và 1 mặt hàng màu xanh
SELECT DISTINCT NCC.[MSNCC]
FROM NCC
JOIN CungCap CC on NCC.MSNCC = CC.MSNCC
JOIN MatHang MH on MH.MSMH = CC.MSMH
WHERE MH.[Màu sắc] = N'Đỏ'
AND NCC.MSNCC IN (
    SELECT NCC.MSNCC
    FROM NCC
    JOIN CungCap CC on NCC.MSNCC = CC.MSNCC
    JOIN MatHang MH on MH.MSMH = CC.MSMH
    WHERE MH.[Màu sắc] = N'Xanh'
);
go
-- d. Đưa ra mã số của hãng cung ứng tất cả các mặt hàng màu đỏ
SELECT DISTINCT NCC.[MSNCC]
FROM NCC
JOIN CungCap CC on NCC.MSNCC = CC.MSNCC
JOIN MatHang MH on MH.MSMH = CC.MSMH
where MH.[Màu sắc] = N'Đỏ'
GROUP BY NCC.[MSNCC]
HAVING COUNT(DISTINCT MH.MSMH) = (
    SELECT COUNT(DISTINCT MH.MSMH)
    FROM MatHang MH
    WHERE MH.[Màu sắc] = N'Đỏ'
);
go
-- e. Đưa ra mã số của hãng cung ứng tất cả các mặt hàng màu đỏ và màu xanh
declare @SoDoAndXanh int;
set @SoDoAndXanh = (SELECT COUNT(DISTINCT MH.MSMH) from MatHang MH where MH.[Màu sắc] in (N'Đỏ',N'Xanh'));

SELECT DISTINCT NCC.[MSNCC]
FROM NCC
JOIN CungCap CC on NCC.MSNCC = CC.MSNCC
JOIN MatHang MH on MH.MSMH = CC.MSMH
WHERE MH.[Màu sắc] in (N'Đỏ', N'Xanh')
GROUP BY NCC.[MSNCC], MH.[Màu sắc]
HAVING COUNT(MH.MSMH) = @SoDoAndXanh;
GO
-- f. Đưa ra mã số của hãng cung ứng tất cả các mặt hàng màu đỏ hoặc tất cả các mặt hàng màu xanh
SELECT DISTINCT NCC.[MSNCC]
FROM NCC
JOIN CungCap CC ON NCC.MSNCC = CC.MSNCC
JOIN MatHang  MH ON CC.MSMH = MH.MSMH
WHERE MH.[Màu sắc] IN (N'Đỏ', N'Xanh')
GROUP BY NCC.[MSNCC], MH.[Màu sắc]
HAVING COUNT(DISTINCT CASE WHEN MH.[Màu sắc] = N'Đỏ' THEN MH.MSMH END) = (
    SELECT COUNT(DISTINCT MH.MSMH)
    FROM MatHang MH
    WHERE MH.[Màu sắc] = N'Đỏ'
) OR COUNT(DISTINCT CASE WHEN MH.[Màu sắc] = N'Xanh' THEN MH.MSMH END) = (
    SELECT COUNT(DISTINCT MH.MSMH)
    FROM MatHang MH
    WHERE MH.[Màu sắc] = N'Xanh'
);
GO
-- g. Đưa ra cặp mã số của hãng cung ứng sao cho hãng cung ứng tương
-- ứng với mã số thứ nhất cung cấp một mặt hàng nào đó với giá cao hơn
-- so với giá mà hãng tương ứng với mã số thứ hai cung cấp cũng mặt
-- hàng đó
SELECT DISTINCT NCC1.[MSNCC], NCC2.[MSNCC]
FROM NCC NCC1
JOIN NCC NCC2 ON NCC2.MSNCC != NCC1.MSNCC
JOIN CungCap CC1 ON NCC1.MSNCC = CC1.MSNCC
JOIN CungCap CC2 ON NCC2.MSNCC = CC2.MSNCC
JOIN MatHang MH1 ON CC1.MSMH = MH1.MSMH
JOIN MatHang MH2 ON CC2.MSMH = MH2.MSMH
WHERE MH1.MSMH = MH2.MSMH AND CC1.[Giá tiền] > CC2.[Giá tiền];

GO
-- h. Đưa ra mã số của mặt hàng được cung cấp bởi ít nhất hai hãng cung ứng
SELECT DISTINCT CungCap.MSMH
FROM CungCap
GROUP BY CungCap.MSMH
HAVING COUNT(DISTINCT CungCap.MSNCC) >= 2;
GO
-- i. Đưa ra mã số của mặt hàng đắt nhất được cung cấp bởi hãng Dustin
SELECT TOP 1 CungCap.MSMH
FROM CungCap
JOIN NCC ON CungCap.MSNCC = NCC.MSNCC
WHERE NCC.[Ten NCC] = N'Dustin'
ORDER BY CungCap.[Giá tiền] DESC;
GO
-- j. Đưa ra mã số của mặt hàng được cung ứng bởi tất cả các hãng mà giá tiền đều nhỏ hơn 200
SELECT DISTINCT CungCap.MSMH
FROM CungCap
JOIN NCC ON CungCap.MSNCC = NCC.MSNCC
WHERE CungCap.[Giá tiền] < 200
GROUP BY CungCap.MSMH
HAVING COUNT(DISTINCT CungCap.MSNCC) =(
    SELECT COUNT(DISTINCT NCC.MSNCC)
    FROM NCC
);