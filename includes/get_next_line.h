/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:41 by asezgin           #+#    #+#             */
/*   Updated: 2025/03/19 08:23:21 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 9999

# endif

char	*ft_calloc(int nmemb, int size);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
int		ft_gt_strchr(const char *s);
int		ft_strlen(const char *s);

#endif