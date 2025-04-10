# 排序演算法報告

**41243217 杜長勳  41243222 林諺晟**  
Mar. 30 / 2025  

## 目錄

1. [解題說明](#解題說明)
2. [演算法設計與實作](#演算法設計與實作)
3. [效能分析](#效能分析)
4. [測試與結果](#測試與結果)
5. [結論](#結論)

---

## 解題說明

本報告實作並比較了五種常見排序演算法的效能：

- **插入排序（Insertion Sort）**
- **選擇排序（Selection Sort）**
- **快速排序（Quick Sort）**
- **合併排序（Merge Sort）**
- **堆排序（Heap Sort）**

測試目標為分析各演算法在不同輸入大小下的執行時間，並探討其效能特性。

---

## 演算法設計與實作

### 插入排序 (Insertion Sort)
插入排序的核心思想是將資料一一插入已排序的部分：

1. 對於每個元素 `arr[i]`，將它插入到正確的位置。
2. 使得 `arr[0] ~ arr[i]` 之間保持有序。
```
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```
### 選擇排序 (Selection Sort)
選擇排序的基本原理是：

1. 每次遍歷找出最小值。
2. 將最小值放到當前位置。
3. 重複直到所有元素排序完成。
```
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}
```

### 快速排序 (Quick Sort)
快速排序採用分治法策略：

1. **選擇基準值（pivot）**：使用三數取中法。
2. **分割**：小於 pivot 的元素放左邊，大於 pivot 的放右邊。
3. **遞迴**：對左右兩個子陣列重複上述步驟。
4. **優化**：小於閾值的子陣列改用插入排序。
```
void quickSort(vector<int>& arr, int low, int high) {
    if (low + 10 <= high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    } else {
        insertionSort(arr);
    }
}
```

選取 pivot 方法：

選擇三個元素（頭、中、尾），取中位數作為 pivot，減少最壞情況出現機率。
```
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    swap(arr[mid], arr[high - 1]);
    return arr[high - 1];
}
```


### 合併排序 (Merge Sort)
此實作採用 **迭代式合併排序**：

1. 由下而上合併子陣列。
2. 避免遞迴開銷。
3. 依序處理不同大小的子陣列。
```
void mergeSort(vector<int>& arr) {
    int n = arr.size();
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);
            merge(arr, left, mid, right);
        }
    }
}
```

### 堆排序 (Heap Sort)
堆排序使用 **最大堆** 資料結構：

1. **建立最大堆**。
2. **反覆將堆頂元素（最大值）移至陣列末尾**。
3. **調整剩餘元素為最大堆**。
```
void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

---

## 效能分析

### 時間複雜度比較

| 演算法 | 最佳情況 | 平均情況 | 最差情況 |
|---------|---------|---------|---------|
| 插入排序 | O(n) | O(n²) | O(n²) |
| 選擇排序 | O(n²) | O(n²) | O(n²) |
| 快速排序 | O(n log n) | O(n log n) | O(n²) |
| 合併排序 | O(n log n) | O(n log n) | O(n log n) |
| 堆排序 | O(n log n) | O(n log n) | O(n log n) |

### 主要影響因素

#### 資料大小

- **小型資料集（n < 10）**：插入排序效能優於其他演算法。
- **大型資料集**：`O(n log n)` 演算法明顯優於 `O(n²)` 演算法。

#### 資料分佈

- **近乎有序的資料** → 插入排序較有優勢。
- **隨機分佈的資料** → 快速排序通常表現較好。
- **合併排序與堆排序** → 資料分佈對其影響較小。

---

## 測試與結果

測試使用不同大小的隨機整數陣列（500 至 5000 元素），並呼叫testSorting函式進行測試。
```
int main() {
    vector<int> sizes = { 500, 1000, 2000, 3000, 4000, 5000 };
    srand(time(0)); 

    for (int n : sizes) {
        vector<int> arr(n);
        for (int& x : arr) x = rand() % 10000 + 1; // 依照size生成隨機測資當作排序測資

        cout << "\nSorting for n = " << n << endl;
        testSorting(arr, insertionSort, "Insertion Sort");
        testSorting(arr, selectionSort, "Selection Sort");
        testSorting(arr, quickSort, "Quick Sort");
        testSorting(arr, mergeSort, "Merge Sort");
        testSorting(arr, heapSort, "Heap Sort");
    }

    return 0;
}
```

- **測試方法**：
  - 使用標準 C++ 庫中的 `chrono` 計時工具，確保測量準確性。
  - 每個演算法以相同資料執行，以維持公平比較。
```
void testSorting(vector<int>& arr, void (*sortFunc)(vector<int>&), string sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << sortName << " took " << duration.count() << " ms." << endl;
}
```

### 測試結果趨勢
- 結果
![image](https://github.com/user-attachments/assets/6e2bf288-b234-4a32-8866-a7357f3c8db0)
- 趨勢
1. **O(n²) 演算法**：隨資料量增加，執行時間呈二次方增長。
2. **O(n log n) 演算法**：隨資料量增加，執行時間增長較為緩和。


---

## 結論

### 小資料集

- 插入排序效能佳，實作簡單。
- 快速排序的小型資料優化（閾值轉換為插入排序）有效提升效能。

### 大資料集

- **快速排序** 在實際應用中通常表現最佳。
- **合併排序** 提供穩定的效能保證。
- **堆排序** 在極端情況下有較好的穩定性。

### 應用選擇

| 需求 | 推薦演算法 |
|------|----------|
| **需要穩定排序** | 合併排序 |
| **平均情況效能考量** | 快速排序 |
| **記憶體受限情境** | 堆排序（原地排序） |

---

