#pragma once

#include<Siv3D.hpp>

#include"Global.hpp"

#include"Unit.hpp"
#include"Drag.hpp"

inline Line getLine(const Vec2& base, double length, const Vec2& direction){
	return Line(base, base+Vec2(direction).setLength(length));
}
inline double vec2ToRadian(const Vec2& v){
	return Atan2(v.y,v.x);
}

class GameScene:public MySceneManager::Scene{
private:
	const int hitsize=50;
public:
	Drag drag;
	Unit unit;
	EasingController<double> powercircleease;
	Stopwatch stopwatch;
	void init() override{
		drag=Drag();
		unit=Unit({240,240});
		powercircleease=EasingController<double>(
			0.0,
			10.0,
			Easing::Circ,
			700.0
			);
		m_data->score=0;

		stopwatch=Stopwatch(true);
	}
	void update() override{
		drag.update();
		unit.update();

		if(Input::MouseL.clicked){
			powercircleease.reset();
			powercircleease.start();
		}

		auto it = m_data->seeds.begin();
		const int curtimemilli = stopwatch.ms();
		while(it != m_data->seeds.end()){
			if(it->pos.distanceFrom(unit.pos)<=hitsize){
				++m_data->score;
				m_data->flowers.push_back(
					Object{
						Point(it->pos),
						Random(Name::Flower::colors.size()-1),
						curtimemilli
					}
				);
				it = m_data->seeds.erase(it);
			}else{
				++it;
			}
		}

		while(m_data->seedslimit > m_data->seeds.size()){
			m_data->seeds.push_back(
				Object{
					Point{Random(960),Random(640)},
					Random(Name::Seed::colors.size()-1),
					curtimemilli
				}
			);
		}

		//FontAsset(L"font").draw(L"‚Ù‚°");
 		if(Input::MouseL.released&&drag.moved()){
			unit.accel(drag.duration()/3.0/60.0, drag.direction());
		}
	}
	void draw() const override{

		const int curtimemilli = stopwatch.ms();

		constexpr bool DEBUG=false;

		for(Object& o:m_data->flowers){
			const int livetime=curtimemilli-o.time;
			TextureAsset(Name::Flower::colors[o.id])
				.scale(EaseOut(0.0,0.5,Easing::Elastic,Min(livetime/1000.0,0.5)))
 				.rotate(livetime/4000.0*TwoPi)
				.drawAt(o.pos);
		}

		FontAsset(Name::font)(ToString(m_data->score)+L"‚±").draw({50,50}, Palette::White);
		FontAsset(Name::font)(L"‚Ì‚±‚è"+ToString(30-stopwatch.s())+L"‚Ñ‚å‚¤").draw({50,100}, Palette::White);

		for(Object& o:m_data->seeds){
			if(DEBUG)
				Circle(o.pos, hitsize).draw(Palette::Blue);
			const int livetime=curtimemilli-o.time;
			TextureAsset(Name::Seed::colors[o.id])
				.scale(EaseOut(0.0, 0.3, Easing::Elastic, Min(livetime/1000.0, 0.5)))
				.rotate(livetime/4000.0*TwoPi)
				.drawAt(o.pos);
		}

		//Circle(unit.pos,30).draw({165,42,42,200});
		(unit.speed.x>=0?
			TextureAsset(Name::bee).mirror():
			TextureAsset(Name::bee)
			)
			.scale(0.2)
			.drawAt(unit.pos);

		if(Input::MouseL.pressed){
			getLine(drag.from(), drag.duration()/1000.0*180+3.2, drag.direction())
				.drawArrow(9.0, {15.0,15.0}, {100,100,100});
			getLine(drag.from(), drag.duration()/1000.0*180, drag.direction())
				.drawArrow(5.0, {10.0,10.0}, Palette::White);
			Circle(drag.from(), powercircleease.easeOut()+drag.duration()/120.0)
				.drawShadow({0,0}, 10, 2.5, Palette::Black)
				.draw(Palette::White);
		}
	}
};