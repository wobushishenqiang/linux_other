//
// Created by xyx on 11/2/20.
//

#ifndef _POOLALLOCATOR_H
#define _POOLALLOCATOR_H

#include <cstdlib>
#include <cstddef>
#include <stdint-gcc.h>
#include <new>
#include "mallocallocator.h"
#define __THROW_BAD_ALLOC throw std::bad_alloc()

namespace ma
{
    enum {ALIGN = 8};//each list byte align
    enum {MAX_BYTES = 128};//max byte in list
    enum {NFREELISTS = 16};// list num
    template<bool threads, class T>
    class pool_allocator
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
            typedef pool_allocator<threads,U> other;
        };

        pool_allocator() noexcept {;}
        pool_allocator(const pool_allocator&) noexcept {;}
        template<typename U>
        explicit pool_allocator(const pool_allocator<threads,U>&) noexcept {;}
        ~pool_allocator() noexcept {;}

        static pointer allocate(size_t n)
        {
            pointer ret = nullptr;
            size_t _bytes = n * sizeof(value_type);
            if(_bytes > (size_t) MAX_BYTES)
            {
                ret = malloc_allocator<T>::allocate(n);
            }
            else
            {
                //_S_free_list is an array store node*
                volatile node* *my_free_list = free_list + freelist_index(_bytes);

                Lock lock_instance;
                node* res = *my_free_list;
                if(nullptr == res)
                {
                    ret = refill(n);
                }
                else
                {
                    *my_free_list = res->_M_free_list_link;
                    ret = (pointer)res;
                }

            }

            return ret;


        }

        static void deallocate(void* p, size_t n)
        {
            size_t bytes = n * sizeof(value_type);
            if(bytes > MAX_BYTES)
                malloc_allocator<T>::deallocate(p, n);
            else
            {
                volatile node ** my_free_list = free_list + freelist_index(bytes);
                node* q = (node*)p;

                Lock lock_instance;
                q->_M_free_list_link = *my_free_list;
                *my_free_list = q;
            }
        }

        static pointer reallocate(pointer p, size_t old_n, size_t new_n)
        {
            size_t old_sz = old_n * sizeof(value_type);
            size_t new_sz = new_n * sizeof(value_type);
            pointer ret;
            size_t copy_sz;

           if(old_sz > (size_t) MAX_BYTES && new_sz > (size_t) MAX_BYTES)
           {
              return  malloc_allocator<T>::allocate(new_n);
           }

           if(round_up(old_sz) == round_up(new_sz) )
           {
               return p;
           }
           ret = allocate(new_n);
           copy_sz = new_sz > old_sz? old_sz : new_sz;
           memcpy(ret, p, copy_sz);
           deallocate(p, old_n);
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

    private:
        //free list pool

        //when you allocate something ,the allocator should
        //allocate some space fix the list node byte
        //change the space need by something into 8 16 24 32 ... 128 bytes
        static size_t round_up(size_t bytes)
        {
            return ((bytes + (size_t)ALIGN - 1) & ~((size_t)ALIGN - 1));
        }

        //the freelist node, when it used ,it point to the data
        //when it was not used , it point to the next free space
        union node{
            union node* free_list_link;
            char client_data[1];
        };

        //freelist
        static node* volatile free_list[];

        //get the index of the space need
        static size_t freelist_index(size_t bytes)
        {
            return ( (bytes + (size_t)ALIGN -1) /(size_t)ALIGN - 1);
        }

        static pointer refill(size_t n);

        //get in pool
        static pointer chunk_alloc(size_t n, int& nobjs);

        //pool
        static char* start_free;
        static char* end_free;
        static size_t heap_size;

        class Lock;
        friend class Lock;
        class Lock
        {
        public:
            Lock(){
                //Lock
                ;
            }
            ~Lock(){
                //Unlock;
                ;
            }
        };
    };

    template<bool threads, typename T>
    char* pool_allocator<threads, T>::start_free = nullptr;

    template<bool threads, typename T>
    char* pool_allocator<threads, T>::end_free = nullptr;

    template<bool threads, typename T>
    size_t pool_allocator<threads, T>::heap_size = 0;

    template<bool threads, typename T>
    typename pool_allocator<threads, T>::node* volatile
        pool_allocator<threads, T>::free_list[NFREELISTS]=
                {nullptr, nullptr, nullptr, nullptr,
                 nullptr, nullptr, nullptr, nullptr,
                 nullptr, nullptr, nullptr, nullptr,
                 nullptr, nullptr, nullptr, nullptr};


    template<bool threads, typename T>
    T* pool_allocator<threads, T>::refill(size_t n)
    {
        int nobjs = 20;
        size_t bytes = round_up(n * sizeof(value_type));
        pointer chunk = chunk_alloc(n, nobjs);
        node* volatile *my_free_list;
        node* res;
        node* current;
        node* next;
        int i;

        if(1 == nobjs) return chunk;
        my_free_list = free_list + freelist_index(bytes);

        res = (node*)chunk;
        *my_free_list = next = (node*)(chunk + bytes);
        for(i = 1; ; ++i)
        {
            current = next;
            next = (node*)((char*)next + bytes);
            if(nobjs - 1 == i)
            {
                current->free_list_link = nullptr;
                break;
            }
            else
            {
                current->free_list_link = next;
            }
        }
        return res;
    }

    template<bool threads, typename T>
    T* pool_allocator<threads, T>::chunk_alloc(size_t n, int &nobjs)
    {
        pointer res;
        size_t bytes = round_up(n * sizeof(value_type));
        size_t total_bytes = bytes * nobjs;
        size_t bytes_left = end_free - start_free;

        //enough
        if(bytes_left >= total_bytes)
        {
            res = (pointer)start_free;
            start_free += total_bytes;
            return res;
        }
        else if(bytes_left >= bytes)//more than 1 less than nobjs
        {
            nobjs = (int)(bytes_left / bytes);
            total_bytes = bytes * nobjs;
            res = (pointer)start_free;
            start_free += total_bytes;
            return res;
        }
        else
        {
            size_t bytes_to_get = 2 * total_bytes + round_up(heap_size >> 4);
            //if has left, fill in freelist
            if(bytes_left > 0)
            {
                node* volatile *my_free_list = free_list + freelist_index(bytes_left);
                ((node*)start_free)->free_list_link = *my_free_list;
                *my_free_list = (node*)start_free;
            }

            start_free = (char*)malloc(bytes_to_get);
            if(nullptr == start_free)
            {
                //find other bigger block if has space
                size_t i;
                node* volatile *my_free_list;
                node *p;
                for(i = bytes; i <= (size_t)MAX_BYTES; i += (size_t)ALIGN)
                {
                    my_free_list = free_list + freelist_index(i);
                    p = *my_free_list;
                    if(nullptr != p)
                    {
                        *my_free_list = p->free_list_link;
                        start_free = (char*)p;
                        end_free = start_free + i;
                        return chunk_alloc(n, &nobjs);
                    }
                }

                end_free = nullptr;
                start_free = (char*)malloc_allocator<T>::allocate(n);
            }
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            return chunk_alloc(n, &nobjs);
        }
    }
}
#endif //_POOLALLOCATOR_H
