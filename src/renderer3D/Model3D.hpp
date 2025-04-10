#include <string>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"
#include "glm/fwd.hpp"
#include "renderer3D/utils.hpp"

// Model3D peut représenter l'échiquier, ou un pion, ou un fou... + il contient toutes les INFOS sur ses instances
class Model3D {
public:
    void load_mesh(const std::string& path, const std::string& name); // 1
    void setup_buffers();                                             // 2
    void render(glmax::Shader& shader) const;                         // 3
    //
    void move(glm::vec3 new_pos, int index);
    //
    void push_data(const ModelData& data);
    void clear_data();

private:
    // single mesh
    glmax::Mesh            m_mesh;
    std::vector<ModelData> m_model_data; //INFOS des instances
    // Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};