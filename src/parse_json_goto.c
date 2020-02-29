/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json_goto.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:59:50 by odrinkwa          #+#    #+#             */
/*   Updated: 2020/02/29 15:08:27 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "validation.h"

int				ft_gotochar(char **str, char ch)
{
	int		len;

	if (!str || !*str)
		return (-1);
	len = 0;
	while (**str != ch && **str)
	{
		(*str)++;
		len++;
	}
	return (len);
}

int				ft_goto_endnumber(char **str)
{
	int		len;

	if (!str || !*str)
		return (-1);
	len = 0;
	while ((**str == '.' || ('0' <= **str && **str <= '9')) && **str)
	{
		(*str)++;
		len++;
	}
	return (len);
}

static int		select_closechar(char openchar)
{
	char	closechar;

	if (openchar == '[')
		closechar = ']';
	else if (openchar == '{')
		closechar = '}';
	else if (('0' <= openchar && openchar <= '9') || openchar == '.')
		closechar = 0;
	else
		closechar = -1;
	return (closechar);
}

static int		find_end_param(char **str, char openchar, char closechar)
{
	int		len;
	int		count_openchars;

	len = 0;
	count_openchars = 1;
	while (**str)
	{
		if (**str == openchar)
			count_openchars++;
		else if (**str == closechar)
			count_openchars--;
		if (!count_openchars)
		{
			(*str)++;
			return (len);
		}
		len++;
		(*str)++;
	}
	return (0);
}

int				ft_goto_endparam(char **str, char openchar)
{
	int		len;
	char	closechar;
	int		count_openchars;

	if (openchar == '"')
	{
		len = ft_gotochar(str, openchar);
		(*str)++;
		return (len);
	}
	closechar = select_closechar(openchar);
	if (!str || !*str || closechar == -1)
		return (0);
	else if (closechar == 0)
		return (ft_goto_endnumber(str));
	else
		return (find_end_param(str, openchar, closechar));
	return (0);
}
