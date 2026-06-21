# Hệ Thống Quản Lý Chi Tiêu Cá Nhân (C)

Chương trình quản lý tài chính cá nhân viết bằng C thuần, sử dụng kỹ thuật mảng động (Dynamic Array), kiến trúc phân chia module rõ ràng và không phụ thuộc thư viện ngoài (Ngoại trừ `<windows.h>` để hỗ trợ Unicode tiếng Việt).

---

## Cấu Trúc Dự Án

```
QUAN_LY_CHI_TIEU
├── include/
│   ├── models.h          # Cấu trúc GiaoDich, NganSach và biến toàn cục
│   ├── utils.h           # Khai báo các hàm tiện ích (kiểm tra ngày tháng, in ấn)
│   ├── file_io.h         # Khai báo các hàm cấp phát bộ nhớ & Đọc/Ghi file
│   └── features.h        # Khai báo các hàm xử lý logic nghiệp vụ & UI
|

├── src/
│   ├── main.c            # Điểm vào chương trình (Menu điều hướng chính)
│   ├── globals.c         # Khởi tạo vùng nhớ cho các biến toàn cục
│   ├── utils.c           # Triển khai logic định dạng, validate dữ liệu
│   ├── file_io.c         # Triển khai thuật toán đọc/ghi file và malloc/realloc
│   └── features.c        # Triển khai nghiệp vụ (Thêm, Sửa, Xóa, Lọc, Báo cáo)
|
├── data/

│   ├── giaodich.txt      # Lưu trữ vĩnh viễn lịch sử các khoản thu/chi
│   └── ngansach.txt      # Lưu trữ vĩnh viễn cấu hình hạn mức định biên theo tháng
└── README.md
```
---

## Tính Năng

### Quản Lý Giao Dịch
- Thêm, xóa, sửa thông tin các khoản Thu / Chi.
- **Máy quét danh mục thông minh:** Tự động trích xuất các tên danh mục đã nhập trong lịch sử để tạo menu chọn nhanh, giúp tiết kiệm thời gian gõ phím.
- Sắp xếp lịch sử giao dịch đa chiều: Theo ID, Ngày tháng, Số tiền (Tăng/Giảm dần).

### Quản Lý Ngân Sách
- Thiết lập, cập nhật, xóa hạn mức chi tiêu tối đa cho từng hạng mục theo từng tháng (Ví dụ: Tháng 06-2026, Ăn uống: 3 triệu).
- Tự động cập nhật giới hạn nếu người dùng thiết lập lại ngân sách cho một mục đã tồn tại.

### Tìm Kiếm & Lọc Nâng Cao
- Tìm kiếm linh hoạt theo từ khóa: Hệ thống tự động quét chuỗi con trên cả 2 trường hợp `Phân loại` và `Ghi chú`.
- Lọc theo khoảng thời gian: Hiển thị các giao dịch phát sinh từ `Ngày A` đến `Ngày B`.

### Báo Cáo & Thống Kê
- Chốt số dư hiện tại của ví tiền (Tổng Thu - Tổng Chi).
- Báo cáo tỷ lệ phần trăm (%) chi tiêu của từng hạng mục trong 1 tháng cụ thể.
- **Đối chiếu ngân sách:** Đặt số tiền Thực tế đã chi cạnh số tiền Định mức, tự động tính toán và in ra trạng thái "Còn dư" hoặc "Vượt mức".

---

## Quy Tắc Nghiệp Vụ

| Quy tắc | Chi tiết |
|---|---|
| **Dữ liệu số tiền** | Bắt buộc phải là số thực dương (`> 0`). Hệ thống sẽ ép nhập lại nếu nhập sai. |
| **Định dạng ngày** | Bắt buộc `DD-MM-YYYY`. Tự động kiểm tra tính hợp lệ của lịch (Năm nhuận, số ngày tối đa trong tháng). |
| **Cảnh báo âm tiền** | Phát tín hiệu cảnh báo ngay khi một khoản Chi mới khiến Tổng Chi > Tổng Thu (Tài khoản mang nợ). |
| **Cảnh báo ngân sách** | Nếu một khoản chi làm vượt hạn mức đã thiết lập của tháng, cảnh báo sẽ hiển thị ngay lập tức. |
| **An toàn dữ liệu** | Các thao tác sắp xếp bảng chỉ làm thay đổi hiển thị, **không làm thay đổi ID gốc** của bản ghi. |

---

## Cài Đặt & Biên Dịch

**Yêu cầu hệ thống:** Trình biên dịch GCC hỗ trợ ngôn ngữ C.

Mở Terminal / Command Prompt và di chuyển đến thư mục gốc của dự án (`QuanLyChiTieu/`) và thực hiện tuần tự 2 bước sau:

**Bước 1: Biên dịch chương trình (Compile)**

```bash
gcc src/globals.c src/utils.c src/file_io.c src/features.c src/main.c -o QuanLyChiTieu
```

**Bước 2: Khởi chạy chương trình (Run)**

* Đối với Windows (PowerShell/CMD):

```bash
.\QuanLyChiTieu
```

* Đối với Linux / macOS:

```bash
./QuanLyChiTieu
```

---

## Hướng Dẫn Sử Dụng

Chương trình chạy hoàn toàn trên giao diện CLI (Command Line Interface). Sau khi khởi động, menu chính hiện ra:

```
+=============================================+
|     QUẢN LÝ CHI TIÊU CÁ NHÂN (TERMINAL)     |
+=============================================+
| 1. Thêm giao dịch (Thu/Chi)                 |
| 2. Sửa giao dịch                            |
| 3. Xóa giao dịch                            |
| 4. Tìm kiếm & Lọc giao dịch                 |
| 5. Thêm/Thiết lập ngân sách                 |
| ...                                         |
| 12. Thoát                                   |
+=============================================+
 Lựa chọn của bạn:
```

Nhập số tương ứng từ 1 đến 12 và nhấn Enter để chọn tính năng.

Lưu ý quan trọng: Lần đầu tiên chạy, chương trình sẽ tự động tạo các file `giaodich.txt` và `ngansach.txt` trong thư mục data/ nếu chúng chưa tồn tại (Vui lòng đảm bảo bạn đã tạo sẵn thư mục trống có tên data/ ở thư mục gốc). Luôn sử dụng tùy chọn `12. Thoát` trong Menu để đóng chương trình. Điều này giúp hệ thống lưu trữ toàn bộ dữ liệu mới nhất xuống ổ cứng và giải phóng RAM an toàn. 

---

## Chi Tiết Kỹ Thuật

- **Quản lý bộ nhớ động**: Cấp phát mảng động bằng `malloc`, mở rộng tự động với `realloc` và thu hồi bằng `free`. Xóa bỏ giới hạn phần tử cố định.

- **Mảng chỉ mục ảo (Virtual Index Array)**: Thuật toán sắp xếp nổi bọt (Bubble Sort) được áp dụng trên một mảng index phụ. Kỹ thuật này giúp in ra danh sách đã được sắp xếp nhưng không làm xáo trộn vị trí của dữ liệu gốc trong mảng thực.

- **Tìm kiếm chuỗi**: Sử dụng hàm `strstr()` tiêu chuẩn của C để tìm kiếm chuỗi con.

- **Xử lý phông chữ**: Sử dụng `SetConsoleOutputCP(CP_UTF8)` của API Windows để ép Terminal hiển thị chuẩn Tiếng Việt có dấu mà không bị lỗi Mojibake.

---




