/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:26:01 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/23 11:28:52 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_free_cmds(char **cmd_to_free)
{
    int i;
    if(cmd_to_free)
    {
        i = 0;
        while (cmd_to_free[i])
        {
            free(cmd_to_free[i]);
            i++;
        }
        free(cmd_to_free);
    }
}