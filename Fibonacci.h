#pragma once
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "bigint.h"
#define vec2 sf::Vector2f
using namespace std;




static void setupAxes(sf::Vertex *axes) {
    for (size_t i = 0; i < 4; i++)
    {
        axes[i] = sf::Vertex();
    }
    axes[0].position = vec2(0, 501);
    axes[1].position = vec2(1010, 501);
    axes[2].position = vec2(10, 0);
    axes[3].position = vec2(10, 510);
}


static long long getTimeMS() {
    auto now = chrono::system_clock::now();

    // Convert the current time to time since epoch
    auto duration = now.time_since_epoch();

    // Convert duration to milliseconds
    auto milliseconds
        = chrono::duration_cast<chrono::milliseconds>(
            duration)
        .count();
    return milliseconds;
}




static bigint fibRec(int n) {
    if (n <= 1) {
        return n;
    }
    return fibRec(n - 1) + fibRec(n - 2);
}
static vector<bigint> memo({0,1});
static bigint fibMemo(int n) {
    if (memo.size() > n) {
        return memo[n];
    }else{
        memo.push_back(fibMemo(n - 1) + fibMemo(n - 2));
        return memo[n];
    }
}
static bigint fibBottomUp(int n) {
    if (n <= 1) {
        return n;
    }
    bigint a = bigint(0);
    bigint b = bigint(1);
    bigint tmp = bigint(0);
    for (size_t i = 2; i <= n; i++)
    {
        tmp = a + b;
        a = b;
        b = tmp;
    }
    return b;
}

class Mat2x2 {
public:
    bigint data[2][2] = { {bigint(0),bigint(0)},{bigint(0),bigint(0)} };
    Mat2x2() {

    }
    Mat2x2(bigint values[2][2]) {
        memcpy(&data,&values,sizeof(values));
    }
    Mat2x2(initializer_list<initializer_list<int>> values) {
        data[0][0] = bigint(values.begin()[0].begin()[0]);
        data[0][1] = bigint(values.begin()[0].begin()[1]);
        data[1][0] = bigint(values.begin()[1].begin()[0]);
        data[1][1] = bigint(values.begin()[1].begin()[1]);
    }
    Mat2x2(initializer_list<initializer_list<bigint>> values) {
        data[0][0] = bigint(values.begin()[0].begin()[0]);
        data[0][1] = bigint(values.begin()[0].begin()[1]);
        data[1][0] = bigint(values.begin()[1].begin()[0]);
        data[1][1] = bigint(values.begin()[1].begin()[1]);
    }
    Mat2x2 operator *(Mat2x2 other) {
        return Mat2x2({
            {data[0][0] * other.data[0][0] + data[0][1] * other.data[1][0]  ,   data[0][0] * other.data[1][0] + data[0][1] * other.data[1][1]},
            {data[1][0] * other.data[0][0] + data[1][1] * other.data[1][0]  ,   data[1][0] * other.data[1][0] + data[1][1] * other.data[1][1]}
        });
    }
    Mat2x2 multiply(Mat2x2 first,Mat2x2 other) {
        return Mat2x2({
            {first.data[0][0] * other.data[0][0] + first.data[0][1] * other.data[1][0]  ,   first.data[0][0] * other.data[1][0] + first.data[0][1] * other.data[1][1]},
            {first.data[1][0] * other.data[0][0] + first.data[1][1] * other.data[1][0]  ,   first.data[1][0] * other.data[1][0] + first.data[1][1] * other.data[1][1]}
            });
    }
    Mat2x2& operator *= (Mat2x2 const other) {
        (*this) = (*this) * other;
        return (*this);
    }
};
class BigVec2
{
public:
    bigint x;
    bigint y;

    BigVec2(bigint x, bigint y) {
        this->x = x;
        this->y = y;
    }
    BigVec2 operator *(Mat2x2 other) {
        return BigVec2(other.data[0][0] * x + other.data[0][1] * y, other.data[1][0] * x + other.data[1][1] * y);
    }
    BigVec2& operator *= (Mat2x2 const other) {
        (*this) = (*this) * other;
        return (*this);
    }
};
static bigint fibMatrix(int n) {
    if (n <= 1) {
        return n;
    }

    BigVec2 F(0, 1);
    Mat2x2 A({ {1, 1}, {1,0} });
    Mat2x2 B(A);

    for (int i = 1; i < n;i++) {
        A *= B;
    }
    F *= A;
    return F.x;



}


