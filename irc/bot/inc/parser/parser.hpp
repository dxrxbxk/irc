/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 01:09:46 by diroyer           #+#    #+#             */
/*   Updated: 2023/09/27 16:37:56 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <iostream>
# include <stdint.h>
# include <memory>
# include "utils.hpp"
# include "message.hpp"

class Parser {
	public:
		//static HttpMessage& parse(const char* buf, HttpMessage&);
		static Message	parse(const std::string&);
		//Parser(const char*);

	private:
		typedef void(Parser::*action_p)(void);

		Parser(const std::string&, Message&);

		void					run(void);
		const char				*msg;
		std::size_t				i;
		Message					&request;

		enum 					e_state {
			DEFAULT,
			PREFIX,
			COMMAND,
			PARAMS,
			MIDDLE,
			TRAILING,
			DCC,
			COMMAND_END,
			ERROR,
			END,
			S_SIZE
		};

		enum					e_action {
			SKIP,
			INCREMENT,
			RESET,
			ADD_PREFIX,
			ADD_COMMAND,
			ADD_MIDDLE,
			ADD_TRAILING,
			ADD_DCC_PARAM,
			P_ERROR,
			A_SIZE
		};

		enum					e_chartype {
			COLON,
			LF,
			CR,
			SP,
			OTHER,
			CTL,
			SOH,
			NUL,
			CT_SIZE
		};

		struct					transition {
			e_state				state;
			e_action			action;
		};

		transition				tr;

		void					skip(void);
		void					increment(void);
		void					reset(void);
		void					addPrefix(void);
		void					addCommand(void);
		void					addMiddle(void);
		void					addTrailing(void);
		void					addDccParam(void);
		void					pError(void);
		void 					debug(void);
		void					addValue(void);

		static void				*a_firstline[3];
		static action_p			a_table[A_SIZE];
		static transition		t_table[S_SIZE][CT_SIZE];
		static const e_chartype	c_table[256];
};

#endif
