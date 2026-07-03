#include <shapes/Box.h>
#include <glm/glm.hpp>
#include <stdexcept>

// Private functions ========================================================

void Box::calculateStride()
{
	m_strideFloats = 3; // position is always included

	if (hasColor())
	{
		m_strideFloats += 3; // r, g, b
	}

	if (hasTextureCoordinate())
	{
		m_strideFloats += 2; // u, v
	}

	if (hasNormal())
	{
		m_strideFloats += 3; // nx, ny, nz
	}
}

void Box::addVertex(
	const glm::vec3& position,
	const glm::vec2& texCoord,
	const glm::vec3& normal
)
{
	// Position: x, y, z
	m_vertices.push_back(position.x);
	m_vertices.push_back(position.y);
	m_vertices.push_back(position.z);

	if (hasColor())
	{
		m_vertices.push_back(m_color.getRed());
		m_vertices.push_back(m_color.getBlue());
		m_vertices.push_back(m_color.getGreen());
	}

	if (hasTextureCoordinate())
	{
		m_vertices.push_back(texCoord.x);
		m_vertices.push_back(texCoord.y);
	}

	if (hasNormal())
	{
		m_vertices.push_back(normal.x);
		m_vertices.push_back(normal.y);
		m_vertices.push_back(normal.z);
	}
}

void Box::addFace(
	const glm::vec3& v0,
	const glm::vec3& v1,
	const glm::vec3& v2,
	const glm::vec3& v3,
	const glm::vec3& normal
)
{
	glm::vec2 uv0(0.0f, 0.0f);
	glm::vec2 uv1(1.0f, 0.0f);
	glm::vec2 uv2(1.0f, 1.0f);
	glm::vec2 uv3(0.0f, 1.0f);

	// Triangle 1
	addVertex(v0, uv0, normal);
	addVertex(v1, uv1, normal);
	addVertex(v2, uv2, normal);

	// Triangle 2
	addVertex(v2, uv2, normal);
	addVertex(v3, uv3, normal);
	addVertex(v0, uv0, normal);
}

void Box::buildVertices()
{
	calculateStride();

	m_vertices.clear();
	m_vertices.reserve(36 * m_strideFloats);

	float halfWidth = m_width / 2.0f;
	float halfHeight = m_height / 2.0f;
	float halfDepth = m_depth / 2.0f;

	float left = m_position.x - halfWidth;
	float right = m_position.x + halfWidth;
	float bottom = m_position.y - halfHeight;
	float top = m_position.y + halfHeight;
	float back = m_position.z - halfDepth;
	float front = m_position.z + halfDepth;

	glm::vec3 LBF(left, bottom, front);
	glm::vec3 RBF(right, bottom, front);
	glm::vec3 RTF(right, top, front);
	glm::vec3 LTF(left, top, front);

	glm::vec3 LBB(left, bottom, back);
	glm::vec3 RBB(right, bottom, back);
	glm::vec3 RTB(right, top, back);
	glm::vec3 LTB(left, top, back);

	// Front face
	addFace(LBF, RBF, RTF, LTF, glm::vec3(0.0f, 0.0f, 1.0f));

	// Back face
	addFace(RBB, LBB, LTB, RTB, glm::vec3(0.0f, 0.0f, -1.0f));

	// Left face
	addFace(LBB, LBF, LTF, LTB, glm::vec3(-1.0f, 0.0f, 0.0f));

	// Right face
	addFace(RBF, RBB, RTB, RTF, glm::vec3(1.0f, 0.0f, 0.0f));

	// Top face
	addFace(LTF, RTF, RTB, LTB, glm::vec3(0.0f, 1.0f, 0.0f));

	// Bottom face
	addFace(LBB, RBB, RBF, LBF, glm::vec3(0.0f, -1.0f, 0.0f));
}

// Constructors =============================================================

Box::Box(float x, float y, float z, float width, float height, float depth, Color color)
	: m_width(width),
	m_height(height),
	m_depth(depth),
	m_color(color),
	m_position(x, y, z),
	m_attributes(static_cast<unsigned int>(VertexAttribute::Position)),
	m_strideFloats(3)
{
	if (width <= 0.0f || height <= 0.0f || depth <= 0.0f)
	{
		throw std::runtime_error("Box dimensions must be greater than zero.");
	}

	buildVertices();
}

Box::Box(int x, int y, int z, int width, int height, int depth, Color color)
	: Box(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z),
		  static_cast<float>(width), static_cast<float>(height), static_cast<float>(depth), color)
{}

// Public functions ========================================================

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

void Box::includeTextureCoordinates()
{
	m_attributes |= static_cast<unsigned int>(VertexAttribute::TextureCoordinate);
	buildVertices();
}

void Box::excludeTextureCoordinates()
{
	m_attributes &= ~static_cast<unsigned int>(VertexAttribute::TextureCoordinate);
	buildVertices();
}

void Box::includeNormal()
{
	m_attributes |= static_cast<unsigned int>(VertexAttribute::Normal);
	buildVertices();
}

void Box::excludeNormal()
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

bool Box::hasTextureCoordinate() const
{
	return hasAttribute(VertexAttribute::TextureCoordinate);
}

bool Box::hasNormal() const
{
	return hasAttribute(VertexAttribute::Normal);
}

const std::vector<float>& Box::getVertices() const
{
	return m_vertices;
}

std::size_t Box::getStrideFloats() const
{
	return m_strideFloats;
}

std::size_t Box::getStrideBytes() const
{
	return m_strideFloats * sizeof(float);
}

int Box::getVertexCount() const
{
	if (m_strideFloats == 0)
	{
		return 0;
	}

	return static_cast<int>(m_vertices.size() / m_strideFloats);
}

std::size_t Box::getPositionOffsetBytes() const
{
	return 0;
}

std::size_t Box::getColorOffsetBytes() const
{
	std::size_t offset = 3; // position

	return offset * sizeof(float);
}

std::size_t Box::getTextureCoordinatesOffsetBytes() const
{
	std::size_t offset = 3;

	if (hasColor())
	{
		offset += 3;
	}

	return offset * sizeof(float);
}

std::size_t Box::getNormalOffsetBytes() const
{
	std::size_t offset = 3;

	if (hasColor())
	{
		offset += 3;
	}

	if (hasTextureCoordinate())
	{
		offset += 2;
	}

	return offset * sizeof(float);
}

