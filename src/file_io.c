// Triển khai thuật toán đọc/ghi file và malloc/realloc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/models.h"
#include "../include/utils.h"
#include "../include/file_io.h"

void capPhatGiaoDich() {
    if (soLuongGiaoDich >= sucChuaGiaoDich) {
        sucChuaGiaoDich = (sucChuaGiaoDich == 0) ? 10 : sucChuaGiaoDich * 2;
        danhSachGiaoDich = (GiaoDich*)realloc(danhSachGiaoDich, sucChuaGiaoDich * sizeof(GiaoDich));
    }
}

void capPhatNganSach() {
    if (soLuongNganSach >= sucChuaNganSach) {
        sucChuaNganSach = (sucChuaNganSach == 0) ? 5 : sucChuaNganSach * 2;
        danhSachNganSach = (NganSach*)realloc(danhSachNganSach, sucChuaNganSach * sizeof(NganSach));
    }
}

void giaiPhongBoNho() {
    if (danhSachGiaoDich != NULL) free(danhSachGiaoDich);
    if (danhSachNganSach != NULL) free(danhSachNganSach);
}

void taiDuLieu() {
    FILE *tepGiaoDich = fopen("data/giaodich.txt", "r"); 
    char buffer[150];
    if (tepGiaoDich != NULL) {
        while (fgets(buffer, sizeof(buffer), tepGiaoDich)) {
            capPhatGiaoDich(); 
            danhSachGiaoDich[soLuongGiaoDich].loai = atoi(buffer);
            fgets(buffer, sizeof(buffer), tepGiaoDich);
            danhSachGiaoDich[soLuongGiaoDich].so_tien = atof(buffer);
            fgets(danhSachGiaoDich[soLuongGiaoDich].phan_loai, 50, tepGiaoDich);
            xoaXuongDong(danhSachGiaoDich[soLuongGiaoDich].phan_loai);
            fgets(danhSachGiaoDich[soLuongGiaoDich].ngay_thang, 15, tepGiaoDich);
            xoaXuongDong(danhSachGiaoDich[soLuongGiaoDich].ngay_thang);
            fgets(danhSachGiaoDich[soLuongGiaoDich].ghi_chu, 100, tepGiaoDich);
            xoaXuongDong(danhSachGiaoDich[soLuongGiaoDich].ghi_chu);
            soLuongGiaoDich++;
        }
        fclose(tepGiaoDich);
    }

    FILE *tepNganSach = fopen("data/ngansach.txt", "r"); 
    if (tepNganSach != NULL) {
        while (fgets(buffer, sizeof(buffer), tepNganSach)) {
            capPhatNganSach(); 
            strcpy(danhSachNganSach[soLuongNganSach].phan_loai, buffer);
            xoaXuongDong(danhSachNganSach[soLuongNganSach].phan_loai);
            fgets(danhSachNganSach[soLuongNganSach].thang, 10, tepNganSach);
            xoaXuongDong(danhSachNganSach[soLuongNganSach].thang);
            fgets(buffer, sizeof(buffer), tepNganSach);
            danhSachNganSach[soLuongNganSach].han_muc = atof(buffer);
            soLuongNganSach++;
        }
        fclose(tepNganSach);
    }
}

void luuDuLieu() {
    FILE *tepGiaoDich = fopen("data/giaodich.txt", "w"); 
    if (tepGiaoDich != NULL) {
        for (int i = 0; i < soLuongGiaoDich; i++) {
            fprintf(tepGiaoDich, "%d\n%.2f\n%s\n%s\n%s\n", 
                    danhSachGiaoDich[i].loai, danhSachGiaoDich[i].so_tien, 
                    danhSachGiaoDich[i].phan_loai, danhSachGiaoDich[i].ngay_thang, danhSachGiaoDich[i].ghi_chu);
        }
        fclose(tepGiaoDich);
    }

    FILE *tepNganSach = fopen("data/ngansach.txt", "w"); 
    if (tepNganSach != NULL) {
        for (int i = 0; i < soLuongNganSach; i++) {
            fprintf(tepNganSach, "%s\n%s\n%.2f\n", 
                    danhSachNganSach[i].phan_loai, danhSachNganSach[i].thang, danhSachNganSach[i].han_muc);
        }
        fclose(tepNganSach);
    }
}