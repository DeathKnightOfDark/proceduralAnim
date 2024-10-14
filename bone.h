#pragma once




#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
class bone
{
public:
	bone();
	bone(Vector2f baseJointPos, Vector2f secondaryJointPos);
	bone(Vector2f baseJointPos, float boneLength, float baseAngle);
	void link_linkedTransformable(Transformable* input);
	void updateJoints();
	void set_boneBaseJointPos_glob(Vector2f input);
	void set_boneOtherJointPos_glob(Vector2f input);
	void rotateBone(float grad);
	void moveBone(Vector2f movementVector);
	void setBonePos(Vector2f newPos);
	void drawBone(RenderWindow& renderWindow);
	float getBoneLength();
	void addAncestor(bone ancestor);

	void updateboneDrawable();
	Vector2f get_boneOtherJointPos_glob();

private:
	Vector2f boneBaseJointPos_glob;
	Vector2f boneOtherJointPos_glob;
	Transformable* linkedTransformable;
	Transformable boneTransformable;
	float boneLength;
	std::vector<bone> ancestors;
	RectangleShape boneDrawable;
	CircleShape baseJointDrawable;
	CircleShape secondaryJointDrawable;
	float startRotAngle;
};
