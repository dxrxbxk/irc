/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 01:09:59 by diroyer           #+#    #+#             */
/*   Updated: 2023/09/25 14:49:22 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

void	Parser::increment(void) { ++i; }

void	Parser::reset(void) { i = 0; }

void 	Parser::debug(void) {
	std::cout << "current char: ";
    std::cout << std::hex << static_cast<uint8_t>(*msg);

    e_chartype type = c_table[static_cast<uint8_t>(*msg)];
    std::cout << " chartype: \x1b[32m" << c_table[type] << "\x1b[0m";
    std::cout << " state: \x1b[33m" << tr.state << "\x1b[0m";
    std::cout << " action: \x1b[34m" << a_table[tr.action] << "\x1b[0m\n" << std::endl;
}

void	Parser::addStartLine(void) {
	i = 0;
//	request.addStartLine();
}

void	Parser::addHeaderName(void) {
	std::string	header_name(msg - i, i);
	i = 0;
//	request.addHeaderName(header_name);
}

void	Parser::addHeaderValue(void) {
	std::string	header_value(msg - i, i);
	i = 0;
//	request.addHeaderValue(header_value);
}

void	Parser::addBody(void) {
	std::string	body(msg - i, i);
	i = 0;
//	request.addBody(body);
}

void	Parser::addValue(void) {
	std::string	value(msg - i, i);
	i = 0;
//	request.addValue(value);
}

void	Parser::skip(void) {
}

void	Parser::pError(void) {
	PRINT("error");
}

void	Parser::run(void) {
	while (tr.state != ERROR && tr.state != END) {
		//  			debug();
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
	&Parser::addValue,
	&Parser::addStartLine,
	&Parser::addHeaderName,
	&Parser::addHeaderValue,
	&Parser::addBody,	
	&Parser::pError,
};

Parser::transition		Parser::t_table[Parser::S_SIZE][Parser::CT_SIZE] = {
	/* DEFAULT */
	{ 	
		{ ERROR, P_ERROR }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ ERROR, P_ERROR }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ ERROR, P_ERROR }, /* HTAB */
		{ START_LINE, INCREMENT }, /* VCHAR */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* START_LINE */
	{ 	
		{ ERROR, P_ERROR }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ START_LINE_END,  ADD_VALUE}, /* CR */
		{ START_LINE, ADD_VALUE}, /* SP */
		{ ERROR, P_ERROR }, /* HTAB */
		{ START_LINE, INCREMENT}, /* VCHAR */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* START_LINE_END */
	{ 	
		{ ERROR, P_ERROR }, /* COLON */
		{ HEADER_NAME, SKIP }, /* LF */
		{ ERROR, P_ERROR }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ ERROR, P_ERROR }, /* HTAB */
		{ ERROR, P_ERROR }, /* VCHAR */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* HEADER_NAME */
	{ 	
		{ HEADER_NAME_SP, ADD_HEADER_NAME }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ HEADER_BLOCK_END, SKIP}, /* CR */
		{ ERROR, P_ERROR }, /* SP */ 
		{ ERROR, P_ERROR }, /* HTAB */
		{ HEADER_NAME, INCREMENT }, /* VCHAR */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* HEADER_NAME_SP */
	{ 	
		{ ERROR, P_ERROR }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ ERROR, P_ERROR }, /* CR */
		{ HEADER_VALUE, SKIP }, /* SP */
		{ ERROR, P_ERROR }, /* HTAB */
		{ ERROR, P_ERROR }, /* VCHAR */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* HEADER_VALUE */
	{ 	
		{ HEADER_VALUE, INCREMENT }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ HEADER_LINE_END, ADD_HEADER_VALUE }, /* CR */
		{ HEADER_VALUE, INCREMENT }, /* SP */
		{ ERROR, P_ERROR }, /* HTAB */
		{ HEADER_VALUE, INCREMENT }, /* VCHAR */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* HEADER_LINE_END */
	{ 	
		{ ERROR, P_ERROR }, /* COLON */
		{ HEADER_NAME, SKIP }, /* LF */
		{ ERROR, P_ERROR }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ ERROR, P_ERROR }, /* HTAB */
		{ ERROR, P_ERROR }, /* VCHAR */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* HEADER_BLOCK_END */
	{ 	
		{ ERROR, P_ERROR }, /* COLON */
		{ BODY, SKIP }, /* LF */
		{ ERROR, P_ERROR }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ ERROR, P_ERROR }, /* HTAB */
		{ ERROR, P_ERROR }, /* VCHAR */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* BODY */
	{ 	
		{ BODY, INCREMENT }, /* COLON */
		{ BODY, INCREMENT }, /* LF */
		{ BODY, INCREMENT }, /* CR */
		{ BODY, INCREMENT }, /* SP */
		{ BODY, INCREMENT }, /* HTAB */
		{ BODY, INCREMENT }, /* VCHAR */
		{ BODY, INCREMENT }, /* CTL */
		{ END, ADD_BODY }, /* NUL */
	},
};
/*
HttpMessage&	Parser::parse(const char* buf, HttpMessage& ref) {
	Parser(buf, ref).run();
	return ref;
}
*/

Parser::Parser(const char* buf) 
: msg(buf), i(0) {
	tr.state = DEFAULT;
	tr.action = SKIP;
}

const Parser::e_chartype	Parser::c_table[128] = {
	//0-31
    NUL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,
    CTL, HTAB, LF, CTL, CTL, CR, CTL, CTL,
    CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,
    CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,
	//32-63
    SP, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
    VCHAR, VCHAR, COLON, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
	//64-95
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
	//96-127
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR,
    VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, VCHAR, CTL
};
