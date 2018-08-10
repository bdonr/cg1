#ifndef CGEXAMPLETRIANGLE_H
#define CGEXAMPLETRIANGLE_H

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgClasses/CgAppearance.h"
#include <iostream>
#include <map>
class CgExampleTriangle : public CgBaseTriangleMesh
{

public:
    CgExampleTriangle();
    CgExampleTriangle(int id);

    ~CgExampleTriangle();

    //inherited from CgBaseRenderableObject
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    void init (std::vector<glm::vec3> arg_verts, std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices);
    void init( std::string filename);
    void calculateNormals();
    //inherited from CgBaseTriangleMesh
    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
    const std::vector<glm::vec2>& getVertexTexCoords() const;

    const std::vector<unsigned int>& getTriangleIndices() const;

    const std::vector<glm::vec3>& getFaceNormals() const;
    const std::vector<glm::vec3>& getFaceColors() const;


    CgAppearance *getAppearance() const;
    void setAppearance(CgAppearance *value);
    std::map<int, std::vector<glm::vec3> *> getMap_vertex_normals() const;
    void setMap_vertex_normals(const std::map<int, std::vector<glm::vec3> *> &value);

    float getScalar() const;
    void setScalar(float value);

private:

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;
    std::map<int, std::vector<glm::vec3>*> map_vertex_normals;

    std::vector<unsigned int>  m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;
    float scalar;
    const Cg::ObjectType m_type;
    const unsigned int m_id;
    CgAppearance *appearance;
    void calculateVertexNormals();



};


inline Cg::ObjectType  CgExampleTriangle::getType() const {return m_type;}
inline unsigned int CgExampleTriangle::getID() const {return m_id;}

#endif // CGEXAMPLETRIANGLE_H
