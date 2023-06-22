/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:04:07 by lsadiq            #+#    #+#             */
/*   Updated: 2023/06/22 15:11:37 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_len_env(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char **ft_add_str_to_tab(char **tab, char *str)
{
    int i = 0;
    char **tmp;

    tmp = malloc(sizeof(char *) * (ft_len_env(tab) + 2));
    while (tab[i])
    {
        tmp[i] = ft_strdup(tab[i]);
        i++;
    }
    tmp[i] = ft_strdup(str);
    tmp[i + 1] = NULL;
    return (tmp);
}

char **clone_env(char **str)
{
    int i;
    char **new;

    i = 0;
    while (str[i])
        i++;
    new = ft_calloc(i + 1, sizeof(char *));
    i = 0;
    while (str[i])
    {
        new[i] = ft_strdup(str[i]);
        i++;
    }
    return (new);
}

void sort_env(char **str)
{
    int i = 0;
    int j = 0;
    char *tmp;

    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (ft_strcmp(str[i], str[j]) > 0)
            {
                tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

char **print_export(char **str)
{
    int i = 0;
    int j = 0;

    while (str[i])
    {
        if (!ft_strchr(str[i], '='))
            printf("declare -x %s\n", str[i]);
        else
        {
            j = 0;
            printf("declare -x ");
            while (str[i][j])
            {
                printf("%c", str[i][j]);
                if (str[i][j] == '=')
                    break;
                j++;
            }
            j++;
            printf("%c%s%c\n", '"', str[i] + j, '"');
        }
        i++;
    }
    return (str);
}
// void ft_add_to_value(char *str, char *new)
// {
// 	int i = 0;
// 	int j = 0;
// 	char *tmp;

// 	while(str[i])
// 	{
// 		if(str[i] == '=')
// 			break;
// 		i++;
// 	}
// 	i++;
// 	tmp = malloc(sizeof(char) * ft_strlen(str) + ft_strlen(new) + 1);
// 	while(str[j])
// 	{
// 		tmp[j] = str[j];
// 		j++;
// 	}
// 	while(new[j])
// 	{
// 		tmp[i] = new[j];
// 		i++;
// 		j++;
// 	}
// 	tmp[i] = '\0';
// 	free(str);
// 	str = ft_strdup(tmp);
// 	free(tmp);
// }

// void	add_to_value(char **str, char *new)
// {
// 	int i=0;
// 	char *tmp;

// 	while(str[i])
// 	{
// 		if(ft_strchr(str[i], '+'))
// 			if(ft_strchr(str[i], '='))
// 				break;
// 		i++;
// 	}
// 	i++;
// 	while(str[i])
// 	{
// 		tmp[i] = str[i];
// 		if(str[i + 1] == '\0')
// 			tmp[i] = ft_strjoin(tmp, new);
// 		i++;
// 	}
// 	tmp[i] = '\0';
// 	free(tmp[i]);
// }

int ft_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        return (1);
    return (0);
}

char **ft_replace_env(char **str, char *new)
{
    int i = 0;
    int j = 0;
    char **tmp;

    tmp = malloc(sizeof(char *) * (ft_len_env(str) + 1));
    while (new[i])
    {
        if (new[i] == '=')
            break;
        i++;
    }
    while (str[j])
    {
        if (ft_strncmp(str[j], new, i) == 0)
        {
            tmp[j] = ft_strdup(new);
            // free(str[j]);
            // free(new);
        }
        else
            tmp[j] = ft_strdup(str[j]);
        j++;
    }
    tmp[j] = NULL;
    // free(str);
    return (tmp);
}

int ft_does_it_exist(char **str, char *new)
{
    int i = 0;

    while (new[i])
    {
        if (new[i] == '=')
            break;
        i++;
    }
    int j = 0;
    while (str[j])
    {
        if (!ft_strncmp(str[j], new, i))
        {
            if (str[j][i] == '=' || !str[j][i])
                return (1);
        }
        j++;
    }
    return (0);
}

int ft_export(t_shell *shell)
{
    int i = 1;
    t_shell *tmp = shell;

    sort_env(tmp->env);
    if (!tmp->ms->stack[i])
        tmp->exp = print_export(tmp->env);
    while (tmp->ms->stack[i])
    {
        if (ft_alpha(tmp->ms->stack[i][0]))
        {
            if (!ft_does_it_exist(tmp->env, tmp->ms->stack[i]))
                tmp->env = ft_add_str_to_tab(tmp->env, tmp->ms->stack[i]);
            else
                tmp->env = ft_replace_env(tmp->env, tmp->ms->stack[i]);
        }
        else      
            printf("minishell: export: `%s': not a valid identifier\n", tmp->ms->stack[i]);
        g_data.exit_s = 1;
        i++;
    }
    // g_data.exit_s = 0;
    return (g_data.exit_s);
}
