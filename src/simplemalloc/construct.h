//
// Created by xyx on 10/29/20.
//

#ifndef _CONSTRUCT_H
#define _CONSTRUCT_H

#include <cstddef>
#include <stdint-gcc.h>
#include <new>
namespace sa
{
    template<typename>
    class simple_allocator;

    template<>
    class simple_allocator<void>;

    template<typename T>
    class simple_allocator
    {
    public:
        //type thing
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef T         value_type;
        //type thing

        template<typename U>
        struct rebind
        {
            typedef simple_allocator<U> other;
        };

        //init and des
        simple_allocator() noexcept { }

        simple_allocator(const simple_allocator&) noexcept { }

        template<typename T1>
        simple_allocator(const simple_allocator<T1>&) noexcept { }

        ~simple_allocator() noexcept { }
        //init and des

        pointer allocate(size_type n, const void* = static_cast<const void*>(0) )
        {
            if(n > this->max_size())
            {
                throw std::bad_alloc();
            }
            return static_cast<T*>( ::operator new( n * sizeof(T) ) );
        }

        void deallocate(pointer p, size_type)
        {
            ::operator delete(p);
        }

        void construct(pointer p, )
        {

        }

        size_type max_size() const noexcept
        {
#if PTRDIFF_MAX < SIZE_MAX
            return size_t(PTRDIFF_MAX) / sizeof(T);
#else
            return size_t(-1) / sizeof(T);
#endif
        }

    };
}


#endif //_CONSTRUCT_H
