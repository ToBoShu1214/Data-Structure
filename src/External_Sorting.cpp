#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;

double calculateInputTime(int n, int S, int k, double ts, double tl, double tt) {
    int m = n / S; // 假設n/S整除
    double log_k_m = log(static_cast<double>(m)) / log(static_cast<double>(k));
    int passes = static_cast<int>(ceil(log_k_m));
    double block_time = ts + tl + tt * (S / k);
    double total_blocks = (static_cast<double>(n) / S) * k;
    return passes * total_blocks * block_time;
}

int main() {
    int n = 200000;
    int S = 2000;
    int m = 100; // 使用n/S=100，忽略問題中的m=64以保持一致性
    double ts = 80.0; // ms
    double tl = 20.0; // ms
    double tt = 1.0;  // ms/record
    vector<int> k_values = { 2, 4, 8, 16, 32 };
    vector<double> input_times;

    // 獲取當前時間
    time_t now = time(0);
    tm* ltm = localtime(&now);
    cout << "當前日期和時間: " << 1900 + ltm->tm_year << "年"
        << 1 + ltm->tm_mon << "月" << ltm->tm_mday << "日星期"
        << (ltm->tm_wday == 1 ? "一" : ltm->tm_wday == 2 ? "二" :
            ltm->tm_wday == 3 ? "三" : ltm->tm_wday == 4 ? "四" :
            ltm->tm_wday == 5 ? "五" : ltm->tm_wday == 6 ? "六" : "日")
        << (ltm->tm_hour >= 12 ? "下午" : "上午")
        << (ltm->tm_hour >= 12 ? ltm->tm_hour - 12 : ltm->tm_hour) << ":"
        << (ltm->tm_min < 10 ? "0" : "") << ltm->tm_min << " (CST)" << endl;
    cout << "計算 t_input (單位: 秒):" << endl;

    for (int k : k_values) {
        double t_input = calculateInputTime(n, S, k, ts, tl, tt) / 1000.0; // 轉換為秒
        input_times.push_back(t_input);
        cout << "k = " << k << ", t_input = " << fixed << setprecision(1)
            << t_input << " 秒" << endl;
    }

    return 0;
}
