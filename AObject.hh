// Started by Simon Bulcke
// Last update by Clovis Masson
//


#ifndef			AOBJECT_HH_
# define		AOBJECT_HH_

#include		"Bomberman.hh"

class AObject
{
public:

  AObject();
  virtual		~AObject();
  virtual bool		initialize();
  virtual void		update(gdl::Clock const&, gdl::Input&);
  virtual void		draw(gdl::AShader&, gdl::Clock const &) = 0;
  void			translate(glm::vec3 const&);
  void			rotate(glm::vec3 const&, float);
  void			setRotation(glm::vec3 const&, float);
  void			scale(glm::vec3 const&);
  void			setScale(glm::vec3 const&);
  glm::mat4		getTransformation()const;
  int			getPosX()const;
  int			getPosY()const;
  int			getPosZ()const;
  int			getRotX()const;
  int			getRotY()const;
  int			getRotZ()const;
  void			Print()const;
  void			setPos(glm::vec3);
  virtual std::string	getType()const = 0;
  virtual glm::vec3	getPos()const = 0;
  virtual char		getT()const = 0;
  virtual std::string	getData()const = 0;

protected:

  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;
};

#endif		/* AOBJECT_HH_ */
