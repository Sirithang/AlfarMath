#pragma once

#include "math_types.h"
#include "functions.h"
#include "vector4.h"

namespace alfar
{
    namespace quaternion
    {
		
        inline Quaternion create(float x, float y, float z, float w)
        {
            Quaternion quat;
            quat.x = x;
            quat.y = y;
            quat.z = z;
            quat.w = w;

            return quat;
        }

		//=============================================================

		inline Quaternion identity()
		{
			return create(0,0,0,1);
		}

        //-------------------------------------------------------------

        inline float sqrMagnitude(const Quaternion& p_Quat)
        {
            return p_Quat.x * p_Quat.x + p_Quat.y * p_Quat.y + p_Quat.z * p_Quat.z + p_Quat.w * p_Quat.w;
        }

        inline float magnitude(const Quaternion& p_Quat)
        {
            return sqrt(sqrMagnitude(p_Quat));
        }

        //---------------------------------------------------------------

        inline Quaternion normalized(const Quaternion& p_Quat)
        {
            Quaternion quat;
            float mag = magnitude(p_Quat);
            quat.x = p_Quat.x / mag;
            quat.y = p_Quat.y / mag;
            quat.z = p_Quat.z / mag;
            quat.w = p_Quat.w / mag;
            
            return quat;
        }

		//--------------------------------------------------------------------

		inline Quaternion mul(const Quaternion& a, const Quaternion& b)
		{
			Quaternion quat;

			quat.w = (a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z);
			quat.x = (a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y);
			quat.y = (a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x);
			quat.z = (a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w);

			return quat;
		}

        //--------------------------------------------------------------------
		
		inline Quaternion axisAngle(const Vector3& axis, const float angle)
		{
			Quaternion quat;

			float angOver2 = angle / 2.0f;

			quat.w = cosf(angOver2);
			quat.x = axis.x * sinf(angOver2);
			quat.y = axis.y * sinf(angOver2);
			quat.z = axis.z * sinf(angOver2);

			return quat;
		}

		//=====================================================================

		inline Matrix4x4 toMat4x4(const Quaternion& q)
		{
			Quaternion uq = approximatly(sqrMagnitude(q), 1.0f) ? q : normalized(q);

			Matrix4x4 mat;

			mat.x = vector4::create(1 - 2 * uq.y * uq.y - 2 * uq.z * uq.z, 
									2 * uq.x * uq.y - 2 * uq.w * uq.z,
									2 * uq.x * uq.z + 2 * uq.w * uq.y,
									0);

			mat.y = vector4::create(2 * uq.x * uq.y + 2 * uq.w * uq.z,
									1 - 2 * uq.x * uq.x - 2 * uq.z * uq.z,
									2 * uq.y * uq.z + 2 * uq.w * uq.x, 
									0);

			mat.z = vector4::create(2 * uq.x * uq.z - 2 * uq.w * uq.y,
									2 * uq.y * uq.z - 2 * uq.w * uq.x,
									1 - 2 * uq.x * uq.x - 2* uq.y * uq.y,
									0);

			mat.t = vector4::create(0,0,0,1);

			return mat;
		}
    }
}