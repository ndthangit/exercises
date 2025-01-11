
CREATE TABLE `dataIT3170`.department (
    department_id VARCHAR(20) PRIMARY KEY,
    department_name VARCHAR(100) CHARACTER SET utf8mb4 NOT NULL,
    description TEXT CHARACTER SET utf8mb4,
    phone_number VARCHAR(20),
    location VARCHAR(255) CHARACTER SET utf8mb4
);

CREATE TABLE `dataIT3170`.type_doctor (
    type_id VARCHAR(20) PRIMARY KEY,
    type_name VARCHAR(100) CHARACTER SET utf8mb4,
    description TEXT CHARACTER SET utf8mb4,
    price INT
);

CREATE TABLE `dataIT3170`.doctors (
    doctor_id INT PRIMARY KEY AUTO_INCREMENT,
    doctor_name VARCHAR(100) CHARACTER SET utf8mb4,
    department_id VARCHAR(20),
    type_id VARCHAR(20),
    phone VARCHAR(15),
    email VARCHAR(25),
    address VARCHAR(255) CHARACTER SET utf8mb4,
    FOREIGN KEY (department_id) REFERENCES `dataIT3170`.department(department_id),
    FOREIGN KEY (type_id) REFERENCES `dataIT3170`.type_doctor(type_id),
    cccd VARCHAR(20) NOT NULL UNIQUE
);

-- Tạo bảng Patients (Bảng Bệnh Nhân)
CREATE TABLE `dataIT3170`.patients (
    patient_id INT PRIMARY KEY AUTO_INCREMENT,
    patient_name VARCHAR(100) CHARACTER SET utf8mb4,
    date_of_birth DATE,
    gender VARCHAR(10) CHARACTER SET utf8mb4 CHECK (gender IN ('male', 'female', 'other')),
    phone VARCHAR(15),
    email VARCHAR(25),
    address VARCHAR(255) CHARACTER SET utf8mb4,
    cccd VARCHAR(20) NOT NULL UNIQUE,
    registration_date DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Tạo bảng services (bảng dịch vụ)
CREATE TABLE `dataIT3170`.services (
    service_id VARCHAR(20) PRIMARY KEY,
    service_name VARCHAR(255) CHARACTER SET utf8mb4 NOT NULL,
    description TEXT CHARACTER SET utf8mb4 ,
    price DECIMAL(10,2) NOT NULL,
    department_id VARCHAR(20),
    FOREIGN KEY (department_id) REFERENCES `dataIT3170`.department(department_id)
);
-- Tạo bảng Appointments (Bảng Lịch Hẹn)
CREATE TABLE `dataIT3170`.appointments (
    appointment_id INT PRIMARY KEY AUTO_INCREMENT,
    patient_id INT NOT NULL,
    doctor_id INT NOT NULL,
    appointment_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    reason TEXT CHARACTER SET utf8mb4,
    status VARCHAR(50) CHARACTER SET utf8mb4 CHECK (status IN ('pending', 'confirmed', 'completed', 'canceled')),
    FOREIGN KEY (doctor_id) REFERENCES `dataIT3170`.doctors(doctor_id),
    FOREIGN KEY (patient_id) REFERENCES `dataIT3170`.patients(patient_id)
);

-- Tạo bảng Medical Exam (Bảng Khám Bệnh)
CREATE TABLE `dataIT3170`.medical_exam (
    exam_id INT PRIMARY KEY AUTO_INCREMENT,           -- Mã khám bệnh
    appointment_id INT NOT NULL UNIQUE,               -- Mã lịch hẹn, liên kết với bảng appointments
    exam_date DATETIME DEFAULT CURRENT_TIMESTAMP,     -- Ngày khám bệnh
    symptoms TEXT CHARACTER SET utf8mb4,                                    -- Triệu chứng của bệnh nhân
    diagnosis TEXT CHARACTER SET utf8mb4,                                   -- Chẩn đoán của bác sĩ
    notes TEXT,                                       -- Ghi chú bổ sung từ bác sĩ
    FOREIGN KEY (appointment_id) REFERENCES `dataIT3170`.appointments(appointment_id) -- Liên kết với bảng appointments
);

-- Tạo bảng Service Usage (Sử Dụng Dịch Vụ)
CREATE TABLE `dataIT3170`.service_usage (
    exam_id INT NOT NULL,
    service_id VARCHAR(20) NOT NULL,
    usage_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    note TEXT CHARACTER SET utf8mb4,
    PRIMARY KEY (exam_id, service_id),
    FOREIGN KEY (exam_id) REFERENCES `dataIT3170`.medical_exam(exam_id),
    FOREIGN KEY (service_id) REFERENCES `dataIT3170`.services(service_id)
);

-- Bảng Thuốc (Medicines)
CREATE TABLE `dataIT3170`.medicines (
    medicine_id VARCHAR(20) PRIMARY KEY,
    medicine_name VARCHAR(100) CHARACTER SET utf8mb4,
    description VARCHAR(255) CHARACTER SET utf8mb4,
    price DECIMAL(10,2) NOT NULL,
    manufacturer VARCHAR(100) CHARACTER SET utf8mb4
);

-- Tạo bảng Invoices (Bảng Đơn Thuốc)
CREATE TABLE `dataIT3170`.invoices (
    exam_id INT,
    medicine_id VARCHAR(20),
    quantity DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (medicine_id, exam_id),
    FOREIGN KEY (exam_id) REFERENCES `dataIT3170`.medical_exam(exam_id),
    FOREIGN KEY (medicine_id) REFERENCES `dataIT3170`.medicines(medicine_id)
);

-- Tạo bảng Payments (Bảng Thanh Toán)
CREATE TABLE `dataIT3170`.payments (
    payment_id INT PRIMARY KEY AUTO_INCREMENT,
    exam_id INT NOT NULL,
    payment_amount DECIMAL(10,2) NOT NULL,
    payment_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    status VARCHAR(50) CHARACTER SET utf8mb4 CHECK (status IN ('pending', 'completed', 'failed', 'refunded')),
    updated_at DATETIME,
    FOREIGN KEY (exam_id) REFERENCES `dataIT3170`.medical_exam(exam_id)
);

-- Tạo bảng Patient Account (Tài Khoản Bệnh Nhân)
CREATE TABLE `dataIT3170`.patient_account (
    account_id INT PRIMARY KEY AUTO_INCREMENT,
    user_name VARCHAR(20) CHARACTER SET utf8mb4 NOT NULL UNIQUE, -- sử dụng CCCD
    password VARCHAR(255) CHARACTER SET utf8mb4 NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Tạo bảng Doctor Account (Tài Khoản Bác Sĩ)
CREATE TABLE `dataIT3170`.doctor_account (
    account_id INT PRIMARY KEY AUTO_INCREMENT,
    user_name VARCHAR(20) CHARACTER SET utf8mb4 NOT NULL UNIQUE,
    password VARCHAR(255) CHARACTER SET utf8mb4 NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Tạo bảng Admin Account (Tài Khoản Admin)
CREATE TABLE `dataIT3170`.admin_account (
    account_id INT PRIMARY KEY AUTO_INCREMENT,
    user_name VARCHAR(20) CHARACTER SET utf8mb4 NOT NULL UNIQUE,
    password VARCHAR(255) CHARACTER SET utf8mb4 NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);


-- add new user
USE dataIT3170;
DELIMITER //

CREATE TRIGGER after_patient_account_insert
AFTER INSERT ON `dataIT3170`.patient_account
FOR EACH ROW
BEGIN
    -- lấy username là cccd
    INSERT INTO `dataIT3170`.patients (cccd)
    VALUES (NEW.user_name);
END//

-- exporting payment after inserting an ivoice
DELIMITER //

-- Tạo trigger sau khi thêm dữ liệu vào bảng doctor_account
USE dataIT3170;
DELIMITER //
CREATE TRIGGER after_doctor_account_insert
AFTER INSERT ON `dataIT3170`.doctor_account
FOR EACH ROW
BEGIN
    -- Thêm dữ liệu vào bảng doctors
    INSERT INTO `dataIT3170`.doctors (cccd)
    VALUES (NEW.user_name);
END//
DELIMITER //;


INSERT INTO `dataIT3170`.department (department_id, department_name, description, phone_number, location) VALUES
('D001', 'Khoa Khám Bệnh', 'Nơi tiếp nhận bệnh nhân khám sức khỏe, thực hiện kiểm tra và chuyển hướng điều trị.', '0123456789', 'Tầng 1, Bệnh viện A'),
('D002', 'Khoa Nội Tim Mạch', 'Chuyên điều trị các bệnh lý tim mạch, sử dụng siêu âm tim và điện tâm đồ.', '0123456790', 'Tầng 2, Bệnh viện A'),
('D003', 'Khoa Ngoại Tổng Hợp', 'Thực hiện các phẫu thuật tổng quát cho bệnh nhân, bao gồm phẫu thuật nội soi và mở lớn.', '0123456791', 'Tầng 3, Bệnh viện A'),
('D004', 'Khoa Nhi', 'Chăm sóc sức khỏe cho trẻ em từ sơ sinh đến 18 tuổi, điều trị các bệnh lý nhi khoa.', '0123456792', 'Tầng 4, Bệnh viện A'),
('D005', 'Khoa Da Liễu', 'Chuyên điều trị các bệnh lý da, tóc và móng, cung cấp dịch vụ điều trị mụn trứng cá, viêm da, và các bệnh mãn tính.', '0123456793', 'Tầng 5, Bệnh viện A');

INSERT INTO `dataIT3170`.patients (patient_id, patient_name, date_of_birth, gender, phone, email, address, cccd) VALUES
(1, 'Nguyễn Văn A', '1980-01-01', 'male', '0123456789', 'vana@example.com', 'Hà Nội', '123456789012'),
(2, 'Trần Thị B', '1990-05-15', 'female', '0987654321', 'tranb@example.com', 'Hà Nội', '123456789013'),
(3, 'Lê Văn C', '1985-09-20', 'other', '0912345678', 'vanc@example.com', 'Hà Nội', '123456789014');


INSERT INTO `dataIT3170`.patient_account (user_name, password)
VALUES
('123456789012', 'password1'),  -- Tài khoản cho bệnh nhân Nguyễn Văn A
('123456789013', 'password2'),  -- Tài khoản cho bệnh nhân Trần Thị B
('123456789014', 'password3');  -- Tài khoản cho bệnh nhân Lê Văn C

INSERT INTO `dataIT3170`.type_doctor (type_id, type_name, description, price) VALUES
('T001', 'Bác sĩ chuyên khoa 1', 'Bác sĩ có trình độ chuyên môn chuyên khoa 1', 2000000),
('T002', 'Bác sĩ chuyên khoa 2', 'Bác sĩ có trình độ chuyên môn chuyên khoa 2', 2500000),
('T003', 'Tiến sĩ', 'Bác sĩ có trình độ Tiến sĩ', 3000000),
('T004', 'Giáo sư', 'Bác sĩ có học vị Giáo sư', 3500000),
('T005', 'Phó Giáo sư', 'Bác sĩ có học vị Phó Giáo sư', 3200000);



# fake data for doctor_account
INSERT INTO `dataIT3170`.doctor_account (user_name, password)
VALUES
('123456789015', 'password4'),  -- Tài khoản cho bác sĩ Nguyễn Văn D
('123457789016', 'password5'),  -- Tài khoản cho bác sĩ Trần Thị E
('123456789017', 'password6');  -- Tài khoản cho bác sĩ Lê Văn F



