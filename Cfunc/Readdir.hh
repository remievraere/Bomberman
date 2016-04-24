// Started by Simon Bulcke
// Last update by Simon Bulcke
//


#ifndef		READDIR_HH_
# define	READDIR_HH_

# include	<iostream>
# include	<vector>
# include	<dirent.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<string.h>

class		Readdir
{
private:

  std::vector<std::string>	_res;

public:

  Readdir(std::string path);
  ~Readdir();
  std::vector<std::string>	getRes()const;

};

#endif		/* READDIR_HH_ */
