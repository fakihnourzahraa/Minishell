/* Fixed main_test.c */
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
        default: printf("UNKNOWN(%d)", type); break;
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
    free_tokens(&shell);
    printf("\n");
}

int main(void)
{
    printf("TOKENIZATION TEST\n");
    printf("=================\n\n");
    
    // Basic tests
    test_string("echo hello");
    test_string("echo 'hello world'");
    test_string("echo \"hello world\"");
    test_string("ls -l");
    test_string("cat < file.txt");
    test_string("ls > output.txt");
    test_string("echo hello >> log.txt");
    test_string("cat << EOF");
    test_string("ls | grep .c");
    test_string("echo hello | wc -l");
    
    // Edge cases
    test_string("echo");
    test_string("   echo   hello   ");
    test_string("");
    test_string("echo 'unclosed quote");  // Error case
    
    printf("All tests completed!\n");
    return 0;
}