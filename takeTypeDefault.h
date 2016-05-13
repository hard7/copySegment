#ifndef __HAS_TYPE_H__
#define __HAS_TYPE_H__


#include <type_traits>

namespace detail_takeType_ {
    template<class T> struct _void { typedef void type; };

    template<class Packed, class Default, class Dispatch =void>
    struct TakeType {
        static_assert(not std::is_same<Dispatch, void>::value, "************ Error: determine typedef <Entity>::type");
        typedef Default type;
    };

    template<class Packed, class Default>
    struct TakeType< Packed, Default, typename _void<typename Packed::type>::type > {
        typedef typename Packed::type type;
    };


} // namespace detail_takeType_


// http://stackoverflow.com/questions/11813940/possible-to-use-type-traits-sfinae-to-find-if-a-class-defines-a-member-type
template <typename Packed, typename Default> using takeTypeDefault = typename detail_takeType_::TakeType<Packed, Default>::type;


#endif //__HAS_TYPE_H__
