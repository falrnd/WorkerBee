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
	int32	duration() const{return Input::MouseL.pressedDuration;};
	double	length() const{return from().distanceFrom(to());};
	Vec2	direction() const{ return Vec2(to()-from()).normalize(); };
	bool	moved() const{return from()!=to();};
};