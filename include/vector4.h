#pragma once 

#include "math_types.h"
#include "functions.h"
#include "vector3.h"
#include <stdint.h>
#include <algorithm>
#include <math.h>
#include <memory>

namespace alfar
{
    namespace vector4
    {
        inline Vector4 create(float x, float y, float z, float w)
        {
            Vector4 ret;
            ret.x = x;
            ret.y = y;
            ret.z = z;
            ret.w = w;

            return ret;
        }

        //-------------------------------------------------------------------

        inline Vector4 create(Vector3 p_Vect, float w = 1.0f)
        {
            return create(p_Vect.x, p_Vect.y, p_Vect.z, w);
        }

		//------------------------------------------------------------------

		inline Vector3 toVec3(alfar::Vector4 vec)
		{
			return alfar::vector3::create(vec.x, vec.y, vec.z);
		}

        //-------------------------------------------------------------------

        inline Vector4 add(const Vector4& p_First, const Vector4& p_Second)
        {
            Vector4 ret;
            ret.x = p_First.x + p_Second.x;
            ret.y = p_First.y + p_Second.y;
            ret.z = p_First.z + p_Second.z;
            ret.w = p_First.w + p_Second.w;

            return ret;
        }

        //---------------------------------------------------------------------

        inline Vector4 sub(const Vector4& p_First, const Vector4& p_Second)
        {
            Vector4 ret;
            ret.x = p_First.x - p_Second.x;
            ret.y = p_First.y - p_Second.y;
            ret.z = p_First.z - p_Second.z;
            ret.w = p_First.w - p_Second.w;

            return ret;
        }

        //---------------------------------------------------------------------

        inline Vector4 mul(const Vector4& p_Vec, const float p_Scalar)
        {
            Vector4 ret;
            ret.x = p_Vec.x * p_Scalar;
            ret.y = p_Vec.y * p_Scalar;
            ret.z = p_Vec.z * p_Scalar;
            ret.w = p_Vec.w * p_Scalar;

            return ret;
        }

		//=======================================================================

		inline Vector4 mul(const Matrix4x4& p_Mat, const Vector4& p_Vec)
		{
			Vector4 ret;

			ret.x = p_Mat.x.x * p_Vec.x + p_Mat.x.y * p_Vec.y + p_Mat.x.z * p_Vec.z + p_Mat.x.w * p_Vec.w;
			ret.y = p_Mat.y.x * p_Vec.x + p_Mat.y.y * p_Vec.y + p_Mat.y.z * p_Vec.z + p_Mat.y.w * p_Vec.w;
			ret.z = p_Mat.z.x * p_Vec.x + p_Mat.z.y * p_Vec.y + p_Mat.z.z * p_Vec.z + p_Mat.z.w * p_Vec.w;
			ret.w = p_Mat.t.x * p_Vec.x + p_Mat.t.y * p_Vec.y + p_Mat.t.z * p_Vec.z + p_Mat.t.w * p_Vec.w;

			return ret;
		}

		//-----------------------------------------------------------------------

		inline float lengthSqr(const Vector4& p_vec)
		{
			return p_vec.x * p_vec.x + p_vec.y * p_vec.y + p_vec.z * p_vec.z + p_vec.w + p_vec.w;
		}

		inline float length(const Vector4& p_vec)
		{
			return sqrt(lengthSqr(p_vec));
		}

		inline Vector4 normalize(const Vector4& p_vec)
		{
			Vector4 ret;
			float norme = length(p_vec);

			ret.x = p_vec.x / norme;
			ret.y = p_vec.y / norme;
			ret.z = p_vec.z / norme;
			ret.w = p_vec.w / norme;

			return ret;
		}

        //-----------------------------------------------------------------------

        inline Vector4 scale(const Vector4& p_First, const Vector4& p_Second)
        {
            Vector4 ret;
            ret.x = p_First.x * p_Second.x;
            ret.y = p_First.y * p_Second.y;
            ret.z = p_First.z * p_Second.z;
            ret.w = p_First.w * p_Second.w;

            return ret;
        }

		//---------------------------------------------------------------------------

		inline Vector4 interpolatedFromBarycentric(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector3& barycentric)
		{
			return vector4::add(vector4::add(vector4::mul(v1, barycentric.x), vector4::mul(v2, barycentric.y)), vector4::mul(v3, barycentric.z));
		}

		//---------------------------------------------------------------------------

		inline Vector4 lerp(const Vector4& p1, const Vector4& p2, float t)
		{
			return vector4::create(	p1.x * (1.0f - t) + p2.x * t, 
									p1.y * (1.0f - t) + p2.y * t,
									p1.z * (1.0f - t) + p2.z * t,
									p1.w * (1.0f - t) + p2.w * t);
		}

		//---------------------------------------------------------------------------

		inline Vector4 clamp(const Vector4& p, const float min, const float max)
		{
			return vector4::create(	
				alfar::clamp(p.x, min, max), 
				alfar::clamp(p.y, min, max),
				alfar::clamp(p.z, min, max),
				alfar::clamp(p.w, min, max));
		}

        //---------------------------------------------------------------------------

        inline float dot(const Vector4& p_First, const Vector4& p_Second)
        {
            return p_First.x * p_Second.x + p_First.y * p_Second.y + p_First.z * p_Second.z;
        }

		//---------------------------------------------------------------------------

        //----- array version


        inline void init(Vector4* p_Array, uint32_t p_Number)
        {
            memset(p_Array, 0, p_Number * sizeof(Vector4));
        }

        //--------------------------------------------------------------------------

        inline void add(Vector4* p_Firsts, Vector4* p_Seconds, Vector4* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                alfar::Vector4& o = *(p_Out+i);
                alfar::Vector4& a = *(p_Firsts+i);
                alfar::Vector4& b = *(p_Seconds+i);

                o.x = a.x + b.x;
                o.y = a.y + b.y;
                o.z = a.z + b.z;
                o.w = a.w + b.w;
            }
        }

        //---------------------------------------------------------------------------

        inline void sub(Vector4* p_Firsts, Vector4* p_Seconds, Vector4* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                alfar::Vector4& o = *(p_Out+i);
                alfar::Vector4& a = *(p_Firsts+i);
                alfar::Vector4& b = *(p_Seconds+i);

                o.x = a.x - b.x;
                o.y = a.y - b.y;
                o.z = a.z - b.z;
                o.w = a.w - b.w;
            }
        }

        //------------------------------------------------------------------------------

        inline void mul(Vector4* p_Firsts, float* p_Scalars, Vector4* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                alfar::Vector4& o = *(p_Out+i);
                alfar::Vector4& a = *(p_Firsts+i);
                float& s = *(p_Scalars+i);

                o.x = a.x * s;
                o.y = a.y * s;
                o.z = a.z * s;
                o.w = a.w * s;
            }
        }

        //----------------------------------------------------------------------------------

        inline void scale(Vector4* p_Firsts, Vector4* p_Seconds, Vector4* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                alfar::Vector4& o = *(p_Out+i);
                alfar::Vector4& a = *(p_Firsts+i);
                alfar::Vector4& b = *(p_Seconds+i);

                o.x = a.x * b.x;
                o.y = a.y * b.y;
                o.z = a.z * b.z;
                o.w = a.w + b.w;
            }
        }

        //--------------------------------------------------------------------------------------

        inline void dot(Vector4* p_Firsts, Vector4* p_Seconds, float* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                float& o = *(p_Out+i);
                alfar::Vector4& a = *(p_Firsts+i);
                alfar::Vector4& b = *(p_Seconds+i);

                o = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
            }
        }
    }
}
