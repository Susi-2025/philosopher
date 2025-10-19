
#include "philo.h"

int ft_valid_num(char *s)
{
    int i;
    int res;

    i = 0;
    res = 0;
    if (!s)
        return (1);
    while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '-')
        return (1);
    while (s[i])
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (1);
        res = res * 10 + (s[i] - '0');
        if (res > INT_MAX)
            return (1);
        i++;
    }
    return (0);
}

int ft_atoi(char *s)
{
    int i;
    unsigned int    res;

    i = 0;
    res = 0;
    while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '+')
        i++;
    while (s[i])
    {
        res = res * 10 +  s[i] - '0';
        i++;
    }
    return (res);
}

int check_args(int ac, char *av[])
{
    int i;

    if (!av[0])
        printf("Wrong arguments\n");
    i = 1;
    while (i < ac)
    {
        if (ft_valid_num(av[i]) == 1)
            return (1);
        i++;
    }
    return (0);
}

uint64_t   get_time(void)
{
    struct timeval  c_time;
    uint64_t        time;

    gettimeofday(&c_time, NULL);
    time = ((uint64_t)c_time.tv_sec * 1000) + ((uint64_t)c_time.tv_usec / 1000);
    return (time);
}

