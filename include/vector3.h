#pragma once

#include "math_types.h"
#include "functions.h"
#include <stdint.h>
#include <algorithm>
#include <math.h>
#include <memory>

namespace alfar
{
    namespace vector3
    {
        inline Vector3 create(float x, float y, float z)
        {
            Vector3 ret;
            ret.x = x;
            ret.y = y;
            ret.z = z;

            return ret;
        }

        inline Vector3 add(const Vector3& p_First, const Vector3& p_Second)
        {
            Vector3 ret;
            ret.x = p_First.x + p_Second.x;
            ret.y = p_First.y + p_Second.y;
            ret.z = p_First.z + p_Second.z;

            return ret;
        }

        //---------------------------------------------------------------------

        inline Vector3 sub(const Vector3& p_First, const Vector3& p_Second)
        {
            Vector3 ret;
            ret.x = p_First.x - p_Second.x;
            ret.y = p_First.y - p_Second.y;
            ret.z = p_First.z - p_Second.z;

            return ret;
        }

        //---------------------------------------------------------------------

        inline Vector3 mul(const Vector3& p_Vec, const float p_Scalar)
        {
            Vector3 ret;
            ret.x = p_Vec.x * p_Scalar;
            ret.y = p_Vec.y * p_Scalar;
            ret.z = p_Vec.z * p_Scalar;

            return ret;
        }

		//=======================================================================

		inline Vector3 mul(const Matrix4x4& p_Mat, const Vector3& p_Vec)
		{
			Vector3 ret;

			float w = p_Mat.t.x * p_Vec.x + p_Mat.t.y * p_Vec.y + p_Mat.t.z * p_Vec.z + p_Mat.t.w * 1;

			ret.x = (p_Mat.x.x * p_Vec.x + p_Mat.x.y * p_Vec.y + p_Mat.x.z * p_Vec.z + p_Mat.x.w * 1)/w;
			ret.y = (p_Mat.y.x * p_Vec.x + p_Mat.y.y * p_Vec.y + p_Mat.y.z * p_Vec.z + p_Mat.y.w * 1)/w;
			ret.z = (p_Mat.z.x * p_Vec.x + p_Mat.z.y * p_Vec.y + p_Mat.z.z * p_Vec.z + p_Mat.z.w * 1)/w;
			

			return ret;
		}

        //-----------------------------------------------------------------------

        inline Vector3 scale(const Vector3& p_First, const Vector3& p_Second)
        {
            Vector3 ret;
            ret.x = p_First.x * p_Second.x;
            ret.y = p_First.y * p_Second.y;
            ret.z = p_First.z * p_Second.z;

            return ret;
        }

        //------------------------------------------------------------------------

        inline Vector3 cross(const Vector3& p_First, const Vector3& p_Second)
        {
            Vector3 ret;
            ret.x = p_First.y * p_Second.z - p_Second.y * p_First.z;
            ret.y = p_First.z * p_Second.x - p_Second.z * p_First.x;
            ret.z = p_First.x * p_Second.y - p_Second.x * p_First.y;

            return ret;
        }

        //---------------------------------------------------------------------------

        inline float dot(const Vector3& p_First, const Vector3& p_Second)
        {
            return p_First.x * p_Second.x + p_First.y * p_Second.y + p_First.z * p_Second.z;
        }

        //-------------------------------------------------------------------------

        inline float sqrMagnitude(const Vector3& p_Vector)
        {
            return p_Vector.x * p_Vector.x + p_Vector.y * p_Vector.y + p_Vector.z * p_Vector.z;
        }

        inline float magnitude(const Vector3& p_Vector)
        {
            return sqrt(sqrMagnitude(p_Vector));
        }

		inline Vector3 normalize(const Vector3& p_Vector)
		{
			Vector3 ret;
			float norme = magnitude(p_Vector);

			ret.x = p_Vector.x / norme;
			ret.y = p_Vector.y / norme;
			ret.z = p_Vector.z / norme;

			return ret;
		}

		inline Vector3 barycentric(const Vector3 a, const Vector3 b, const Vector3 c, const Vector3 pos)
		{
			float det = ((b.y-c.y)*(a.x-c.x) + (c.x-b.x)*(a.y-c.y));

			float xb = ((b.y - c.y)*(pos.x - c.x) + (c.x - b.x)*(pos.y - c.y)) / det;
			float yb = ((c.y - a.y)*(pos.x - c.x) + (a.x - c.x)*(pos.y - c.y)) / det;
			float zb = 1.0f - xb - yb;

			//return add(add(mul(a,xb), mul(b,yb)), mul(c,zb));

			return vector3::create(xb,yb,zb);
		}


		//return dist to intersections. return -1 if no intersection or behind.
		inline float linePlaneIntersection(const Vector3& planeOrigin, const Vector3& planeNormal, const Vector3 rayOrigin, const Vector3& rayDir)
		{
			float num = vector3::dot(vector3::sub(planeOrigin, rayOrigin), planeNormal);
			float den = vector3::dot(rayDir, planeNormal);

			if(approximatly(den, 0.0f) || approximatly(num, 0.0f))
			{
				return -1.0f;
			}


			float d = num/den;
			return d;
		}

		//====

		//return -1 if no intersection
		inline float raySphereIntersection(const Vector3& sphereCenter, const float sphereRadius, const Vector3& rayOrigin, const Vector3& rayDir)
		{
			Vector3 objectSpaceRayPos = vector3::sub(rayOrigin, sphereCenter);

			float a = vector3::dot(rayDir, rayDir);
			float b = 2 * vector3::dot(rayDir, objectSpaceRayPos);
			float c = vector3::dot(objectSpaceRayPos, objectSpaceRayPos) - (sphereRadius*sphereRadius);

			float disc = b*b - 4 * a * c;

			if(disc < 0)
				return -1.0f;

			float distSqrt = sqrtf(disc);
			float q;

			if(b < 0 )
				q = (-b - distSqrt)/2.0f;
			else
				q = (-b + distSqrt)/2.0f;

			float t0 = q / a;
			float t1 = c / q;

			if(t0 > t1)
			{
				float temp = t0;
				t0 = t1;
				t1 = temp;
			}

			if(t1 < 0)
				return -1.0f;

			if(t0 < 0 )
			{
				return t1;
			}
			else
			{
				return t0;
			}
		}


        //----- array version


        inline void init(Vector3* p_Array, uint32_t p_Number)
        {
            memset(p_Array, 0, p_Number * sizeof(Vector3));
        }

        //--------------------------------------------------------------------------

        inline void add(Vector3* p_Firsts, Vector3* p_Seconds, Vector3* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                alfar::Vector3& o = *(p_Out+i);
                alfar::Vector3& a = *(p_Firsts+i);
                alfar::Vector3& b = *(p_Seconds+i);

                o.x = a.x + b.x;
                o.y = a.y + b.y;
                o.z = a.z + b.z;
            }
        }

        //---------------------------------------------------------------------------

        inline void sub(Vector3* p_Firsts, Vector3* p_Seconds, Vector3* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                alfar::Vector3& o = *(p_Out+i);
                alfar::Vector3& a = *(p_Firsts+i);
                alfar::Vector3& b = *(p_Seconds+i);

                o.x = a.x - b.x;
                o.y = a.y - b.y;
                o.z = a.z - b.z;
            }
        }

        //------------------------------------------------------------------------------

        inline void mul(Vector3* p_Firsts, float* p_Scalars, Vector3* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                alfar::Vector3& o = *(p_Out+i);
                alfar::Vector3& a = *(p_Firsts+i);
                float& s = *(p_Scalars+i);

                o.x = a.x * s;
                o.y = a.y * s;
                o.z = a.z * s;
            }
        }

        //----------------------------------------------------------------------------------

        inline void scale(Vector3* p_Firsts, Vector3* p_Seconds, Vector3* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                alfar::Vector3& o = *(p_Out+i);
                alfar::Vector3& a = *(p_Firsts+i);
                alfar::Vector3& b = *(p_Seconds+i);

                o.x = a.x * b.x;
                o.y = a.y * b.y;
                o.z = a.z * b.z;
            }
        }

        //-----------------------------------------------------------------------------------
            
        inline void cross(Vector3* p_Firsts, Vector3* p_Seconds, Vector3* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                alfar::Vector3& o = *(p_Out+i);
                alfar::Vector3& a = *(p_Firsts+i);
                alfar::Vector3& b = *(p_Seconds+i);

                o.x = a.y * b.z - b.y * a.z;
                o.y = a.z * b.x - b.z * a.x;
                o.z = a.x * b.y - b.x * a.y;
            }
        }

        //--------------------------------------------------------------------------------------

        inline void dot(Vector3* p_Firsts, Vector3* p_Seconds, float* p_Out, uint32_t p_Number)
        {
            for(uint32_t i = 0; i < p_Number; ++i)
            {
                float& o = *(p_Out+i);
                alfar::Vector3& a = *(p_Firsts+i);
                alfar::Vector3& b = *(p_Seconds+i);

                o = a.x * b.x + a.y * b.y + a.z * b.z;
            }
        }
    }
}

