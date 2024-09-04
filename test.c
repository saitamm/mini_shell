#include "stdio.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i += 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int main() {
    printf("%d\n", check_n("-nl -n -nbonjour"));          // 1
    // printf("%d\n", check_string("-nnnnnnn"));    // 1
    // printf("%d\n", check_string("-nnnn"));       // 1
    // printf("%d\n", check_string("-n -n -n"));    // 1
    // printf("%d\n", check_string("-nl"));         // 0
    // printf("%d\n", check_string("-nff"));        // 0
    return 0;
}
