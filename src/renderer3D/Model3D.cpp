#include "Model3D.hpp"
#include <cstddef>
#include <iostream>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include "utils.hpp"


void Model3D::load_mesh(const std::string& path, const std::string& name)
{
    m_mesh.load(path, name);
}

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

// void Model3D::fill_matrices(std::array<std::unique_ptr<Piece>, 64>&board)
// {
//     m_model_matrices.clear(); //on clear pour s'assurer de bien toujours avoir un nombre correcte de matrices. (et pas les accumuler)
//     for (size_t i{0}; i < board.size(); i++)
//     {
//         if (board[i])
//         {
//             PieceType piece_type = board[i]->get_type();
//             Color piece_color = board[i]->get_color();

//             glm::vec2 position2D = from_index_to_2D_pos(i);
//             glm::vec3 position3D = from_2D_pos_to_3D_pos(position2D);
//             glm::mat4 matrice_piece = glm::translate(glm::mat4(1.0f),position3D);
//             m_model_matrices.push_back(matrice_piece);
//         }
//     }
// }


// render mon mesh
void Model3D::render(glmax::Shader& shader) const
{
    m_vao.bind();
    
    for (const auto& matrix : m_model_matrices)
    {

        shader.set_uniform_matrix_4fv("model", matrix);
    
        for (const glmax::Submesh& submesh : m_mesh.get_submeshes())
        {
            const glmax::Material& material = m_mesh.get_materials().at(submesh.m_material_id);
    
            // Configurer les uniformes pour les propriétés du matériau
            // shader.set_uniform_3fv("Kd", glm::vec3(1.0f,0.0f,0.0f));
            shader.set_uniform_3fv("Kd", material.m_Kd);
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

void Model3D::move(const glm::vec2 &position)
{
    //TODO : arriver à move LA BONNE PIECE.
    for (auto& model_matrix : m_model_matrices)
    {
        model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x,0,position.y));
    }

}

void Model3D::push_matrix(const glm::mat4& matrix)
{
    m_model_matrices.push_back(matrix);
}

void Model3D::clear_matrices()
{
    m_model_matrices.clear();
}