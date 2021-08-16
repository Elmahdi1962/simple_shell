#!/bin/bash

#region Prompt Modifier
branch_test=`git branch`
if [[ ${#branch_test} > 0 ]]; then
	export PS1='\[\033]0;$TITLEPREFIX:$PWD\007\]\n\[\033[32m\]\u@PC \[\033[33m\]${PWD##*/}\[\033[36m\] (`git branch | cut -c 3-`)\[\033[0m\]\n$ '
else
	export PS1='\[\033]0;$TITLEPREFIX:$PWD\007\]\n\[\033[32m\]\u@PC \[\033[33m\]${PWD##*/}\[\033[36m\]\[\033[0m\]\n$ '
fi
#endregion

#region Helper Functions

build () { gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o rash; }

run () { ./rash; }

vueman () { man ./man_1_simple_shell; }

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
