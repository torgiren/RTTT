/*
 * resource.h
 *
 *  Created on: 23-12-2011
 *      Author: crm
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

class Resfile;

namespace Resource
	{
	void init(const std::string& name);
	void clear();
	void clearCache();

	char* load(const std::string& file);
	int getSize(const std::string& file);
	int getLastSize();
	};

#endif /* RESOURCE_H_ */
