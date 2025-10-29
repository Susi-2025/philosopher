
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
    unsigned int res;

    i = 0;
    res = 0;
    while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '+')
        i++;
    while (s[i])
    {
        res = res * 10 + s[i] - '0';
        i++;
    }
    return (res);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    if (!s1 && !s2)
        return (0);
    if (!s1)
        return (-1);
    if (!s2)
        return (1);
    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}