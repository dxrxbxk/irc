#ifndef CRYPT_HPP
# define CRYPT_HPP
# include <crypt.h>
# include <string>

//void	encryptPassword(std::string& password, const char* salt);
std::string extractSalt(const std::string& hash);
const char*	gensalt();
std::string encryptPassword(const std::string& password, const char* salt);
std::string encryptPassword(const char* password, const char* salt);

#endif
