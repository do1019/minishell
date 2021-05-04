/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:29:24 by dogata            #+#    #+#             */
/*   Updated: 2021/04/27 09:11:07 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lines(t_ms *ms)
{
	if (ms->semicolon_flag == true)
		free_td_array(&ms->sc_splited_line, 0);
	free_od_array(&ms->line, 0);
}
