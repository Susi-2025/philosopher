
#include "philo.h"

int ft_valid_pos_num(char *s)
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