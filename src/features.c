// Triển khai nghiệp vụ (Thêm, Sửa, Xóa, Lọc, Báo cáo)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/models.h"
#include "../include/utils.h"
#include "../include/file_io.h"
#include "../include/features.h"

void chonPhanLoai(int loai_giao_dich, char* ket_qua) {
    char danhMuc[100][50];
    int soLuongDanhMuc = 0;

    for (int i = 0; i < soLuongGiaoDich; i++) {
        if (danhSachGiaoDich[i].loai == loai_giao_dich) {
            int trung = 0;
            for (int j = 0; j < soLuongDanhMuc; j++) {
                if (strcmp(danhMuc[j], danhSachGiaoDich[i].phan_loai) == 0) { trung = 1; break; }
            }
            if (!trung) {
                strcpy(danhMuc[soLuongDanhMuc++], danhSachGiaoDich[i].phan_loai);
            }
        }
    }

    if (loai_giao_dich == 2) {
        for (int i = 0; i < soLuongNganSach; i++) {
            int trung = 0;
            for (int j = 0; j < soLuongDanhMuc; j++) {
                if (strcmp(danhMuc[j], danhSachNganSach[i].phan_loai) == 0) { trung = 1; break; }
            }
            if (!trung) {
                strcpy(danhMuc[soLuongDanhMuc++], danhSachNganSach[i].phan_loai);
            }
        }
    }

    if (soLuongDanhMuc == 0) {
        xoaBoNhoDem();
        printf("Nhập tên phân loại mới (vd: Lương, Ăn uống): ");
        fgets(ket_qua, 50, stdin);
        xoaXuongDong(ket_qua);
    } else {
        printf("\n  [CHỌN DANH MỤC CÓ SẴN]\n");
        for (int i = 0; i < soLuongDanhMuc; i++) {
            printf("  %d. %s\n", i + 1, danhMuc[i]);
        }
        printf("  %d. [+ Nhập phân loại mới...]\n", soLuongDanhMuc + 1);
        
        int chon_dm;
        do {
            printf("  Lựa chọn của bạn (1-%d): ", soLuongDanhMuc + 1);
            if (scanf("%d", &chon_dm) != 1) { xoaBoNhoDem(); chon_dm = 0; }
        } while(chon_dm < 1 || chon_dm > soLuongDanhMuc + 1);
        
        xoaBoNhoDem(); 
        if (chon_dm <= soLuongDanhMuc) {
            strcpy(ket_qua, danhMuc[chon_dm - 1]);
            printf("=> Đã chọn danh mục: %s\n", ket_qua);
        } else {
            printf("Nhập tên phân loại mới: ");
            fgets(ket_qua, 50, stdin);
            xoaXuongDong(ket_qua);
        }
    }
}

void kiemTraCanhBaoNganSach(char* phan_loai, char* ngay_thang) {
    char thang_hien_tai[10];
    strcpy(thang_hien_tai, &ngay_thang[3]);
    float tongChi = 0;
    for (int i = 0; i < soLuongGiaoDich; i++) {
        char thang_giao_dich[10];
        strcpy(thang_giao_dich, &danhSachGiaoDich[i].ngay_thang[3]);
        if (danhSachGiaoDich[i].loai == 2 && strcmp(danhSachGiaoDich[i].phan_loai, phan_loai) == 0 && strcmp(thang_giao_dich, thang_hien_tai) == 0) {
            tongChi += danhSachGiaoDich[i].so_tien;
        }
    }
    for (int i = 0; i < soLuongNganSach; i++) {
        if (strcmp(danhSachNganSach[i].phan_loai, phan_loai) == 0 && strcmp(danhSachNganSach[i].thang, thang_hien_tai) == 0) {
            if (tongChi > danhSachNganSach[i].han_muc) {
                printf("\n[!!! CẢNH BÁO NGÂN SÁCH !!!] Hạng mục '%s' trong tháng %s đã VƯỢT ngân sách!\n", phan_loai, thang_hien_tai);
                printf("Đã chi: %.2f / Ngân sách định mức: %.2f\n", tongChi, danhSachNganSach[i].han_muc);
            }
            return;
        }
    }
}

void themGiaoDich() {
    capPhatGiaoDich(); 
    GiaoDich gd_moi;
    printf("\n--- THÊM GIAO DỊCH ---\n");
    do {
        printf("Loại giao dịch (1 - Thu, 2 - Chi): ");
        scanf("%d", &gd_moi.loai);
        if (gd_moi.loai != 1 && gd_moi.loai != 2) printf("[LỖI] Chỉ được nhập 1 hoặc 2!\n");
    } while (gd_moi.loai != 1 && gd_moi.loai != 2);
    
    do {
        printf("Số tiền: ");
        scanf("%f", &gd_moi.so_tien);
        if (gd_moi.so_tien <= 0) printf("[LỖI] Số tiền phải lớn hơn 0. Vui lòng nhập lại!\n");
    } while (gd_moi.so_tien <= 0);
    
    chonPhanLoai(gd_moi.loai, gd_moi.phan_loai);
    
    int ngay_hop_le = 0;
    do {
        printf("Ngày (DD-MM-YYYY, vd: 15-06-2026): ");
        scanf("%s", gd_moi.ngay_thang);
        ngay_hop_le = kiemTraNgayHopLe(gd_moi.ngay_thang);
        if (!ngay_hop_le) printf("[LỖI] Ngày sai định dạng. Vui lòng nhập lại!\n");
    } while (!ngay_hop_le);
    
    xoaBoNhoDem();
    printf("Ghi chú (Bấm Enter để bỏ qua): ");
    fgets(gd_moi.ghi_chu, 100, stdin); xoaXuongDong(gd_moi.ghi_chu);
    if(strlen(gd_moi.ghi_chu) == 0) strcpy(gd_moi.ghi_chu, "-");

    if (gd_moi.loai == 2) {
        float vi_tien_hien_tai = tinhSoDuHienTai();
        if (vi_tien_hien_tai - gd_moi.so_tien < 0) {
            printf("\n[!!! CẢNH BÁO SỐ DƯ !!!] Khoản chi này khiến tổng chi VƯỢT QUÁ tổng thu!\n");
        }
    }
    danhSachGiaoDich[soLuongGiaoDich++] = gd_moi;
    luuDuLieu();
    printf("=> Thêm giao dịch thành công!\n");
    if (gd_moi.loai == 2) kiemTraCanhBaoNganSach(gd_moi.phan_loai, gd_moi.ngay_thang);
}

void suaGiaoDich() {
    if (soLuongGiaoDich == 0) { printf("\nChưa có giao dịch nào để sửa.\n"); return; }
    int id;
    printf("\n--- SỬA GIAO DỊCH ---\nNhập ID cần sửa (hoặc 0 để hủy): "); scanf("%d", &id);
    if (id == 0) return;
    if (id < 1 || id > soLuongGiaoDich) { printf("=> [LỖI] ID không tồn tại!\n"); return; }
    
    int index = id - 1; 
    GiaoDich gd_sua; 
    do {
        printf("Loại giao dịch mới (1 - Thu, 2 - Chi): "); scanf("%d", &gd_sua.loai);
    } while (gd_sua.loai != 1 && gd_sua.loai != 2);
    
    do {
        printf("Số tiền mới: "); scanf("%f", &gd_sua.so_tien);
    } while (gd_sua.so_tien <= 0);
    
    chonPhanLoai(gd_sua.loai, gd_sua.phan_loai);
    
    int ngay_hop_le = 0;
    do {
        printf("Ngày mới (DD-MM-YYYY): "); scanf("%s", gd_sua.ngay_thang);
        ngay_hop_le = kiemTraNgayHopLe(gd_sua.ngay_thang);
    } while (!ngay_hop_le);
    
    xoaBoNhoDem();
    printf("Ghi chú mới: "); fgets(gd_sua.ghi_chu, 100, stdin); xoaXuongDong(gd_sua.ghi_chu);
    if(strlen(gd_sua.ghi_chu) == 0) strcpy(gd_sua.ghi_chu, "-");

    float soDuNền = tinhSoDuHienTai() - (danhSachGiaoDich[index].loai == 1 ? danhSachGiaoDich[index].so_tien : -danhSachGiaoDich[index].so_tien);
    float soDuGiaDinh = soDuNền + (gd_sua.loai == 1 ? gd_sua.so_tien : -gd_sua.so_tien);
    if (soDuGiaDinh < 0) printf("\n[!!! CẢNH BÁO SỐ DƯ !!!] Chỉnh sửa khiến tổng chi VƯỢT QUÁ tổng thu!\n");

    danhSachGiaoDich[index] = gd_sua;
    luuDuLieu();
    printf("=> Sửa giao dịch thành công!\n");
    if (danhSachGiaoDich[index].loai == 2) kiemTraCanhBaoNganSach(danhSachGiaoDich[index].phan_loai, danhSachGiaoDich[index].ngay_thang);
}

void xoaGiaoDich() {
    if (soLuongGiaoDich == 0) { printf("\nChưa có giao dịch nào để xóa.\n"); return; }
    int id;
    printf("\n--- XÓA GIAO DỊCH ---\nNhập ID cần xóa (hoặc 0 để hủy): "); scanf("%d", &id);
    if (id == 0) return;
    if (id < 1 || id > soLuongGiaoDich) { printf("=> [LỖI] ID không tồn tại!\n"); return; }
    for (int i = id - 1; i < soLuongGiaoDich - 1; i++) danhSachGiaoDich[i] = danhSachGiaoDich[i + 1];
    soLuongGiaoDich--; 
    luuDuLieu();
    printf("=> Đã xóa thành công giao dịch ID %d!\n", id);
}

void timKiemVaLoc() {
    if (soLuongGiaoDich == 0) { printf("\nChưa có giao dịch nào.\n"); return; }
    int lua_chon;
    printf("\n--- TÌM KIẾM & LỌC ---\n1. Theo từ khóa\n2. Theo thời gian\nLựa chọn: ");
    if (scanf("%d", &lua_chon) != 1) { xoaBoNhoDem(); return; }
    xoaBoNhoDem();

    int* ket_qua = (int*)malloc(soLuongGiaoDich * sizeof(int));
    int so_ket_qua = 0;

    if (lua_chon == 1) {
        char tu_khoa[50];
        printf("Nhập từ khóa: "); fgets(tu_khoa, 50, stdin); xoaXuongDong(tu_khoa);
        for (int i = 0; i < soLuongGiaoDich; i++) {
            if (strstr(danhSachGiaoDich[i].phan_loai, tu_khoa) || strstr(danhSachGiaoDich[i].ghi_chu, tu_khoa))
                ket_qua[so_ket_qua++] = i;
        }
    } else if (lua_chon == 2) {
        char tu_ngay[15], den_ngay[15]; int hop_le = 0;
        do {
            printf("Từ ngày: "); scanf("%s", tu_ngay);
            printf("Đến ngày: "); scanf("%s", den_ngay);
            if (kiemTraNgayHopLe(tu_ngay) && kiemTraNgayHopLe(den_ngay)) hop_le = 1;
        } while (!hop_le);
        for (int i = 0; i < soLuongGiaoDich; i++) {
            if (soSanhNgay(danhSachGiaoDich[i].ngay_thang, tu_ngay) >= 0 && soSanhNgay(danhSachGiaoDich[i].ngay_thang, den_ngay) <= 0)
                ket_qua[so_ket_qua++] = i;
        }
    }
    
    if (so_ket_qua == 0) printf("\n-> Không tìm thấy kết quả.\n");
    else {
        printf("\n-> TÌM THẤY %d GIAO DỊCH:\n", so_ket_qua);
        printf("+----+------+-------------+---------------------------+------------------+-------------------------+\n");
        printf("| ID | Loại | Ngày tháng  | Phân loại                 | Số tiền          | Ghi chú                 |\n");
        printf("+----+------+-------------+---------------------------+------------------+-------------------------+\n");
        for (int k = 0; k < so_ket_qua; k++) {
            int i = ket_qua[k];
            char loai_chu[10]; strcpy(loai_chu, danhSachGiaoDich[i].loai == 1 ? "Thu " : "Chi ");
            char ghi_chu_hien_thi[100]; strcpy(ghi_chu_hien_thi, danhSachGiaoDich[i].ghi_chu);
            if (strlen(ghi_chu_hien_thi) == 0) strcpy(ghi_chu_hien_thi, "-"); 
            printf("| %-2d | %-4s | %-11s | ", i + 1, loai_chu, danhSachGiaoDich[i].ngay_thang);
            inChuoiCanLe(danhSachGiaoDich[i].phan_loai, 25);
            printf(" | %-16.2f | ", danhSachGiaoDich[i].so_tien);
            inChuoiCanLe(ghi_chu_hien_thi, 23); printf(" |\n");
        }
        printf("+----+------+-------------+---------------------------+------------------+-------------------------+\n");
    }
    free(ket_qua); 
}

void xemDanhSachNganSach() {
    if (soLuongNganSach == 0) { printf("\nChưa có ngân sách.\n"); return; }
    printf("\n+----+---------------------------+------------+------------------+\n");
    printf("| ID | Hạng mục ngân sách        | Tháng      | Hạn mức định biên|\n");
    printf("+----+---------------------------+------------+------------------+\n");
    for (int i = 0; i < soLuongNganSach; i++) {
        printf("| %-2d | ", i + 1); inChuoiCanLe(danhSachNganSach[i].phan_loai, 25);
        printf(" | %-10s | %-16.2f |\n", danhSachNganSach[i].thang, danhSachNganSach[i].han_muc);
    }
    printf("+----+---------------------------+------------+------------------+\n");
}

void themNganSach() {
    capPhatNganSach(); 
    NganSach ns_moi;
    printf("\n--- THÊM NGÂN SÁCH ---\n");
    chonPhanLoai(2, ns_moi.phan_loai);
    printf("Tháng (MM-YYYY): "); scanf("%s", ns_moi.thang);
    do {
        printf("Hạn mức tối đa: "); scanf("%f", &ns_moi.han_muc);
    } while (ns_moi.han_muc <= 0);

    for (int i = 0; i < soLuongNganSach; i++) {
        if (strcmp(danhSachNganSach[i].phan_loai, ns_moi.phan_loai) == 0 && strcmp(danhSachNganSach[i].thang, ns_moi.thang) == 0) {
            danhSachNganSach[i].han_muc = ns_moi.han_muc;
            luuDuLieu(); printf("=> Đã cập nhật hạn mức!\n"); return;
        }
    }
    danhSachNganSach[soLuongNganSach++] = ns_moi;
    luuDuLieu(); printf("=> Thiết lập thành công!\n");
}

void suaNganSach() {
    if (soLuongNganSach == 0) return;
    xemDanhSachNganSach();
    int id; printf("\nNhập ID cần sửa: "); scanf("%d", &id);
    if (id < 1 || id > soLuongNganSach) return;
    int index = id - 1;
    chonPhanLoai(2, danhSachNganSach[index].phan_loai);
    printf("Tháng mới (MM-YYYY): "); scanf("%s", danhSachNganSach[index].thang);
    do { printf("Hạn mức mới: "); scanf("%f", &danhSachNganSach[index].han_muc); } while (danhSachNganSach[index].han_muc <= 0);
    luuDuLieu(); printf("=> Sửa thành công!\n");
}

void xoaNganSach() {
    if (soLuongNganSach == 0) return;
    xemDanhSachNganSach();
    int id; printf("\nNhập ID cần xóa: "); scanf("%d", &id);
    if (id < 1 || id > soLuongNganSach) return;
    for (int i = id - 1; i < soLuongNganSach - 1; i++) danhSachNganSach[i] = danhSachNganSach[i + 1];
    soLuongNganSach--; luuDuLieu(); printf("=> Xóa thành công!\n");
}

void xemLichSuGiaoDich() {
    if (soLuongGiaoDich == 0) return;
    printf("\n--- SẮP XẾP ---\n1. Theo ID\n2. Tiền tăng dần\n3. Tiền giảm dần\n4. Ngày gần nhất\nChọn: ");
    int lua_chon_sap_xep; if (scanf("%d", &lua_chon_sap_xep) != 1) { xoaBoNhoDem(); lua_chon_sap_xep = 1; }
    
    int* id_ao = (int*)malloc(soLuongGiaoDich * sizeof(int));
    for (int i = 0; i < soLuongGiaoDich; i++) id_ao[i] = i; 

    for (int i = 0; i < soLuongGiaoDich - 1; i++) {
        for (int j = i + 1; j < soLuongGiaoDich; j++) {
            int hoan_doi = 0;
            if (lua_chon_sap_xep == 2 && danhSachGiaoDich[id_ao[i]].so_tien > danhSachGiaoDich[id_ao[j]].so_tien) hoan_doi = 1;
            else if (lua_chon_sap_xep == 3 && danhSachGiaoDich[id_ao[i]].so_tien < danhSachGiaoDich[id_ao[j]].so_tien) hoan_doi = 1;
            else if (lua_chon_sap_xep == 4 && soSanhNgay(danhSachGiaoDich[id_ao[i]].ngay_thang, danhSachGiaoDich[id_ao[j]].ngay_thang) < 0) hoan_doi = 1;
            if (hoan_doi) { int temp = id_ao[i]; id_ao[i] = id_ao[j]; id_ao[j] = temp; }
        }
    }
    printf("\n+----+------+-------------+---------------------------+------------------+-------------------------+\n");
    printf("| ID | Loại | Ngày tháng  | Phân loại                 | Số tiền          | Ghi chú                 |\n");
    printf("+----+------+-------------+---------------------------+------------------+-------------------------+\n");
    for (int k = 0; k < soLuongGiaoDich; k++) {
        int i = id_ao[k]; 
        char loai_chu[10]; strcpy(loai_chu, danhSachGiaoDich[i].loai == 1 ? "Thu " : "Chi ");
        char ghi_chu_hien_thi[100]; strcpy(ghi_chu_hien_thi, danhSachGiaoDich[i].ghi_chu);
        if (strlen(ghi_chu_hien_thi) == 0) strcpy(ghi_chu_hien_thi, "-"); 
        printf("| %-2d | %-4s | %-11s | ", i + 1, loai_chu, danhSachGiaoDich[i].ngay_thang);
        inChuoiCanLe(danhSachGiaoDich[i].phan_loai, 25);
        printf(" | %-16.2f | ", danhSachGiaoDich[i].so_tien);
        inChuoiCanLe(ghi_chu_hien_thi, 23); printf(" |\n");
    }
    printf("+----+------+-------------+---------------------------+------------------+-------------------------+\n");
    free(id_ao);
}

void xemSoDuHienTai() {
    float tongThu = 0, tongChi = 0;
    for (int i = 0; i < soLuongGiaoDich; i++) {
        if (danhSachGiaoDich[i].loai == 1) tongThu += danhSachGiaoDich[i].so_tien;
        else tongChi += danhSachGiaoDich[i].so_tien;
    }
    printf("\n+---------------------------------------+\n|             SỐ DƯ HIỆN TẠI            |\n+-----------------------+---------------+\n");
    printf("| Tổng thu              | %13.2f |\n| Tổng chi              | %13.2f |\n+-----------------------+---------------+\n", tongThu, tongChi);
    printf("| SỐ DƯ CÒN LẠI         | %13.2f |\n+-----------------------+---------------+\n", tongThu - tongChi);
    if (tongChi > tongThu) printf("|   [!!! CẢNH BÁO TÌNH TRẠNG ÂM !!!]    |\n+---------------------------------------+\n");
}

void baoCaoVaThongKe() {
    char thang[10]; xoaBoNhoDem();
    printf("\nNhập tháng cần xem (MM-YYYY): "); scanf("%s", thang);
    float tongChi = 0, tongTienDM[100] = {0};
    char danhMuc[100][50]; int soDM = 0;

    for (int i = 0; i < soLuongGiaoDich; i++) {
        char thang_gd[10]; strcpy(thang_gd, &danhSachGiaoDich[i].ngay_thang[3]); 
        if (danhSachGiaoDich[i].loai == 2 && strcmp(thang_gd, thang) == 0) {
            tongChi += danhSachGiaoDich[i].so_tien;
            int pos = -1;
            for (int j = 0; j < soDM; j++) if (strcmp(danhMuc[j], danhSachGiaoDich[i].phan_loai) == 0) { pos = j; break; }
            if (pos != -1) tongTienDM[pos] += danhSachGiaoDich[i].so_tien;
            else { strcpy(danhMuc[soDM], danhSachGiaoDich[i].phan_loai); tongTienDM[soDM++] = danhSachGiaoDich[i].so_tien; }
        }
    }

    printf("\n1. TỶ LỆ CHI TIÊU THÁNG %s:\n", thang);
    if (tongChi == 0) printf("-> Chưa có giao dịch.\n");
    else {
        printf("+---------------------------+---------------+\n");
        for (int i = 0; i < soDM; i++) {
            printf("| "); inChuoiCanLe(danhMuc[i], 25); printf(" | %12.2f%% |\n", (tongTienDM[i] / tongChi) * 100);
        }
        printf("+---------------------------+---------------+\n");
    }

    printf("\n2. TÌNH TRẠNG NGÂN SÁCH:\n+----------------------+------------------+------------------+------------------+\n");
    int coNS = 0;
    for (int j = 0; j < soLuongNganSach; j++) {
        if (strcmp(danhSachNganSach[j].thang, thang) == 0) {
            coNS++; float chiThucTe = 0;
            for (int i = 0; i < soLuongGiaoDich; i++) {
                char thang_gd[10]; strcpy(thang_gd, &danhSachGiaoDich[i].ngay_thang[3]);
                if (danhSachGiaoDich[i].loai == 2 && strcmp(danhSachGiaoDich[i].phan_loai, danhSachNganSach[j].phan_loai) == 0 && strcmp(thang_gd, thang) == 0) 
                    chiThucTe += danhSachGiaoDich[i].so_tien;
            }
            printf("| "); inChuoiCanLe(danhSachNganSach[j].phan_loai, 20); printf(" | %16.2f | %16.2f | ", chiThucTe, danhSachNganSach[j].han_muc);
            char trang_thai[50];
            if (chiThucTe > danhSachNganSach[j].han_muc) sprintf(trang_thai, "Vượt %.2f", chiThucTe - danhSachNganSach[j].han_muc);
            else sprintf(trang_thai, "Còn dư %.2f", danhSachNganSach[j].han_muc - chiThucTe);
            inChuoiCanLe(trang_thai, 16); printf(" |\n");
        }
    }
    if (coNS == 0) printf("| %-72s |\n", "Không có dữ liệu.");
    printf("+----------------------+------------------+------------------+------------------+\n");
}