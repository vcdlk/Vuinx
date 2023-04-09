#include <vinx/string.h>

// src 拷贝到 dest
char *strcpy(char *dest, const char *src)
{
    char *ptr = dest;
    while (true)
    {
        *ptr++ = *src;
        if (*(src++) == EOS)
        {
            return dest;
        }
    }
    return dest;
}

char *strncpy(char *dest, const char *src, size_t count)
{
    char *ptr = dest;
    size_t nr = 0;
    for (; nr < count; nr++)
    {
        *ptr++ = *src;
        if (*src++ == EOS)
            return dest;
    }
    dest[count - 1] = EOS;
    return dest;
}

// dest 结尾拼接 src
char *strcat(char *dest, const char *src)
{
    char *ptr = dest;
    while (*ptr != EOS)
    {
        ptr++;
    }
    while (true)
    {
        *ptr++ = *src++;
        if (*src++ == EOS)
        {
            return dest;
        }
    }
    return dest;
}

// str长度
size_t strlen(const char *str)
{
    char *ptr = (char *)str;
    while (*str != EOS)
    {
        str++;
    }
    return str - ptr;
}

// 比较 lhs 和 rhs 大小
int strcmp(const char *lhs, const char *rhs)
{
    while (*lhs == *rhs && *lhs != EOS && *rhs != EOS)
    {
        lhs++;
        rhs++;
    }
    return *lhs < *rhs ? -1 : *lhs > *rhs;
}

// str 中找到 ch 首次出现的指针
char *strchr(const char *str, int ch)
{
    char *ptr = (char *)str;
    while (true)
    {
        if (*ptr == ch)
        {
            return ptr;
        }
        if (*ptr++ == EOS)
        {
            return NULL;
        }
    }
}

//  从 str 的右侧寻找首个 ch， 返回期指针
char *strrchr(const char *str, int ch)
{
    char *last = NULL;
    char *ptr = (char *)str;
    while (true)
    {
        if (*ptr == ch)
        {
            last = ptr;
        }
        if (*ptr++ == EOS)
        {
            return last;
        }
    }
}

int memcmp(const void *lhs, const void *rhs, size_t count)
{
    char *lptr = (char *)lhs;
    char *rptr = (char *)rhs;
    while (*lptr == *rptr && count-- > 0)
    {
        lptr++;
        rptr++;
    }
    return *lptr < *rptr ? -1 : *lptr > *rptr;
}

void *memset(void *dest, int ch, size_t count)
{
    char *ptr = dest;
    while (count--)
    {
        *ptr++ = ch;
    }
    return dest;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    char *ptr = dest;
    while (count--)
    {
        *ptr++ = *((char *)(src++));
    }
    return dest;
}

void *memchr(const void *str, int ch, size_t count)
{
    char *ptr = (char *)str;
    while (count--)
    {
        if (*ptr == ch)
        {
            return (void *)ptr;
        }
        ptr++;
    }
}