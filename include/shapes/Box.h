#pragma once
#include <core/Color.h>
#include <glm/glm.hpp>

#include <vector>

enum class VertexAttribute {
	Position = 1 << 0,
	Color = 1 << 1,
	TextureCoordinate = 1 << 2,
	Normal = 1 << 3
};

class Box {
private:
	float m_width;
	float m_height;
	float m_depth;

	glm::vec3 m_position;
	Color m_color;

	unsigned int m_attributes;
	std::size_t m_strideFloats;

	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
private:
	void calculateStride();

	void addVertex(
		const glm::vec3& position,
		const glm::vec2& texCoord,
		const glm::vec3& normal
	);

	void addFace(
		const glm::vec3& v0,
		const glm::vec3& v1,
		const glm::vec3& v2,
		const glm::vec3& v3,
		const glm::vec3& normal
	);

	void buildVertices();
public:
	Box(float x, float y, float z, float width, float height, float depth, Color color);
	Box(int x, int y, int z, int width, int height, int depth, Color color);

	float getWidth() const;
	float getHeight() const;
	float getDepth() const;

	void setWidth(float width);
	void setHeight(float height);
	void setDepth(float depth);

	glm::vec3 getPosition() const;
	void setPosition(float x, float y, float z);
	void setPosition(const glm::vec3& position);

	Color getColor() const;
	glm::vec3 getColorVec3() const;
	void setColor(const Color& color);

	void includeColor();
	void excludeColor();

	void includeTextureCoordinates();
	void excludeTextureCoordinates();

	void includeNormal();
	void excludeNormal();

	bool hasAttribute(VertexAttribute attribute) const;
	bool hasColor() const;
	bool hasTextureCoordinate() const;
	bool hasNormal() const;

	const std::vector<float>& getVertices() const;
	std::size_t getStrideFloats() const;
	std::size_t getStrideBytes() const;
	int getVertexCount() const;

	std::size_t getPositionOffsetBytes() const;
	std::size_t getColorOffsetBytes() const;
	std::size_t getTextureCoordinatesOffsetBytes() const;
	std::size_t getNormalOffsetBytes() const;

	const std::vector<unsigned int>& getIndices() const;
	int getIndexCount() const;

};