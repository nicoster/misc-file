#include <windows.h>
#include <boost/assert.hpp>

typedef 
/**
    Created 2007.6.7 by PeakGao
    Email: peakgao163@163.com
*/

#ifndef __IOBUFFER_H__
#define __IOBUFFER_H__


//**//** ʾ��.
// @code
 //@endcode
 //*/

/**//// ����������
class basic_buffer
{
public:
    enum bufstate{ _good = 0x0, _eof = 0x1, _fail = 0x2, _bad = 0x4/**//*���ش���*/};

protected:
    void*        _buf;        /**//// �������׵�ַ
    size_t        _bufSize;    /**//// ��������С
    size_t        _pos;        /**//// ��ǰ����λ��
    bufstate    _state;        /**//// ��������ǰ������״̬

    // ���죨������
protected:
    basic_buffer() : _buf(0), _bufSize(0), _pos(0), _state(_good) { }

public:
    basic_buffer(void* buffer, size_t maxsize) : _buf(buffer), _bufSize(maxsize), _pos(0), _state(_good)
    {
        assert(buffer != 0 && maxsize > 0);
    }

    ~basic_buffer() { }

    // ״̬��أ����ڼ������Ľ����
public:
    bool operator !() const
    {
        return (!good());
    }

    operator bool() const
    {
        return (good());
    }

    bufstate state() const
    {
        return _state;
    }

    void setstate(bufstate state_)
    {
        if (state_ != _good)
            _state = (bufstate)((int)_state | (int)state_);
    }

    void setstate(int state_)
    {
        setstate((bufstate)state_);
    }

    bool good() const
    {
        return ((int)state() == (int)_good || (int)state() == (int)(_good | _eof));
    }

    bool eof() const
    {
        return ((int)state() & (int)_eof);
    }

    bool fail() const
    {
        return (((int)state() & ((int)_fail | (int)_bad)) != 0);
    }

    bool bad() const
    {
        return (((int)state() & (int)_bad) != 0);
    }


    // ���Լ�����
public:
    /**//// �������������
    void clear()
    {
        memset(_buf, 0, _bufSize);
        _pos = 0;
        _state = _good;
    }

    /**//// ����ǰλ������ƶ�ָ���Ĵ�С
    void skipn(size_t bytes)
    {
        if (_pos + bytes <= _bufSize)
        {
            _pos += bytes;

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
            setstate(basic_buffer::_eof|basic_buffer::_fail);
    }

    /**//// ��ȡ��������ַ
    void* buffer() const
    {
        return _buf;
    }

    /**//// ��ȡ��������ǰλ�õĵ�ַ
    void* current() const
    {
        return (char*)_buf + _pos;
    }

    /**//// ��ȡ���������ݲ����ĵ�ǰλ��ƫ��
    size_t pos() const
    {
        return _pos;
    }

    /**//// ��ȡ�����������������������Ĵ�С��
    size_t capacity() const
    {
        return _bufSize;
    }
};




/**//// ������壨ָ�������ݵ��뵽�������У�
class obuffer : public basic_buffer
{
    // ���죨������
protected:
    obuffer() : basic_buffer() { }

public:
    obuffer(void* buffer, size_t maxsize) : basic_buffer(buffer, maxsize)    { }

    ~obuffer() { }


    // ����
public:
    /**//// ��ȡ�����������ݵ�ʵ��ռ�óߴ�
    size_t size() const
    {
        return pos();
    }

    /**//// �򻺳���д����־��й̶����ȵ��������ͣ����������ͺ͸������ͣ��ṹ��
    template <class T> obuffer& operator << (T value)
    {
        if (_pos + sizeof(T) <= _bufSize)
        {
            *(T*)((char*)_buf + _pos) = value;
            _pos += sizeof(T);

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
        {
            setstate(basic_buffer::_eof|basic_buffer::_fail);
        }
        return (*this);
    }

//ʹ��GCC����ʱ,�öδ������Ҫ��ֲ��buffer.cpp�ļ��з������
#ifdef _MSC_VER

    /**//// �Գ��ַ������ػ�����
    template<> obuffer& operator << (const char* value)
    {
        return push((void*)value, strlen(value) + sizeof(char));
    }
    
    /**//// ���ַ������ػ�����
    template<> obuffer& operator << (char* value)
    {
        return push((void*)value, strlen(value) + sizeof(char));
    }

    /**//// �Գ����ַ������ػ�����
    template<> obuffer& operator << (const wchar_t* value)
    {
        return push((void*)value, (wcslen(value) + 1) * sizeof(wchar_t));
    }

    /**//// �Կ��ַ������ػ�����
    template<> obuffer& operator << (wchar_t* value)
    {
        return push((void*)value, (wcslen(value) + 1) * sizeof(wchar_t));
    }

#endif

    /**//// ����ĳ���������ͣ������и�ֵ�������ı䵱ǰλ�ã�
    template <class T> obuffer& skip()
    {
        if (_pos + sizeof(T) <= _bufSize)
        {
            _pos += sizeof(T);

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
        {
            setstate(basic_buffer::_eof|basic_buffer::_fail);
        }
        return (*this);
    }

    /**//// �ڵ�ǰλ�õ���һ�λ���
    obuffer& push(void* buffer, size_t bytes)
    {
        if (buffer == 0 || bytes == 0)
        {
            setstate(basic_buffer::_bad|basic_buffer::_fail);
            return (*this);
        }

        if (_pos + bytes <= _bufSize)
        {
            memcpy((char*)_buf + _pos, buffer, bytes);
            _pos += bytes;

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
        {
            setstate(basic_buffer::_eof|basic_buffer::_fail);
        }
        return (*this);
    }
};


/**//// �̶���С���������
template <size_t _MaxBytes = 256>
class FixOutBuffer : public obuffer
{
protected:
    enum {_Buf_Size = _MaxBytes ? ((_MaxBytes + 7) & ~7) : 8}; // 8�ֽڶ���
    char _data[_Buf_Size];

public:
    FixOutBuffer()
    {
        _buf = _data;
        _bufSize = _Buf_Size;
        _pos = 0;
        _state = basic_buffer::_good;
    }

    ~FixOutBuffer() { }
};




/**//// ���뻺�壨ָ�ӻ������е����������ݣ�
class ibuffer : public basic_buffer
{
    // ���죨������
protected:
    ibuffer() : basic_buffer() { }

public:
    ibuffer(void* buffer, size_t actualSize) : basic_buffer(buffer, actualSize)    { }

    ~ibuffer() { }


    // ����
public:
    /**//// ��ȡ�����������ݵ�ʵ��ռ�óߴ�
    size_t size() const
    {
        return _bufSize;
    }

    /**//// �ӻ������������־��й̶����ȵ��������ͣ����������ͺ͸������ͣ��ṹ��
    template <class T> ibuffer& operator >> (T& value)
    {
        if (_pos + sizeof(T) <= _bufSize)
        {
            value = *(T*)((char*)_buf + _pos);
            _pos += sizeof(T);

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
        {
            setstate(basic_buffer::_eof|basic_buffer::_fail);
        }
        return (*this);
    }

//ʹ��GCC����ʱ,�öδ������Ҫ��ֲ��buffer.cpp�ļ��з������
#ifdef _MSC_VER
    /**//// �Գ��ַ������ػ�����
    template<> ibuffer& operator >> (const char*& value)
    {
        const char* str = (const char*)_buf + _pos;
        while ((size_t)(str - (const char*)_buf) < _bufSize && *str++);
        size_t bytes = (size_t)(str - (char*)_buf) - _pos;
        if (bytes > 0 && _pos + bytes <= _bufSize)
        {
            if (*((char*)_buf + _pos + bytes - 1) != 0) // ����0��β���ַ���
            {
                setstate(basic_buffer::_eof|basic_buffer::_bad);
                return (*this);
            }
            value = (char*)_buf + _pos;
            _pos += bytes;

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
        {
            setstate(basic_buffer::_eof|basic_buffer::_fail);
            value = 0;
        }

        return (*this);
    }

    /**//// ���ַ������ػ�����
    template<> ibuffer& operator >> (char*& value)
    {
        const char* str = (const char*)_buf + _pos;
        while ((size_t)(str - (const char*)_buf) < _bufSize && *str++);
        size_t bytes = (size_t)(str - (char*)_buf) - _pos;
        if (bytes > 0 && _pos + bytes <= _bufSize)
        {
            if (*((char*)_buf + _pos + bytes - 1) != 0) // ����0��β
            {
                setstate(basic_buffer::_eof|basic_buffer::_bad);
                return (*this);
            }
            value = (char*)_buf + _pos;
            _pos += bytes;

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
        {
            setstate(basic_buffer::_eof|basic_buffer::_fail);
            value = 0;
        }

        return (*this);
    }

    /**//// �Գ����ַ������ػ�����
    template<> ibuffer& operator >> (const wchar_t*& value)
    {
        const wchar_t* str = (const wchar_t*)((Int8*)_buf + _pos);
        while ((size_t)((Int8*)str - (Int8*)_buf) < _bufSize && *str++);
        size_t bytes = (size_t)((Int8*)str - (Int8*)_buf) - _pos;
        if (bytes > 0 && _pos + bytes <= _bufSize)
        {
            if (*(const wchar_t*)((Int8*)_buf + _pos + bytes - sizeof(wchar_t)) != 0) // ����0��β
            {
                setstate(basic_buffer::_eof|basic_buffer::_bad);
                return (*this);
            }
            value = (const wchar_t*)((Int8*)_buf + _pos);
            _pos += bytes;

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
        {
            setstate(basic_buffer::_eof|basic_buffer::_fail);
            value = 0;
        }

        return (*this);
    }

    /**//// �Կ��ַ������ػ�����
    template<> ibuffer& operator >> (wchar_t*& value)
    {
        const wchar_t* str = (const wchar_t*)((Int8*)_buf + _pos);
        while ((size_t)((Int8*)str - (Int8*)_buf) < _bufSize && *str++);
        size_t bytes = (size_t)((Int8*)str - (Int8*)_buf) - _pos;
        if (bytes > 0 && _pos + bytes <= _bufSize)
        {
            if (*(const wchar_t*)((Int8*)_buf + _pos + bytes - sizeof(wchar_t)) != 0) // ����0��β
            {
                setstate(basic_buffer::_eof|basic_buffer::_bad);
                return (*this);
            }
            value = (wchar_t*)((Int8*)_buf + _pos);
            _pos += bytes;

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
        {
            setstate(basic_buffer::_eof|basic_buffer::_fail);
            value = 0;
        }

        return (*this);
    }
#endif

    /**//// ����ĳ���������ͣ������и�ֵ�������ı䵱ǰλ�ã�
    template <class T> ibuffer& skip()
    {
        if (_pos + sizeof(T) <= _bufSize)
        {
            _pos += sizeof(T);

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
            setstate(basic_buffer::_eof|basic_buffer::_fail);
        return (*this);
    }

    /**//// �ڵ�ǰλ�õ���һ�λ���
    ibuffer& pop(void* buffer, size_t bytes)
    {
        if (buffer == 0 || bytes == 0)
        {
            setstate(basic_buffer::_bad|basic_buffer::_fail);
            return (*this);
        }

        if (_pos + bytes <= _bufSize)
        {
            memcpy(buffer, (char*)_buf + _pos, bytes);
            _pos += bytes;

            if (_pos == _bufSize)
                setstate(basic_buffer::_eof);
        }
        else
        {
            setstate(basic_buffer::_eof|basic_buffer::_fail);
        }
        return (*this);
    }
};


#ifndef FIXOUTBUFFER_TYPEDEF
#    define FIXOUTBUFFER_TYPEDEF
    typedef FixOutBuffer<32>    obuffer32;
    typedef FixOutBuffer<64>    obuffer64;
    typedef FixOutBuffer<256>    obuffer256;
    typedef FixOutBuffer<512>    obuffer512;
    typedef FixOutBuffer<1024>    obuffer1024;
    typedef FixOutBuffer<2048>    obuffer2048;
    typedef FixOutBuffer<4096>    obuffer4096;
#endif

    struct SimpleStruct
    {
        Uint x,y;
    };

    void main()
    {
        SimpleStruct ss;
        ss.x = 11111;
        ss.y = 22222;
        Uint8 v8 = 8;
        Uint16 v16 = 16;
        Uint32 v32 = 32;
        Uint v = 123456789;
        Float vf = 3.1415926f;
        Double vd = 3.1415926535897932;
        long vl = 0xffffffff;
        unsigned long vul = 0xffffffff;
        const char* name = "user name";
        Uint8 mydata[12] = {0,1,2,3,4,5,6,7,8,9,10,11};

        char data[256];
        obuffer out(data, sizeof(data)); // ����ʹ�ã� FixOutBuffer<256> out;
        out < < ss << name << v8 << v16 << v32 << v < < vf << vd << vl << vul; // ����̶��������͵����ݵ�������
        out.push(mydata, sizeof(mydata)); // ����һ�����飨�����������û�����
        if (!out)
        {
            Error("error\n");
        }

        ibuffer in(out.buffer(), out.size());
        ss.x = ss.y = 0;
        const char* nameptr = 0;
        memset(mydata, 0, sizeof(mydata));
        in >> ss >> nameptr >> v8 >> v16;
        in.skip<Uint32>();    // ����һ��Uint32���������ǲ���Ҫ�������
        in >> v >> vf >> vd >> vl >> vul;
        in.pop(mydata, sizeof(mydata));
        if (!in)
        {
            Error("error");
        }
    }


#endif // __BUFFER_H__


