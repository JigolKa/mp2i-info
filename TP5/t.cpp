#include <string>
#include <assert.h>
// template <int>
template <typename T>
constexpr T fun(T x, T a) noexcept
{
    return x < a;
}

double a = fun<double>(9.0, 6.2);
int main()
{
    int x = 0;
    assert(0 <= x <= -1);
}
