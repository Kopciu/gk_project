#pragma once
#include <iostream>

class Color
{
	private:
		float mColors[4];
	public:
		Color();
		Color(float r,float g,float b,float a = 0.0f);
		float * asFloatArray();
		void set(float r = 0.0f,float g = 0.0f, float b = 0.0f, float a = 0.0f);
		float getR();
		float getG();
		float getB();
		float getA();
		Color &operator=(Color &src);
		bool operator==(Color &other);
		Color operator+(Color &src);
};

class Material
{
	private:
		Color mAmbient;
		Color mSpecular;
		Color mDiffuse;
		std::string mTextureName;
	public:
		Material();
		Material(Color amb,Color spec,Color dif, std::string tex);
		Color * getAmbient();
		Color * getSpecular();
		Color * getDiffuse();
		void setTextureName(std::string tex);
		std::string getTextureName();
};