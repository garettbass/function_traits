#pragma once
#include "cxx/push.h"
#include "cxx/cxx.h"
#include <tuple>

//------------------------------------------------------------------------------

#ifdef FUNCTION_TRAITS_NAMESPACE
namespace FUNCTION_TRAITS_NAMESPACE {
#endif // FUNCTION_TRAITS_NAMESPACE

    template<typename Pointer, typename Result, typename... Params>
    struct basic_function_traits {

        using result_t = Result;

        using function_t = Pointer;

        using tuple_t = std::tuple<Params...>;

        template<unsigned N>
        using parameter_t = typename std::tuple_element<N,tuple_t>::type;

        enum { parameter_count = sizeof...(Params) };

    };

    //--------------------------------------------------------------------------

    template<typename Struct>
    struct function_traits
    : function_traits<decltype(&Struct::operator())> {};

    template<typename Struct, typename Result, typename... Args>
    struct function_traits<Result(Struct::*)(Args...)>
    : function_traits<Result(*)(Args...)> {};

    template<typename Struct, typename Result, typename... Args>
    struct function_traits<Result(Struct::*)(Args...) const>
    : function_traits<Result(*)(Args...)> {};

    template<typename R, typename... Params>
    struct function_traits<R(Params...)>
    : function_traits<R(*)(Params...)> {};

    template<typename R, typename... Params>
    struct function_traits<R(*)(Params...)>
    : basic_function_traits<R(*)(Params...),R,Params...> {};

    #if CXX_OS_MICROSOFT && CXX_X86

        template<typename R, typename... Params>
        struct function_traits<R(__cdecl*)(Params...)>
        : basic_function_traits<R(__cdecl*)(Params...),R,Params...> {};

        template<typename R, typename... Params>
        struct function_traits<R(__fastcall*)(Params...)>
        : basic_function_traits<R(__fastcall*)(Params...),R,Params...> {};

        template<typename R, typename... Params>
        struct function_traits<R(__stdcall*)(Params...)>
        : basic_function_traits<R(__stdcall*)(Params...),R,Params...> {};

        template<typename R, typename... Params>
        struct function_traits<R(__thiscall*)(Params...)>
        : basic_function_traits<R(__thiscall*)(Params...),R,Params...> {};

        template<typename R, typename... Params>
        struct function_traits<R(__vectorcall*)(Params...)>
        : basic_function_traits<R(__vectorcall*)(Params...),R,Params...> {};

    #else

        #ifndef __cdecl
        #define __cdecl
        #endif

        #ifndef __fastcall
        #define __fastcall
        #endif

        #ifndef __stdcall
        #define __stdcall
        #endif

        #ifndef __thiscall
        #define __thiscall
        #endif

        #ifndef __vectorcall
        #define __vectorcall
        #endif

    #endif // CXX_OS_MICROSOFT && CXX_X86

    //--------------------------------------------------------------------------

    template<typename>
    struct cdecl_traits;

    template<typename R, typename... Params>
    struct cdecl_traits<R(Params...)>
    : function_traits<R(__cdecl*)(Params...)> {};

    //--------------------------------------------------------------------------

    template<typename>
    struct fastcall_traits;

    template<typename R, typename... Params>
    struct fastcall_traits<R(Params...)>
    : function_traits<R(__fastcall*)(Params...)> {};

    //--------------------------------------------------------------------------

    template<typename>
    struct stdcall_traits;

    template<typename R, typename... Params>
    struct stdcall_traits<R(Params...)>
    : function_traits<R(__stdcall*)(Params...)> {};

    //--------------------------------------------------------------------------

    template<typename>
    struct thiscall_traits;

    template<typename R, typename... Params>
    struct thiscall_traits<R(Params...)>
    : function_traits<R(__thiscall*)(Params...)> {};

    //--------------------------------------------------------------------------

    template<typename>
    struct vectorcall_traits;

    template<typename R, typename... Params>
    struct vectorcall_traits<R(Params...)>
    : function_traits<R(__vectorcall*)(Params...)> {};

    //--------------------------------------------------------------------------

    template<typename Fn>
    using function_t = typename function_traits<Fn>::function_t;

    template<typename Fn>
    using cdecl_t = typename cdecl_traits<Fn>::function_t;

    template<typename Fn>
    using fastcall_t = typename fastcall_traits<Fn>::function_t;

    template<typename Fn>
    using stdcall_t = typename stdcall_traits<Fn>::function_t;

    template<typename Fn>
    using thiscall_t = typename thiscall_traits<Fn>::function_t;

    template<typename Fn>
    using vectorcall_t = typename vectorcall_traits<Fn>::function_t;

    //--------------------------------------------------------------------------

    template<typename Fn>
    using result_t = typename function_traits<Fn>::result_t;

    template<unsigned N,typename Fn>
    using parameter_t = typename function_traits<Fn>::template parameter_t<N>;

#ifdef FUNCTION_TRAITS_NAMESPACE
} // namespace FUNCTION_TRAITS_NAMESPACE
#endif // FUNCTION_TRAITS_NAMESPACE

//------------------------------------------------------------------------------

#include "cxx/pop.h"