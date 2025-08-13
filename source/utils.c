#include "shmup.h"

unsigned int ft_numlen(unsigned int num)
{
	unsigned int len;

	if (num == 0)
		return 1;
	len = 0;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	if (!s)
		return ;
	ptr = (unsigned char *)s;
	while (n--)
		*(ptr++) = 0;
	return ;
}
