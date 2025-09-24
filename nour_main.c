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
            printf("  Args:\n");
            for (int i = 0; c->args[i]; i++)
            {
                printf("    [%d]: '%s'", i, c->args[i] ? c->args[i] : "(null)");                
                printf("\n");
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
    if (check_tkns(shell.tkns) == -1)
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
    printf("TOKENIZATION & REDIRECTION TEST\n");
    printf("===============================\n\n");
    
  //  Basic command tests
//     printf("=== BASIC COMMANDS ===\n");
   //  test_string(" \"\" \"\" \"\"\"\" ");
    test_string("echo h\"\"");
//     test_string("pwd");
    
//  // Quote tests
//     printf("=== QUOTE TESTS ===\n");
//     test_string("echo 'hello world'");
   // test_string("echo \"hello world\"");
    // test_string("echo 'single' \"double\"");
    
//     // Basic redirection tests
//     printf("=== BASIC REDIRECTION TESTS ===\n");
//     test_string("cat < file.txt");
//     test_string("ls > output.txt");
//     test_string("echo hello >> log.txt");
//     test_string("cat << EOF");
    
//     // // Command with arguments and redirections
//     printf("=== COMPLEX REDIRECTION TESTS ===\n");
//     test_string("ls -l > output.txt");
//     test_string("cat file.txt > output.txt");
//     test_string("echo hello world >> log.txt");
//     test_string("grep pattern < input.txt > output.txt");
    
//     // Multiple redirections
//     printf("=== MULTIPLE REDIRECTION TESTS ===\n");
// 	test_string("cat<input.tx");
//     test_string("cat < input.txt > output.txt");
//     test_string("sort < data.txt >> sorted.txt");
    
//     // Pipe tests (if you want to test those too)
//     printf("=== PIPE TESTS ===\n");
//    test_string("ls | grep .c");
//     test_string("cat file.txt | grep hello");
//     test_string("ls -l | wc -l");
    
//     // Pipe with redirection
//     printf("=== PIPE + REDIRECTION TESTS ===\n");
// test_string("ls | grep .c | wc -l");
//    test_string("ls | grep .c > result.txt | grep .y > a.txt");
//     test_string("echo hello | echo bye");
//     // Edge cases
//     printf("=== EDGE CASE TESTS ===\n");
//    test_string("cat file.txt | grep error");
//    test_string("echo > ");          // Missing filename
//    test_string("< file.txt");       // No command
//      test_string("echo < > file.txt"); // Invalid syntax
//      test_string("   echo   hello   > output.txt   "); // Extra spaces
//      test_string("");                 // Empty input
    
//     // Error cases for redirection
//     printf("=== ERROR CASE TESTS ===\n");
//     test_string(">");               // Just redirection operator
//     test_string("< >");             // Two operators
//     test_string("echo >");          // Missing filename
//     test_string(">> file.txt");     // No command before append
    
// 	 test_string("|");                    // Just pipe
//     test_string("| grep hello");         // Starts with pipe
//     test_string(">");                    // Just redirection
//     test_string("> file.txt");          // Starts with redirection
//     test_string("<");                    // Just input redirection
//     test_string("< file.txt");          // Starts with input redirection
//     test_string(">>");                   // Just append
//     test_string(">> file.txt");         // Starts with append
//     test_string("<<");                   // Just heredoc
//     test_string("<< EOF");   

// 	 test_string("echo hello |");         // Ends with pipe
//     test_string("cat file.txt >");       // Ends with output redirection
//     test_string("ls -l <");              // Ends with input redirection
//     test_string("echo hello >>");        // Ends with append
//     test_string("cat <<");               // Ends with heredoc
//     test_string("echo | ls |"); 

// 	    test_string("cat > > file.txt");     // Double output redirection
//     test_string("cat < < file.txt");     // Double input redirection
//      test_string("cat >> >> file.txt");   // Double append
//      test_string("cat << << EOF");        // Double heredoc
// test_string("echo > | grep");        // Double pipe
//      test_string("cat > < file.txt");     // Mixed redirections
//     test_string("cat < > file.txt");     // Mixed redirections
//      test_string("cat >> < file.txt");    // Mixed redirections
//   test_string("cat | > file.txt");     // Pipe then redirection
//    test_string("cat | < file.txt");     // Pipe then input redirection
//    test_string("cat | >> file.txt");    // Pipe then append
//     test_string("cat | 'EOF' ");  
//      printf("All tests completed!\n");
     return 0;
}