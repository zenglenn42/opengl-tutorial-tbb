//
//  camera.h
//  opengl-tutorial-tbb
//

#ifndef camera_h
#define camera_h

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
    Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
    {
        m_perspective = glm::perspective(fov, aspect, zNear, zFar);
        m_position    = pos;
        m_forward     = glm::vec3(0.0, 0.0, 1.0); // down z-axis into screen
        m_up          = glm::vec3(0.0, 1.0, 0);   // y-axis
    }
    
    inline glm::mat4 GetViewProjection() const
    {
        return m_perspective * glm::lookAt(m_position,
                                           m_position + m_forward,
                                           m_up);
    }
    
protected:
private:
    glm::mat4 m_perspective;
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
    
    float m_fov;
    float m_aspect;
};

#endif // camera_h
