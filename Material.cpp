#include "Material.h"

Color::Color()
{
	mColors[0] = 0;
	mColors[1] = 0;
	mColors[2] = 0;
	mColors[3] = 0;
}

Color::Color(float r,float g,float b,float a)
{
	mColors[0] = r;
	mColors[1] = g;
	mColors[2] = b;
	mColors[3] = a;	
}

float * Color::asFloatArray()
{
	return mColors;
}

void Color::set(float r,float g, float b, float a)
{
	mColors[0] = r;
	mColors[1] = g;
	mColors[2] = b;
	mColors[3] = a;	
}

float Color::getR()
{
	return mColors[0];
}

float Color::getG()
{
	return mColors[1];
}

float Color::getB()
{
	return mColors[2];
}

float Color::getA()
{
	return mColors[3];
}

Color& Color::operator=(Color &src)
{
	mColors[0] = src.mColors[0];
	mColors[1] = src.mColors[1];
	mColors[2] = src.mColors[2];
	mColors[3] = src.mColors[3];
	return *this;
}

bool Color::operator==(Color &other)
{
	if(mColors[0] == other.mColors[0] && mColors[1] == other.mColors[1] && mColors[2] == other.mColors[2] && mColors[3] == other.mColors[3])
		return true;
	return false;
}

Color Color::operator+(Color &src)
{
	Color buf;
	buf.mColors[0] = (this->mColors[0] + src.mColors[0])/2;
	buf.mColors[1] = (this->mColors[1] + src.mColors[1])/2;
	buf.mColors[2] = (this->mColors[2] + src.mColors[2])/2;
	buf.mColors[3] = (this->mColors[3] + src.mColors[3])/2;
	return buf;
}

Material::Material()
{

}

Material::Material(Color amb,Color spec,Color dif, std::string tex)
{
	mAmbient = amb;
	mSpecular = spec;
	mDiffuse = dif;
	mTextureName = tex;
}

Color * Material::getAmbient()
{
	return &mAmbient;
}

Color * Material::getSpecular()
{
	return &mSpecular;
}

Color * Material::getDiffuse()
{
	return &mDiffuse;
}

void Material::setTextureName(std::string tex)
{
	mTextureName = tex;
}

std::string Material::getTextureName()
{
	return mTextureName;
}