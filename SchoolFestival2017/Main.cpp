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
	double	radian(){ return Atan2((double)(to().y-from().y), to().x-from().x); };
	Vec2	direction(){ return Vec2(to()-from()).normalize(); };
	bool	moved(){return from()!=to();};
};

/*
inline Line getLine(const Vec2& base, double length, double radian){
	return Line(base, {base.x+length*cos(radian),base.y+length*sin(radian)});
}
*/
inline Line getLine(const Vec2& base, double length, const Vec2& direction){
	return Line(base, base+Vec2(direction).setLength(length));
}

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
		/*
		const double dir=Atan2(speed.y, speed.x);
		const double dx=cos(dir)*-friction,dy=sin(dir)*-friction;
		LOG_DEBUG(dir);
		*/
		if(!speed.isZero()){
			const Vec2 dir=speed.normalized();
			const double dx=dir.x*-friction, dy=dir.y*-friction;
			LOG_DEBUG(dir);

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
	/*
	void accel(double v, double radian){
		speed.moveBy(cos(radian)*v, sin(radian)*v);
	}
	*/
	void accel(double v, const Vec2& direction){
		speed.moveBy(Vec2(direction).setLength(v));
	}
};

void Main(){
	Window::Resize(960,640);
	Graphics::SetBackground(Palette::Green);
	Drag drag;
	Unit unit({240,240});
	EasingController<double> powercircleease(
		 0.0,
		10.0,
		Easing::Circ,
		700.0);

	FontManager::Register(L"resources/nekokaburi.otf");
	FontAsset::Register(L"font",40,L"ねこかぶり");
	while (System::Update()){
		drag.update();
		unit.update();

		if(Input::MouseL.clicked){
			powercircleease.reset();
			powercircleease.start();
		}

		FontAsset(L"font").draw(L"ほげ");

		if(Input::MouseL.pressed){
			getLine(drag.from(), drag.duration()/1000.0*150+3.2, drag.direction())
				.drawArrow( 9.0,{15.0,15.0},Palette::Black);
			getLine(drag.from(), drag.duration()/1000.0*150    , drag.direction())
				.drawArrow( 5.0,{10.0,10.0},Palette::White);
			LOG_DEBUG(drag.duration());
			Circle(drag.from(),powercircleease.easeOut()+drag.duration()/120.0)
				.drawShadow({0,0},10,3,Palette::Black)
				.draw(Palette::White);
		}
		if(Input::MouseL.released&&drag.moved()){
			unit.accel(drag.duration()/3.0/60.0, drag.direction());
		}
		Circle(unit.pos,10).draw(Palette::Red);
	}
}
