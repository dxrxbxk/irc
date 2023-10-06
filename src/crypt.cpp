#include "crypt.hpp"
#include "utils.hpp"

#define ENCRYPT "$6$"

std::string extractSalt(const std::string& hash) {
    size_t third_dollar = hash.rfind('$');

        if (third_dollar != std::string::npos) {
            return hash.substr(0, third_dollar);
        }
    return "";
}

const char*	gensalt(const char* salt) {
    if (salt == NULL) {
		throw std::runtime_error(handleSysError("crypt_gensalt"));
    }
	return salt;
}

const char*	gensalt(void) {
    const char* salt = crypt_gensalt(ENCRYPT, 0, 0, 0);

    if (salt == NULL) {
		throw std::runtime_error(handleSysError("crypt_gensalt"));
    }
	return salt;
}

std::string encryptPassword(const std::string& password, const char* salt) {
    char* encrypted = crypt(password.c_str(), salt);
    if (encrypted == NULL)
		throw::std::runtime_error(handleSysError("crypt"));
    return std::string(encrypted);
}

std::string encryptPassword(const char* password, const char* salt) {
    char* encrypted = crypt(password, salt);
    if (encrypted == NULL)
		throw::std::runtime_error(handleSysError("crypt"));
    return std::string(encrypted);
}
