/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:07:31 by dogata            #+#    #+#             */
/*   Updated: 2021/04/11 15:07:32 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prepare_split_command(t_ms *ms)
{
	ms->separate_flag = false;
	ms->single_quate_flag = false;
	ms->double_quate_flag = false;
	ms->back_slash_flag = false;
}
