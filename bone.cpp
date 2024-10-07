#include "bone.h"
#include <math.h>
using namespace sf;
float getAngleFromTwoPoints(Vector2f basePoint, Vector2f secondaryPoint, float radius)
{
	float val = (secondaryPoint.x - basePoint.x) / radius;
	return std::acosf(val);
}
bone::bone() : boneBaseJointPos_glob{ 0.0f, 0.0f }, boneOtherJointPos_glob{ 0.0f, 0.0f }, boneLength{0.0f}
{
	this->linkedTransformable = nullptr;
	
	this->boneDrawable.setSize(sf::Vector2f{boneOtherJointPos_glob.x, 1});
	this->boneDrawable.setFillColor(Color::White);
}
void bone::link_linkedTransformable(Transformable* input)
{
	this->linkedTransformable = input;
}
bone::bone(Vector2f baseJointPos, Vector2f secondaryJointPos): boneBaseJointPos_glob{baseJointPos}, boneOtherJointPos_glob{secondaryJointPos}
{
	this->linkedTransformable = nullptr;
	float x = this->boneBaseJointPos_glob.x - this->boneOtherJointPos_glob.x;
	this->boneDrawable.setPosition(this->boneBaseJointPos_glob);
	this->boneDrawable.setSize(sf::Vector2f{x, 1});
	this->boneDrawable.rotate(getAngleFromTwoPoints(boneBaseJointPos_glob, boneOtherJointPos_glob, this->getBoneLength()));
	float y = this->boneBaseJointPos_glob.y - this->boneOtherJointPos_glob.y;
	this->boneLength = this->getBoneLength();
}

void bone::set_boneBaseJointPos_glob(Vector2f input)
{
	this->boneBaseJointPos_glob = input;
	float x = this->boneBaseJointPos_glob.x - this->boneOtherJointPos_glob.x;
	float y = this->boneBaseJointPos_glob.y - this->boneOtherJointPos_glob.y;
	this->boneLength = this->getBoneLength();
	this->boneDrawable.setPosition(this->boneBaseJointPos_glob);
	this->boneDrawable.setSize(Vector2f{ this->boneLength,2 });
	this->boneDrawable.setRotation(getAngleFromTwoPoints(this->boneBaseJointPos_glob, this->boneOtherJointPos_glob, this->boneLength));
}
void bone::set_boneOtherJointPos_glob(Vector2f input)
{
	this->boneOtherJointPos_glob = input;
	float x = this->boneBaseJointPos_glob.x - this->boneOtherJointPos_glob.x;
	float y = this->boneBaseJointPos_glob.y - this->boneOtherJointPos_glob.y;
	this->boneLength = this->getBoneLength();
	this->boneDrawable.setSize(sf::Vector2f{this->boneLength, 2});
	this->boneDrawable.setRotation(getAngleFromTwoPoints(this->boneBaseJointPos_glob, this->boneOtherJointPos_glob, this->boneLength));
}

void bone::updateJoints()
{
	if (this->linkedTransformable != nullptr)
	{
		Vector2f trPoint = this->linkedTransformable->getPosition();
		Vector2f newOrigPoint{ this->boneBaseJointPos_glob.x - trPoint.x,this->boneBaseJointPos_glob.y - trPoint.y };
		//this->linkedTransformable->setOrigin(newOrigPoint);

	}
}

void bone::rotateBone(float grad)
{
	float rotAngle = grad;
	if (rotAngle > 360.0f) rotAngle = grad - 360.0f;
	if (this->linkedTransformable != nullptr)
	{
		this->linkedTransformable->rotate(rotAngle);
		float newRot = this->linkedTransformable->getRotation();
		Vector2f newPosOt{ this->boneBaseJointPos_glob.x + this->boneLength * std::cosf(newRot), this->boneBaseJointPos_glob.y + this->boneLength * std::sinf(newRot) };
		this->boneDrawable.rotate(grad);
	}
}

float bone::getBoneLength()
{
	float x = this->boneOtherJointPos_glob.x - this->boneBaseJointPos_glob.x;
	float y = this->boneOtherJointPos_glob.y - this->boneBaseJointPos_glob.y;
	return std::sqrt(x * x + y * y);
}
void bone::drawBone(RenderWindow& renderWindow)
{
	renderWindow.draw(this->boneDrawable);
}