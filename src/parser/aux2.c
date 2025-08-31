/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 00:28:41 by fheaton-          #+#    #+#             */
/*   Updated: 2025/08/31 11:37:08 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_false(bool *in_q, bool *in_dq, bool *in_var, bool *skip)
{
	*(in_q) = false;
	*(in_dq) = false;
	*(in_var) = false;
	*(skip) = false;
}
