#include <core/Color.h>

#include <algorithm>
#include <cstdlib>

const Color Color::White = { 1.0f, 1.0f, 1.0f, 1.0f };
const Color Color::Black = { 0.0f, 0.0f, 0.0f, 1.0f };
const Color Color::Red = { 1.0f, 0.0f, 0.0f, 1.0f };
const Color Color::Green = { 0.0f, 1.0f, 0.0f, 1.0f };
const Color Color::Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
const Color Color::Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
const Color Color::Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
const Color Color::Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
const Color Color::Transparent = { 0.0f, 0.0f, 0.0f, 0.0f };
const Color Color::Gray = { 0.3f, 0.3f, 0.3f, 1.0f };

static float clampByte(float value)
{
    return std::max(0.0f, std::min(1.0f, value));
}

Color::Color(float red, float green, float blue, float alpha)
    : m_red(clampByte(red)), m_green(clampByte(green)), m_blue(clampByte(blue)), m_alpha(clampByte(alpha))
{}

float Color::getRed()   const { return m_red; }
float Color::getGreen() const { return m_green; }
float Color::getBlue()  const { return m_blue; }
float Color::getAlpha() const { return m_alpha; }

void Color::setRed(float red)
{
    m_red = clampByte(red);
}

void Color::setGreen(float green)
{
    m_green = clampByte(green);
}

void Color::setBlue(float blue)
{
    m_blue = clampByte(blue);
}

void Color::setAlpha(float alpha)
{
    m_alpha = clampByte(alpha);
}

void Color::setRGBA(float red, float green, float blue, float alpha)
{
    m_red = clampByte(red);
    m_green = clampByte(green);
    m_blue = clampByte(blue);
    m_alpha = clampByte(alpha);
}

Color Color::operator+(const Color& o) const
{
    return Color(
        clampByte(m_red + o.m_red),
        clampByte(m_green + o.m_green),
        clampByte(m_blue + o.m_blue),
        clampByte(m_alpha + o.m_alpha)
    );
}

Color Color::operator*(float s) const
{
    return Color(
        clampByte(m_red * s),
        clampByte(m_green * s),
        clampByte(m_blue * s),
        clampByte(m_alpha * s)
    );
}

bool Color::operator==(const Color& o) const
{
    return m_red == o.m_red && m_green == o.m_green && m_blue == o.m_blue && m_alpha == o.m_alpha;
}

bool Color::operator!=(const Color& o) const
{
    return !(*this == o);
}