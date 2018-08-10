#include "CgExampleTriangle.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"
#include "CgUtils/CgUtils.h"

CgExampleTriangle::CgExampleTriangle():
m_type(Cg::TriangleMesh),
m_id(42)
{
    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
    m_vertices.push_back(glm::vec3(0.5,-0.5,0.0));
    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

}

CgExampleTriangle::CgExampleTriangle(int id):
m_type(Cg::TriangleMesh),
m_id(id)
{

    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
    m_vertices.push_back(glm::vec3(0.0,-0.5,0.0));
    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));
    m_vertices.push_back(glm::vec3(0.5,0.0,0.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(3);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

}



CgExampleTriangle::~CgExampleTriangle()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
    map_vertex_normals.clear();
}

/**
 * calculate vertext normals
 * @brief CgExampleTriangle::calculateVertexNormals
 */
void CgExampleTriangle::calculateVertexNormals()
{
    for(int i = 0; i < (int) m_vertices.size(); i++){
        map_vertex_normals[i] = new std::vector<glm::vec3>;
        }
        
        int p1, p2, p3;
        for(int i = 0; i <= m_triangle_indices.size() - 3; i += 3){
        p1 = m_triangle_indices.at(i);
        p2 = m_triangle_indices.at(i+1);
        p3 = m_triangle_indices.at(i+2);
        
        //Calculate and push faceNormal
        glm::vec3 faceNormal = CgUtils::calcFaceNormal(m_vertices.at(p1),m_vertices.at(p2),m_vertices.at(p3));
        m_face_normals.push_back(faceNormal);
        
        //Map faceNormal to vertex
        map_vertex_normals.at(p1)->push_back(faceNormal);
        map_vertex_normals.at(p2)->push_back(faceNormal);
        map_vertex_normals.at(p3)->push_back(faceNormal);
        }
}

/**
 * creating object
 * @brief CgExampleTriangle::init
 * @param arg_verts
 * @param arg_normals
 * @param arg_triangle_indices
 */
void CgExampleTriangle::init(std::vector<glm::vec3> arg_verts,std::vector<glm::vec3> arg_normals,std::vector<unsigned int> arg_triangle_indices){
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
    calculateVertexNormals();
}
/**
 * loading object based of its name
 * @brief CgExampleTriangle::init
 * @param filename
 */
void CgExampleTriangle::init( std::string filename)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();

    ObjLoader loader;
    loader.load(filename);

    loader.getPositionData(m_vertices);
    loader.getNormalData(m_vertex_normals);
    loader.getFaceIndexData(m_triangle_indices);
}

const std::vector<glm::vec3>& CgExampleTriangle::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgExampleTriangle::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgExampleTriangle::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgExampleTriangle:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgExampleTriangle::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgExampleTriangle::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgExampleTriangle::getFaceColors() const
{
    return m_face_colors;
}

CgAppearance *CgExampleTriangle::getAppearance() const
{
    return appearance;
}

void CgExampleTriangle::setAppearance(CgAppearance *value)
{
    appearance = value;
}

std::map<int, std::vector<glm::vec3> *> CgExampleTriangle::getMap_vertex_normals() const
{
    return map_vertex_normals;
}

void CgExampleTriangle::setMap_vertex_normals(const std::map<int, std::vector<glm::vec3> *> &value)
{
    map_vertex_normals = value;
}

float CgExampleTriangle::getScalar() const
{
    return scalar;
}

void CgExampleTriangle::setScalar(float value)
{
    scalar = value;
}


