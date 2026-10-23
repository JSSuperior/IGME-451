// Intrinsic Practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <chrono>
#include <xmmintrin.h>

using namespace std;
using namespace std::chrono;

struct Vector2 {
    float x;
    float y;
};

Vector2 NonInstrinsicSlerp(Vector2 sP, Vector2 eP, float t) {
    const float omega = acos((sP.x * eP.x) + (sP.y * eP.y));
    Vector2 result;

    result.x = (sin((1 - t) * omega) / sin(omega)) * sP.x + (sin(t * omega) / sin(omega)) * eP.x;
    result.y = (sin((1 - t) * omega) / sin(omega)) * sP.y + (sin(t * omega) / sin(omega)) * eP.y;

    return result;
};

__m128 __forceinline IntrinsicSlerp(const __m128& sP, __m128& eP, float t) {
    
    
    //__m128 p1 = { sP.x, sP.x };
    //__m128 p2 = { eP.y, sP.y };
    
    //_mm_acos_pd()

    //return null;
}

int main()
{
    steady_clock::time_point t1, t2;
    duration<double, milli> span;

    // non-intrinsic method
    std::cout << "Non-Intrinsic Method: " << endl;
    t1 = steady_clock::now();
    Vector2 calculatedPoint = NonInstrinsicSlerp(Vector2(1,0), Vector2(0,1), 0.5f);
    t2 = steady_clock::now();

    span = t2 - t1;

    cout << "Non-Intrinsic X: " << calculatedPoint.x << endl;
    cout << "Non-Intrinsic Y: " << calculatedPoint.y << endl;
    cout << "Time: " << span.count() << "ms" << endl;


}

