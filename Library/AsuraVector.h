/************************************************************************
�@�@AsuraVector.h

�@�@Vector Library
�@
�@�@Date : July 24, 2007
�@�@Version : 1.0
�@�@Author : Pocol, Yoshiaki Ishibashi
�@�@Memo :
*************************************************************************/

#ifndef _ASURA_VECTOR_H_INCLUDED_
#define _ASURA_VECTOR_H_INCLUDED_

//
//�@include
//
#include <iostream>
#include <cmath>
using namespace std;


//
//�@namespace Asura
//
namespace Asura
{
	//
	//�@const
	//
	const double PI = 3.14159265358979323846264338327;

	//
	//�@prototype
	//
	template <class T>class Vector2D;
	template <class T>class Vector3D;
	template <class T>class Vector4D;

	//
	//�@typedef
	//
	typedef Vector2D<double>			vector2;
	typedef Vector2D<double>			vector2d;
	typedef Vector2D<float>				vector2f;
	typedef Vector2D<int>					vector2i;

	typedef Vector3D<double>			vector3;
	typedef Vector3D<double>			vector3d;
	typedef Vector3D<float>				vector3f;
	typedef Vector3D<int>					vector3i;
	
	typedef Vector4D<double>			vector4;
	typedef Vector4D<double>			vector4d;
	typedef Vector4D<float>				vector4f;
	typedef Vector4D<int>					vector4i;

	
	//////////////////////////////////////////////////////////////////////
	//�@�@Functoin
	//////////////////////////////////////////////////////////////////////
	template<class T>static inline T RadToDeg(T rad) { return ( (rad)*(180.0/PI) ); }
	template<class T>static inline T DegToRad(T deg) { return ( (deg)*(PI/180.0) ); }

	/////////////////////////////////////////////////////////////////////
	//�@�@Vector2D class
	/////////////////////////////////////////////////////////////////////
	template <class T>
	class Vector2D
	{
	public:
		union{ struct{ T x, y; }; T v[2]; };
		Vector2D<T> (T nx=0, T ny=0) : x(nx), y(ny) {}
		Vector2D<T> (const Vector2D<T> &vec) : x(vec.x), y(vec.y) {}
		Vector2D<T> (const Vector2D<T> &a, const Vector2D<T> &b) : x(a.x - b.x), y(a.y - b.y) {}
		Vector2D<T> (const T *v) : x(v[0]), y(v[1]) {}
		T &operator[] (const long index)
			{ return *((&x)+index); }
		const Vector2D<T> &operator= (const Vector2D<T> &vec)
			{ x=vec.x, y=vec.y; return *this; }
		const Vector2D<T> &operator= (const T &s)
			{ x=y=s; return *this; }
		const bool operator == (const Vector2D<T> &vec)const
			{ return ( x==vec.x && y==vec.y ); }
		const bool operator != (const Vector2D<T> &vec)const
			{ return !(*this==vec); }
		const bool operator > (const Vector2D<T> &vec)const
			{ return (x>vec.x && y>vec.y); }
		const bool operator < (const Vector2D<T> &vec)const
			{ return (x<vec.x && y<vec.y); }
		const bool operator >= (const Vector2D<T> &vec)const
			{ return (x>=vec.x && y>=vec.y); }
		const bool operator <= (const Vector2D<T> &vec)const
			{ return (x<=vec.x && y<=vec.y); }
		const Vector2D<T> operator+ (const Vector2D<T> &vec)const
			{ return Vector2D<T>(x+vec.x, y+vec.y); }
		const Vector2D<T> operator- (const Vector2D<T> &vec) const
			{ return Vector2D<T>(x-vec.x, y-vec.y); }
		const Vector2D<T> operator+() const
			{ return Vector2D<T>(*this); }
		const Vector2D<T> &operator-() const
			{ return Vector2D<T>(-x, -y); }
		const Vector2D<T> &operator+= (const Vector2D<T> &vec)
			{ x+=vec.x; y+=vec.y; return *this; }
		const Vector2D<T> &operator-= (const Vector2D<T> &vec)
			{ x-=vec.x, y-=vec.y; return *this; }
		const Vector2D<T> &operator*= (const T s)
			{ x*=s; y*=s; return *this; }
		const Vector2D<T> &operator/= (const T s)
			{ const T recip =1.0/s; x*= recip; y*= recip; return *this; }
		const Vector2D<T> operator* (const T s)const
			{ return Vector2D<T>(x*s, y*s); }
		friend const Vector2D<T> operator* (const T s, const Vector2D<T> &vec)
			{ return (vec*s); }
		const Vector2D<T> operator/ (const T s)const
			{ const T recip = 1.0/s; return Vector2D<T>(recip*x, recip*y); }
		const Vector2D<T> operator* (const Vector2D<T> &vec)const
			{ return Vector2D<T>(x*vec.x, y*vec.y); }
		const Vector2D<T> UnitVector() const
			{ if ( Length() != 0.0 )return (*this)/Length(); else return Vector2D<T>(0.0, 0.0); }
		const T DotProduct(const Vector2D<T> &vec) const
			{ return (x*vec.x + y*vec.y); }
		const T Length() const
			{ return (T)sqrt(x*x + y*y); }
		const T Angle(const Vector2D<T> &vec) const	
			{ return (T)acos(DotProduct(vec)); }
		void Set(T nx=0, T ny=0)	
			{ x = nx; y = ny; }
		void Normalize()
			{ if ( Length() != 0.0)(*this)/=Length(); }
		void One()
			{ x = 1.0; y = 1.0; }
		void Zero()
			{ x = 0.0; y = 0.0; }
		void ConsoleOut()
			{ cout << "(x, y) = (" << x << ", " << y << ")\n"; }
		T* Get()
			{ return (this->v); }
		void Copy(T dest[2])
			{ dest[0]=x; dest[1]=y; }
	};

	/////////////////////////////////////////////////////////////////////
	//�@�@Vector3D class
	/////////////////////////////////////////////////////////////////////
	template <class T>
	class Vector3D
	{
	public:
		union{ struct{ T x, y, z; }; T v[3]; };
		Vector3D<T> (T nx=0.0, T ny=0.0, T nz=0.0) : x(nx), y(ny), z(nz) {}
		Vector3D<T> (const Vector3D<T> &vec) : x(vec.x), y(vec.y), z(vec.z) {}
		Vector3D<T> (const Vector3D<T> &a, const Vector3D<T> &b) : x(a.x - b.x), y(a.y - b.y), z(a.z - b.z) {}
		Vector3D<T> (const T *v) : x(v[0]), y(v[1]), z(v[2]) {}
		T &operator[] (const long index)
			{ return *((&x)+index); }
		const Vector3D<T> &operator= (const Vector3D<T> &vec)
			{ x=vec.x; y=vec.y; z=vec.z; return *this; }
		const Vector3D<T> &operator= (const T &s)
			{ x=y=z=s; return *this; }
		const bool operator== (const Vector3D<T> &vec)const
			{ return ((x==vec.x)&&(y==vec.y)&&(z==vec.z)); }
		const bool operator!= (const Vector3D<T> &vec)const
			{ return!(*this==vec); }
		const bool operator> (const Vector3D<T> &vec)const
			{ return (x>vec.x && y>vec.y && z>vec.z); }
		const bool operator< (const Vector3D<T> &vec)const
			{ return (x<vec.x && y<vec.y && z<vec.z); }
		const bool operator>= (const Vector3D<T> &vec)const
			{ return (x>=vec.x && y>=vec.y && z>=vec.z); }
		const bool operator<= (const Vector3D<T> &vec)const
			{ return (x<=vec.x && y<=vec.y && z<=vec.z); }
		const Vector3D<T> operator+ (const Vector3D<T> &vec)const
			{ return Vector3D<T>(x+vec.x, y+vec.y, z+vec.z); }
		const Vector3D<T> operator+() const
			{ return Vector3D<T>(*this); }
		const Vector3D<T> &operator+= (const Vector3D<T> &vec)
			{ x+=vec.x; y+=vec.y; z+=vec.z; return *this; }
		const Vector3D<T> operator- (const Vector3D<T> &vec)const
			{ return Vector3D<T>(x-vec.x, y-vec.y, z-vec.z); }
		const Vector3D<T> operator-() const
			{ return Vector3D<T>(-x, -y, -z); }
		const Vector3D<T> &operator-= (const Vector3D<T> &vec)
			{ x-=vec.x; y-=vec.y; z-=vec.z; return *this; }
		const Vector3D<T> &operator*= (const T s)
			{ x*=s; y*=s; z*=s; return *this; }	
		const Vector3D<T> &operator/= (const T s)
			{ const T recip = 1/s; x*= recip; y*=recip; z*=recip; return *this; }
		const Vector3D<T> operator* (const T s)const
			{ return Vector3D<T>(x*s, y*s, z*s); }
		friend const Vector3D<T> operator* (const T s, const Vector3D<T> &vec)
			{ return vec*s; }
		const Vector3D<T> operator/ (const T s)const
			{ const T recip = 1/s; return Vector3D<T>(recip*x, recip*y, recip*z); }
		const Vector3D<T> operator* (const Vector3D<T> &vec) const
			{ return Vector3D<T>(x*vec.x, y*vec.y, z*vec.z); }
		const Vector3D<T> CrossProduct(const Vector3D<T> &vec) const 
			{ return Vector3D<T>(y*vec.z-z*vec.y, z*vec.x-x*vec.z, x*vec.y-y*vec.x); }
		const Vector3D<T> UnitVector() const 
			{ if ( Length() != 0.0 )return (*this)/Length(); else return Vector3D<T>(0.0, 0.0, 0.0); }
		const T DotProduct(const Vector3D<T> &vec) const
			{ return (x*vec.x+ y*vec.y + z*vec.z); }
		const T Length() const
			{ return (T)sqrt(x*x + y*y + z*z ); }
		const T Angle(const Vector3D<T> &vec)  const
			{ return (T)acos(DotProduct(vec)); }
		void Set(T nx=0, T ny=0, T nz=0)
			{ x =nx; y = ny; z = nz; }
		void Normalize()
			{ if ( Length() != 0.0)(*this)/=Length(); }
		void One()
			{ x=1.0; y=1.0; z=1.0; }
		void Zero()
			{ x=0.0; y=0.0; z=0.0; }
		void ConsoleOut()
			{ cout << "(x, y, z) = (" << x << ", " << y << ", " << z << ")\n"; }
		T* Get()
			{ return (this->v); }
		void Copy(T dest[3])
			{ dest[0]=x; dest[1]=y; dest[2]=z; }
	};

	/////////////////////////////////////////////////////////////////////
	//�@�@Vector4D class
	/////////////////////////////////////////////////////////////////////
	template <class T>
	class Vector4D
	{
	public:
		union{ struct{ T x, y, z, w; }; T v[4]; };

		Vector4D<T> (T nx=0.0, T ny=0.0, T nz=0.0, T nw=0.0) : x(nx), y(ny), z(nz), w(nw) {}
		Vector4D<T> (const Vector4D<T> &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
		Vector4D<T> (const Vector4D<T> &a, const Vector4D<T> &b) : x(a.x - b.x), y(a.y - b.y), z(a.z - b.z), w(a.w - b.w) {}
		Vector4D<T> (const T *v) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {}
		T &operator[] (const long idx)
			{ return *(&(x)+idx); }
		const Vector4D<T> &operator= (const Vector4D<T> &vec)
			{ x=vec.x; y=vec.y; z=vec.z; w=vec.w; return *this; }	
		const Vector4D<T> &operator= (const T &s)
			{ x=y=z=w=s; return *this; }
		const bool operator== (const Vector4D<T> &vec)const
			{ return ((x==vec.x)&&(y==vec.y)&&(z==vec.z)&&(w==vec.w)); }
		const bool operator!= (const Vector4D<T> &vec)const
			{ return !(*this==vec); }
		const bool operator> (const Vector4D<T> &vec)const
			{ return (x>vec.x && y>vec.y && z>vec.z && w>vec.w); }
		const bool operator< (const Vector4D<T> &vec)const
			{ return (x<vec.x && y<vec.y && vec.z && vec.w); }
		const bool operator>= (const Vector4D<T> &vec)const
			{ return (x>=vec.x && y>=vec.y && z>=vec.z && w>=vec.w); }
		const bool operator <= (const Vector4D<T> &vec)const
			{ return (x<=vec.x && y<=vec.y && z<=vec.z && w<=vec.w); }
		const Vector4D<T> operator+ (const Vector4D<T> &vec)const
			{ return Vector4D<T>(x+vec.x, y+vec.y, z+vec.z, w+vec.w); }
		const Vector4D<T> operator+() const
			{ return Vector4D<T>(*this); }
		const Vector4D<T> &operator+= (const Vector4D<T> &vec)
			{ x+=vec.x; y+=vec.y; z+=vec.z; w+=vec.w; return *this; }
		const Vector4D<T> operator- (const Vector4D<T> &vec)const
			{ return Vector4D<T>(x-vec.x, y-vec.y, z-vec.z, w-vec.w); }
		const Vector4D<T> operator-() const
			{ return Vector4D<T>(-x, -y, -z, -w); }
		const Vector4D<T> &operator-= (const Vector4D<T> &vec)
			{ x-=vec.x; y-=vec.y; z-=vec.z; w-=vec.w; return *this; }
		const Vector4D<T> &operator*= (const T s)
			{ x*=s; y*=s; z*=s; w*=s; return *this; }
		const Vector4D<T> &operator/= (const T s)
			{ const T recip = 1/s; x*= recip; y*= recip; z*=recip; w*=recip; return *this; }
		const Vector4D<T> operator* (const T s)const
			{ return Vector4D<T>(x*s, y*s, z*s, w*s); }
		friend const Vector4D<T> operator*(const T s, const Vector4D<T> &vec)
			{ return vec*s; }
		const Vector4D<T> operator/ (const T s)const
			{ const T recip = 1/s; return Vector4D<T>(recip*x, recip*y, recip*z, recip*w); }
		const Vector4D<T> operator* (const Vector4D<T> &vec)const
			{ return Vector4D<T>(x*vec.x, y*vec.y, z*vec.z, w*vec.w); }
		const Vector4D<T> CrossProduct(const Vector4D<T> &vec) const
			{ return Vector4D<T>(y*vec.z-z*vec.y, z*vec.x-x*vec.z, x *vec.y-y*vec.x, 1); }
		const Vector4D<T> UnitVector() const
			{ if ( Length() != 0.0 )return (*this)/Length(); else return Vector4D<T>(0.0, 0.0, 0.0, 0.0); }
		const T DotProduct(const Vector4D<T> &vec) const
			{ return (T)(x*vec.x+y*vec.y+z*vec.z+w*vec.w); }
		const T Length() const
			{ return (T)sqrt(x*x+y*y+z*z+w*w); }
		const T Angle(const Vector4D<T> &vec) const
			{ return (T)acos(DotProduct(vec)); }
		void Set(T nx=0, T ny=0, T nz=0, T nw=0)
			{ x=nx; y=ny; z=nz; w=nw; }
		void Normalize()
			{ if ( Length() != 0.0)(*this)/=Length(); }
		void One()
			{ x=1.0; y=.10; z=1.0; w=1.0; }
		void Zero()
			{ x=0.0; y=0.0; z=0.0; w=0.0; }
		void ConsoleOut()
			{ cout <<  "(x, y, z, w) = (" << x << ", " << y << ", " << z <<  ", " << w << ")\n"; }
		T* Get()
			{ return (this->v); }
		void Copy(T dest[4])
			{ dest[0]=x; dest[1]=y; dest[2]=z; dest[3]=w; }
	};

	//////////////////////////////////////////////////////////////////////
	//�@�@Vector function
	/////////////////////////////////////////////////////////////////////
	
	//-------------------------------------------------------------------------------------------------
	//�@�@Distance
	//-------------------------------------------------------------------------------------------------
	template<class T> inline T Distance(const Vector2D<T> &v1, const Vector2D<T> &v2)
		{ Vector2D<T> temp(v1-v2); return temp.Length(); }
	template<class T> inline T Distance(const Vector3D<T> &v1, const Vector3D<T> &v2)
		{ Vector3D<T> temp(v1-v2); return temp.Length(); }
	template<class T> inline T Distance(const Vector4D<T> &v1, const Vector4D<T> &v2)
		{ Vector4D<T> temp(v1-v2); return temp.Length(); }
	
	//--------------------------------------------------------------------------------------------------
	//�@�@DotProduct
	//--------------------------------------------------------------------------------------------------
	template<class T> inline T DotProduct( const Vector2D<T> &v1, const Vector2D<T> &v2)
		{ return v1.DotProduct(v2); }
	template<class T> inline T DotProduct( const Vector3D<T> &v1, const Vector3D<T> &v2)
		{ return v1.DotProduct(v2); }
	template<class T> inline T DotProduct( const Vector4D<T> &v1, const Vector4D<T> &v2)
		{ return v1.DotProduct(v2); }

	//--------------------------------------------------------------------------------------------------
	//�@�@CrossProduct
	//--------------------------------------------------------------------------------------------------
	template<class T> inline Vector3D<T> CrossProduct(const Vector3D<T> &v1, const Vector3D<T> &v2)
		{ Vector3D<T> temp; temp= v1.CrossProduct(v2); return temp; }
	template<class T> inline Vector4D<T> CrossProduct(const Vector4D<T> &v1, const Vector4D<T> &v2)
		{ Vector4D<T> temp; temp = v1.CrossProduct(v2); return temp; }

	//--------------------------------------------------------------------------------------------------
	//�@�@TripleScalarProduct
	//--------------------------------------------------------------------------------------------------
	template<class T> inline T TripleScalarProduct(const Vector3D<T> &v1, const Vector3D<T> &v2, const Vector3D<T> &v3)
		{ return (T)( 	(v1.x * (v2.y*v3.z - v2.z*v3.y)) + (v1.y * (-v2.x*v3.z + v2.z*v3.x)) + (v1.z * (v2.x*v3.y + v2.y*v3.x)) ); }
	template<class T> inline T TripleScalarProduct(const Vector4D<T> &v1, const Vector4D<T> &v2, const Vector4D<T> &v3)
		{ return (T)( 	(v1.x * (v2.y*v3.z - v2.z*v3.y)) + (v1.y * (-v2.x*v3.z + v2.z*v3.x)) + (v1.z * (v2.x*v3.y + v2.y*v3.x)) ); }

	//--------------------------------------------------------------------------------------------------
	//�@�@Normalize
	//--------------------------------------------------------------------------------------------------
	template<class T> inline Vector2D<T> Normalize(Vector2D<T> &v)
		{ v.Normalize(); return v; }
	template<class T> inline Vector3D<T> Normalize(Vector3D<T> &v)
		{ v.Normalize(); return v; }
	template<class T> inline Vector4D<T> Normalize(Vector4D<T> &v)
		{ v.Normalize(); return v; }

	//-------------------------------------------------------------------------------------------------
	//�@�@GetNormal
	//-------------------------------------------------------------------------------------------------
	template<class T> inline Vector3D<T> GetNormal(const Vector3D<T> &v1, const Vector3D<T> &v2, const Vector3D<T> &v3)
		{
			Vector3D<T> vec1(v1-v2);
			Vector3D<T>vec2(v1-v3);
			Vector3D<T> temp;
			temp = vec1.CrossProduct(vec2);
			temp.Normalize();
			return temp;
		}
	template<class T> inline Vector4D<T> GetNormal(const Vector4D<T> &v1, const Vector4D<T> &v2, const Vector4D<T> &v3)
		{
			Vector4D<T> vec1(v1-v2);
			Vector4D<T> vec2(v1-v3);
			Vector4D<T> temp;
			temp = vec1.CrossProduct(vec2);
			temp.Normalize();
			return temp;
		}

	//-------------------------------------------------------------------------------------------------
	//�@�@GetQuadNormal
	//-------------------------------------------------------------------------------------------------
	template<class T> inline Vector3D<T> GetQuadNormal(const Vector3D<T> &v1, const Vector3D<T> &v2, const Vector3D<T> &v3, const Vector3D<T> &v4)
		{
			Vector3D<T> n, n1a, n1b, n2a, n2b;
			n1a = GetNormal(v1, v2, v3);
			n1b = GetNormal(v1, v3, v4);
			n2a = GetNormal(v2, v3, v4);
			n2b = GetNormal(v2, v4, v1);
			if ( DotProduct(n1a, n1b) > DotProduct(n2a, n2b) )
			{
				Vector3D<T> temp1 = (n1a + n1b);
				n = Normalize(temp1);
			}
			else
			{
				Vector3D<T> temp2 = (n2a + n2b);
				n = Normalize(temp2);
			}
			return n;
		}
	template<class T> inline Vector4D<T> GetQuadNormal(const Vector4D<T> &v1, const Vector4D<T> &v2, const Vector4D<T> &v3, const Vector4D<T> &v4)
		{
			Vector4D<T> n, n1a, n1b, n2a, n2b;
			n1a = GetNormal(v1, v2, v3);
			n1b = GetNormal(v1, v3, v4);
			n2a = GetNormal(v2, v3, v4);
			n2b = GetNormal(v2, v4, v1);
			if ( DotProduct(n1a, n1b) > DotProduct(n2a, n2b) )
			{
				Vector3D<T> temp1 = (n1a + n1b);
				n = Normalize(temp1);
			}
			else
			{
				Vector3D<T> temp2 = (n2a + n2b);
				n = Normalize(temp2);
			}
			return n;
		}

	//--------------------------------------------------------------------------------------------------
	//�@�@GetCrossingAngle
	//--------------------------------------------------------------------------------------------------
	template<class T> inline T GetCrossingAngle(const Vector2D<T> &v1, const Vector2D<T> &v2)
		{
			T d = v1.Length() *v2.Length();
			if ( d == 0.0 ) return 0;
			T c = DotProduct(v1, v2)/d;
			if ( c >= 1.0 ) return 0;
			if ( c <= -1.0 ) return (T)PI;
			return (T)acos(c);
		}
	template<class T> inline T GetCrossingAngle(const Vector3D<T> &v1, const Vector3D<T> &v2)
		{
			T d = v1.Length() *v2.Length();
			if ( d == 0.0 ) return 0;
			T c = DotProduct(v1, v2)/d;
			if ( c >= 1.0 ) return 0;
			if ( c <= -1.0 ) return (T)PI;
			return (T)acos(c);
		}
	template<class T> inline T GetCrossingAngle(const Vector4D<T> &v1, const Vector4D<T> &v2)
		{
			T d = v1.Length() *v2.Length();
			if ( d == 0.0 ) return 0;
			T c = DotProduct(v1, v2)/d;
			if ( c >= 1.0 ) return 0;
			if ( c <= -1.0 ) return (T)PI;
			return (T)acos(c);
		}

	//--------------------------------------------------------------------------------------------------
	//�@�@Lerp
	//--------------------------------------------------------------------------------------------------
	template<class T> inline Vector2D<T> Lerp(const Vector2D<T> &v1, const Vector2D<T> &v2, const T &t)
		{ Vector2D<T> temp = (1.0-t)*v1 + t*v2; return temp; }
	template<class T> inline Vector3D<T> Lerp(const Vector3D<T> &v1, const Vector3D<T> &v2, const T &t)
		{ Vector3D<T> temp = (1.0-t)*v1 + t*v2; return temp; }
	template<class T> inline Vector4D<T> Lerp(const Vector4D<T> &v1, const Vector4D<T> &v2, const T &t)
		{ Vector4D<T> temp = (1.0-t)*v1 + t*v2; return temp; }
}

#endif	//�@_ASURA_VECTOR_H_INCLUDED_
