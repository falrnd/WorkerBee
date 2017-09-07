#pragma once
#include<Siv3D.hpp>
class Drag{
private:
	Point clicked;
public:
	void update(){
		if(Input::MouseL.clicked){
			clicked=Mouse::Pos();
		}
	}
	Point	from() const{return clicked;};
	Point	to() const{return Mouse::Pos();};
	int32	duration(){return Input::MouseL.pressedDuration;};
	double	length(){return from().distanceFrom(to());};
	Vec2	direction(){ return Vec2(to()-from()).normalize(); };
	bool	moved(){return from()!=to();};
};