#include "tulippch.h"
#include "openGLGAPI.h"
#include <GL\glew.h>

#include <profiling/profiler.h>
#include <shader/standard_shader/standard_shader.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/matrix_decompose.hpp>

namespace tulip {
	OpenGL::OpenGL() {

	}
	OpenGL::~OpenGL() {
	}
	void OpenGL::initImpl() {
		GLenum result = glewInit();

		if (result != GLEW_OK) {
			TULIP_CORE_CRITICAL("ERROR: GLEW initialization failed!");
			TULIP_CORE_ERROR("GLEW-ERROR: {}", glewGetErrorString(result));
			exit(EXIT_FAILURE);
		}

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		float verts_flat_color[4 * 4] = {

			/*#### VERTEX COORDS ####*/ /**/
			-0.5f,	-0.5f,  0.0f,  1.0f,
			 0.5f,	-0.5f,  0.0f,  1.0f,
			 0.5f,	 0.5f,  0.0f,  1.0f,
			-0.5f,	 0.5f,  0.0f,  1.0f,

		};

		uint32_t ind_quad[6] = { 0, 1, 2, 0, 2, 3 };

		auto flat_color_vbo = tulip::VertexBuffer::create(verts_flat_color, sizeof(verts_flat_color));
		auto flat_color_ibo = tulip::IndexBuffer::create(ind_quad, sizeof(ind_quad));

		tulip::BufferLayout buffer_layout_flat_color = { {tulip::BufferElementType::Float4, "VertexCoordinates"}};
		flat_color_vbo->setLayout(buffer_layout_flat_color);

		this->m_flat_color_vao = tulip::VertexArray::create();
		this->m_flat_color_vao->addVertexBuffer(flat_color_vbo);
		this->m_flat_color_vao->setIndexBuffer(flat_color_ibo);


		float verts_sprite[4 * 6] = {

			/*#### VERTEX COORDS ####*/ /**/
			-0.5f,	-0.5f,  0.0f,  1.0f, 0.0f, 0.0f,
			 0.5f,	-0.5f,  0.0f,  1.0f, 1.0f, 0.0f,
			 0.5f,	 0.5f,  0.0f,  1.0f, 1.0f, 1.0f,
			-0.5f,	 0.5f,  0.0f,  1.0f, 0.0f, 1.0f

		};

		auto sprite_vbo = tulip::VertexBuffer::create(verts_sprite, sizeof(verts_sprite));
		auto sprite_ibo = tulip::IndexBuffer::create(ind_quad, sizeof(ind_quad));

		tulip::BufferLayout buffer_layout_sprite = { {tulip::BufferElementType::Float4, "VertexCoordinates"}, {tulip::BufferElementType::Float2, "TextureCoordinates"} };
		sprite_vbo->setLayout(buffer_layout_sprite);

		this->m_sprite_vao = tulip::VertexArray::create();
		this->m_sprite_vao->addVertexBuffer(sprite_vbo);
		this->m_sprite_vao->setIndexBuffer(sprite_ibo);

		this->m_flat_color_shader = tulip::Shader::create();
		this->m_flat_color_shader->setSource(OGL_TULIP_FLAT_COLOR_SHADER);
		this->m_flat_color_shader->compile();

		this->m_sprite_shader = tulip::Shader::create();
		this->m_sprite_shader->readFile("assets/shader/sprite.tulipshader");
		this->m_sprite_shader->compile();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);

		TULIP_CORE_TRACE("OpenGL {} initialized!", glGetString(GL_VERSION));
	}
	void OpenGL::clearColorBufferBitImpl() const {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGL::clearDepthBufferBitImpl() const {
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGL::clearStencilBufferBitImpl() const {
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	void OpenGL::setClearColorImpl(const float& r, const float& g, const float& b, const float& a) const {
		glClearColor(r, g, b, a);
	}

	void OpenGL::beginSceneImpl(const glm::mat4& camera_transform, const glm::mat4& camera_projection) {
		m_scene_projection = camera_projection;
		m_scene_view = camera_transform;
	}

	void OpenGL::endSceneImpl() {
	}

	void OpenGL::drawEditorQuadImpl(const glm::mat4& transform, const glm::vec4& color, bool selected = false) {
		glEnable(GL_BLEND);
		TULIP_PROFILE_SCOPE("draw quad");
		m_flat_color_vao->bind();
		m_flat_color_shader->bind();
		m_flat_color_shader->setMat4("u_Model", transform);
		m_flat_color_shader->setMat4("u_View", m_scene_view);
		m_flat_color_shader->setMat4("u_Projection", m_scene_projection);
		m_flat_color_shader->setFloat4("u_Color", color);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glDrawElements(GL_TRIANGLES, m_flat_color_vao->getIndexBuffer()->getSize(), GL_UNSIGNED_INT, 0);
		glDisable(GL_BLEND);
	}

	void OpenGL::drawEditorQuadImpl(const glm::mat4& transform, const glm::vec4& color, RendererID texture_id, bool selected = false) {
		glEnable(GL_BLEND);
		TULIP_PROFILE_SCOPE("draw quad");
		m_sprite_vao->bind();
		m_sprite_shader->bind();
		glBindTextureUnit(0, texture_id);
		m_sprite_shader->setMat4("u_Model", transform);
		m_sprite_shader->setMat4("u_View", m_scene_view);
		m_sprite_shader->setMat4("u_Projection", m_scene_projection);
		m_sprite_shader->setFloat4("u_Color", color);
		m_sprite_shader->setInt("u_Texture", 0);
		glDrawElements(GL_TRIANGLES, m_sprite_vao->getIndexBuffer()->getSize(), GL_UNSIGNED_INT, 0);
		glDisable(GL_BLEND);
	}

}
