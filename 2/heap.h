class Heap {
protected:
	int *h;
	int s;
	int p;

public:
	Heap(int size) {
		this->h = (int*)malloc(sizeof(int)*(size+1));
		this->s = size;
		this->p = 0;
	}

	~Heap() {
		free(this->h);
	}

	void push(int item) {
		if (this->p + 1 > this->s) {
			this->s *= 2;
			this->h = (int*)realloc(this->h, sizeof(int)*this->s);
		}
		this->h[++this->p] = item;
		int p = this->p;
		while (p > 1 && this->h[p] < this->h[p/2]) {
			this->swap(p, p/2);
			p /= 2;
		}
	}

	int pop() {
		int ret = this->h[1];
		this->h[1] = this->h[this->p--];
		int p = 1;
		while (p*2+1 < this->p && (this->h[p] > this->h[p*2] || this->h[p] > this->h[p*2+1])) {
			if (p*2+1 >= this->p || this->h[p*2] < this->h[p*2+1]) {
				this->swap(p, p*2);
				p *= 2;
			} else {
				this->swap(p, p*2+1);
				p = p*2+1;
			}
		}
		return ret;
	}

protected:
	void swap(int x, int y) {
		int c;
		c = this->h[x];
		this->h[x] = this->h[y];
		this->h[y] = c;
	}
};
