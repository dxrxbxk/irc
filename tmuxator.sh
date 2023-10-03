#!/bin/sh

NAME_1='poutine'
NAME_2='bobby'

PROGRAM='./ircserv'
SCRIPT='./launch.sh'

tmux new-session \; split-window -h \; split-window -v \; \
	select-pane -t 0 \; send-keys $PROGRAM C-m \; \
	select-pane -t 1 \; send-keys $SCRIPT" "$NAME_1 C-m \; \
	select-pane -t 2 \; send-keys $SCRIPT" "$NAME_2 C-m

