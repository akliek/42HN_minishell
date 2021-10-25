# 42HN_minishell
Summary:

The objective of this project is to create a simple shell.

Foreword:

The existence of shells is linked to the very existence of IT. At the time, all coders agreed that communicating with a computer using aligned 1/0 switches was seriously irritating. It was only logical that they came up with the idea to communicate with
a computer using interactive lines of commands in a language somewhat close to english.

Links:

Wikipedia about shell: https://en.wikipedia.org/wiki/Shell_script

Subject PDF: https://github.com/akliek/42HN_minishell/blob/master/en.subject.pdf

Note:

Readline libraries required. MacOS only supported.

# Clone:
Open a terminal and run following command:
```
git clone <repository url>
```
# Installation:

If you don't have readline libraries firstly need to install them. Open your terminal and run following commands:
```
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" 2> /dev/null
```
```
brew install readline
```
After that go to created repository and run following command:
```
make
```
# Run
After installation run following command:
```
./minishell
```
# Usage
```
      - History
      - Searching and launching the right executable
      - Implemented the builtins:
            • echo with option -n
            • cd with only a relative or absolute path
            • pwd with no options
            • export with no options
            • unset with no options
            • env with no options or arguments
            • exit with no options
      - ’ inhibit all interpretation of a sequence of characters
      - " inhibit all interpretation of a sequence of characters except for $
      - Redirections:
            • < should redirect input
            • > should redirect output
            • “<<” read input from the current source until a line containing only the de- limiter is seen
            • “>>” should redirect output with append mode
      - Pipes
      - Environment variables
      - Exit status
      - Signals:
            • ctrl-C
            • ctrl-D
            • ctrl-\
      - Other commads work only with default inputs      
```

