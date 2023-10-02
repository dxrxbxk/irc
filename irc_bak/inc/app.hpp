/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:59:48 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/27 16:02:42 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_HPP 
# define APP_HPP 

# include <exception>
# include <iostream>

# include "server.hpp"

// namespace Web

// parser le web file type NGINX
// parser du protocole http
// classe http genere la reponse qui l'envois a la classe connexion
// inline 
// singleton pour le parser
// jetons pour les headers

class App {
	private:
		Server		server;
		//webParser parser;
	public:
		App();
		~App();
};

#endif
