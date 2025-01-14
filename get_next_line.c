/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:15:08 by mayoucha          #+#    #+#             */
/*   Updated: 2025/01/03 11:47:34 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*reserve = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		ft_free_reserve(reserve);
		reserve = NULL;
		return (NULL);
	}
	line = NULL;
	ft_read_and_stock(fd, &reserve);
	if (reserve == NULL)
		return (NULL);
	ft_extract_line(reserve, &line);
	ft_clean_reserve(&reserve);
	if (line != NULL && line[0] == '\0')
	{
		ft_free_reserve(reserve);
		reserve = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	ft_read_and_stock(int fd, t_list **reserve)
{
	char	*buffer;
	int		reader;

	reader = 1;
	while (!ft_found_new_line(*reserve) && reader != 0)
	{
		buffer = malloc(sizeof (char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		reader = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*reserve == NULL && reader == 0) || reader == -1)
		{
			free (buffer);
			return ;
		}
		buffer[reader] = '\0';
		ft_buf_to_reserve(reserve, buffer, reader);
		free (buffer);
	}
}

void	ft_buf_to_reserve(t_list **reserve, char *buffer, int reader)
{
	t_list	*new_node;
	t_list	*last;
	int		i;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof (char) * (reader + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buffer[i] != '\0' && i < reader)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*reserve == NULL)
	{
		*reserve = new_node;
		return ;
	}
	last = ft_find_last_node(*reserve);
	last->next = new_node;
}

void	ft_extract_line(t_list *reserve, char **line)
{
	int	i;
	int	j;

	if (reserve == NULL)
		return ;
	ft_allocate_line(line, reserve);
	if (*line == NULL)
		return ;
	j = 0;
	while (reserve != NULL)
	{
		i = 0;
		while (reserve->content[i])
		{
			if (reserve->content[i] == '\n')
			{
				(*line)[j++] = reserve->content[i];
				break ;
			}
			(*line)[j++] = reserve->content[i++];
		}
		reserve = reserve->next;
	}
	(*line)[j] = '\0';
}

void	ft_clean_reserve(t_list **reserve)
{
	t_list	*clean;
	t_list	*last;
	int		i;
	int		j;

	clean = malloc(sizeof (t_list));
	if (reserve == NULL || clean == NULL)
		return ;
	clean->next = NULL;
	last = ft_find_last_node(*reserve);
	i = 0;
	while (last->content[i] != '\0' && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean->content = malloc(sizeof (char) * ((ft_len(last->content) - i) + 1));
	if (clean->content == NULL)
		return ;
	j = 0;
	while (last->content[i] != '\0')
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	ft_free_reserve(*reserve);
	*reserve = clean;
}
/*
int main()
{
    int fd;
    char *line;

    // Ouvrir un fichier pour tester
    fd = open("test.txt", O_RDONLY); 
    if (fd == -1)
	{
        perror("Erreur");
        return 1;
    }
    // Lire et afficher chaque ligne
    while ((line = get_next_line(fd)) != NULL)
	{
        printf("%s", line);
        free(line);  // Libérer la mémoire après utilisation
    }
    // Fermer le fichier
    close(fd);
    return 0;
}*/
