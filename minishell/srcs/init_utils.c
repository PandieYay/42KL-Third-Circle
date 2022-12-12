/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlim <edlim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:28:11 by jakoh             #+#    #+#             */
/*   Updated: 2022/11/01 18:54:29 by edlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *envp)
{
	char	*temp;

	temp = ft_strchr(envp, '=');
	return (ft_substr(envp, 0, temp - envp));
}

char	*get_val(char *envp)
{
	char	*temp;
	int		len;

	len = ft_strlen(envp);
	temp = ft_strchr(envp, '=');
	return (ft_substr(temp + 1, 0, len));
}
