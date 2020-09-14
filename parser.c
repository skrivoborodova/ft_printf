/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oearlene <oearlene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:19:45 by oearlene          #+#    #+#             */
/*   Updated: 2020/09/14 16:29:40 by oearlene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_flags(t_data *ptr)
{
	while (ft_strchr("#0-+ ", ptr->f_copy[ptr->i]))
	{
		if (ptr->f_copy[ptr->i] == '#')
			ptr->flags->hash = 1;
		else if (ptr->f_copy[ptr->i] == '0')
			ptr->flags->zero = 1;
		else if (ptr->f_copy[ptr->i] == '-')
			ptr->flags->minus = 1;
		else if (ptr->f_copy[ptr->i] == '+')
			ptr->flags->plus = 1;
		else if (ptr->f_copy[ptr->i] == ' ')
			ptr->flags->space = 1;
		else if (ptr->f_copy[ptr->i] == '\0')
			break ;
	//	else
	//		printf_error("Parse Flags fucked up.");
		ptr->i++;
	}
	//if (!ptr->f_print)
	//	printf_error("Invalid format. (After Flags)");
}

void	parse_min_width(t_data *ptr)
{
	char *str;

	str = &(ptr->f_copy[ptr->i]);
	// add '*.'
	ptr->conv->min_width = ft_atoi(str);
	while (ft_isdigit(ptr->f_copy[ptr->i]))
		ptr->i++;
//	if (!ptr->f_print)
	//	printf_error("Invalid format. (After Min Width)");
}

void	parse_precision(t_data *ptr)
{
	char *str;

	if (ptr->f_copy[ptr->i] != '.')
		return ;
	ptr->i++;
	str = &(ptr->f_copy[ptr->i]);
	// add '.*'
	ptr->conv->precision = ft_atoi(str);
	ptr->conv->prec_set = 1;
	while (ft_isdigit(ptr->f_copy[ptr->i]))
		ptr->i++;
//	if (!ptr->f_print)
	//	printf_error("Invalid format. (After Precision)");
}

void	parse_length(t_data *ptr)
{
	char *str;
	if (!ft_strchr("hl", ptr->f_copy[ptr->i]))
		return ;
	str = &(ptr->f_copy[ptr->i]);
	if (ft_strncmp(str, "hh", 2) == 0)
	{
		ptr->length = HH;
		ptr->i += 2;
	}
	if (ft_strncmp(str, "ll", 2) == 0)
	{
		ptr->length = LL;
		ptr->i += 2;
	}
	else if (ptr->f_copy[ptr->i] == 'h')
		ptr->length = H;
	else if (ptr->f_copy[ptr->i] == 'l')
		ptr->length = L;
	ptr->i++;
}

void	parse_conversion(t_data *ptr)
{
	parse_flags(ptr);
	if (ft_strchr(",;:_", ptr->f_copy[ptr->i]))
	{
		ptr->conv->sep = ptr->f_copy[ptr->i];
		ptr->i++;
	}
//	if (!ptr->f_print)
//		printf_error("Invalid format. (After Separator)");
	parse_min_width(ptr);
	parse_precision(ptr);
	parse_length(ptr);
//	if (!ptr->f_print)
//		printf_error("Invalid format. (After Length)");
	ptr->conv->type = ptr->f_copy[ptr->i];
}