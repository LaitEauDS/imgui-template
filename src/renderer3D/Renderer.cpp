#include "Renderer.hpp"
#include "glm/ext/matrix_clip_space.hpp"

void Renderer::init(std::array<std::unique_ptr<Piece>, 64>& board)
{
    // renderer3D
    classic_shader.load_shader("model.vs.glsl", "model.fs.glsl");
    model_manager.init_chessboard();
    model_manager.init_pieces_positions_in_board(board);
    model_manager.load_all_meshes();
    // shader
    skybox_shader.load_shader("skybox.vs.glsl", "skybox.fs.glsl");
    skybox.load_cube_maps();
    skybox.setup_buffers();
}

void Renderer::update(std::array<std::unique_ptr<Piece>, 64>& board)
{
    model_manager.init_pieces_positions_in_board(board);
}

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

void Renderer::cursor_position_callback(double xpos, double ypos)
{
    camera.process_mouse_movement(xpos, ypos);
}
void Renderer::scroll_callback(double xoffset, double yoffset)
{
    camera.process_scroll(yoffset);
}