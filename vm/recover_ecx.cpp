struct foo_t
{
	foo_t() : name_("foo_t"){}
	~foo_t() {delete p_; p_ = 0;}
	char* name_;
	void func()
	{
		p_ = new int;
	}
	int *p_;
};

struct bar_t
{
	bar_t() : name_("bar_t"){t_ = new foo_t();}
	char* name_;
	void func()
	{
		t_->func();
	}
	foo_t* t_;
};

struct zoo_t
{
	zoo_t() : name_("zoo_t"){}
	char* name_;
	void func()
	{
		t.func();
	}
	int n;
	bar_t t;
};

void main(){zoo_t z; z.func();}