#!/bin/sh

make logger || exit 1

NAME_1='didir'
NAME_2='tutur'

PROGRAM='./ircserv 8080 pass'
SCRIPT='./launch.sh'

tmux new-session \; split-window -h \; split-window -v \; \
	select-pane -t 0 \; send-keys "eval $PROGRAM" C-m \; \
	select-pane -t 1 \; send-keys $SCRIPT" "$NAME_1 C-m \; \
	select-pane -t 2 \; send-keys $SCRIPT" "$NAME_2 C-m

