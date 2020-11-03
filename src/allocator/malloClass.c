//
// Created by xyx on 11/2/20.
//
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("please enter the class name!\n");
        return 0;
    }
    int ret = access(argv[1], F_OK);
    if(ret != 0)
    {
        int fd = open(argv[1], O_RDWR | O_CREAT, 00777);
        if(fd < 0)
        {
            perror("open error");
            return -1;
        }

        dup2(fd, STDOUT_FILENO);
        printf(" template<class T>\n");
        printf(" class %s\n",argv[1]);
        printf(" {\n");
        printf("     public:\n");
        printf("     //type thing\n");
        printf("     typedef size_t    size_type;\n");
        printf("     typedef ptrdiff_t difference_type;\n");
        printf("     typedef T*        pointer;\n");
        printf("     typedef const T*  const_pointer;\n");
        printf("     typedef T&        reference;\n");
        printf("     typedef const T&  const_reference;\n");
        printf("     typedef T         value_type;\n");
        printf("     //type thing\n");
        printf("\n");
        printf("     template<typename U>\n");
        printf("     struct rebind\n");
        printf("     {\n");
        printf("         typedef %s<U> other;\n", argv[1]);
        printf("     };\n");
        printf("\n");
        printf("     %s() noexcept { }\n", argv[1]);
        printf("     %s(const %s&) noexcept { }\n", argv[1], argv[1]);
        printf("     template<typename U>\n");
        printf("                       %s(const %s<U>&) noexcept { }\n", argv[1], argv[1]);
        printf("     ~%s() noexcept { }\n", argv[1]);
        printf("\n");
        printf("     static pointer allocate(size_t n)\n");
        printf("     {\n");
        printf("         pointer res = (pointer)malloc(n * sizeof(value_type));\n");
        printf("         if(nullptr == res) res = (pointer)_S_oom_malloc(n * sizeof(value_type));\n");
        printf("         return res;\n");
        printf("\n");
        printf("     }\n");
        printf("\n");
        printf("     static void deallocate(void* p, size_t)\n");
        printf("     {\n");
        printf("         free(p);\n");
        printf("     }\n");
        printf("\n");
        printf("     static pointer reallocate(pointer p, size_t /*old size*/, size_t new_sz)\n");
        printf("     {\n");
        printf("         pointer res = (pointer)realloc(p, new_sz * sizeof(value_type));\n");
        printf("         if(nullptr == res) res = (pointer)_S_oom_realloc(p, new_sz * sizeof(value_type));\n");
        printf("         return res;\n");
        printf("     }\n");
        printf("\n");
        printf("     static void construct(pointer p, const T& value)\n");
        printf("     {\n");
        printf("         ::new((void *)p) T(value);\n");
        printf("     }\n");
        printf("\n");
        printf("     static void destroy(pointer p)\n");
        printf("     {\n");
        printf("         p->~value_type();\n");
        printf("     }\n");
        printf("\n");
        printf("     size_type max_size() const noexcept\n");
        printf("     {\n");
        printf("       #if PTRDIFF_MAX < SIZE_MAX\n");
        printf("         return  size_t(PTRDIFF_MAX) / sizeof(T);\n");
        printf("       #else\n");
        printf("         return size_t(-1) / sizeof(T);\n");
        printf("       #endif\n");
        printf("     }\n");
        printf("\n");
        printf("     pointer address(reference x)\n");
        printf("     {\n");
        printf("         return (pointer)&x;\n");
        printf("     }\n");
        printf("n");
        printf("     const_pointer  const_address(const_reference x)\n");
        printf("     {\n");
        printf("         return (const_pointer)&x;\n");
        printf("     }\n");
        printf("\n");
        printf("     static void (* set_malloc_handler(void (*func)() ))()\n");
        printf("     {\n");
        printf("         void (* old)() = __malloc_alloc_oom_handler;\n");
        printf("         __malloc_alloc_oom_handler = func;\n");
        printf("         return old;\n");
        printf("     }\n");
        printf("     private:\n");
        printf("     static void (* __malloc_alloc_oom_handler)();\n");
        printf("     static void* _S_oom_malloc(size_t);\n");
        printf("     static void* _S_oom_realloc(void*, size_t);\n");
        printf(" };\n");
        printf("\n");
        printf(" template<typename T>\n");
        printf(" void (* %s<T>::__malloc_alloc_oom_handler)() = nullptr;\n", argv[1]);
        printf("\n");
        printf(" template<typename T>\n");
        printf(" void* %s<T>::_S_oom_malloc(size_t n)\n", argv[1]);
        printf(" {\n");
        printf("     void (* __my_malloc_handler)();\n");
        printf("     void* res;\n");
        printf("\n");
        printf("     while(true)\n");
        printf("     {\n");
        printf("         __my_malloc_handler = __malloc_alloc_oom_handler;\n");
        printf("         if(nullptr == __my_malloc_handler) { __THROW_BAD_ALLOC; }\n");
        printf("         (*__my_malloc_handler)();\n");
        printf("         res = malloc(n);\n");
        printf("         if(res) return res;\n");
        printf("     }\n");
        printf(" }\n");
        printf("\n");
        printf(" template<typename T>\n");
        printf(" void* %s<T>::_S_oom_realloc(void *p, size_t n)\n", argv[1]);
        printf(" {\n");
        printf("     void (* __my_malloc_handler)();\n");
        printf("     void *res;\n");
        printf("     while(true)\n");
        printf("     {\n");
        printf("         __my_malloc_handler = __malloc_alloc_oom_handler;\n");
        printf("         if(nullptr == __my_malloc_handler) { __THROW_BAD_ALLOC; }\n");
        printf("         (*__my_malloc_handler)();\n");
        printf("         res = realloc(p, n);\n");
        printf("         if(res) return res;\n");
        printf("     }\n");
        printf(" }\n");
        close(fd);
    }
    else
    {
        printf("%s aready exists!\n",argv[1]);
    }

    return 0;
}
