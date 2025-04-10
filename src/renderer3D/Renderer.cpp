#include "Renderer.hpp"
#include "GLFW/glfw3.h"
#include "chess2D/ChessBoard.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "renderer3D/utils.hpp"

//On initialise le shader, la caméra, l'échiquier et les pièces
void Renderer::init(std::array<std::unique_ptr<Piece>, 64>& board)
{
    // load du classic shader
    classic_shader.load_shader("model.vs.glsl", "model.fs.glsl");
    //Initialisation du chessboard et des pièces
    model_manager.init_chessboard();
    model_manager.init_pieces_positions_in_board(board);
    //On charge tous les meshs (1 fois uniquement à l'initialisation)
    model_manager.load_all_meshes();


    // load du skybox shader
    skybox_shader.load_shader("skybox.vs.glsl", "skybox.fs.glsl");
    //Initialisation de la skybox
    skybox.load_cube_maps();
    skybox.setup_buffers();
}

//Update met à jour la position des pièces sur l'échiquier APRES l'animation déclenché par le mouvement d'une pièce
void Renderer::update(std::array<std::unique_ptr<Piece>, 64>& board, std::optional<Move> &move)
{
    //Si le joueur a cliqué sur une case, on lance l'animation.
    if (move.has_value())
    {
        //On garde en mémoire le temps de début de l'animation (une seule fois au début)
        if (start_animation_time == 0.0)
        {
            start_animation_time = glfwGetTime();
        }
        //On calcule le temps écoulé depuis le début de l'animation
        double elapsed_time = glfwGetTime() - start_animation_time;

        //Si l'animation n'est pas terminée, on interpole la position de la pièce entre la position de départ et la position d'arrivée
        if (elapsed_time < end_animation_time)
        {
            //animation
            double t = elapsed_time / end_animation_time;
            glm::vec3 start_pos = from_2D_pos_to_3D_pos(from_index_to_2D_pos(move->from));
            glm::vec3 end_pos   = from_2D_pos_to_3D_pos(from_index_to_2D_pos(move->to));
            glm::vec3 interpolated_pos = glm::mix(start_pos, end_pos, t);
            model_manager.move_piece(move->piece_type_to_move, interpolated_pos, move->from);
        }
        else
        {
            //+ on remet à zéro le temps de début de l'animation
            //+ on reset l'optional
            //Quand l'animation est terminée, on met à jour la position (modèle matrice)
            start_animation_time = 0.0;
            move.reset();
            model_manager.init_pieces_positions_in_board(board);
        }
        
    }
}

// On render la skybox avec skybox_shader, (l'échiquier et toutes les pièces avec classic_shader)
void Renderer::render()
{
       
        // renderer3D
        glClearColor(0.847f, 0.82f, 0.929f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        //
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(1280) / static_cast<float>(720), 0.1f, 100.0f);

        // RENDER SKYBOX (start)
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);
        skybox_shader.use();
        glm::mat4 view = glm::mat4(glm::mat3(camera.get_view_matrix()));

        skybox_shader.set_uniform_1i("skybox", 0);
        skybox_shader.set_uniform_matrix_4fv("view", view);
        skybox_shader.set_uniform_matrix_4fv("projection", projection);

        skybox.m_vao.bind();
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.get_textureID());
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        skybox.m_vao.unbind();

        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
        // RENDER SKYBOX (end)




        // RENDER OBJECTS
        classic_shader.use();

        // VP
        classic_shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
        classic_shader.set_uniform_matrix_4fv("projection", projection);

        // LIGHT SETTINGS
        classic_shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
        classic_shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

        // CAMERA SETTINGS
        classic_shader.set_uniform_3fv("viewPos", camera.get_position());

        // MODEL RENDER
        model_manager.render(classic_shader);

}


//callbacks
void Renderer::cursor_position_callback(double xpos, double ypos)
{
        camera.track_ball_move_callback(xpos, ypos);
}
void Renderer::scroll_callback(double xoffset, double yoffset)
{
    camera.process_scroll(yoffset);
}

void Renderer::key_callback(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        camera.toggle_lock();
    };
}