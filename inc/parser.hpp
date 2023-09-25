/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 01:09:46 by diroyer           #+#    #+#             */
/*   Updated: 2023/09/25 14:48:56 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <iostream>
# include <stdint.h>
# include <memory>
# include "utils.hpp"

class Parser {
	public:
		//static HttpMessage& parse(const char* buf, HttpMessage&);
		Parser(const char*);

	private:
		typedef void(Parser::*action_p)(void);


		void					run(void);
		const char				*msg;
		std::size_t				i;

		enum 					e_state {
			DEFAULT,
			START_LINE,
			START_LINE_END,
			HEADER_NAME,
			HEADER_NAME_SP,
			HEADER_VALUE,
			HEADER_LINE_END,
			HEADER_BLOCK_END,
			BODY,
			ERROR,
			END,
			S_SIZE
		};

		enum					e_action {
			SKIP,
			INCREMENT,
			RESET,
			ADD_VALUE,
			ADD_START_LINE,
			ADD_HEADER_NAME,
			ADD_HEADER_VALUE,
			ADD_BODY,
			P_ERROR,
			A_SIZE
		};

		enum					e_chartype {
			COLON,
			LF,
			CR,
			SP,
			HTAB,
			VCHAR,
			CTL,
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
		void					addStartLine(void);
		void					addHeaderName(void);
		void					addHeaderValue(void);
		void					addBody(void);
		void					pError(void);
		void 					debug(void);
		void					addValue(void);

		static void				*a_firstline[3];
		static action_p			a_table[A_SIZE];
		static transition		t_table[S_SIZE][CT_SIZE];
		static const e_chartype	c_table[128];
};

#endif
