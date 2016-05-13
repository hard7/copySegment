#ifndef __COPY_SEGMENT__TYPE_DEDUCT_H__
#define __COPY_SEGMENT__TYPE_DEDUCT_H__


namespace detail_typeDeduct {
    template<class T> struct void_ { typedef void type; };
    template<class T> using always_void = typename void_<T>::type;
    template <typename... Ts> using void_t = void;

    template<class Package, class Dispatch =void>
    struct TypeDeduct {
        static_assert(not std::is_same<Dispatch, void>::value, "************ Error: determine typedef <Entity>::type");
        typedef double type;
    };

    template<class Package>
    struct TypeDeduct< Package, always_void<typename Package::type> > {
        typedef typename Package::type type;
    };

    template <typename T, class = void>
    struct hasType : std::false_type {};

    template <typename T>
    struct hasType <T, void_t<typename T::type> >  : std::true_type {};
}

template<class Package> using TypeDeductOrError = typename detail_typeDeduct::TypeDeduct<Package>::type;
template<class T> constexpr int hasType() { return detail_typeDeduct::hasType<T>::value; }


#endif //__COPY_SEGMENT__TYPE_DEDUCT_H__
