// Khai báo các hàm tiện ích (kiểm tra ngày tháng, in ấn)
#ifndef UTILS_H
#define UTILS_H

void xoaBoNhoDem();
void xoaXuongDong(char* chuoi);
int laNamNhuan(int nam);
int soNgayTrongThang(int thang, int nam);
int kiemTraNgayHopLe(char* ngay_thang);
void inChuoiCanLe(char* chuoi, int chieu_rong);
int soSanhNgay(char* ngay1, char* ngay2);
float tinhSoDuHienTai();

#endif