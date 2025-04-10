#include <string>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"
#include "renderer3D/utils.hpp"



//Model3D gère toutes les instances d'un même modèle.
//Model3D Pawn => il gère les 16 pawns = il contient toutes matrices modèles.
class Model3D {
public:
    void load_mesh(const std::string& path, const std::string& name); // 1
    void setup_buffers();                                             // 2
    void render(glmax::Shader& shader) const;                         // 3
    //
    void push_data(const ModelData& data);
    void clear_data();
    
    
    private:
    // single mesh
    glmax::Mesh m_mesh;
    std::vector<ModelData> m_model_data;
    // Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};