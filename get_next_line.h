/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:11:55 by mayoucha          #+#    #+#             */
/*   Updated: 2024/12/30 18:49:05 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

// Fonctions utiles
int		ft_len(const char *str);
int		ft_found_new_line(t_list *reserve);
void	ft_allocate_line(char **line, t_list *reserve);
void	ft_free_reserve(t_list *reserve);
t_list	*ft_find_last_node(t_list *reserve);
// Fonctions de GNL
char	*get_next_line(int fd);
void	ft_read_and_stock(int fd, t_list **reserve);
void	ft_buf_to_reserve(t_list **reserve, char *buffer, int reader);
void	ft_extract_line(t_list *reserve, char **line);
void	ft_clean_reserve(t_list **reserve);
#endif
