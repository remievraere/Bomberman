// Started by Simon Bulcke
// Last update by Simon Bulcke
//


#include	"Readdir.hh"

Readdir::Readdir(std::string path)
{
  struct stat	sb;
  struct dirent	*lecture;
  DIR		*rep;
  int		nbRes;

  nbRes = 0;
  if ((rep = opendir(path.c_str())) != NULL)
    {
      while (lecture = readdir(rep))
	{
	  if (strcmp(lecture->d_name, ".") != 0 && strcmp(lecture->d_name, "..") != 0)
	    {
	      //	      stat(lecture->d_name, &sb);
	      //	      if (S_ISDIR(sb.st_mode))
	      _res.push_back(lecture->d_name);
	      nbRes++;
	    }
	}
      closedir(rep);
    }
  if (nbRes == 0)
    _res.clear();
}

Readdir::~Readdir()
{
}

std::vector<std::string>	Readdir::getRes()const
{
  return (_res);
}
