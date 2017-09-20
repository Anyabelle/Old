#include <iostream>
#include <iostream>
#include <string>
#include <cmath>
using std::swap;
using std::cout;
//using std::string;
//using std::sqrt;
class complex
    {
    public:
        complex(const double, const double);
        explicit complex(const char *);
        complex operator~() const;
        complex operator-() const;
        double get_re() const;
        double get_im() const;
        double abs2() const;
        double abs() const;
        void to_string(char *, size_t) const;
    private:
        double re, im;
    };

    complex::complex(const double a = 0, const double b = 0)
    {
        re = a;
        im = b;
    }

    complex::complex(const char *s)
    {
        double a, b;
        if (sscanf(s, "(%lf,%lf)", &a, &b) == 2){
            re = a;
            im = b;
        } else {
            re = 0;
            im = 0;
        }
    }

    complex complex::operator~() const
    {
        return complex(this->re, -this->im);
    }

    complex complex::operator-() const
    {
        return complex(-this->re, -this->im);
    }

    double complex::get_re() const
    {
        return this->re;
    }

    double complex::get_im() const
    {
        return this->im;
    }   

    complex operator+(const complex &c, const complex &d)
    {
        return complex(d.get_re() + c.get_re(), d.get_im() + c.get_im());
    }

    complex operator-(const complex &c, const complex &d)
    {
        return complex(c.get_re() - d.get_re(), c.get_im() - d.get_im());
    }

    complex operator*(const complex &c, const complex &d)
    {
        double newre = d.get_re() * c.get_re() - d.get_im() * c.get_im();
        double newim = d.get_im() * c.get_re() + d.get_re() * c.get_im();
        return complex(newre, newim);
    }

    complex operator/(const complex &c, const complex &d)
    {
        complex nd;
        double div = d.abs2();
        nd = (~d);
        nd = nd * c;
        double nre = nd.get_re() / div;
        double nim = nd.get_im() / div;
        return complex(nre, nim);
    }

    void complex::to_string(char *buf, size_t size) const
    {
        snprintf(buf, size, "(%.10g,%.10g)", re, im);
    }

    double complex::abs2() const
    {
        return re * re + im * im;
    }

    double complex::abs() const
    {
        return sqrt(this->abs2());
    }

class complex_stack
{	
public:
	complex_stack();
	complex_stack(const complex_stack &);
	size_t size() const;
	complex &operator[](const int);
	complex &operator+();
	complex_stack &operator~();
	complex_stack &operator<<(const complex);
	complex_stack &operator=(const complex_stack &);
	~complex_stack();
private:
	size_t sz;
	size_t alsz;
	complex *st;
};

complex_stack::complex_stack()
{
	st = new complex[1];
	*st = complex();
	sz = 0;
	alsz = 1;
}

complex_stack::complex_stack(const complex_stack &s)
{
	st = new complex[(int)s.size()];
    sz = s.size();
    alsz = s.size();
    memcpy(st, s.st, s.size());
}

complex_stack &complex_stack::operator=(const complex_stack &s) 
{
    complex_stack stt(s);
    swap(sz, stt.sz);
    swap(st, stt.st);
    swap(alsz, stt.alsz);
    return *this;
}

complex_stack::~complex_stack()
{
	delete [] st;
}

size_t complex_stack::size() const
{
	return sz;
}

complex & complex_stack::operator+()
{
	return st[sz - 1];
}

complex_stack & complex_stack::operator<<(const complex c)
{
	complex_stack stnew;
	if (sz < alsz) {
		stnew = complex_stack(this);
		stnew[sz] = c;
		stnew.sz++;
	} else {
		stnew = new complex[(int)alsz];
		stnew.alsz = alsz * 2;
		memcpy(&stnew, st, sz);
		st[sz] = c;
		sz++;
	}
	return stnew;
}

/*complex_stack &
complex_stack::operator~()
{
	complex_stack newst = complex_stack(sz - 1);
	for (int i = 0; i < (int)sz - 1; i++) {
		newst[i] = (*this)[i];
	}
	return newst;
}*/

complex & complex_stack::operator[](int i)
{
	return st[i];
}

int
main()
{
	complex c = complex(2, 3);
	char s[100];
	c.to_string(s, 20);
	cout << s;
	complex_stack sta = complex_stack();
	//sta[0].to_string(s);
	//cout << s;
	//c = +sta;
	//c.to_string(s);
	//cout << s;
	return 0;
}