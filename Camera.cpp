// Started by Simon Bulcke
// Last update by Kevin Fandi
//


#include "Camera.hh"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void		Camera::setPos(glm::vec3 pos)
{
  this->_pos = pos;
}

void		Camera::setFocus(glm::vec3 focus)
{
  this->_focus = focus;
}

void		Camera::setTransfo(glm::mat4 transfo)
{
  this->_transformation = transfo;
}

void		Camera::setProj(glm::mat4 proj)
{
  this->_projection = proj;
}

glm::vec3	Camera::getPos() const
{
  return (this->_pos);
}

glm::vec3	Camera::getFocus() const
{
  return (this->_focus);
}

glm::mat4	Camera::getTransfo() const
{
  return (this->_transformation);
}

glm::mat4	Camera::getProj() const
{
  return (this->_projection);
}
