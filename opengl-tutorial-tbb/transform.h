//
//  transform.h
//  opengl-tutorial-tbb
//

#ifndef transform_h
#define transform_h

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
    Transform(const glm::vec3& pos = glm::vec3(),
              const glm::vec3& rot = glm::vec3(),
              const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
            m_pos(pos),
            m_rot(rot),
            m_scale(scale) { }
    
    inline glm::mat4 GetModel() const
    {
        glm::mat4 posMatrix = glm::translate(m_pos);
        
        glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
        
        glm::mat4 scaleMatrix = glm::scale(m_scale);
        
        return posMatrix * rotMatrix * scaleMatrix;
    }
    inline glm::vec3& GetPos() { return m_pos; }
    inline glm::vec3& GetRot() { return m_rot; }
    inline glm::vec3& GetScale() { return m_scale; }
    
    inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
    inline void SetRot(const glm::vec3& rot) { m_rot = rot; }
    inline void SetScale(const glm::vec3& scale) { m_scale = scale; }
    
    ~Transform() {}
protected:
private:
    glm::vec3 m_pos;
    glm::vec3 m_rot;
    glm::vec3 m_scale;
};
#endif // transform_h
