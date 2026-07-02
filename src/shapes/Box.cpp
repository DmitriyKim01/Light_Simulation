#include <shapes/Box.h>
#include <glm/glm.hpp>
#include <stdexcept>

Box::Box(float x, float y, float z, float width, float height, float depth, Color color)
	: m_position(x, y, z), m_color(color)
{
	setWidth(width);
	setHeight(height);
	setDepth(depth);
	buildVertices();
}

Box::Box(int x, int y, int z, int width, int height, int depth, Color color)
	: Box(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z),
		  static_cast<float>(width), static_cast<float>(height), static_cast<float>(depth), color)
{}

float Box::getWidth() const
{
	return m_width;
}

float Box::getHeight() const
{
	return m_height;
}

float Box::getDepth() const
{
	return m_depth;
}

void Box::setWidth(float width)
{
	if (width <= 0.0f)
	{
		throw std::runtime_error("Width must be greater than zero.");
	}
	m_width = width;
	buildVertices();
}

void Box::setHeight(float height)
{
	if (height <= 0.0f)
	{
		throw std::runtime_error("Height must be greater than zero.");
	}
	m_height = height;
	buildVertices();
}

void Box::setDepth(float depth)
{
	if (depth <= 0.0f)
	{
		throw std::runtime_error("Depth must be greater than zero.");
	}
	m_depth = depth;
	buildVertices();
}

glm::vec3 Box::getPosition() const
{
	return m_position;
}

void Box::setPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
	buildVertices();
}

void Box::setPosition(const glm::vec3& position)
{
	m_position = position;
	buildVertices();
}

Color Box::getColor() const
{
	return m_color;
}

void Box::setColor(const Color& color)
{
	m_color = color;
	buildVertices();
}

void Box::includeColor()
{
	m_attributes |= static_cast<unsigned int>(VertexAttribute::Color);
	buildVertices();
}

void Box::excludeColor()
{
	m_attributes &= ~static_cast<unsigned int>(VertexAttribute::Color);
	buildVertices();
}

void Box::includeTexture()
{
	m_attributes |= static_cast<unsigned int>(VertexAttribute::TexCoord);
	buildVertices();
}

void Box::excludeTexture()
{
	m_attributes &= ~static_cast<unsigned int>(VertexAttribute::TexCoord);
	buildVertices();
}

void Box::includeNormals()
{
	m_attributes |= static_cast<unsigned int>(VertexAttribute::Normal);
	buildVertices();
}

void Box::excludeNormals()
{
	m_attributes &= ~static_cast<unsigned int>(VertexAttribute::Normal);
	buildVertices();
}

bool Box::hasAttribute(VertexAttribute attribute) const
{
	return (m_attributes & static_cast<unsigned int>(attribute)) != 0;
}

bool Box::hasColor() const
{
	return hasAttribute(VertexAttribute::Color);
}

bool Box::hasTexture() const
{
	return hasAttribute(VertexAttribute::TexCoord);
}

bool Box::hasNormals() const
{
	return hasAttribute(VertexAttribute::Normal);
}

const std::vector<float>& Box::getVertices() const
{
	return m_vertices;
}

int Box::getVertexCount() const
{
	return static_cast<int>(m_vertices.size() / 6);
}

std::size_t Box::getPositionOffsetBytes() const
{
	return 0;
}

void Box::addVertex(float x, float y, float z)
{
	// Position
	m_vertices.push_back(x);
	m_vertices.push_back(y);
	m_vertices.push_back(z);

	// Color
	m_vertices.push_back(m_color.getRed());
	m_vertices.push_back(m_color.getGreen());
	m_vertices.push_back(m_color.getBlue());
}

void Box::addVertex(float x, float y, float z, glm::vec3 normal)
{
	// Position
	m_vertices.push_back(x);
	m_vertices.push_back(y);
	m_vertices.push_back(z);
	// Color
	//m_vertices.push_back(m_color.getRed());
	//m_vertices.push_back(m_color.getGreen());
	//m_vertices.push_back(m_color.getBlue());
	// Texture
	
	// Normal
	m_vertices.push_back(normal.x);
	m_vertices.push_back(normal.y);
	m_vertices.push_back(normal.z);
}
void Box::buildVertices()
{
	m_vertices.clear();
	m_vertices.reserve(36 * 6);

	float halfWidth = m_width / 2.0f;
	float halfHeight = m_height / 2.0f;
	float halfDepth = m_depth / 2.0f;

	float left = m_position.x - halfWidth;
	float right = m_position.x + halfWidth;
	float bottom = m_position.y - halfHeight;
	float top = m_position.y + halfHeight;
	float back = m_position.z - halfDepth;
	float front = m_position.z + halfDepth;

	// Front face
	addVertex(left, bottom, front);
	addVertex(right, bottom, front);
	addVertex(right, top, front);

	addVertex(right, top, front);
	addVertex(left, top, front);
	addVertex(left, bottom, front);


	// Back face
	addVertex(right, bottom, back);
	addVertex(left, bottom, back);
	addVertex(left, top, back);

	addVertex(left, top, back);
	addVertex(right, top, back);
	addVertex(right, bottom, back);

	// Left face
	addVertex(left, bottom, back);
	addVertex(left, bottom, front);
	addVertex(left, top, front);

	addVertex(left, top, front);
	addVertex(left, top, back);
	addVertex(left, bottom, back);

	// Right face
	addVertex(right, bottom, front);
	addVertex(right, bottom, back);
	addVertex(right, top, back);

	addVertex(right, top, back);
	addVertex(right, top, front);
	addVertex(right, bottom, front);

	// Top face
	addVertex(left, top, front);
	addVertex(right, top, front);
	addVertex(right, top, back);

	addVertex(right, top, back);
	addVertex(left, top, back);
	addVertex(left, top, front);

	// Bottom face
	addVertex(left, bottom, back);
	addVertex(right, bottom, back);
	addVertex(right, bottom, front);

	addVertex(right, bottom, front);
	addVertex(left, bottom, front);
	addVertex(left, bottom, back);
}

void Box::buildVerticesWithNormals()
{
	m_vertices.clear();
	m_vertices.reserve(36 * 6);

	float halfWidth = m_width / 2.0f;
	float halfHeight = m_height / 2.0f;
	float halfDepth = m_depth / 2.0f;

	float left = m_position.x - halfWidth;
	float right = m_position.x + halfWidth;
	float bottom = m_position.y - halfHeight;
	float top = m_position.y + halfHeight;
	float back = m_position.z - halfDepth;
	float front = m_position.z + halfDepth;

	// Back face: normal -Z
	glm::vec3 normalBack(0.0f, 0.0f, -1.0f);
	addVertex(left, bottom, back, normalBack);
	addVertex(right, bottom, back, normalBack);
	addVertex(right, top, back, normalBack);

	addVertex(right, top, back, normalBack);
	addVertex(left, top, back, normalBack);
	addVertex(left, bottom, back, normalBack);

	// Front face: normal +Z
	glm::vec3 normalFront(0.0f, 0.0f, 1.0f);
	addVertex(left, bottom, front, normalFront);
	addVertex(right, bottom, front, normalFront);
	addVertex(right, top, front, normalFront);

	addVertex(right, top, front, normalFront);
	addVertex(left, top, front, normalFront);
	addVertex(left, bottom, front, normalFront);

	// Left face: normal -X
	glm::vec3 normalLeft(-1.0f, 0.0f, 0.0f);
	addVertex(left, top, front, normalLeft);
	addVertex(left, top, back, normalLeft);
	addVertex(left, bottom, back, normalLeft);

	addVertex(left, bottom, back, normalLeft);
	addVertex(left, bottom, front, normalLeft);
	addVertex(left, top, front, normalLeft);

	// Right face: normal +X
	glm::vec3 normalRight(1.0f, 0.0f, 0.0f);
	addVertex(right, top, front, normalRight);
	addVertex(right, top, back, normalRight);
	addVertex(right, bottom, back, normalRight);

	addVertex(right, bottom, back, normalRight);
	addVertex(right, bottom, front, normalRight);
	addVertex(right, top, front, normalRight);

	// Bottom face: normal -Y
	glm::vec3 normalBottom(0.0f, -1.0f, 0.0f);
	addVertex(left, bottom, back, normalBottom);
	addVertex(right, bottom, back, normalBottom);
	addVertex(right, bottom, front, normalBottom);

	addVertex(right, bottom, front, normalBottom);
	addVertex(left, bottom, front, normalBottom);
	addVertex(left, bottom, back, normalBottom);

	// Top face: normal +Y
	glm::vec3 normalTop(0.0f, 1.0f, 0.0f);
	addVertex(left, top, back, normalTop);
	addVertex(right, top, back, normalTop);
	addVertex(right, top, front, normalTop);

	addVertex(right, top, front, normalTop);
	addVertex(left, top, front, normalTop);
	addVertex(left, top, back, normalTop);
}

void Box::calculateStride()
{
	m_strideFloats = 3; // position: x, y, z

	if (hasColor())
	{
		m_strideFloats += 3; // r, g, b
	}

	if (hasTexture())
	{
		m_strideFloats += 2; // u, v
	}

	if (hasNormals())
	{
		m_strideFloats += 3; // nx, ny, nz
	}

}


