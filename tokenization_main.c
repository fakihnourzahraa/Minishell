/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:00:00 by test              #+#    #+#             */
/*   Updated: 2025/09/05 21:00:00 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization/tokenization.h"

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

// Safe version - prints redirections for each command with NULL checks
void print_redirections_for_cmd(t_cmd *cmd, int cmd_num)
{
    t_redir *current;
    int i = 0;
    
    if (!cmd || !cmd->rd)
    {
        return;
    }
    
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

// SAFE version with extensive NULL checking
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
        
        // Safe cmd printing
        if (c->cmd)
            printf("  cmd: '%s'\n", c->cmd);
        else
            printf("  cmd: (null)\n");
        
        // Safe args printing
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
        
        // Safe redirection printing
        print_redirections_for_cmd(c, cmd_num);
        
        c = c->next;
        cmd_num++;
    }
}

// Updated test_string function with better error handling
void test_string(char *input)
{
    t_shell shell;
    
    if (!input)
    {
        printf("ERROR: input is NULL\n");
        return;
    }
    
    memset(&shell, 0, sizeof(t_shell)); 
    
    printf("Testing: \"%s\"\n", input);
    printf("=====================================\n");
    
    shell.in = input;
    
    int result = tokenize_line(&shell);
    if (result == -1)
    {
        printf("ERROR: Tokenization failed!\n\n");
        return;
    }
    
    print_tokens(&shell);
    
    // Add token validation check here
    if (check_tkns(shell, shell.tkns) == -1)
    {
        printf("SYNTAX ERROR: Invalid token sequence detected!\n\n");
        cleanup_t(&shell);
        cleanup_p(&shell);
        return;
    }
    
    printf("--- PARSING ---\n");
    parse(&shell, shell.tkns);
    
    // Use the safe printing function
    print_commands_safe(&shell);
    
    printf("--- END PARSING ---\n\n");
    cleanup_t(&shell);
    cleanup_p(&shell);
}
int main(void)
{

printf("\n=== CONCATENATION ===\n");
test_string("echo a'hi'b");
test_string("echo ''a''");
test_string("echo a'b'\"c\"d");

printf("\n=== REDIRECTIONS ===\n");
test_string("echo hello > file");
test_string("cat < file");
test_string("echo test >> file");
test_string("cat << EOF");

printf("\n=== REDIRECTIONS WITH QUOTES ===\n");
test_string(">a'hi'b");
test_string("<<a'hi'");
test_string("echo test >a''b");

printf("\n=== PIPES ===\n");
test_string("echo hi | cat");
test_string("ls | grep test | wc -l");

printf("\n=== PIPES WITH REDIRECTIONS ===\n");
test_string("cat < file | grep test > out");

    return 0;
}