// Started by Simon Bulcke
// Last update by Kevin Fandi
//


#ifndef CAMERA_HH_
# define CAMERA_HH_

# include "Bomberman.hh"
# include "GameEngine.hh"

class Camera
{
private:

  glm::vec3	_pos;
  glm::vec3	_focus;
  glm::mat4	_transformation;
  glm::mat4	_projection;

public:

  Camera();
  ~Camera();
  void		setPos(glm::vec3);
  void		setFocus(glm::vec3);
  void		setTransfo(glm::mat4);
  void		setProj(glm::mat4);
  glm::vec3	getPos() const;
  glm::vec3	getFocus() const;
  glm::mat4	getTransfo() const;
  glm::mat4	getProj() const;
};

#endif /*CAMERA_HH_*/
