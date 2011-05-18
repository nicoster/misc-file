#include <windows.h>

struct _lock
{
public:
	_lock() { InitializeCriticalSection( &cs ); }
	virtual ~_lock() { DeleteCriticalSection( &cs ); }
public:
	void lock() { EnterCriticalSection( &cs ); }
	void unlock() { LeaveCriticalSection( &cs ); }
//	bool try_lock() { return TryEnterCriticalSection( &cs ); }
private:
	CRITICAL_SECTION	cs;
};

typedef _lock lock;


class auto_lock
{
public:
	auto_lock( _lock& lock ) : lock(lock) { lock.lock(); }
	~auto_lock() { lock.unlock(); }
private:
	_lock&	lock;
};

struct foo
{
	void bar() const
	{
		auto_lock al(m_lock);
		
		// do some operation..
		
	}
	mutable _lock m_lock;
};

void main()
{
	foo f;
	f.bar();
}