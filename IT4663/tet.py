import re
import csv

# Đường dẫn tới file .conf
file_path = "REQUEST-942-APPLICATION-ATTACK-SQLI.conf"  # Thay đổi đường dẫn nếu cần

# Đọc nội dung từ file .conf
try:
    with open(file_path, "r", encoding="utf-8") as file:
        text = file.read()
except FileNotFoundError:
    print(f"Không tìm thấy file: {file_path}")
    exit(1)

# Tìm tất cả các dòng SecRule và trích xuất id
secrule_lines = []
for line in text.splitlines():
    if line.strip().startswith("SecRule"):
        # Tìm id bằng regex
        # id_match = re.search(r"id:(\d+)", line)
        # if id_match:
            # rule_id = id_match.group(1)
        secrule_lines.append({ "line": line.strip()})

# In kết quả ra màn hình
# for rule in secrule_lines:
#     print(f"ID: {rule['id']}\nLine: {rule['line']}\n")

# Lưu kết quả vào file CSV
output_file = "secrule_output.csv"
with open(output_file, "w", newline="", encoding="utf-8") as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=["id", "line"])
    writer.writeheader()
    writer.writerows(secrule_lines)
print(f"Kết quả đã được lưu vào file: {output_file}")