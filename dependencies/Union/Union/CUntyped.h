// Supported with union (c) 2018-2021 Union team

#ifndef __UNION_UNTYPED_H__
#define __UNION_UNTYPED_H__

namespace UnionCore
{
    typedef struct _tagUntyped
    {
        void32 data;

        template <class T> _tagUntyped(T x){ data = reinterpret_cast<void*>(x); }
        operator void32 () const { return data; }

    } TInstance;
} // namespace UnionCore

#endif // __UNION_UNTYPED_H__