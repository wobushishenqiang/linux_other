//
// Created by xyx on 11/2/20.
//

#ifndef _MALLOCALLOCATOR_H
#define _MALLOCALLOCATOR_H

#include <cstdlib>
#include <cstddef>
#include <stdint-gcc.h>
#include <new>
#define __THROW_BAD_ALLOC throw std::bad_alloc()

namespace ma
{
    template<class T>
    class malloc_allocator
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
            typedef malloc_allocator<U> other;
        };

        malloc_allocator() noexcept { }
        malloc_allocator(const malloc_allocator&) noexcept { }
        template<typename U>
        malloc_allocator(const malloc_allocator<U>&) noexcept { }
        ~malloc_allocator() noexcept { }

        static pointer allocate(size_t n)
        {
            pointer res = (pointer)malloc(n * sizeof(value_type));
            if(nullptr == res) res = (pointer)_S_oom_malloc(n * sizeof(value_type));
            return res;

        }

        static void deallocate(void* p, size_t)
        {
            free(p);
        }

        static pointer reallocate(pointer p, size_t /*old size*/, size_t new_sz)
        {
            pointer res = (pointer)realloc(p, new_sz * sizeof(value_type));
            if(nullptr == res) res = (pointer)_S_oom_realloc(p, new_sz * sizeof(value_type));
            return res;
        }

        static void construct(pointer p, const T& value)
        {
            ::new((void *)p) T(value);
        }

        static void destroy(pointer p)
        {
            p->~value_type();
        }

        size_type max_size() const noexcept
        {
#if PTRDIFF_MAX < SIZE_MAX
            return  size_t(PTRDIFF_MAX) / sizeof(T);
#else
            return size_t(-1) / sizeof(T);
#endif
        }

        pointer address(reference x)
        {
            return (pointer)&x;
        }

        const_pointer  const_address(const_reference x)
        {
            return (const_pointer)&x;
        }

        static void (* set_malloc_handler(void (*func)() ))()
        {
            void (* old)() = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = func;
            return old;
        }
    private:
        static void (* __malloc_alloc_oom_handler)();
        static void* _S_oom_malloc(size_t);
        static void* _S_oom_realloc(void*, size_t);
    };

    template<typename T>
    void (* malloc_allocator<T>::__malloc_alloc_oom_handler)() = nullptr;

    template<typename T>
    void* malloc_allocator<T>::_S_oom_malloc(size_t n)
    {
        void (* __my_malloc_handler)();
        void* res;

        while(true)
        {
            __my_malloc_handler = __malloc_alloc_oom_handler;
            if(nullptr == __my_malloc_handler) { __THROW_BAD_ALLOC; }
            (*__my_malloc_handler)();
            res = malloc(n);
            if(res) return res;
        }
    }

    template<typename T>
    void* malloc_allocator<T>::_S_oom_realloc(void *p, size_t n)
    {
        void (* __my_malloc_handler)();
        void *res;
        while(true)
        {
            __my_malloc_handler = __malloc_alloc_oom_handler;
            if(nullptr == __my_malloc_handler) { __THROW_BAD_ALLOC; }
            (*__my_malloc_handler)();
            res = realloc(p, n);
            if(res) return res;
        }
    }
}

#endif //_MALLOCALLOCATOR_H
