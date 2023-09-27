/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 01:09:59 by diroyer           #+#    #+#             */
/*   Updated: 2023/09/27 15:59:36 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"


const char* state_debug[] = {
	"DEFAULT",
	"PREFIX",
	"COMMAND",
	"PARAMS",
	"MIDDLE",
	"TRAILING",
	"COMMAND_END",
	"ERROR",
	"END"
};

const char* chartype_debug[] = {
	"COLON",
	"LF",
	"CR",
	"SP",
	"OTHER",
	"CTL",
	"NUL",
};

const char* action_debug[] = {
	"SKIP",
	"INCREMENT",
	"RESET",
	"ADD_PREFIX",
	"ADD_COMMAND",
	"ADD_MIDDLE",
	"ADD_TRAILING",
	"P_ERROR"
};
void 	Parser::debug(void) {
	std::cout << "current char: ";
    std::cout << std::hex << static_cast<uint8_t>(*msg);


    e_chartype type = c_table[static_cast<uint8_t>(*msg)];
    std::cout << " chartype: \x1b[32m" << chartype_debug[type] << "\x1b[0m";
    std::cout << " state: \x1b[33m" << state_debug[tr.state] << "\x1b[0m";
    std::cout << " action: \x1b[34m" << action_debug[tr.action] << "\x1b[0m" << std::endl;
}



void	Parser::increment(void) { ++i; }

void	Parser::reset(void) { i = 0; }


void	Parser::addPrefix(void) {
	std::string	prefix(msg - i, i);
	i = 0;
	request.addPrefix(prefix);
}

void	Parser::addCommand(void) {
	std::string	command(msg - i, i);
	i = 0;
	request.addCommand(command);
}

void	Parser::addMiddle(void) {
	std::string	middle(msg - i, i);
	i = 0;
	request.addMiddle(middle);
}

void	Parser::addTrailing(void) {
	std::string	trailing(msg - i, i);
	i = 0;
	request.addTrailing(trailing);
}

void	Parser::skip(void) {
}

void	Parser::pError(void) {
	PRINT("error");
}


void debug_raw(const char* msg) {

	std::cout << "\n\n\n\x1b[32mRAW: \x1b[0m";
	while (*msg) {
		if (*msg < 32) {
			if (*msg == '\r')
				std::cout << " CR ";
			else if (*msg == '\n')
				std::cout << " LF ";
			else
				std::cout << std::hex << static_cast<uint8_t>(*msg);
		}
		else {
			std::cout << *msg;
		}
		++msg;
	}
	std::cout << std::endl<< std::endl;
}


void	Parser::run(void) {

	debug_raw(msg);

	while (tr.state != ERROR && tr.state != END) {
		// debug();
		e_chartype type = c_table[static_cast<uint8_t>(*msg)];
		tr = t_table[tr.state][type];
		(this->*a_table[tr.action])();
		++msg;
	}
}

Parser::action_p	Parser::a_table[Parser::A_SIZE] = {
	&Parser::skip,
	&Parser::increment,
	&Parser::reset,
	&Parser::addPrefix,
	&Parser::addCommand,
	&Parser::addMiddle,
	&Parser::addTrailing,
	&Parser::pError,
};

Parser::transition		Parser::t_table[Parser::S_SIZE][Parser::CT_SIZE] = {
	/* DEFAULT */
	{
		{ PREFIX, INCREMENT }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ COMMAND_END, INCREMENT }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ COMMAND, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* PREFIX */
	{
		{ ERROR, P_ERROR }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ ERROR,  P_ERROR }, /* CR */
		{ COMMAND, ADD_PREFIX }, /* SP */
		{ PREFIX, INCREMENT}, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* COMMAND */
	{
		{ ERROR, P_ERROR }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ COMMAND_END, ADD_COMMAND }, /* CR */
		{ PARAMS, ADD_COMMAND }, /* SP */
		{ COMMAND, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* PARAMS */
	{
		{ TRAILING, SKIP }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ ERROR, P_ERROR }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ MIDDLE, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* MIDDLE */
	{
		{ MIDDLE, INCREMENT }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ COMMAND_END, ADD_MIDDLE }, /* CR */
		{ PARAMS, ADD_MIDDLE }, /* SP */
		{ MIDDLE, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* TRAILING */
	{
		{ TRAILING, INCREMENT }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ COMMAND_END, ADD_TRAILING }, /* CR */
		{ TRAILING, INCREMENT }, /* SP */
		{ TRAILING, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* COMMAND_END */
	{
		{ ERROR, P_ERROR }, /* COLON */
		{ END, SKIP }, /* LF */
		{ ERROR, P_ERROR }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ ERROR, P_ERROR }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */
	},
};

Message		Parser::parse(const std::string& ref) {
	Message	request;
	Parser(ref, request).run();
	return request;
}

Parser::Parser(const std::string& ref, Message& req)
: msg(ref.c_str()), i(0), request(req) {
	tr.state = DEFAULT;
	tr.action = SKIP;
}

const Parser::e_chartype	Parser::c_table[128] = {
	//0-31
    NUL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,
    CTL, CTL, LF, CTL, CTL, CR, CTL, CTL,
    CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,
    CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,
	//32-63
    SP, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, COLON, OTHER, OTHER, OTHER, OTHER, OTHER,
	//64-95
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
	//96-127
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, CTL
};



