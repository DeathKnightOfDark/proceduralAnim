#include "bone.h"
#include <math.h>
using namespace sf;
float getAngleFromTwoPoints(Vector2f basePoint, Vector2f secondaryPoint, float radius)
{
	float val = (secondaryPoint.x - basePoint.x) / radius;
	return std::acosf(val)*(180.0f/3.14f);
}
bone::bone() : boneBaseJointPos_glob{ 0.0f, 0.0f }, boneOtherJointPos_glob{ 0.0f, 0.0f }, boneLength{0.0f}, rotAngle{ 0 }
{
	this->linkedTransformable = nullptr;
	
	this->boneDrawable.setSize(sf::Vector2f{boneOtherJointPos_glob.x, 1});
	this->boneDrawable.setFillColor(Color::White);
}
void bone::link_linkedTransformable(Transformable* input)
{
	this->linkedTransformable = input;
}
bone::bone(Vector2f baseJointPos, Vector2f secondaryJointPos): boneBaseJointPos_glob{baseJointPos}, boneOtherJointPos_glob{secondaryJointPos}, rotAngle{0}
{
	this->linkedTransformable = nullptr;
	float x = this->boneBaseJointPos_glob.x - this->boneOtherJointPos_glob.x;
	float y = this->boneBaseJointPos_glob.y - this->boneOtherJointPos_glob.y;
	this->boneLength = this->getBoneLength();
	this->updateboneDrawable();
}

void bone::set_boneBaseJointPos_glob(Vector2f input)
{
	this->boneBaseJointPos_glob = input;
	
}
void bone::set_boneOtherJointPos_glob(Vector2f input)
{
	this->boneOtherJointPos_glob = input;
	this->boneLength = this->getBoneLength();
	this->boneDrawable.setSize(sf::Vector2f{this->boneLength, 2});
	this->boneDrawable.setRotation(getAngleFromTwoPoints(this->boneBaseJointPos_glob, this->boneOtherJointPos_glob, this->boneLength));*/
}

void bone::updateJoints()
{
	if (this->linkedTransformable != nullptr)
	{
	

	}
}

void bone::rotateBone(float grad)
{
	
}
void bone::moveBone(Vector2f movementVector)
{
	this->boneBaseJointPos_glob += movementVector;
	this->boneOtherJointPos_glob += movementVector;
	this->boneDrawable.setPosition(this->boneBaseJointPos_glob);
	if (this->linkedTransformable != nullptr)
	{
		this->linkedTransformable->setPosition(this->boneBaseJointPos_glob);
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
	for (auto it = this->ancestors.begin(); it != this->ancestors.end(); it++)
	{
		it->drawBone(renderWindow);
	}
}

Vector2f bone::get_boneOtherJointPos_glob()
{
	return this->boneOtherJointPos_glob;
}

void bone::addAncestor(bone ancestor)
{
	this->ancestors.push_back(ancestor);
}

void bone::setBonePos(Vector2f newPos)
{
	Vector2f newPosMoveVector = newPos - this->boneBaseJointPos_glob;
	this->set_boneBaseJointPos_glob(newPos);
	this->set_boneOtherJointPos_glob(this->boneOtherJointPos_glob + newPosMoveVector);
}

void bone::updateboneDrawable()
{

	this->boneDrawable.setOrigin(Vector2f{ 0.5f, 0.5f });
	this->boneDrawable.setPosition(this->boneBaseJointPos_glob);
	this->boneDrawable.setSize(Vector2f{ this->getBoneLength(),1 });
	this->boneDrawable.setRotation(getAngleFromTwoPoints(this->boneBaseJointPos_glob, this->boneOtherJointPos_glob, this->getBoneLength()));
}