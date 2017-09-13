#pragma once
#include <Siv3D.hpp>
class Unit{
private:
	static constexpr double friction=-4.5/60;
public:
	Vec2 pos,speed{0,0};
	Unit(const Vec2& pos={0,0})
		:pos(pos){
	};
	void update(){
		pos.moveBy(speed);
		if(!speed.isZero()){
			const Vec2 dir=speed.normalized();
			const double dx=dir.x*-friction, dy=dir.y*-friction;

			if(Abs(speed.x)<dx)
				speed.x=0;
			else
				speed.x-=dx;
			if(Abs(speed.y)<dy)
				speed.y=0;
			else
				speed.y-=dy;
		}
	}
	void accel(double v, const Vec2& direction){
		speed.moveBy(Vec2(direction).setLength(v));
	}
};