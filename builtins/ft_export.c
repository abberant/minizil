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

t_env   *ft_set(char *str)
{
    t_env *env;
    int i;
    int j;

    i = 0;
    j = 0;
    env = malloc(sizeof(t_env));
    while(str[i])
    {
        if(str[i] == '=')
        {
            if (str[i - 1] == '+')
                j = i - 1;
            else
                j = i;
            break;
        }
        i++;
    }
    env->name = cancel_quotes(ft_substr(str, 0, j));
    env->value = cancel_quotes(ft_substr(str, i + 1, ft_strlen(str) - i - 1));
    env->next = NULL;
    return (env);
}

void    ft_free_env(t_env *env)
{
    free(env->name);
    free(env->value);
    free(env);
}

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
    t_env   *env;
    char    *holder;

    tmp = malloc(sizeof(char *) * (ft_len_env(tab) + 2));
    while (tab[i])
    {
        tmp[i] = ft_strdup(tab[i]);
        i++;
    }
    env = ft_set(str);
    holder = ft_strjoin(env->name, "=");
    tmp[i] = ft_strjoin(holder, env->value);
    free(holder);
    ft_free_env(env);
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

int ft_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        return (1);
    return (0);
}

char *ft_replace_env(char *str, char *new)
{
    t_env *env;
    t_env *env2;
    char    *holder;
    char    *holder2;
    
    env = ft_set(str);
    env2 = ft_set(new);
    holder = ft_strjoin(env->name, "=");
    holder2 = ft_strjoin(holder, env2->value);
    free(holder);
    free(str);
    ft_free_env(env);
    ft_free_env(env2);
    return (holder2);
}

int ft_does_it_exist(char **str, char *new)
{
    int i = 0;

    while (new[i])
    {
        if (new[i] == '=' || new[i] == '+')
            break;
        i++;
    }
    int j = 0;
    while (str[j])
    {
        if (!ft_strncmp(str[j], new, i))
        {
            if (str[j][i] == '=' || !str[j][i])
                return (j + 1);
        }
        j++;
    }
    return 0;
}
int ft_check(char *str)
{
    int i = 0;

    while(str[i])
    {
        if (str[i] == '+' && str[i + 1] == '=')
            return (1);
        if ((str[i] == '+' && str[i + 1] != '=') || str[i] == '-')
        {
            g_data.exit_s = 1;
            return (2);
        }
        if (str[i] == '=')
            break ;
        i++;
    }
    return (0);
}

char    *ft_exp_append(char *old, char *new, char *holder, char *holder2)
{
    char *holder3;
    t_env *env;
    t_env *env2;

    env = ft_set(old);
    env2 = ft_set(new);
    holder = ft_strjoin(env->value, env2->value);
    holder2 = ft_strjoin(env->name, "=");
    holder3 = ft_strjoin(holder2, holder);
    free(holder);
    free(holder2);
    free(old);
    ft_free_env(env);
    ft_free_env(env2);
    return(holder3);
}
int ft_export(t_shell *shell)
{
    int i = 1;
    int j;

    t_shell *tmp = shell;

    sort_env(tmp->env);
    if (!tmp->ms->stack[i])
        tmp->exp = print_export(tmp->env);
    while (tmp->ms->stack[i])
    {
        if (ft_alpha(tmp->ms->stack[i][0]) && ft_check(tmp->ms->stack[i]) != 2)
        {
            j = ft_does_it_exist(tmp->env, tmp->ms->stack[i]);
            if (!j)
                tmp->env = ft_add_str_to_tab(tmp->env, tmp->ms->stack[i]);
            else if (ft_check(tmp->ms->stack[i]))
                tmp->env[j - 1] = ft_exp_append(tmp->env[j - 1], tmp->ms->stack[i], NULL, NULL);
            else
                tmp->env[j - 1] = ft_replace_env(tmp->env[j - 1], tmp->ms->stack[i]);
        }
        else      
            printf("minishell: export: `%s': not a valid identifier\n", tmp->ms->stack[i]);
        g_data.exit_s = 1;
        i++;
    }
    // g_data.exit_s = 0;
    return (g_data.exit_s);
}
