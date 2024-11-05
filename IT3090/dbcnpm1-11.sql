CREATE TABLE `dataIT3170`.doctors (
    doctor_id nvarchar(20) PRIMARY KEY ,
    doctor_name nvarchar(100) ,
    specialty NVARCHAR(100) ,
    phone NVARCHAR(15),
    email NVARCHAR(25),
    address NVARCHAR(255)
);

-- Tạo bảng Appointments (Bảng Lịch Hẹn)
CREATE TABLE `dataIT3170`.appointments (
    appointment_id INT PRIMARY KEY auto_increment,
    patient_id nvarchar(20) NOT NULL,
    doctor_id nvarchar(20) NOT NULL,
    appointment_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    reason NVARCHAR(255),
    status NVARCHAR(50) CHECK (status IN ('pending', 'confirmed', 'completed', 'canceled')),
    FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id),
    FOREIGN KEY (patient_id) REFERENCES patients(patient_id)
);


-- Tạo bảng Payments (Bảng Thanh Toán)
CREATE TABLE `dataIT3170`.payments (
	payment_id int primary key auto_increment,
    appointment_id INT not null,
    payment_amount DECIMAL(10,2) NOT NULL,
    payment_date datetime default current_timestamp,
    status NVARCHAR(50) CHECK (status IN ('pending', 'completed', 'failed', 'refunded')),
	updated_at DATETIME ,
    FOREIGN KEY (appointment_id) REFERENCES appointments(appointment_id)
);

-- Tạo bảng Patients (Bảng Bệnh Nhân)
CREATE TABLE `dataIT3170`.patients (
    patient_id nvarchar(20) PRIMARY KEY,
    patient_name NVARCHAR(100) ,
    date_of_birth DATE,
    gender NVARCHAR(10) CHECK (gender IN ('male', 'female', 'other')),
    phone NVARCHAR(15),
    email NVARCHAR(25),
    address NVARCHAR(255),
    registration_date DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE `dataIT3170`.account (
	account_id nvarchar(20) primary key ,
    password NVARCHAR(255) NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);



CREATE TABLE `dataIT3170`.medicines (
    medicine_id INT PRIMARY KEY AUTO_INCREMENT,
    medicine_name NVARCHAR(100),
    description NVARCHAR(255),
    dosage NVARCHAR(50),
    quantity_in_stock INT DEFAULT 0,
    price DECIMAL(10, 2),
    expiration_date DATE,
    manufacturer NVARCHAR(100)
);



-- Tạo bảng Invoices (Bảng Hóa Đơn)
CREATE TABLE `dataIT3170`.invoices (
    appointment_id INT,
    medicine_id int not null,
    quantity DECIMAL(10,2) NOT NULL,
    primary key (appointment_id, medicine_id),
    FOREIGN KEY (appointment_id) REFERENCES appointments(appointment_id),
    FOREIGN KEY (medicine_id) REFERENCES medicines(medicine_id)
);


-- add new user
USE dataIT3170;
DELIMITER //

CREATE TRIGGER after_account_insert
AFTER INSERT ON `dataIT3170`.account
FOR EACH ROW
BEGIN
    -- Insert a new patient record with the same ID as the account ID, leaving other fields NULL
    INSERT INTO `dataIT3170`.patients (patient_id)
    VALUES (NEW.account_id);
END//

-- exporting payment after inserting an ivoice
USE dataIT3170;
DELIMITER //

CREATE TRIGGER after_invoice_insert
AFTER INSERT ON `dataIT3170`.invoices
FOR EACH ROW
BEGIN
    DECLARE total_amount DECIMAL(10, 2);

    -- Calculate the total invoice amount for the appointment_id of the newly inserted invoice
    SET total_amount = (SELECT SUM(i.quantity * m.price)
                        FROM `dataIT3170`.invoices AS i
                        JOIN `dataIT3170`.medicines AS m ON i.medicine_id = m.medicine_id
                        WHERE i.appointment_id = NEW.appointment_id);

    -- Check if a payment record already exists for this appointment_id
    IF EXISTS (SELECT 1 FROM `dataIT3170`.payments WHERE appointment_id = NEW.appointment_id) THEN
        -- Update the existing payment record with the new total amount, current payment date, and updated_at timestamp
        UPDATE `dataIT3170`.payments
        SET payment_amount = total_amount,
            payment_date = CURRENT_TIMESTAMP,
            updated_at = CURRENT_TIMESTAMP
        WHERE appointment_id = NEW.appointment_id;
    ELSE
        -- Insert a new payment record with the appointment_id, total amount, current timestamp, 'pending' status, and updated_at timestamp
        INSERT INTO `dataIT3170`.payments (appointment_id, payment_amount, payment_date, status, updated_at)
        VALUES (NEW.appointment_id, total_amount, CURRENT_TIMESTAMP, 'pending', CURRENT_TIMESTAMP);
    END IF;
END//

DELIMITER ;

-- decreasethe the number of equivalent medicines
USE dataIT3170;
DELIMITER //

CREATE TRIGGER after_payment_update
AFTER UPDATE ON `dataIT3170`.payments
FOR EACH ROW
BEGIN
    -- Check if the payment status has changed to 'completed'
    IF NEW.status = 'completed' AND OLD.status <> 'completed' THEN
        -- Update the quantity_in_stock for each medicine associated with this appointment_id
        UPDATE `dataIT3170`.medicines AS m
        JOIN `dataIT3170`.invoices AS i ON m.medicine_id = i.medicine_id
        SET m.quantity_in_stock = m.quantity_in_stock - i.quantity
        WHERE i.appointment_id = NEW.appointment_id;
    END IF;
END//

DELIMITER ;



INSERT INTO `dataIT3170`.doctors (doctor_id, doctor_name, specialty, phone, email, address) VALUES
(1, 'Dr. John Smith', 'Cardiology', '0123456789', 'john.smith@example.com', '123 Main St, City A'),
(2, 'Dr. Emily Johnson', 'Neurology', '0123456788', 'emily.johnson@example.com', '456 Elm St, City B'),
(3, 'Dr. Michael Brown', 'Pediatrics', '0123456787', 'michael.brown@example.com', '789 Maple St, City C'),
(4, 'Dr. Sarah Wilson', 'Orthopedics', '0123456786', 'sarah.wilson@example.com', '321 Oak St, City D'),
(5, 'Dr. David Lee', 'Dermatology', '0123456785', 'david.lee@example.com', '654 Pine St, City E');

INSERT INTO `dataIT3170`.patients (patient_id, patient_name, date_of_birth, gender, phone, email, address) VALUES
(1, 'Alice Green', '1985-03-12', 'female', '0987654321', 'alice.green@example.com', '111 First St, City A'),
(2, 'Bob White', '1990-07-22', 'male', '0987654322', 'bob.white@example.com', '222 Second St, City B'),
(3, 'Cathy Black', '1978-01-05', 'female', '0987654323', 'cathy.black@example.com', '333 Third St, City C'),
(4, 'Daniel Gray', '2000-11-15', 'male', '0987654324', 'daniel.gray@example.com', '444 Fourth St, City D'),
(5, 'Eva Brown', '1995-09-30', 'female', '0987654325', 'eva.brown@example.com', '555 Fifth St, City E');

INSERT INTO `dataIT3170`.medicines (medicine_id, medicine_name, description, dosage, quantity_in_stock, price, expiration_date, manufacturer) VALUES
(1, 'Aspirin', 'Pain reliever and anti-inflammatory', '500mg', 100, 0.50, '2025-12-31', 'Pharma Co.'),
(2, 'Amoxicillin', 'Antibiotic used to treat infections', '250mg', 50, 0.80, '2024-06-30', 'Health Inc.'),
(3, 'Ibuprofen', 'Nonsteroidal anti-inflammatory drug', '200mg', 75, 0.60, '2025-01-31', 'Med Supply Ltd.'),
(4, 'Metformin', 'Medication for type 2 diabetes', '500mg', 40, 1.20, '2023-11-15', 'CarePharma'),
(5, 'Lisinopril', 'Medication for high blood pressure', '10mg', 60, 1.00, '2026-03-01', 'Wellness LLC');

INSERT INTO `dataIT3170`.appointments (appointment_id, patient_id, doctor_id, appointment_date, reason, status) VALUES
(1, 1, 1, '2023-10-15 09:00:00', 'Regular check-up', 'confirmed'),
(2, 2, 3, '2023-10-16 10:00:00', 'Headache and fever', 'completed'),
(3, 3, 2, '2023-10-17 11:00:00', 'Neurological assessment', 'pending'),
(4, 4, 4, '2023-10-18 14:00:00', 'Knee pain', 'canceled'),
(5, 5, 5, '2023-10-19 15:00:00', 'Skin rash', 'confirmed');

INSERT INTO `dataIT3170`.payments (payment_id, appointment_id, payment_amount, payment_date) VALUES
(1, 1, 50.00, '2023-10-15 09:30:00'),
(2, 2, 80.00, '2023-10-16 10:30:00'),
(3, 3, 30.00, '2023-10-17 11:30:00'),
(4, 5, 100.00, '2023-10-19 15:30:00');


