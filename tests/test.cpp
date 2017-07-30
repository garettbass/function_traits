#include <cassert>
#include <cstdio>
#include "../function_traits.hpp"

int f(int i) { return i; }

int __cdecl fcdecl(int i) { return i; }

int __fastcall ffastcall(int i) { return i; }

int __stdcall fstdcall(int i) { return i; }

int __thiscall fthiscall(void* _this, int i) { return i; }

int __vectorcall fvectorcall(int i) { return i; }

int main(int argc, char* argv[]) {

    assert(42 == f(42));
    assert(42 == fcdecl(42));
    assert(42 == ffastcall(42));
    assert(42 == fstdcall(42));
    assert(42 == fthiscall(nullptr,42));
    assert(42 == fvectorcall(42));

    function_t<int(int)> p = f;
    assert(42 == p(42));

    {
        function_t<int(__cdecl*)(int)> pcdecl = fcdecl;
        assert(42 == pcdecl(42));

        function_t<int(__fastcall*)(int)> pfastcall = ffastcall;
        assert(42 == pfastcall(42));

        function_t<int(__stdcall*)(int)> pstdcall = fstdcall;
        assert(42 == pstdcall(42));

        function_t<int(__thiscall*)(void*,int)> pthiscall = fthiscall;
        assert(42 == pthiscall(nullptr,42));

        function_t<int(__vectorcall*)(int)> pvectorcall = fvectorcall;
        assert(42 == pvectorcall(42));
    }

    {
        cdecl_t<int(int)> pcdecl = fcdecl;
        assert(42 == pcdecl(42));

        fastcall_t<int(int)> pfastcall = ffastcall;
        assert(42 == pfastcall(42));

        stdcall_t<int(int)> pstdcall = fstdcall;
        assert(42 == pstdcall(42));

        thiscall_t<int(void*,int)> pthiscall = fthiscall;
        assert(42 == pthiscall(nullptr,42));

        vectorcall_t<int(int)> pvectorcall = fvectorcall;
        assert(42 == pvectorcall(42));
    }

    puts("OK");
    return 0;
}