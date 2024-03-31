#include <iostream>
#include <deque>
#include <thread>
#include <chrono>
#include <iomanip>
#include <Windows.h>  // For Windows OS
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// Constants
const int SCAN_INTERVAL = 30;  // Scan interval in seconds
const int MOVING_AVG_WINDOW = 300;  // Moving average window in seconds

// Function to get CPU usage (Windows-specific)
double get_cpu_usage() {
    FILETIME idle_time, kernel_time, user_time;
    GetSystemTimes(&idle_time, &kernel_time, &user_time);

    ULONGLONG kernel_diff = (kernel_time.dwHighDateTime << 32) + kernel_time.dwLowDateTime;
    ULONGLONG user_diff = (user_time.dwHighDateTime << 32) + user_time.dwLowDateTime;
    ULONGLONG idle_diff = (idle_time.dwHighDateTime << 32) + idle_time.dwLowDateTime;

    ULONGLONG total = kernel_diff + user_diff;
    ULONGLONG idle = idle_diff;

    double cpu_usage = 100.0 - (100.0 * idle) / total;
    return cpu_usage;
}

// Function to get memory usage
double get_memory_usage() {
    MEMORYSTATUSEX mem_info;
    mem_info.dwLength = sizeof(mem_info);
    GlobalMemoryStatusEx(&mem_info);
    double memory_usage = 100.0 * (1.0 - ((double)mem_info.ullAvailPhys / (double)mem_info.ullTotalPhys));
    return memory_usage;
}

// Calculate minimum, maximum, average
void calculate_stats(const std::deque<double>& data, double& minimum, double& maximum, double& average) {
    if (data.empty()) {
        minimum = maximum = average = 0.0;
        return;
    }

    minimum = *std::min_element(data.begin(), data.end());
    maximum = *std::max_element(data.begin(), data.end());

    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    average = sum / data.size();
}

// Calculate moving average
double calculate_moving_avg(const std::deque<double>& data) {
    if (data.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

int main() {
    std::deque<double> cpu_usage_data;
    std::deque<double> memory_usage_data;

    while (true) {
        double cpu_usage = get_cpu_usage();
        double memory_usage = get_memory_usage();

        cpu_usage_data.push_back(cpu_usage);
        memory_usage_data.push_back(memory_usage);

        if (cpu_usage_data.size() > (MOVING_AVG_WINDOW / SCAN_INTERVAL)) {
            cpu_usage_data.pop_front();
        }
        if (memory_usage_data.size() > (MOVING_AVG_WINDOW / SCAN_INTERVAL)) {
            memory_usage_data.pop_front();
        }

        // Calculate min, max, avg for CPU
        double cpu_min, cpu_max, cpu_avg;
        calculate_stats(cpu_usage_data, cpu_min, cpu_max, cpu_avg);

        // Calculate min, max, avg for Memory
        double memory_min, memory_max, memory_avg;
        calculate_stats(memory_usage_data, memory_min, memory_max, memory_avg);

        // Calculate moving average
        double cpu_moving_avg = calculate_moving_avg(cpu_usage_data);
        double memory_moving_avg = calculate_moving_avg(memory_usage_data);

        // Print results
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "CPU Usage - Min: " << cpu_min << "% Max: " << cpu_max << "% Avg: " << cpu_avg << "% Moving Avg: " << cpu_moving_avg << "%" << std::endl;
        std::cout << "Memory Usage - Min: " << memory_min << "% Max: " << memory_max << "% Avg: " << memory_avg << "% Moving Avg: " << memory_moving_avg << "%" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(SCAN_INTERVAL));
    }

    return 0;
}
