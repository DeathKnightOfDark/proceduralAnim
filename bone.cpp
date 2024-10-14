#include "bone.h"
#include <math.h>

using namespace sf;
#define GRAD_TO_RAD_CNST (3.14f/180.0f)
float getAngleFromTwoPoints(Vector2f basePoint, Vector2f secondaryPoint, float radius)
{
	float val = (secondaryPoint.x - basePoint.x) / radius;
	return std::acosf(val)*(180.0f/3.14f);
}
bone::bone() : boneBaseJointPos_glob{ 0.0f, 0.0f }, boneOtherJointPos_glob{ 0.0f, 0.0f }, boneLength{0.0f}, startRotAngle{ 0 }, boneTransformable{}
{
	this->linkedTransformable = nullptr;
	
	this->boneDrawable.setSize(sf::Vector2f{boneOtherJointPos_glob.x, 1});
	this->boneDrawable.setFillColor(Color::White);
	
}

bone::bone(Vector2f baseJointPos, Vector2f secondaryJointPos): boneBaseJointPos_glob{baseJointPos}, boneOtherJointPos_glob{secondaryJointPos}, startRotAngle{0}, boneTransformable{}
{
	this->linkedTransformable = nullptr;
	this->boneTransformable.setPosition(this->boneBaseJointPos_glob);
	this->boneDrawable.setOrigin(sf::Vector2f{0.0f, 0.5f});
	this->boneDrawable.setPosition(this->boneTransformable.getPosition());
	this->boneDrawable.setSize(Vector2f{ this->getBoneLength(),1 });

}

bone::bone(Vector2f baseJointPos, float boneLength, float baseAngle): boneBaseJointPos_glob { baseJointPos }, startRotAngle{ baseAngle }, boneTransformable{}, boneLength{boneLength}
{
	this->linkedTransformable = nullptr;
	this->boneOtherJointPos_glob = Vector2f{ this->boneBaseJointPos_glob.x + boneLength,boneBaseJointPos_glob.y };
	this->boneTransformable.setPosition(this->boneBaseJointPos_glob);
	this->boneTransformable.setOrigin(Vector2f{ 0.0f,0.0f });
	this->boneDrawable.setOrigin(sf::Vector2f{0.0f, 0.0f});
	this->boneDrawable.setPosition(this->boneTransformable.getPosition());
	this->boneDrawable.setSize(Vector2f{ this->getBoneLength(),1 });
	this->boneTransformable.setRotation(this->startRotAngle);
	this->boneDrawable.setRotation(this->startRotAngle);
}
void bone::link_linkedTransformable(Transformable* input)
{
	this->linkedTransformable = input;
}
void bone::set_boneBaseJointPos_glob(Vector2f input)
{
	this->boneBaseJointPos_glob = input;
	
	
}
void bone::set_boneOtherJointPos_glob(Vector2f input)
{
	this->boneOtherJointPos_glob = input;
	
}

void bone::updateJoints()
{
	
}

void bone::rotateBone(float grad)
{
	this->boneTransformable.rotate(grad);
	this->boneDrawable.rotate(grad);
	if (this->ancestors.size() != 0)
	{
		for (auto it = this->ancestors.begin(); it != this->ancestors.end(); it++)
		{
			float x = this->boneBaseJointPos_glob.x + this->getBoneLength() * std::cosf(this->boneTransformable.getRotation()* GRAD_TO_RAD_CNST);
			
			float y = this->boneBaseJointPos_glob.y + this->getBoneLength() * std::sinf(this->boneTransformable.getRotation()* GRAD_TO_RAD_CNST);
			it->setBonePos(Vector2f{ x,y });
			it->rotateBone(grad);
		}
	}
}
void bone::moveBone(Vector2f movementVector)
{
	this->boneBaseJointPos_glob += movementVector;
	float x = this->boneBaseJointPos_glob.x + this->boneLength * std::cosf(this->boneTransformable.getRotation() * GRAD_TO_RAD_CNST);
	float y = this->boneBaseJointPos_glob.y + this->boneLength * std::sinf(this->boneTransformable.getRotation() * GRAD_TO_RAD_CNST);
	this->boneOtherJointPos_glob = Vector2f{ x,y };
	this->boneTransformable.setPosition(this->boneBaseJointPos_glob);
	this->boneDrawable.setPosition(this->boneTransformable.getPosition());
	if (this->ancestors.size() != 0)
	{
		for (auto it = this->ancestors.begin(); it != this->ancestors.end(); it++)
		{
			it->moveBone(movementVector);
		}
	}
}
float bone::getBoneLength()
{
	/*float x = this->boneOtherJointPos_glob.x - this->boneBaseJointPos_glob.x;
	float y = this->boneOtherJointPos_glob.y - this->boneBaseJointPos_glob.y;
	return std::sqrt(x * x + y * y);*/
	return this->boneLength;
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
	float length = this->getBoneLength();
	this->boneBaseJointPos_glob = newPos;
	this->boneOtherJointPos_glob = Vector2f{ this->boneBaseJointPos_glob.x + length, this->boneBaseJointPos_glob.y };
	this->boneTransformable.setPosition(this->boneBaseJointPos_glob);
	this->boneDrawable.setPosition(this->boneTransformable.getPosition());
	
}

void bone::updateboneDrawable()
{

	this->boneDrawable.setOrigin(Vector2f{ 0.5f, 0.5f });
	this->boneDrawable.setPosition(this->boneBaseJointPos_glob);
	this->boneDrawable.setSize(Vector2f{ this->getBoneLength(),1 });
	this->boneDrawable.setRotation(getAngleFromTwoPoints(this->boneBaseJointPos_glob, this->boneOtherJointPos_glob, this->getBoneLength()));
}