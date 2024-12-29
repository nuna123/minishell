# **MINISHELL**
> **by Naomi Roth**
> GitHub: [nuna123](https://github.com/nuna123) | edX: nuna2209

---
Minishell is a simplified shell written in C that supports essential shell functionalities. execution of commands, pipelines, redirection, working directory, history and environment variables usage.
Working on minishell gave me a deeper understanding of process management, file descriptor handling, memory management and more.

---
## **About**
- Written in C, inspired by bash.
- Has history function (implemented with GNU readline library)
- Uses the environment PATH variable to find and run executables
- correct handling of 'single' and "double" quotes swith variables
- usage of redirections , into/out of files, append, HEREDOC
- implementation of pipes (|), status code ($?)
- implementation of OR (||) and AND (&&) operators
-handling of signals - ctrl-C, ctrl-D and ctrl-\ as bash
- built in functions:
	- echo
	- cd
	- pwd
	- export
	- unset
	- env
	- exit
