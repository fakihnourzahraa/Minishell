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
        default: printf("UNKNOWN"); break;
    }
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

void print_tokens(t_shell *shell)
{
    t_token *current = shell->tkns;
    int i = 0;
    
    printf("\n--- TOKENS ---\n");
    while (current)
    {
        printf("Token %d: ", i++);
        print_token_type(current->type);
        printf(" | Content: '%s' | Quotes: %d\n", 
               current->s ? current->s : "(null)", 
               current->quotes);
        if (current->type == T_EOF)
            break;
        current = current->next;
    }
    printf("--- END TOKENS ---\n\n");
}

void print_redirections(t_shell *shell)
{
    t_redir *current;
    int i = 0;
    
    if (!shell->cmds || !shell->cmds->rd)
    {
        printf("--- NO REDIRECTIONS ---\n\n");
        return;
    }
    
    current = shell->cmds->rd;
    printf("--- REDIRECTIONS ---\n");
    while (current)
    {
        printf("Redir %d: ", i++);
        print_redir_type(current->type);
        printf(" | File: '%s' | FD: %d\n", 
               current->s ? current->s : "(null)", 
               current->fd);
        current = current->next;
    }
    printf("--- END REDIRECTIONS ---\n\n");
}

void free_tokens(t_shell *shell)
{
    t_token *current = shell->tkns;
    t_token *next;
    
    while (current)
    {
        next = current->next;
        if (current->s)
            free(current->s);
        free(current);
        current = next;
    }
    shell->tkns = NULL;
}

void free_redirections(t_shell *shell)
{
    if (!shell->cmds)
        return;
        
    t_redir *current = shell->cmds->rd;
    t_redir *next;
    
    while (current)
    {
        next = current->next;
        if (current->s)
            free(current->s);
        free(current);
        current = next;
    }
    shell->cmds->rd = NULL;
}

void free_command(t_shell *shell)
{
    if (!shell->cmds)
        return;
        
    if (shell->cmds->cmd)
        free(shell->cmds->cmd);
        
    if (shell->cmds->args)
    {
        for (int i = 0; shell->cmds->args[i]; i++)
            free(shell->cmds->args[i]);
        free(shell->cmds->args);
    }
    
}

void test_string(char *input)
{
    t_shell shell = {0};
    
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
    
    // Test parsing
    printf("--- PARSING ---\n");
    parse(&shell);
    
    if (shell.cmds)
    {
        printf("Command: %s\n", shell.cmds->cmd ? shell.cmds->cmd : "(null)");
        printf("Args:\n");
        if (shell.cmds->args)
        {
            for (int i = 0; shell.cmds->args[i]; i++)
            {
                printf("  [%d]: '%s'\n", i, shell.cmds->args[i]);
            }
        }
        
        // Print redirections
        print_redirections(&shell);
        
        // Test redirection parsing if you have the function
        printf("--- TESTING REDIRECTION PARSING ---\n");
        // Call your fill_r function for redirection tokens
        t_token *current = shell.tkns;
        while (current && current->type != T_EOF)
        {
            if (current->type == IN || current->type == OUT || 
                current->type == APPEND || current->type == HEREDOC)
            {
                printf("Processing redirection token: ");
                print_token_type(current->type);
                printf(" with file: %s\n", 
                       current->next && current->next->s ? current->next->s : "(missing)");
                fill_r(current, &shell);
            }
            current = current->next;
        }
        print_redirections(&shell);
    }
    else
    {
        printf("No command parsed\n");
    }
    printf("--- END PARSING ---\n\n");
    
    // Cleanup
}

int main(void)
{
    printf("TOKENIZATION & REDIRECTION TEST\n");
    printf("===============================\n\n");
    
    // // Basic command tests
    printf("=== BASIC COMMANDS ===\n");
    test_string("echo hello");
    test_string("ls -l");
    test_string("pwd");
    
    // Quote tests
    printf("=== QUOTE TESTS ===\n");
    test_string("echo 'hello world'");
    test_string("echo \"hello world\"");
    test_string("echo 'single' \"double\"");
    
    // Basic redirection tests
    printf("=== BASIC REDIRECTION TESTS ===\n");
    test_string("cat < file.txt");
    test_string("ls > output.txt");
    test_string("echo hello >> log.txt");
    test_string("cat << EOF");
    
    // // Command with arguments and redirections
    printf("=== COMPLEX REDIRECTION TESTS ===\n");
    test_string("ls -l > output.txt");
    test_string("cat file.txt > output.txt");
    test_string("echo hello world >> log.txt");
    test_string("grep pattern < input.txt > output.txt");
    
    // Multiple redirections
    printf("=== MULTIPLE REDIRECTION TESTS ===\n");
    test_string("cat < input.txt > output.txt");
    test_string("sort < data.txt >> sorted.txt");
    
    // Pipe tests (if you want to test those too)
    printf("=== PIPE TESTS ===\n");
    test_string("ls | grep .c");
    test_string("cat file.txt | grep hello");
    test_string("ls -l | wc -l");
    
    // Pipe with redirection
    printf("=== PIPE + REDIRECTION TESTS ===\n");
    test_string("ls | grep .c > result.txt");
    test_string("cat < input.txt | sort > output.txt");
    
    // Edge cases
    printf("=== EDGE CASE TESTS ===\n");
    test_string("echo > ");          // Missing filename
    test_string("< file.txt");       // No command
    test_string("echo < > file.txt"); // Invalid syntax
    test_string("   echo   hello   > output.txt   "); // Extra spaces
    test_string("");                 // Empty input
    
    // Error cases for redirection
    printf("=== ERROR CASE TESTS ===\n");
    test_string(">");               // Just redirection operator
    test_string("< >");             // Two operators
    test_string("echo >");          // Missing filename
    test_string(">> file.txt");     // No command before append
    
    // printf("All tests completed!\n");
    return 0;
}