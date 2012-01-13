#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

class Parser
	{
	private:
		std::vector <int> elementy;
		//string element;		// Pozbylem sie jednego stringa, wooo~ o;
		std::string text;
		std::string delimiter;
	public:
		Parser(std::string text="", std::string delim=" \t");
		~Parser();
		Parser& operator=(std::string);
		Parser& operator=(const char *);
		//Parser& operator+=(std::string);
		//Parser& operator=(char*);
		std::string operator[] (int);
		operator const char*();
		void destroy();
		void setText(std::string);
		void setDelimiter(std::string);
		void parse();
		int count();
		std::string show(int);
		void del(int);
		void ins(int, std::string);
		void swap(int, std::string);
		int find(std::string);
		int val(int);
		float valFloat(int);
		bool isVal(int);

		std::string getText();
	};

#endif // PARSER_H
