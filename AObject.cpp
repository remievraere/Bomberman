// Started by Simon Bulcke
// Last update by Clovis Masson
//


#include	"AObject.hh"

AObject::AObject() : _position(0, 0, 0), _rotation(0, 0, 0),  _scale(1, 1, 1)
{
}

AObject::~AObject()
{
}

bool		AObject::initialize()
{
  return (true);
}

void		AObject::update(gdl::Clock const &clock, gdl::Input &input)
{
}

void		AObject::translate(glm::vec3 const &v)
{
  _position += v;
}

void		AObject::setRotation(glm::vec3 const& axis, float angle)
{
  _rotation = (axis * angle);
}

void		AObject::rotate(glm::vec3 const& axis, float angle)
{
  _rotation += (axis * angle);
}

void		AObject::setScale(glm::vec3 const& scale)
{
  _scale = scale;
}

void		AObject::scale(glm::vec3 const& scale)
{
  _scale *= scale;
}

glm::mat4	AObject::getTransformation()const
{
  glm::mat4 transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, _scale);
  return (transform);
}

int		AObject::getPosX()const
{
  return (this->_position.x);
}

int		AObject::getPosY()const
{
  return (this->_position.y);
}

int		AObject::getPosZ()const
{
  return (this->_position.z);
}

int		AObject::getRotX()const
{
  return (this->_rotation.x);
}

int		AObject::getRotY()const
{
  return (this->_rotation.y);
}

int		AObject::getRotZ()const
{
  return (this->_rotation.z);
}

void		AObject::Print()const
{
  std::cout << "X = " << getPosX() << std::endl;
  std::cout << "Y = " << getPosY() << std::endl;
  std::cout << "Z = " << getPosZ() << std::endl;
}

void		AObject::setPos(glm::vec3 pos)
{
  _position = pos;
}
