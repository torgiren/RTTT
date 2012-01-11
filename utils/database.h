#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>

class Database
	{
	private:
		std::string name;

		std::map<std::string, std::string> sdb;
		std::map<std::string, int> vdb;
	public:
		 Database(): name("") {}
		 Database(std::string name): name(name) {load(name);}
		~Database() {save(name);}

		bool load(std::string name);
		bool save(std::string name);
		void clear();

		int getVal(std::string name);
		std::string getStr(std::string name);
		inline int getVal(const char *name) {return getVal((std::string)name);};
		inline const char* getStr(const char *name) {return getStr((std::string)name).c_str();};

		void setVal(std::string name, int val);
		void setStr(std::string name, std::string str);
		inline void setVal(const char *name, int val) {setVal((std::string)name, val);};
		inline void setStr(const char *name, const char *str) {setStr((std::string)name, (std::string)str);};
	};

#endif // DATABASE_H
