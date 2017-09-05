#include<Siv3D.hpp>

class Drag{
public:
	Point clicked;
	void update(){
		if(Input::MouseL.clicked){
			clicked=Mouse::Pos();
		}
	}
	Point from() const{return clicked;};
	Point to() const{return Mouse::Pos();};
	int32 duration(){return Input::MouseL.pressedDuration;};
	double length(){return from().distanceFrom(to());};
	double radian(){return Atan2((double)(to().y-from().y),to().x-from().x);};

	bool moved(){return from()!=to();};
};

inline Line getLine(const Point& base,double length,double radian){
	return Line(base,{base.x+length*cos(radian),base.y+length*sin(radian)});
}

class Unit{
	static constexpr double friction=-4.0/60;
public:
	Vec2 pos,speed{0,0};
	Unit(const Vec2& pos={0,0})
		:pos(pos){
	};
	void update(){
		pos.moveBy(speed);
		const double dir=Atan2(speed.y,speed.x);

		if(Abs(speed.x)<cos(dir)*-friction)
			speed.x=0;
		else
			speed.x+=cos(dir)*friction;
		if(Abs(speed.y)<sin(dir)*-friction)
			speed.y=0;
		else
			speed.y+=sin(dir)*friction;
	}
	void accel(double v,double radian){
		speed.moveBy(cos(radian)*v,sin(radian)*v);
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

	const Font debug(10);
	while (System::Update()){
		drag.update();
		unit.update();

		debug(drag.radian()).draw(0,0);
		debug(unit.pos).draw(0,20);
		debug(unit.speed).draw(0,40);
		if(Input::MouseL.clicked){
			powercircleease.reset();
			powercircleease.start();
		}
		if(Input::MouseL.pressed){
			getLine(drag.from(),drag.length()+3.2,drag.radian())
				.drawArrow( 9.0,{15.0,15.0},Palette::Black);
			getLine(drag.from(),drag.length()    ,drag.radian())
				.drawArrow( 5.0,{10.0,10.0},Palette::White);
			Circle(drag.from(),powercircleease.easeOut()+drag.duration()/120.0)
				.drawShadow({0,0},10,3,Palette::Black)
				.draw(Palette::White);
		}
		if(Input::MouseL.released&&drag.moved()){
			unit.accel(drag.duration()/3.0/60.0,drag.radian());
		}
		Circle(unit.pos,10).draw(Palette::Red);
	}
}
