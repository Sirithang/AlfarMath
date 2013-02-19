#ifndef VECTOR_H
#define VECTOR_H

#include "math_types.h"

namespace alfar
{
    namespace vector3
    {
        inline Vector3 add(const Vector3& p_First, const Vector3& p_Second);
        inline Vector3 sub(const Vector3& p_First, const Vector3& p_Second);
        inline Vector3 mul(const Vector3& p_Vec, const float p_Scalar);
        inline Vector3 scale(const Vector3& p_First, const Vector3& p_Second);
        inline Vector3 cross(const Vector3& p_First, const Vector3& p_Second);

        inline float dot(const Vector3& p_First, const Vector3& p_Second);

        //----- array version

        void add(Vector3* p_Firsts, Vector3* p_Seconds, Vector3* p_Out, int p_Number);
        void sub(Vector3* p_Firsts, Vector3* p_Seconds, Vector3* p_Out, int p_Number);
        void mul(Vector3* p_Firsts, float* p_Salars, Vector3* p_Out, int p_Number);
        void scale(Vector3* p_Firsts, Vector3* p_Seconds, Vector3* p_Out, int p_Number);
        void cross(Vector3* p_Firsts, Vector3* p_Seconds, Vector3* p_Out, int p_Number);

        void dot(Vector3* p_Firts, Vector3* p_Seconds, float* p_Out, int p_Number);
    }
}

#endif // VECTOR_H
