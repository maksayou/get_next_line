/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:09:52 by mayoucha          #+#    #+#             */
/*   Updated: 2024/12/30 18:55:47 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_len(const char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_found_new_line(t_list *reserve)
{
	int		i;
	t_list	*current;

	if (reserve == NULL)
		return (0);
	current = ft_find_last_node(reserve);
	i = 0;
	while (current->content[i] != '\0')
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_allocate_line(char **line, t_list *reserve)
{
	int	i;
	int	len;

	len = 0;
	while (reserve != NULL)
	{
		i = 0;
		while (reserve->content[i])
		{
			if (reserve->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		reserve = reserve->next;
	}
	*line = malloc(sizeof (char) * (len + 1));
}

t_list	*ft_find_last_node(t_list *reserve)
{
	t_list	*tmp;

	tmp = reserve;
	if (tmp == NULL)
		return (NULL);
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_free_reserve(t_list *reserve)
{
	t_list	*tmp;
	t_list	*next;

	tmp = reserve;
	while (tmp != NULL)
	{
		free (tmp->content);
		next = tmp->next;
		free (tmp);
		tmp = next;
	}
}
