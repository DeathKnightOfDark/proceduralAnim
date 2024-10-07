#pragma once




#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
class bone
{
public:
	bone();
	bone(Vector2f baseJointPos, Vector2f secondaryJointPos);
	void link_linkedTransformable(Transformable* input);
	void updateJoints();
	void set_boneBaseJointPos_glob(Vector2f input);
	void set_boneOtherJointPos_glob(Vector2f input);
	void rotateBone(float grad);
	void drawBone(RenderWindow& renderWindow);
	float getBoneLength();
private:
	Vector2f boneBaseJointPos_glob;
	Vector2f boneOtherJointPos_glob;
	Transformable* linkedTransformable;
	float boneLength;
	std::vector<bone> ancestors;
	RectangleShape boneDrawable;
};
