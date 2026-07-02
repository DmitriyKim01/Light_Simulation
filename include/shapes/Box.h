#pragma once
#include <core/Color.h>
#include <glm/glm.hpp>

#include <vector>

class Box {
private:
	float m_width;
	float m_height;
	float m_depth;
	Color m_color;
	bool m_hasNormals = false;

	glm::vec3 m_position;
	std::vector<float> m_vertices;
private:
	void buildVertices();
	void buildVerticesWithNormals();

	void addVertex(float x, float y, float z);
	void addVertex(float x, float y, float z, glm::vec3 normal);
public:
	Box(int x, int y, int z, int width, int height, int depth, Color color);
	Box(float x, float y, float z, float width, float height, float depth, Color color);

	Box(int x, int y, int z, int width, int height, int depth, Color color, bool hasNormals);
	Box(float x, float y, float z, float width, float height, float depth, Color color, bool hasNormals);

	float getWidth() const;
	float getHeight() const;
	float getDepth() const;

	void setWidth(float width);
	void setHeight(float height);
	void setDepth(float depth);

	void enableNormals();
	void disableNormals();

	glm::vec3 getPosition() const;
	void setPosition(float x, float y, float z);
	void setPosition(const glm::vec3& position);

	float getVolume() const;

	Color getColor() const;
	void setColor(const Color& color);

	const std::vector<float>& getVertices() const;
	int getVertexCount() const;
};