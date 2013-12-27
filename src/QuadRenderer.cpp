//
//  Copyright (C) <year> <copyright holders>.
//

#include "QuadRenderer.h"
#include <array>
#include <cstdint>
#include <string>

namespace BuildingCocoaWithGyp {
namespace {
//-----------------------------------------------------------------------
#define BUILDINGCOCOAWITHGYP_TOSTRING_SORRY_FOR_USING_MACRO(x) \
        "#version 330 \n" + std::string(#x)
//-----------------------------------------------------------------------
std::string const vertexShaderCode = BUILDINGCOCOAWITHGYP_TOSTRING_SORRY_FOR_USING_MACRO(
	layout(location = 0) in vec3 Position;
	layout(location = 1) in vec2 TextureCoord;

	out VertexData {
		vec2 TextureCoord;
	} Out;

	void main()
	{
		gl_Position = vec4(Position.xyz, 1.0);
		Out.TextureCoord = TextureCoord.xy;
	}
);
//-----------------------------------------------------------------------
std::string const pixelShaderCode = BUILDINGCOCOAWITHGYP_TOSTRING_SORRY_FOR_USING_MACRO(
	in VertexData {
		vec2 TextureCoord;
	} In;

	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(clamp(In.TextureCoord.xy, 0.0, 1.0), 1.0, 1.0);
	}
);
//-----------------------------------------------------------------------
using Vector3 = std::array<float, 3>;
using Vector2 = std::array<float, 2>;

struct VertexCombined
{
	Vector3 position;
	Vector2 textureCoord;
};

//-----------------------------------------------------------------------
static GLuint CreateVertexBuffer()
{
	std::array<VertexCombined, 4> const vertices = {
		Vector3({ 0.8f, -0.8f, 0.0f}), Vector2({1.0f, 0.0f}),
		Vector3({ 0.8f,  0.8f, 0.0f}), Vector2({1.0f, 1.0f}),
		Vector3({-0.8f,  0.8f, 0.0f}), Vector2({0.0f, 1.0f}),
		Vector3({-0.8f, -0.8f, 0.0f}), Vector2({0.0f, 0.0f}),
	};

	GLuint vertexBuffer = 0;
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(VertexCombined) * vertices.size(),
		vertices.data(),
		GL_STATIC_DRAW);
	
	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	return vertexBuffer;
}
//-----------------------------------------------------------------------
static GLuint CreateIndexBuffer()
{
	std::array<std::uint16_t, 6> const indices = {
		0, 1, 2,
		2, 3, 0
	};
	
	GLuint indexBuffer = 0;
	
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(std::uint16_t) * indices.size(),
		indices.data(),
		GL_STATIC_DRAW);
	
	// unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return indexBuffer;
}
//-----------------------------------------------------------------------
static GLuint CompileShader(GLenum pipelineStage, std::string const& shaderSource)
{
	GLuint vertexShader = glCreateShader(pipelineStage);
	
	GLint sourceLength = shaderSource.size();
	
	std::array<GLchar const*, 1> shaderData = { shaderSource.data() };
	glShaderSource(vertexShader, 1, shaderData.data(), &sourceLength);
	glCompileShader(vertexShader);
	
	return vertexShader;
}
//-----------------------------------------------------------------------
static GLuint CreateShaderProgram()
{
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
	GLuint pixelShader = CompileShader(GL_FRAGMENT_SHADER, pixelShaderCode);
	
	GLuint shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, pixelShader);
	
	glLinkProgram(shaderProgram);
	
	glDeleteShader(pixelShader);
	glDeleteShader(vertexShader);
	
	return shaderProgram;
}
//-----------------------------------------------------------------------
static GLuint CreateInputLayout(GLuint shaderProgram)
{
	GLuint inputLayout = 0;
	
	glGenVertexArrays(1, &inputLayout);
	
	glBindVertexArray(inputLayout);

	auto const attributePosition = glGetAttribLocation(shaderProgram, "Position");
	auto const attributeTextureCoord = glGetAttribLocation(shaderProgram, "TextureCoord");
	
	glEnableVertexAttribArray(attributePosition);
	glEnableVertexAttribArray(attributeTextureCoord);
	
	// unbind
	glBindVertexArray(0);
	
	return inputLayout;
}
//-----------------------------------------------------------------------
static GLubyte const* BufferOffset(std::size_t byteWidth)
{
	return reinterpret_cast<GLubyte const*>(0) + byteWidth;
}
//-----------------------------------------------------------------------
}// namespace
//-----------------------------------------------------------------------
QuadRenderer::QuadRenderer()
{
	vertexBuffer = CreateVertexBuffer();
	indexBuffer = CreateIndexBuffer();
	shaderProgram = CreateShaderProgram();
	inputLayout = CreateInputLayout(shaderProgram);
	
	glDisable(GL_CULL_FACE);
}
//-----------------------------------------------------------------------
QuadRenderer::~QuadRenderer()
{
	glDeleteVertexArrays(1, &inputLayout);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &vertexBuffer);
}
//-----------------------------------------------------------------------
void QuadRenderer::Draw()
{
	glBindVertexArray(inputLayout);
	{
		auto const attributePosition = glGetAttribLocation(shaderProgram, "Position");
		auto const attributeTextureCoord = glGetAttribLocation(shaderProgram, "TextureCoord");
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		GLsizei const components = 3;
		GLsizei const strideBytes = sizeof(VertexCombined);
		glVertexAttribPointer(attributePosition, components, GL_FLOAT, GL_FALSE, strideBytes,
			BufferOffset(0));
		glVertexAttribPointer(attributeTextureCoord, components, GL_FLOAT, GL_FALSE, strideBytes,
			BufferOffset(sizeof(Vector3)));
		glVertexAttribDivisor(0, 0);
	}
	
	glUseProgram(shaderProgram);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	GLsizei const indexCount = 6;
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, nullptr);
}
//-----------------------------------------------------------------------
}// namespace BuildingCocoaWithGyp
