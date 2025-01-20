/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_testing_stuff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumoreno < aumoreno@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:23:41 by aumoreno          #+#    #+#             */
/*   Updated: 2025/01/18 13:26:15 by aumoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    printf("%d\n", argc);

    printf("Command-line arguments:\n");
    for (int i = 0; i < argc; i++)
    {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    printf("Environment variables:\n");
    for (int i = 0; envp[i] != NULL; i++)
    {
        printf("Variable %d: %s\n", i, envp[i]);
    }
    return 0;
}