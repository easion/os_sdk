//
//	iostream
//

#ifndef _IOSTREAM_H
#define _IOSTREAM_H

#include <sys/types.h>

extern "C" char*	ltoa(long value, char* str, int base);
extern "C" char* ltona(long value, char* str, int n, int base);
extern "C" int write(int fd, const char *buf, size_t s);

#ifndef	_MSC_VER
#define	__int64	long long
#endif

enum {
	__STDIN	=0,__STDOUT,__STDERR
		//,__stdaux,__stdprn
};


//	integer pointer
#ifdef	__PTRDIFF_TYPE__
typedef	unsigned __PTRDIFF_TYPE__	uintptr;
typedef	signed __PTRDIFF_TYPE__		sintptr;
#else
#ifdef _MONE64_
typedef	unsigned __int64	uintptr;
typedef	signed __int64		sintptr;
#else
typedef	unsigned int		uintptr;
typedef	signed int			sintptr;
#endif
#endif

#ifdef	_SINTPTR_
typedef	sintptr				intptr;
#else
typedef	uintptr				intptr;
#endif

//namespace std{

typedef	size_t	streamsize;

class	streambuf;
class	filebuf;
class	strstreambuf;
class	ios;
class	istream;
class	ostream;
class	iostream;
class	ostream_withassign;
extern	ostream_withassign	cout;
extern	ostream_withassign	cerr;
extern	ostream_withassign	clog;

//
//	streambuf family
//
class streambuf{

public:
	virtual	~streambuf(){ if(_delete) delete _base; }
	virtual	int	sputn(const char*,int)=0;
	virtual	int sputc(int)=0;
	//int out_waiting() const { return _pptr-_pbase; }

protected:
	streambuf():_base(0),_ebuf(0),_pbase(0),_pptr(0),_epptr(0),_delete(0) {}
	streambuf(char* _p,int _n):_pbase(0),_pptr(0),_epptr(0),_delete(0){ setb(_p,_p+_n); }
	void setb(char* _p,char* _pe,int _d=0){ if(_delete) delete _base; _base=_p; _ebuf=_pe; _delete=_d; }
	char* base() const	{ return _base; }
	char* ebuf() const	{ return _ebuf; }
	int blen() const	{ return _ebuf-_base; }
	char* pbase() const	{ return _pbase; }
	char* pptr() const	{ return _pptr; }
	char* epptr() const	{ return _epptr; }

private:
	char* _base;
	char* _ebuf;
	char* _pbase;
	char* _pptr;
	char* _epptr;
	int _delete;

};


class filebuf: public streambuf{

private:
	int __handle;

public:
	virtual ~filebuf(){}
	filebuf(int h):streambuf(0,0),__handle(h){}
	int	sputn(const char* pch,int nCount);
	int sputc(int nCh);

};

class strstreambuf: public streambuf{

public:
	virtual ~strstreambuf(){}

};


//
//	ios family
//
class ios{
public:
	enum io_state {
		goodbit = 0x00,
		eofbit  = 0x01,
		failbit = 0x02,
		badbit  = 0x04
	};

	enum open_mode {
		in        = 0x01,
		out       = 0x02,
		ate       = 0x04,
		app       = 0x08,
		trunc     = 0x10,
		nocreate  = 0x20,
		noreplace = 0x40,
		binary    = 0x80
	};

	enum seek_dir { beg=0, cur=1, end=2 };

	enum {
		skipws     = 0x0001,
		left       = 0x0002,
		right      = 0x0004,
		internal   = 0x0008,
		dec        = 0x0010,
		oct        = 0x0020,
		hex        = 0x0040,
		showbase   = 0x0080,
		showpoint  = 0x0100,
		uppercase  = 0x0200,
		showpos    = 0x0400,
		scientific = 0x0800,
		fixed      = 0x1000,
		unitbuf    = 0x2000,
		stdio      = 0x4000
	};

	static const long basefield=dec|oct|hex;

	void	init(streambuf* _sb){ if(x_delbuf) delete sb; sb=_sb; }
	streambuf* rdbuf() const { return sb; }

	long flags(long _l){ lock(); long l0=x_flags; x_flags=_l; unlock(); return l0; }
	long flags() const { return x_flags; }
	long setf(long _l,long _m){ long _lO; lock(); _lO = x_flags; x_flags = (_l&_m) | (x_flags&(~_m)); unlock(); return _lO; }
	long setf(long _l)		{ long _lO; lock(); _lO = x_flags; x_flags |= _l; unlock(); return _lO; }
	long unsetf(long _l){ long _lO; lock(); _lO = x_flags; x_flags &= (~_l); unlock(); return _lO; }

	char fill(char _c){ lock(); char _c0=x_fill; x_fill=_c; unlock(); return _c0; }
	char fill() const { return x_fill; }

	int	good() const { return state&goodbit; }
	int	bad() const { return state&eofbit; }
	int	eof() const { return state&eofbit; }
	int	fail() const { return state&(badbit|failbit); }
	int	rdstate() const { return state; }
	void clear(int nState=0) { state=nState; }

	int		delbuf() const { return x_delbuf; }
	void	delbuf(int _i) { x_delbuf = _i; }

	static void lock() { }
	static void unlock() { }

	ios(streambuf* _sb):sb(_sb),x_flags(0),state(0),x_delbuf(0),x_fill(' ') {}
	virtual	~ios(){ if(x_delbuf) delete sb; }

protected:
	ios():sb((streambuf*)0),x_flags(0),state(0),x_delbuf(0),x_fill(' ') {}

	streambuf* sb;
	long	x_flags;
	int	state;
	int	x_delbuf;
	char	x_fill;
};
inline ios& dec(ios& _strm) { _strm.setf(ios::dec,ios::basefield); return _strm; }
inline ios& hex(ios& _strm) { _strm.setf(ios::hex,ios::basefield); return _strm; }
inline ios& oct(ios& _strm) { _strm.setf(ios::oct,ios::basefield); return _strm; }


class istream: public ios{
public:
protected:
};


class ostream: public ios{
public:
	//ostream& itoa(ostream& _os,intptr l,int base);

	ostream& put(char c){ sb->sputc(c); return *this; }
	ostream& write(const char* p, streamsize s){ sb->sputn(p,s); return *this; }
	ostream& write(const signed char* p, streamsize s){ sb->sputn((const char*)p,s); return *this; }
	ostream& write(const unsigned char* p, streamsize s){ sb->sputn((const char*)p,s); return *this; }
	ostream& flush()	{ return *this; }

	ostream& operator<<(const char*);
	ostream& operator<<(const signed char* c){ return operator<<((const char*)c); }
	ostream& operator<<(const unsigned char* c){ return operator<<((const char*)c); }
	ostream& operator<<(const char c){ return put(c); }

	ostream& operator<<(void*);

	ostream& operator<<(long);
	ostream& operator<<(unsigned long);

	ostream& operator<<(__int64 l)	{ return operator<<((long)l); }
	ostream& operator<<(unsigned __int64 l){ return operator<<((long)l); }
	ostream& operator<<(int i){ return operator<<((long)i); }
	ostream& operator<<(unsigned int u){ return operator<<((unsigned long)u); }
	ostream& operator<<(short i)	{ return operator<<((long)i); }
	ostream& operator<<(unsigned short u){ return operator<<((unsigned long)u); }

	ostream& operator<<(ostream& (*f)(ostream&)){ (*f)(*this); return *this; }
	ostream& operator<<(ios& (* _f)(ios&)) { (*_f)(*this); return *this; }

	ostream(streambuf* sb):ios(sb){}

protected:
	ostream(){}
	ostream& operator=(streambuf* _sb){ init(_sb); return *this; }
	ostream& operator=(const ostream& _os) { operator=(_os.rdbuf()); return *this; }
};
inline	ostream& flush(ostream& os){ return os.flush(); }
inline	ostream& endl(ostream& os){ return os << '\n' << flush; }
inline	ostream& ends(ostream& os){ return os << '\0'; }


class ostream_withassign: public ostream{
public:
	ostream_withassign(){}
	ostream_withassign(streambuf* _sb):ostream(_sb){}
	virtual ~ostream_withassign(){}
	ostream& operator=(const ostream& _os) { return ostream::operator=(_os.rdbuf()); }
	ostream& operator=(streambuf* _sb) { return ostream::operator=(_sb); }
};


class iostream: public istream, public ostream{
public:
	iostream();
	virtual ~iostream(){}
};
//}

#endif
