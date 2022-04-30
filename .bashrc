#!/bin/bash
#region Helper Functions
SHELL_NAME="simple_shell"

build () { gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o $SHELL_NAME; }
build_dbg () { gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -g -ggdb3 *.c -o $SHELL_NAME.dbg; }
run () { ./$SHELL_NAME; }
install () {
	mv ./$SHELL_NAME /usr/bin;
	tar -czvf $SHELL_NAME.1.gz man_1_simple_shell;
	mv ./$SHELL_NAME.1.gz /usr/share/man/man1/$SHELL_NAME.1.gz;
}
viewman () { man ./man_1_simple_shell; }
val () { valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./$SHELL_NAME.dbg; }

#endregion

#region Less Colorifier
export LESS_TERMCAP_mb=$(tput bold; tput setaf 2) # green
export LESS_TERMCAP_md=$(tput bold; tput setaf 6) # cyan
export LESS_TERMCAP_me=$(tput sgr0)
export LESS_TERMCAP_so=$(tput bold; tput setaf 3; tput setab 4) # yellow on blue
export LESS_TERMCAP_se=$(tput rmso; tput sgr0)
export LESS_TERMCAP_us=$(tput smul; tput bold; tput setaf 7) # white
export LESS_TERMCAP_ue=$(tput rmul; tput sgr0)
export LESS_TERMCAP_mr=$(tput rev)
export LESS_TERMCAP_mh=$(tput dim)
export LESS_TERMCAP_ZN=$(tput ssubm)
export LESS_TERMCAP_ZV=$(tput rsubm)
export LESS_TERMCAP_ZO=$(tput ssupm)
export LESS_TERMCAP_ZW=$(tput rsupm)
export GROFF_NO_SGR=1         # For Konsole and Gnome-terminal

# Get color support for 'less'
export LESS="--RAW-CONTROL-CHARS"

# Use colors for less, man, etc.
[[ -f ~/.LESS_TERMCAP ]] && . ~/.LESS_TERMCAP
#endregion
