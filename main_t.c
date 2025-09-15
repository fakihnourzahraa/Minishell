/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:54:50 by nour              #+#    #+#             */
/*   Updated: 2025/09/15 19:55:18 by nour             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ----------------- Your Structs -----------------
typedef struct s_env
{
    char *name;
    char *val;
    bool avail;
    struct s_env *next;
} t_env;

typedef enum e_r_type { R_IN, R_OUT, R_APPEND, R_HEREDOC } t_r_type;

typedef struct s_redir
{
    char *s;
    t_r_type type;
    int fd;
    struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
    char *cmd;
    char **args;
    t_redir *rd;
    struct s_cmd *next;
} t_cmd;

typedef struct s_shell
{
    t_env *env;
    t_cmd *cmds;
    char *in;
} t_shell;

// ----------------- Helper Functions -----------------
char *ft_strdup(const char *s)
{
    if (!s) return NULL;
    size_t len = strlen(s);
    char *dup = malloc(len + 1);
    if (dup) strcpy(dup, s);
    return dup;
}

char *ft_strndup(const char *s, size_t n)
{
    char *dup = malloc(n + 1);
    if (!dup) return NULL;
    strncpy(dup, s, n);
    dup[n] = '\0';
    return dup;
}

// ----------------- ENV Functions -----------------
t_env *create_env_node_from_str(char *str)
{
    t_env *node = malloc(sizeof(t_env));
    if (!node) return NULL;

    char *equal = strchr(str, '=');
    if (equal)
    {
        node->name = ft_strndup(str, equal - str);
        node->val = ft_strdup(equal + 1);
    }
    else
    {
        node->name = ft_strdup(str);
        node->val = ft_strdup("");
    }
    node->avail = true;
    node->next = NULL;
    return node;
}

t_env *init_env_from_envp(char **envp)
{
    t_env *head = NULL, *curr = NULL;
    for (int i = 0; envp[i]; i++)
    {
        t_env *node = create_env_node_from_str(envp[i]);
        if (!head) head = node;
        else curr->next = node;
        curr = node;
    }
    return head;
}

void free_env_list(t_env *env)
{
    while (env)
    {
        t_env *tmp = env->next;
        free(env->name);
        free(env->val);
        free(env);
        env = tmp;
    }
}

// ----------------- REDIR & CMD Functions -----------------
t_redir *create_redir(t_r_type type, char *file)
{
    t_redir *r = malloc(sizeof(t_redir));
    r->type = type;
    r->s = ft_strdup(file);
    r->fd = -1;
    r->next = NULL;
    return r;
}

t_cmd *create_cmd_safe(char **args, t_redir *rd)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    cmd->cmd = ft_strdup(args[0]);
    cmd->args = args;
    cmd->rd = rd;
    cmd->next = NULL;
    return cmd;
}

void free_redir_list(t_redir *r)
{
    while (r)
    {
        t_redir *tmp = r->next;
        free(r->s);
        free(r);
        r = tmp;
    }
}

void free_cmd_chain_complete(t_cmd *cmd)
{
    while (cmd)
    {
        t_cmd *tmp = cmd->next;
        free(cmd->cmd);
        if (cmd->args)
        {
            for (int i = 0; cmd->args[i]; i++)
                free(cmd->args[i]);
            free(cmd->args);
        }
        free_redir_list(cmd->rd);
        free(cmd);
        cmd = tmp;
    }
}

// ----------------- PARSE & EXECUTE SAFE -----------------
char **ft_split(const char *str, char delim)
{
    // Minimal split for testing: split by single space
    int count = 0;
    for (const char *s = str; *s; s++)
        if (*s == delim) count++;
    char **res = malloc(sizeof(char *) * (count + 2));
    int i = 0;
    const char *start = str;
    for (const char *s = str; ; s++)
    {
        if (*s == delim || *s == '\0')
        {
            size_t len = s - start;
            char *tok = malloc(len + 1);
            strncpy(tok, start, len);
            tok[len] = '\0';
            res[i++] = tok;
            start = s + 1;
        }
        if (*s == '\0') break;
    }
    res[i] = NULL;
    return res;
}

void free_split_safe(char **split)
{
    if (!split) return;
    for (int i = 0; split[i]; i++) free(split[i]);
    free(split);
}

// Minimal parse function
void parse_and_execute_safe(t_shell *shell, char *input)
{
    char **tokens = ft_split(input, ' ');

    int argc = 0;
    while (tokens[argc]) argc++;

    char **args = malloc(sizeof(char *) * (argc + 1));
    for (int i = 0; i < argc; i++)
        args[i] = ft_strdup(tokens[i]);
    args[argc] = NULL;

    t_redir *r = NULL; // no redirs in this test
    t_cmd *cmd = create_cmd_safe(args, r);
    shell->cmds = cmd;

    // Normally execute here, but we skip execution

    // Free memory
    free_cmd_chain_complete(cmd);
    shell->cmds = NULL;
    free_split_safe(tokens);
}

// ----------------- INIT & CLEANUP -----------------
void init_shell(t_shell *shell, char **envp)
{
    shell->env = init_env_from_envp(envp);
    shell->cmds = NULL;
    shell->in = NULL;
}

void cleanup_shell(t_shell *shell)
{
    if (shell->env) free_env_list(shell->env);
}

// ----------------- MAIN -----------------
int main(void)
{
    t_shell shell;
    char *envp[] = {"PATH=/usr/bin", "HOME=/home/user", "USER=guest", NULL};
    init_shell(&shell, envp);

    parse_and_execute_safe(&shell, "echo hello world");
    parse_and_execute_safe(&shell, "ls -l /tmp");

    cleanup_shell(&shell);
    return 0;
}

