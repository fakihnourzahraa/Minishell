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
    // printf("--- PARSING ---\n");
    // parse(&shell);
    
    // if (shell.cmds)
    // {
    //     printf("Command: %s\n", shell.cmds->cmd ? shell.cmds->cmd : "(null)");
    //     printf("Args:\n");
    //     if (shell.cmds->args)
    //     {
    //         for (int i = 0; shell.cmds->args[i]; i++)
    //         {
    //             printf("  [%d]: '%s'\n", i, shell.cmds->args[i]);
    //         }
    //     }
    // }
    // else
    // {
    //     printf("No command parsed\n");
    // }
    // printf("--- END PARSING ---\n\n");
    
    // // Cleanup
    // free_tokens(&shell);
    // if (shell.cmds)
    // {
    //     if (shell.cmds->cmd)
    //         free(shell.cmds->cmd);
    //     if (shell.cmds->args)
    //     {
    //         for (int i = 0; shell.cmds->args[i]; i++)
    //             free(shell.cmds->args[i]);
    //         free(shell.cmds->args);
    //     }
    //     free(shell.cmds);
    // }
}

int main(void)
{
    printf("TOKENIZATION TEST\n");
    printf("=================\n\n");
    
    // Basic tests
    test_string("echi hel  | lp");
    // test_string("echo 'hello world'");
    // test_string("echo \"hello world\"");
    // test_string("ls -l");
    // test_string("cat < file.txt");
    // test_string("ls > output.txt");
    // test_string("echo hello >> log.txt");
    // test_string("cat << EOF");
    // test_string("ls | grep .c");
    // test_string("echo hello | wc -l");
    
    // // Edge cases
    // test_string("echo");
    // test_string("   echo   hello   ");
    // test_string("");
    
    printf("All tests completed!\n");
    return 0;
}
