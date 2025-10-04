  //  Basic command tests
//     printf("=== BASIC COMMANDS ===\n");
   //  test_string(" \"\" \"\" \"\"\"\" ");
    // test_string("echo h\"\"");
    // test_string("echo hi \"\" b");
    test_string("a'hi'");
	test_string("<<a'hi'");
	
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