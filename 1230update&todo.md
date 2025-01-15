*Changes and some undecided part (0115)*
- Undecided part
	1. env_u.c: 
			change all safe_malloc()/safe_join() to gc_malloc()/join()?
			costomize ft_strdup() to avoid error/null check everytime?
	2. memory management Q
			ft_realloc() in re-allocate mem after change **env (change/add/del var and val) --> need adjust to gc_malloc()? or write gc_realloc()??
	3. minishell.c (decision made after dession)
			*some changes in main()*!!!
				+ line 24 - 29: exit_status = 0, and pass &exit_status to init_data()
				+ line 25: comment out astnode *ast_root due to 5 var imit
				+ line 44: access and print ast_root via: data.ast_root = parse(tokens); print_ast(data.ast_root, 0);

- Changes
	1. builtins:
			all builtins adjustment and error-fixed
	2. execution:
			necessary functions adjusted to t_data struct
	3. logic in executing(in executor.c):!!!
			exec_at_top() into two sub_function:
						:if (type == PIPE) 
							--> exec_with_pipe() 
								 ---> then check if (!= PIPE)-> exec_after_top()
						:if (!= PIPE)
							--> exec_after_top()
	4. init_data():
			retrive *exit_status from main(), create **env
			Q: may put into minishell.c later (???)
			
    - Functions adapted to new struct (t_data)
		command_builtins.c :
				all builtins
		command_binary.c : 
				get_path(t_data *data);
		executor.c:
				exec_at_top() + exec_after_top() + exec_wuth_pipe();
				child_proc() --> restructured
				handle_redir_fd()
		redirec.c
			+ redir_in.c + redir_out.c + redir_heredoc.c
		pipe.c: -->restructured


check the function about env (find/add/mod/del)
debug unset & cd!!! (make sure the PWD function works!!!)
think about *exit_code (necessary or not??? //not required by subject)

check new implementation of AST -> AST printing check, and take into account redirect execution
gc change all the variables used for a gc_handle with static pointer to list initial
gc implement helper functions gc_split and gc_join, etc (out of the library)
change execution according to new AST structures
test execution
signals

TODO (update 11/01/2025)
gc:
- decide how to handle malloc fail (exit?? / return NULL and handle in next functions and check in every return value??)
- include gc_split, gc_join, etc
- change to gc_free_double pointer in parser??
make:
- create source folder and object folder to fully remove in the make fclean (rm -rf)


*1230update*
- remove exit_code(not required and currently no uasge)
- change header file, create s_table as data table
- finish all builtins (export needs 2 more fts)
- **changed env functions**
- finished sort env var
- finished export without arg


*TODO*
- update pwd ft
- export cmd with args 
- export with val & withoit val
- go back to prev finished builtin to modify to match new struct