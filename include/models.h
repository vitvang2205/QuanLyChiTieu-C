// Cấu trúc GiaoDich, NganSach và biến toàn cục
#ifndef MODELS_H
#define MODELS_H

// --- CẤU TRÚC DỮ LIỆU ---
typedef struct {
    int loai; // 1: Thu, 2: Chi
    float so_tien;
    char phan_loai[50];
    char ngay_thang[15];
    char ghi_chu[100];
} GiaoDich;

typedef struct {
    char phan_loai[50];
    char thang[10];
    float han_muc;
} NganSach;

// Sử dụng extern để dùng chung biến toàn cục cho toàn project
extern GiaoDich* danhSachGiaoDich;
extern int soLuongGiaoDich;
extern int sucChuaGiaoDich;

extern NganSach* danhSachNganSach;
extern int soLuongNganSach;
extern int sucChuaNganSach;

#endif