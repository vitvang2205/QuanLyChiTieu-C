// Điểm vào chương trình (Menu điều hướng chính)
#include <stdio.h>
#include <windows.h> // Thêm thư viện Windows để xử lý phông chữ
#include "../include/models.h"
#include "../include/utils.h"
#include "../include/file_io.h"
#include "../include/features.h"

int main() {
    // Ép Terminal của Windows hiển thị chuẩn tiếng Việt UTF-8
    SetConsoleOutputCP(CP_UTF8); 

    taiDuLieu(); 
    int lua_chon;
    do {
        printf("\n+=============================================+\n");
        printf("|     QUẢN LÝ CHI TIÊU CÁ NHÂN (TERMINAL)     |\n");
        printf("+=============================================+\n");
        printf("| 1. Thêm giao dịch (Thu/Chi)                 |\n");
        printf("| 2. Sửa giao dịch                            |\n");
        printf("| 3. Xóa giao dịch                            |\n");
        printf("| 4. Tìm kiếm & Lọc giao dịch                 |\n");
        printf("| 5. Thêm/Thiết lập ngân sách                 |\n");
        printf("| 6. Sửa ngân sách                            |\n");
        printf("| 7. Xóa ngân sách                            |\n");
        printf("| 8. Xem danh sách ngân sách hiện tại         |\n");
        printf("| 9. Xem danh sách lịch sử giao dịch          |\n");
        printf("| 10. Xem số dư hiện tại                      |\n");
        printf("| 11. Báo cáo & Thống kê                      |\n");
        printf("| 12. Thoát                                   |\n");
        printf("+=============================================+\n");
        printf(" Lựa chọn của bạn: ");
        
        if (scanf("%d", &lua_chon) != 1) {
            xoaBoNhoDem();
            lua_chon = 0; 
        }

        switch (lua_chon) {
            case 1: themGiaoDich(); break;
            case 2: suaGiaoDich(); break;
            case 3: xoaGiaoDich(); break;
            case 4: timKiemVaLoc(); break; 
            case 5: themNganSach(); break;
            case 6: suaNganSach(); break;
            case 7: xoaNganSach(); break;
            case 8: xemDanhSachNganSach(); break;
            case 9: xemLichSuGiaoDich(); break;
            case 10: xemSoDuHienTai(); break;
            case 11: baoCaoVaThongKe(); break;
            case 12: 
                luuDuLieu(); 
                giaiPhongBoNho(); 
                printf("\nĐã lưu dữ liệu. Tạm biệt!\n"); 
                break;
            default: printf("Lựa chọn không hợp lệ. Vui lòng thử lại!\n");
        }
    } while (lua_chon != 12);

    return 0;
}