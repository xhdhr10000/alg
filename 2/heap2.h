class Heap2 : public Heap {
public:
	Heap2(int *data, int size) : Heap(size) {
		memcpy(this->h+1, data, sizeof(int)*size);
		this->p = size;
		this->create();
	}

	~Heap2() {
	}

private:
	void create() {
		for (int p=this->p-1; p>0; p--) this->heapify(p);
	}

	void heapify(int p) {
		int l = p*2;
		int r = p*2+1;
		int min = p;
		if (l < this->s && this->h[l] < this->h[p]) min = l;
		if (r < this->s && this->h[r] < this->h[min]) min = r;
		if (min != p) {
			this->swap(p, min);
			this->heapify(min);
		}
	}
};
