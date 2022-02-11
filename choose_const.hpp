#ifndef __CHOOSE_CONST_HPP
#define __CHOOSE_CONST_HPP

namespace ft
{
    /**
    *   Use a boolean to typedef either type 1 or type 2.
    */
    template <bool isConst, typename isFalse, typename isTrue>
    struct chooseConst {};
    /**
    *   Typedef: pointer, ref...
    */
    template <typename isFalse, typename isTrue>
    struct chooseConst<false, isFalse, isTrue>
    {
        typedef isFalse type;
    };
    /**
    *   Typedef: const pointer, const ref...
    */
    template <typename isFalse, typename isTrue>
    struct chooseConst<true, isFalse, isTrue>
    {
        typedef isTrue type;
    };

} //namespace ft

#endif