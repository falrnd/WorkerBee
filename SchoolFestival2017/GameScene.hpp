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
	const int hitsize	=50;
	const size_t seedslimit=5;
public:
	Drag drag;
	Unit unit;
	EasingController<double> powercircleease;
	Stopwatch stopwatch_start;
	Stopwatch stopwatch_main;
	Stopwatch stopwatch_finish;
	void init() override{
		drag=Drag();
		unit=Unit(Window::Center());
		powercircleease=EasingController<double>(
			0.0,
			10.0,
			Easing::Circ,
			700.0
			);
		m_data->score=0;
		m_data->seeds.clear();
		m_data->flowers.clear();
		stopwatch_start=Stopwatch();
		stopwatch_main=Stopwatch();
		stopwatch_finish=Stopwatch();
	}
	void update() override{
		{
			//時間制御
			if(!stopwatch_start.isActive())
				stopwatch_start.start();
			if(stopwatch_start.isActive()&&stopwatch_start.ms()>1500){
				stopwatch_main.start();
				stopwatch_start.pause();
			}
			if(stopwatch_main.ms()>30000){
				stopwatch_main.pause();
				stopwatch_finish.start();
			}
			if(stopwatch_finish.ms()>2500){
				changeScene(Scene::Result);
			}
		}

		drag.update();
		unit.update();
		//溜めの円のサイズのリセット
		if(Input::MouseL.clicked){
			powercircleease.reset();
			powercircleease.start();
		}
		{
			//種の当たり判定
			auto it = m_data->seeds.begin();
			const int curtimemilli = stopwatch_main.ms();
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
			//種配置
			while(seedslimit > m_data->seeds.size()){
				m_data->seeds.push_back(
					Object{
					RandomPoint(Window::ClientRect()),
					Random(Name::Seed::colors.size()-1),
					curtimemilli
				}
				);
			}
		}
		//自機移動
		if(!stopwatch_main.isPaused()&&Input::MouseL.released&&drag.moved()){
			unit.accel(drag.duration()/3.0/60.0, drag.direction());
		}
	}
	void draw() const override{
		{
			//スタート
			const int m=stopwatch_start.ms();
			if(m<1000){
				FontAsset(Name::font)(L"よーい・・・").drawCenter(Window::Center());
				return;
			}else if(m<1500){
				FontAsset(Name::font)(L"スタート！").drawCenter(Window::Center());
				return;
			}
		}

		if(stopwatch_main.isActive()){
			//プレイ中
			const int curtimemilli = stopwatch_main.ms();
			for(Object& o:m_data->flowers){
				const int livetime=curtimemilli-o.time;
				TextureAsset(Name::Flower::colors[o.id])
					.scale(EaseOut(0.0,0.5,Easing::Elastic,Min(livetime/1000.0,0.5)))
					.rotate(livetime/4000.0*TwoPi)
					.drawAt(o.pos);
			}

			FontAsset(Name::font)(ToString(m_data->score)+L"こ")
				.draw({40,80}, Palette::White);
			FontAsset(Name::font)(L"のこり"+ToString(30-stopwatch_main.s())+L"びょう")
				.draw({40,30}, Palette::White);

			for(Object& o:m_data->seeds){
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

			if(Input::MouseL.pressed&&!stopwatch_main.isPaused()){
				getLine(drag.from(), drag.duration()/1000.0*180+3.2, drag.direction())
					.drawArrow(9.0, {15.0,15.0}, {100,100,100});
				getLine(drag.from(), drag.duration()/1000.0*180, drag.direction())
					.drawArrow(5.0, {10.0,10.0}, Palette::White);
				Circle(drag.from(), powercircleease.easeOut()+drag.duration()/120.0)
					.drawShadow({0,0}, 10, 2.5, Palette::Black)
					.draw(Palette::White);
			}
		}
		if(stopwatch_finish.isActive()){
			//終了
			FontAsset(Name::font)(L"おしまい！").drawCenter(Window::Center());
		}
	}
};