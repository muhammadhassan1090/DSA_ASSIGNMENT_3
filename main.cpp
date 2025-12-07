#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>
#include <iomanip>

using namespace std;

// Helper to find maximum value in array
int getMax(const vector<int>& arr) {
    int maxVal = arr[0];
    for (int x : arr) if (x > maxVal) maxVal = x;
    return maxVal;
}

// Helper to find minimum value in array (for Pigeonhole)
int getMin(const vector<int>& arr) {
    int minVal = arr[0];
    for (int x : arr) if (x < minVal) minVal = x;
    return minVal;
}

// ==========================================
// 1. Counting Sort (Non-Stable)
// ==========================================
void countingSortNonStable(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = getMax(arr);
    
    // Create count array
    vector<int> count(maxVal + 1, 0);
    
    // Store count of each integer
    for (int x : arr) count[x]++;
    
    // Overwrite original array
    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
}

// ==========================================
// 2. Counting Sort (Stable)
// ==========================================
void countingSortStable(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = getMax(arr);
    int n = arr.size();
    
    vector<int> count(maxVal + 1, 0);
    vector<int> output(n);
    
    for (int x : arr) count[x]++;
    
    // Cumulative count to determine positions
    for (int i = 1; i <= maxVal; i++) count[i] += count[i - 1];
    
    // Build output array (Iterate backwards for stability)
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
    // Copy back
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

// ==========================================
// 3. LSD Radix Sort
// ==========================================
void countSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};
    
    // Count occurrences of digit at 'exp' place
    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

void radixSortLSD(vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = getMax(arr);
    
    // Do counting sort for every digit position
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countSortForRadix(arr, exp);
    }
}

// =================
// 4. Bucket Sort 
// =================
void bucketSort(vector<int>& arr) {
    if (arr.empty()) return;
    int n = arr.size();
    int maxVal = getMax(arr);
    int minVal = getMin(arr);
    
    // Range of the buckets
    int range = maxVal - minVal + 1;
    int bucketCount = n; // Heuristic: Number of buckets ~ Number of elements
    vector<vector<int>> buckets(bucketCount);
    
    for (int i = 0; i < n; i++) {
        // Map elements to buckets based on range
        int bucketIndex = (long long)(arr[i] - minVal) * (bucketCount - 1) / range;
        buckets[bucketIndex].push_back(arr[i]);
    }
    
    // Sort individual buckets 
    // and concatenate
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        sort(buckets[i].begin(), buckets[i].end());
        for (int val : buckets[i]) {
            arr[index++] = val;
        }
    }
}

// ===================
// 5. Pigeonhole Sort
// ===================
void pigeonholeSort(vector<int>& arr) {
    if (arr.empty()) return;
    int minVal = getMin(arr);
    int maxVal = getMax(arr);
    int range = maxVal - minVal + 1;
    
    vector<vector<int>> holes(range);
    
    for (int x : arr) {
        holes[x - minVal].push_back(x);
    }
    
    int index = 0;
    for (int i = 0; i < range; i++) {
        for (int val : holes[i]) {
            arr[index++] = val;
        }
    }
}

// ==========================================
// Benchmarking Logic
// ==========================================
void benchmark(string name, void (*sortFunc)(vector<int>&), vector<int> data) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    
    cout << left << setw(25) << name << ": " << duration.count() << " ms" << endl;
    
    // Validate sort
    bool sorted = true;
    for(size_t i=0; i<data.size()-1; i++) {
        if(data[i] > data[i+1]) sorted = false;
    }
    if(!sorted) cout << "ERROR: Array not sorted!" << endl;
}

int main() {
    cout << "--- CS250 Assignment 3: Non-Comparison Sorting Benchmarks ---" << endl;
    
    // Experiment Configuration
    int sizes[] = {1000, 10000, 50000};
    
    for (int n : sizes) {
        cout << "\n[Dataset Size: " << n << "]" << endl;
        
        // Generate random data
        vector<int> data(n);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, n * 2); // Range determines performance for Counting Sort
        
        for (int i = 0; i < n; i++) data[i] = dist(gen);
        
        benchmark("Counting Sort (Stable)", countingSortStable, data);
        benchmark("Counting Sort (Non-Stable)", countingSortNonStable, data);
        benchmark("LSD Radix Sort", radixSortLSD, data);
        benchmark("Bucket Sort", bucketSort, data);
        benchmark("Pigeonhole Sort", pigeonholeSort, data);
    }
    
    return 0;
}