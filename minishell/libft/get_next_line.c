/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoh <jakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:05:39 by jakoh             #+#    #+#             */
/*   Updated: 2022/07/09 12:09:18 by jakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Check 'fd' Error 0 == Success | -1 == Fail
// get string "start" and "length" 
// give space to 'temp' & check for NULL;
// might need to check for buffer size if its too large
// store read output to temp;
// 1. Create a loop that check if \n is in "temp"
// 1. if not then strjoin "str" & "temp"
// 1. if "str" is empty then "str" = "temp"
// 2. Append "temp" to "str"
// 2. Check if there is any \n in "str" starting from "length"
void	ft_reader(int fd, int rd, char **str, char *temp);
char	*ft_check_str(char *s);

char	*get_next_line(int fd)
{
	static char	*str[MAX_FD];
	char		*temp;
	int			i;
	int			rd;

	if (fd < 0)
		return (NULL);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
		return (NULL);
	str[fd] = ft_check_str(str[fd]);
	rd = read(fd, temp, BUFFER_SIZE);
	if (rd == -1 || (rd == 0 && str[fd][0] == '\0'))
	{
		free(temp);
		free(str[fd]);
		return (NULL);
	}
	ft_reader(fd, rd, str, temp);
	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	free(temp);
	return (ft_substr(str[fd], 0, i + 1));
}

char	*ft_check_str(char *s)
{
	char	*temp;
	int		i;

	i = 0;
	if (!s)
		return (ft_calloc(1, sizeof(char)));
	while (s[i] != 0 && s[i] != '\n')
		i++;
	if (s[i] == '\n')
	{
		i++;
		temp = ft_substr(s, i, ft_strlen(s) - i);
		free(s);
		return (temp);
	}
	if (s[i] == 0 && i != 0)
		free(s);
	return (ft_calloc(1, sizeof(char)));
}

void	ft_reader(int fd, int rd, char **str, char *temp)
{
	char	*temp2;

	while (rd != 0)
	{
		temp2 = ft_strjoin(str[fd], temp);
		free(str[fd]);
		str[fd] = temp2;
		if (ft_strchr(temp, '\n'))
			break ;
		rd = read(fd, temp, BUFFER_SIZE);
		temp[rd] = 0;
	}
}
// int main(void)
// {
// 	int	o = open("/Users/jakoh/Desktop/gnl/tester/files/41_with_nl",O_RDONLY);
// 	printf("final: %s\n", get_next_line(o));
// 	printf("final: %s\n", get_next_line(o));
// 	printf("final: %s\n", get_next_line(o));
// 	printf("final: %s\n", get_next_line(o));
// 	close(o);
// 	return 0;
// }
