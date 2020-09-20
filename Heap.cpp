#include <iostream>
#include <math.h>

using namespace std;

class Heap
{
private:
	int* heap_;
	int size_;
	int height_;

public:
	Heap() : size_(0), height_(0), heap_(nullptr) { }
	~Heap() { delete[] heap_; }
	int hSize() const { return size_; }
	int hHeight() const { return log2(size_); }
	int hiLnode(const int i) const { return (i << 1) + 1; }
	int hiRnode(const int i) const { return (i << 1) + 2; }
	int hiParent(const int i) const { return (int)ceil(i / 2.f) - 1; }
	int hParent(const int i) const { return heap_[hiParent(i)]; }
	int hvLnode(const int i) const { return heap_[hiLnode(i)]; }
	int hvRnode(const int i) const { return heap_[hiRnode(i)]; }

	void hPushBack(const int newValue)
	{
		int* buffer = new int[size_ + 1];

		for (int i = 0; i < size_; i++)
			buffer[i] = heap_[i];

		buffer[size_] = newValue;

		size_++;
		delete[] heap_;
		heap_ = buffer;
		height_ = hHeight();
	}
	void hMaxHeapify(const int i)
	{
		int left = hiLnode(i);
		int right = hiRnode(i);
		int largest = 0;

		if (heap_[i] < heap_[hiLnode(i)] && left < size_) largest = left;
		else largest = i;
		
		if (heap_[largest] < heap_[right] && right < size_) largest = right;

		if (largest != i)
		{
			int buffer = heap_[i];
			heap_[i] = heap_[largest];
			heap_[largest] = buffer;

			hMaxHeapify(largest);
		}
	}
	void hMinHeapify(const int i)
	{
		int left = hiLnode(i);
		int right = hiRnode(i);
		int lowest = 0;

		if (heap_[i] > heap_[hiLnode(i)] && left < size_) lowest = left;
		else lowest = i;

		if (heap_[lowest] > heap_[right] && right < size_) lowest = right;

		if (lowest != i)
		{
			int buffer = heap_[i];
			heap_[i] = heap_[lowest];
			heap_[lowest] = buffer;

			hMinHeapify(lowest);
		}
	}
	void hBuild(string mode="max")
	{
		if (mode == "max")
		{
			for (int i = (size_ / 2) - 1; i >= 0; i--)
				hMaxHeapify(i);
		}
		else
		{
			for (int i = (size_ / 2) - 1; i >= 0; i--)
				hMinHeapify(i);
		}
	}
	void hSort()
	{
		int bufSize = size_;
		hBuild("max");
		for (int i = bufSize - 1; i > 0; i--)
		{
			int buffer = heap_[0];
			heap_[0] = heap_[size_ - 1];
			heap_[size_ - 1] = buffer;
			size_--;
			hMaxHeapify(0);
		}

		size_ = bufSize;
	}

	void hShow() const 
	{
		for (int i = 0; i < size_; i++)
			cout << heap_[i] << " ";
	}
	void hShowGraph() const
	{
		for (int a = 0; a < height_ + 1; a++)
		{
			for (int i = pow(2, a) - 1; i < pow(2, a + 1) - 1; i++)
			{
				if (i == size_) break;
				cout << heap_[i] << " ";
			}
			cout << endl;
		}
	}

	int operator [](int i) { return heap_[i]; }
};

int main()
{
	Heap hp;
	hp.hPushBack(9);
	hp.hPushBack(14);
	hp.hPushBack(1);
	hp.hPushBack(2);
	hp.hPushBack(7);
	hp.hPushBack(16);
	hp.hPushBack(3);
	hp.hPushBack(8);
	hp.hPushBack(4);
	hp.hPushBack(10);
	hp.hPushBack(1);

	cout << "heap: table\n";
	hp.hShow();
	
	cout << "\n\nheap: graph\n";
	hp.hShowGraph();

	cout << "\nheap: graph\n";
	hp.hMaxHeapify(1);
	hp.hShowGraph();

	cout << "\nbuild: max-heap\n";
	hp.hBuild();
	hp.hShowGraph();

	cout << "\nbuild: min-heap\n";
	hp.hBuild("min");
	hp.hShowGraph();

	cout << "\nheap: sort\n";
	hp.hSort();
	hp.hShow();

	cin.get();
	return 0;
}