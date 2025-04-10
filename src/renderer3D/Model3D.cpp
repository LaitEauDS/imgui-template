#include "Model3D.hpp"
#include <cstddef>
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "utils.hpp"


//On charge le mesh de la pièce
void Model3D::load_mesh(const std::string& path, const std::string& name)
{
    m_mesh.load(path, name);
}

//On remplit les buffers (VBO, EBO, VAO) avec les données du mesh
void Model3D::setup_buffers()
{
    // Lier et configurer les buffers pour les pions (VBO, EBO)
    m_vbo.init();
    m_vbo.bind();
    m_vbo.set_data(m_mesh.get_vertices().data(), m_mesh.get_vertices().size() * sizeof(glmax::Vertex));
    m_vbo.unbind();

    m_ebo.init();
    m_ebo.bind();
    m_ebo.set_data(m_mesh.get_indices().data(), m_mesh.get_indices().size() * sizeof(uint32_t));
    m_ebo.unbind();

    // Lier les matrices d'instance aux attributs de vertex
    m_vao.init();
    m_vao.bind();
    m_vbo.bind();
    m_ebo.bind();

    // Attributs de position, normal et texture pour chaque pièce
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glmax::Vertex), (const GLvoid*)offsetof(glmax::Vertex, m_position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glmax::Vertex), (const GLvoid*)offsetof(glmax::Vertex, m_normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glmax::Vertex), (const GLvoid*)offsetof(glmax::Vertex, m_tex_coord));

    m_vao.unbind();
}


// On met à jour la matrice modèle de la pièce correspondante
void Model3D::move(glm::vec3 new_pos, int index)
{
    for (auto& data : m_model_data)
    {
        //on trouve la bonne matrice modèle grâce à l'index de la pièce (data.index_board == from)
        if (data.index_board == index)
        {
            data.model_matrix = glm::translate(glm::mat4(1.0f), new_pos);
            break;
        }
    }
}

// On dessine le bon modèle 3D.
void Model3D::render(glmax::Shader& shader) const
{
    m_vao.bind();
    
    for (const auto& data : m_model_data)
    {

        shader.set_uniform_matrix_4fv("model", data.model_matrix);
    
        for (const glmax::Submesh& submesh : m_mesh.get_submeshes())
        {
            const glmax::Material& material = m_mesh.get_materials().at(submesh.m_material_id);
    
            // Configurer les uniformes pour les propriétés du matériau
            shader.set_uniform_3fv("Kd", color_to_vec3(data.color));
            shader.set_uniform_3fv("Ka", material.m_Ka);
            shader.set_uniform_3fv("Ks", material.m_Ks);
            shader.set_uniform_1f("Ns", material.m_Ns);
    
            if (material.m_hasMapKd)
            {
                shader.set_uniform_1i("map_Kd", material.m_mapKd.getID());
                material.m_mapKd.bind(material.m_mapKd.getID());
                shader.set_uniform_1i("useTexture", true);
            }
            else
            {
                shader.set_uniform_1i("useTexture", false);
            }
    
            // On dessine !
            glDrawElements(GL_TRIANGLES, submesh.m_index_count, GL_UNSIGNED_INT, (const GLvoid*)(submesh.m_index_offset * sizeof(uint32_t)));
    
            if (material.m_hasMapKd)
                material.m_mapKd.unbind();
        }
    }

    m_vao.unbind();
}

// On remplit la donnée (matrice modèle, index de la pièce, couleur) correspondant à la pièce
void Model3D::push_data(const ModelData& data)
{
    m_model_data.push_back(data);
}

// On vide les données de la pièce (utile lorsqu'on va ensuite remettre à jour les positions des pièces via le chessboard 2D)
void Model3D::clear_data()
{
    m_model_data.clear();
}