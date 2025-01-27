**0127 TEST**
	|ls |ls
	|ls 
	bash: bash: syntax error near unexpected token `|'
	minishell: stuck
	old parsing method: Pipe synchronization failed: Invalid argument

	ls > out >> out1 >out3 | cat out1
	bash: create out123
	ms: cat: out1: No such file or directory
	old_ms: work as bash

	TEST 44:   /Users/ewu/42_minishell_tester/tester.sh: line 217: 53595 Done                    echo -n "$INPUT"
	53596 Abort trap: 6           | $MINISHELL_PATH/$EXECUTABLE 2> tmp_err_minishell > tmp_out_minishell
	 
	echo '              $USER          '
		STD_OUT: ❌  STD_ERR: ✅  EXIT_CODE: ❌ [ minishell(134)  bash(0) ]  
	
Prompt>exit
exit
minishell(55797,0x10dfc8dc0) malloc: *** error for object 0x7f007fbb6dc0: pointer being freed was not allocated
minishell(55797,0x10dfc8dc0) malloc: *** set a breakpoint in malloc_error_break to debug
zsh: abort      ./minishell

*NOT sure how to deal with: cd "nonexist" 2>/dev/null
		ex_st becomes 1 bc '2>/dev/null' is successfully handled
		while bash shows 1 to indicate cd is not success











**mstest m**
	*O = our output*
	*B = bash output*

	echo \\\\$USER
	 	b: \\ewu
		o: \\\\ewu
	echo \\\\\$USER
		b: \\$USER
		o:\\\\\ewu
	echo ''''''''''$USER''''''''''
		b: ewu
		o: Unclosed quotes are not handled in this minishell: Undefined error: 0
			'''ewu'''
	echo ''h'''
		o:  Unclosed quotes are not handled in this minishell: Undefined error: 0
			Unclosed quotes are not handled in this minishell: Undefined error: 0
			h'//debug: error msg showed 2 times, and printed (h')
		
	echo ''''''''''h'''''''''' //check: eliminate of quotes
		o: '''h'''
		b: h
	echo $PWD$noexist$USER //check: $+nonexist/nonextendable var should not be printed
		b: /Users/ewuewu
		o: /Users/ewu/03_minishell$noexistewu
		Prompt>ECHO $PWD $NONEXIST
			/Users/ewu/mini_test/minishell
			Prompt>ECHO $PWD$NONEXIST
			/Users/ewu/mini_test/minishell$NONEXIST

	echo ""$?""
		minishell: syntax error: Undefined error: 0
		bash: 0
	echo ''$?''"42"
		zsh: segmentation fault  ./minishell
		bash: 042
	echo "3"'3'
		minishell: syntax error: Undefined error: 0
		bash: 33
	echo ""'$USER'""
		minishell: syntax error: Undefined error: 0
	echo "''$USER''"
		''ewu''
	echo "'"'$USER'"'"
		''$USER""

		"'"'hello'"'"