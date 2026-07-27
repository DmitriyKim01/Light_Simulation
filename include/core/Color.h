#pragma once

class Color {
private:
	float m_red = 1.0f;
	float m_green = 1.0f;
	float m_blue = 1.0f;
	float m_alpha = 1.0f;
public:
	// If add custom constructor, C++ does not automatically generate the default constructor anymore
	Color() = default;
	Color(float red, float green, float blue, float alpha = 1.0f);

	// Getters
	float getRed()		const;
	float getGreen()	const;
	float getBlue()		const;
	float getAlpha()	const;

	// Setters
	void setRed(float red);
	void setGreen(float green);
	void setBlue(float blue);
	void setAlpha(float alpha);
	void setRGBA(float red, float green, float blue, float alpha = 1.0f);

	// Operators
	Color operator+(const Color& other) const;
	Color  operator*(float scalar)       const;
	bool   operator==(const Color& other) const;
	bool   operator!=(const Color& other) const;

	// Common presets
	static const Color White;
	static const Color Black;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Cyan;
	static const Color Magenta;
	static const Color Transparent;
	static const Color Gray;
};