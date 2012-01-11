#include <dirent.h>

#include "listdir.h"

int listDir(const std::string& dir, std::vector<std::string>& files)
	{
	DIR *dp;
	struct dirent *dirp;
	if((dp=opendir(dir.c_str()))==NULL)
		{
		//printf("FAIL: ListDir: Nie udalo sie otworzyc folderu\n");
		return 0;
		}

	int i=0;
	while((dirp=readdir(dp))!=NULL)
		{
		files.push_back(dirp->d_name);
		i++;
		}
	closedir(dp);
	return i;
	}

