#include "pch.h"
#include "InputValidator.h"

bool InputValidator::IsEmail(std::string email)
{
	const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return std::regex_match(email, pattern);
}

bool InputValidator::IsValidPassword(std::string password)
{
	/*const std::regex pattern("^(\\?=.*?[A-Z])(\\?=.*?[a-z])(\\?=.*?[0-9])[A-Za-z0-9]{6,}$");
	return std::regex_match(password, pattern);*/
	return true;
}
