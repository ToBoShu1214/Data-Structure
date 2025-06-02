#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {} // 虛擬解構函數
    virtual bool IsEmpty() const = 0; // 回傳true如果優先隊列為空
    virtual const T& Top() const = 0; // 回傳最小元素的引用
    virtual void Push(const T&) = 0; // 向優先隊列添加元素
    virtual void Pop() = 0; // 刪除具有最小優先級的元素
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    vector<T> heap; // 儲存堆元素

    // 輔助函數，用於堆操作
    void SiftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] <= heap[index]) break;
            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    void SiftDown(int index) {
        int minIndex = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.size() && heap[left] < heap[minIndex])
            minIndex = left;
        if (right < heap.size() && heap[right] < heap[minIndex])
            minIndex = right;

        if (minIndex != index) {
            swap(heap[index], heap[minIndex]);
            SiftDown(minIndex);
        }
    }

public:
    MinHeap() {} // 建構函數

    bool IsEmpty() const override {
        return heap.empty();
    }

    const T& Top() const override {
        if (IsEmpty()) throw runtime_error("堆為空");
        return heap[0];
    }

    void Push(const T& value) override {
        heap.push_back(value);
        SiftUp(heap.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) throw runtime_error("堆為空");
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) SiftDown(0);
    }
};

int main() {
    MinHeap<int> minHeap;

    // 測試最小堆
    minHeap.Push(5);
    minHeap.Push(3);
    minHeap.Push(7);
    minHeap.Push(1);

    cout << "最小元素: " << minHeap.Top() << endl; // 應輸出1
    minHeap.Pop();
    cout << "刪除最小元素後最小元素: " << minHeap.Top() << endl; // 應輸出3

    while (!minHeap.IsEmpty()) {
        cout << "彈出: " << minHeap.Top() << endl;
        minHeap.Pop();
    }

    return 0;
}
