#ifndef __COPY_SEGMENT__TYPE_DEDUCT_H__
#define __COPY_SEGMENT__TYPE_DEDUCT_H__


namespace detail_deduct {

    template <typename... Ts> using void_t = void;

    template <typename T, class = void> struct hasType : std::false_type {};
    template <typename T> struct hasType <T, void_t<typename T::type> >  : std::true_type {};

    template <typename T, class = void> struct has_PointType : std::false_type {};
    template <typename T> struct has_PointType <T, void_t<typename T::PointType> >  : std::true_type {};

}

namespace deduct {
    template<class T> constexpr int has_type() { return detail_deduct::hasType< T >::value; }
    template<class T> constexpr int has_PointType() { return detail_deduct::has_PointType< T >::value; }
}





#endif //__COPY_SEGMENT__TYPE_DEDUCT_H__
