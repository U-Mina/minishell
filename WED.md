
//TODO 0108

- fix exit_code
- finish *case_match*, *main*, and *builtin_or_exe*
-  




//Todo 0105

//idea: import s_astnode for execution of redirection (not finished yet)

- NEED TO FIX: **Exit_status**!!!!!!//debug

- builtin checker (switch between cases)
- work on redirect
- clean fts (garbage colloctor.c //done)
- 

**based on astnode结构写完redirection.c**

check the function about env (find/add/mod/del)
debug unset & cd!!! (make sure the PWD function works!!!)
think about *exit_code (necessary or not??? //not required by subject)


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

0101
- finished builtin

0102
- command exe
- redirection 
- pipes