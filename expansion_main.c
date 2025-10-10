/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 22:14:23 by nfakih            #+#    #+#             */
/*   Updated: 2025/10/10 19:36:43 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization/tokenization.h"
#include "expansion/expansion.h"  // Add this

void print_token_type(t_token_type type)
{
    switch(type) {
        case WORD: printf("WORD"); break;
        case PIPE: printf("PIPE"); break;
        case IN: printf("IN"); break;
        case OUT: printf("OUT"); break;
        case APPEND: printf("APPEND"); break;
        case HEREDOC: printf("HEREDOC"); break;
        case T_EOF: printf("T_EOF"); break;
        case EMPTY: printf("EMPTY"); break;
        default: printf("UNKNOWN"); break;
    }
}

void print_tokens(t_shell *shell)
{
    t_token *current = shell->tkns;
    int i = 0;

    printf("\n--- TOKENS ---\n");
    while (current)
    {
        printf("Token %d: ", i++);
        print_token_type(current->type);
        printf(" | Content: '%s' | Quotes: %d | Space: %s\n", 
               current->s ? current->s : "(null)", 
               current->quotes,
               current->space ? "true" : "false");
        if (current->type == T_EOF)
            break;
        current = current->next;
    }
    printf("--- END TOKENS ---\n\n");
}

void print_redir_type(t_r_type type)
{
    switch(type) {
        case R_IN: printf("R_IN"); break;
        case R_OUT: printf("R_OUT"); break;
        case R_APPEND: printf("R_APPEND"); break;
        case R_HEREDOC: printf("R_HEREDOC"); break;
        default: printf("UNKNOWN_REDIR"); break;
    }
}

void print_redirections_for_cmd(t_cmd *cmd, int cmd_num)
{
    t_redir *current;
    int i = 0;
    
    if (!cmd || !cmd->rd)
        return;
    
    current = cmd->rd;
    printf("--- REDIRECTIONS FOR CMD %d ---\n", cmd_num);
    while (current)
    {
        printf("Redir %d: ", i++);
        print_redir_type(current->type);
        printf(" | File: '%s' | FD: %d\n", 
               current->s ? current->s : "(null)", 
               current->fd);
        current = current->next;
    }
}

void print_commands_safe(t_shell *shell)
{
    t_cmd *c;
    int cmd_num = 0;
    
    if (!shell)
    {
        printf("ERROR: shell is NULL\n");
        return;
    }
    
    if (!shell->cmds)
    {
        printf("No commands found (shell->cmds is NULL)\n");
        return;
    }
    
    c = shell->cmds;
    while (c)
    {
        printf("Command %d:\n", cmd_num);
        
        if (c->cmd)
            printf("  cmd: '%s'\n", c->cmd);
        else
            printf("  cmd: (null)\n");
        
        if (c->args)
        {
            for (int i = 0; c->args[i]; i++)
            {
                printf("  [%d]: '%s' | Space: %s\n",
                       i, 
                       c->args[i], 
                       (c->space && c->space[i]) ? "true" : "false");
            }
        }
        else
        {
            printf("  Args: (null)\n");
        }
        
        print_redirections_for_cmd(c, cmd_num);
        
        c = c->next;
        cmd_num++;
    }
}

void test_string(char *input, t_shell *shell)
{
    if (!input)
    {
        printf("ERROR: input is NULL\n");
        return;
    }
    
    printf("Testing: \"%s\"\n", input);
    printf("=====================================\n");
    
    shell->in = input;
    
    int result = tokenize_line(shell);
    if (result == -1)
    {
        printf("ERROR: Tokenization failed!\n\n");
        return;
    }
    
    print_tokens(shell);
    
    if (check_tkns(shell->tkns) == -1)
    {
        printf("SYNTAX ERROR: Invalid token sequence detected!\n\n");
        cleanup_t(shell);
        cleanup_p(shell);
        return;
    }
    
    printf("--- PARSING ---\n");
    parse(shell, shell->tkns);
    print_commands_safe(shell);
    printf("--- END PARSING ---\n\n");
    
    printf("--- AFTER EXPANSION ---\n");
    iterate_expansion(shell);  // NEW: Expand variables
    print_commands_safe(shell);  // Print again after expansion
    printf("--- END EXPANSION ---\n\n");
    
    cleanup_t(shell);
    cleanup_p(shell);
}

int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    
    (void)argc;
    (void)argv;
    
    // Initialize shell with environment
    memset(&shell, 0, sizeof(t_shell));
    shell.env = init_env_from_envp(envp);
    shell.exit_status = 0;

    // printf("\n=== CONCATENATION ===\n");
    // test_string("echo a'hi'b", &shell);
    // test_string("echo ''a''", &shell);
    // test_string("echo a'b'\"c\"d", &shell);

    // // printf("\n=== REDIRECTIONS ===\n");
    // // test_string("echo hello > file", &shell);
    // // test_string("cat < file", &shell);
    // // test_string("echo test >> file", &shell);
    // // test_string("cat << EOF", &shell);

    // printf("\n=== REDIRECTIONS WITH QUOTES ===\n");
    // test_string(">a'hi'b", &shell);
    // test_string("<<a'hi'", &shell);
    // test_string("echo test >a''b", &shell);

    // printf("\n=== PIPES ===\n");
    // test_string("echo hi | cat", &shell);
    // test_string("ls | grep test | wc -l", &shell);

    // printf("\n=== PIPES WITH REDIRECTIONS ===\n");
    // test_string("cat < file | grep test > out", &shell);

    printf("\n=== EXPANSION TESTS ===\n");
    test_string("echo 'h'", &shell);
    // test_string("echo '$HOME'", &shell);
    // test_string("echo \"$HOME\"", &shell);
    // test_string("echo $HOME/test", &shell);
    // test_string("echo $?", &shell);
    // test_string("echo test >$HOME/file", &shell);

    // Cleanup
    free_env_list(shell.env);
    
    return 0;
}