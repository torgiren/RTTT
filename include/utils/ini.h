/*
 * ini.h
 *
 *  Created on: 18-10-2011
 *      Author: crm
 */

#ifndef INI_H_
#define INI_H_

#include <string>
#include <map>

/***
 * \class Ini
 * \brief Prosta obsluga plikow ini
 */

class Ini
	{
	private:
		std::map<std::string, std::string> vals;
	public:
		/***
		 * \brief Wczytuje grupe \a group z pliku \a fileName
		 */
		bool open(const std::string& fileName, const std::string& group);
		void clear();

		void get(const std::string& key, std::string& val);
		std::string& get(const std::string& key);
	};

#endif /* INI_H_ */
