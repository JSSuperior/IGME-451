// Intrinsic Practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <chrono>
#include <xmmintrin.h>

using namespace std;
using namespace std::chrono;

struct Vector3 {
    float x;
    float y;
    float z;
};

Vector3 NonInstrinsicSlerp(Vector3 sP, Vector3 eP, float t) {
    const float omega = acos((sP.x * eP.x) + (sP.y * eP.y) + (sP.z * eP.z));
    const float p1 = sin((1 - t) * omega) / sin(omega);
    const float p2 = sin(t * omega) / sin(omega);
    Vector3 result;

    result.x = (p1 * sP.x) + (p2 * eP.x);
    result.y = (p1 * sP.y) + (p2 * eP.y);
    result.z = (p1 * sP.z) + (p2 * eP.z);

    return result;
};

__m128 __forceinline IntrinsicSlerp(const __m128& sP, __m128& eP, float t) {
    float tempStorage[4];
    _mm_storeu_ps(tempStorage, _mm_mul_ps(sP, eP));

    const float omega = acos(tempStorage[0] + tempStorage[1] + tempStorage[2]);
    const float p1 = (sin((1 - t) * omega) / sin(omega));
    const float p2 = (sin(t * omega) / sin(omega));

    __m128 part1 = { p1, p1, p1, 0 };
    __m128 part2 = { p2, p2, p2, 0 };

    return _mm_add_ps(_mm_mul_ps(part1, sP), _mm_mul_ps(part2, eP));
}

int main()
{
    steady_clock::time_point t1, t2;
    duration<double, milli> span;

    // non-intrinsic method
    std::cout << "Non-Intrinsic SLERP: " << endl;
    t1 = steady_clock::now();
    Vector3 calculatedPoint = NonInstrinsicSlerp(Vector3(1, 0, 0), Vector3(0, 1, 0), 0.5f);
    t2 = steady_clock::now();

    span = t2 - t1;

    cout << "Non-Intrinsic X: " << calculatedPoint.x << endl;
    cout << "Non-Intrinsic Y: " << calculatedPoint.y << endl;
    cout << "Non-Intrinsic Z: " << calculatedPoint.z << endl;
    cout << "Time: " << span.count() << "ms" << endl << endl;

    // intrinsic method
    __m128 point1 = { 1, 0, 0, 0 };
    __m128 point2 = { 0, 1, 0, 0 };

    t1 = steady_clock::now();
    __m128 calculatedPoint2 = IntrinsicSlerp(point1, point2, 0.5f);
    t2 = steady_clock::now();

    // unsure if this needs to be a part of the calculation or not
    float retrievedValues[4];
    _mm_storeu_ps(retrievedValues, calculatedPoint2);

    span = t2 - t1;

    std::cout << "Intrinsic SLERP: " << endl;
    cout << "Intrinsic X: " << retrievedValues[0] << endl;
    cout << "Intrinsic Y: " << retrievedValues[1] << endl;
    cout << "Intrinsic Z: " << retrievedValues[2] << endl;
    cout << "Time: " << span.count() << "ms" << endl;
}