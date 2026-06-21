// Triển khai logic định dạng, validate dữ liệu
#include <stdio.h>
#include <string.h>
#include "../include/models.h"
#include "../include/utils.h"

void xoaBoNhoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void xoaXuongDong(char* chuoi) {
    chuoi[strcspn(chuoi, "\r\n")] = 0;
}

int laNamNhuan(int nam) {
    return ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0));
}

int soNgayTrongThang(int thang, int nam) {
    switch(thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return laNamNhuan(nam) ? 29 : 28;
        default: return 0; 
    }
}

int kiemTraNgayHopLe(char* ngay_thang) {
    if (strlen(ngay_thang) != 10) return 0;
    if (ngay_thang[2] != '-' || ngay_thang[5] != '-') return 0;
    int ngay, thang, nam;
    if (sscanf(ngay_thang, "%d-%d-%d", &ngay, &thang, &nam) != 3) return 0;
    if (nam < 1900 || nam > 2100) return 0;
    if (thang < 1 || thang > 12) return 0;
    if (ngay < 1 || ngay > soNgayTrongThang(thang, nam)) return 0;
    return 1; 
}

void inChuoiCanLe(char* chuoi, int chieu_rong) {
    printf("%s", chuoi);
    int do_dai_hien_thi = 0;
    for (int i = 0; chuoi[i] != '\0'; i++) {
        if ((chuoi[i] & 0xC0) != 0x80) do_dai_hien_thi++;
    }
    for (int i = 0; i < chieu_rong - do_dai_hien_thi; i++) {
        printf(" ");
    }
}

int soSanhNgay(char* ngay1, char* ngay2) {
    int d1, m1, y1, d2, m2, y2;
    sscanf(ngay1, "%d-%d-%d", &d1, &m1, &y1);
    sscanf(ngay2, "%d-%d-%d", &d2, &m2, &y2);
    if (y1 != y2) return y1 - y2;
    if (m1 != m2) return m1 - m2;
    return d1 - d2;
}

float tinhSoDuHienTai() {
    float tongThu = 0, tongChi = 0;
    for (int i = 0; i < soLuongGiaoDich; i++) {
        if (danhSachGiaoDich[i].loai == 1) tongThu += danhSachGiaoDich[i].so_tien;
        else if (danhSachGiaoDich[i].loai == 2) tongChi += danhSachGiaoDich[i].so_tien;
    }
    return tongThu - tongChi;
}