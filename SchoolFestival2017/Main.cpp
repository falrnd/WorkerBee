#pragma once

#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Global.hpp"
#include"Unit.hpp"
#include"Drag.hpp"

#include"GameScene.hpp"
#include"ResultScene.hpp"
#include"TitleScene.hpp"
#include"RankScene.hpp"
#include"RuleScene.hpp"

inline Line getLine(const Vec2& base, double length, const Vec2& direction){
	return Line(base, base+Vec2(direction).setLength(length));
}
inline double vec2ToRadian(const Vec2& v){
	return Atan2(v.y,v.x);
}

inline bool _registerflower(const String& v){
	return TextureAsset::Register(v,L"resources/small_"+v+L".png");
}
bool registerAssets(){
	bool error=false;

	error|=!FontManager::Register(L"resources/nekokaburi.otf");
	error|=!FontAsset::Register(L"font",40,L"ねこかぶり");
	for(auto c:Name::Flower::colors)
		error|=!_registerflower(c);
	error|=!TextureAsset::Register(Name::BG,			L"resources/background.png");
	error|=!TextureAsset::Register(Name::Seed::nuts,	L"resources/nuts_himawari_single.png");
	error|=!TextureAsset::Register(Name::Seed::kyuukon,	L"resources/flower_tulip_kyuukon_single.png");
	error|=!TextureAsset::Register(Name::bee,			L"resources/mitsubachi_new.png");

	return !error;
}
void Main(){
	if(!registerAssets()){
		LOG(L"File Loading Failed");
		return;
	}

	Window::Resize(960,640);

	MySceneManager mng;
	mng.add<TitleScene>(Scene::Title);
	mng.add<GameScene>(Scene::Game);
	mng.add<RuleScene>(Scene::Rule);
	mng.add<ResultScene>(Scene::Result);
	mng.add<RankScene>(Scene::Ranking);

	Drag drag;
	Unit unit({240,240});
	EasingController<double> powercircleease(
		0.0,
		10.0,
		Easing::Circ,
		700.0);
	Graphics::SetBackground(Palette::Green);
	while (System::Update()){
		TextureAsset(L"BG").draw();

		drag.update();
		unit.update();

		if(Input::MouseL.clicked){
			powercircleease.reset();
			powercircleease.start();
		}

		//FontAsset(L"font").draw(L"ほげ");

		if(Input::MouseL.pressed){
			getLine(drag.from(), drag.duration()/1000.0*150+3.2, drag.direction())
				.drawArrow( 9.0,{15.0,15.0},{100,100,100});
			getLine(drag.from(), drag.duration()/1000.0*150    , drag.direction())
				.drawArrow( 5.0,{10.0,10.0},Palette::White);
			Circle(drag.from(),powercircleease.easeOut()+drag.duration()/120.0)
				.drawShadow({0,0},10,2.5,Palette::Black)
				.draw(Palette::White);
		}
		if(Input::MouseL.released&&drag.moved()){
			unit.accel(drag.duration()/3.0/60.0, drag.direction());
		}

		//Circle(unit.pos,30).draw({165,42,42,200});
		(unit.speed.x>=0?
			TextureAsset(Name::bee).mirror():
			TextureAsset(Name::bee)
			)
			.scale(0.2)
			.drawAt(unit.pos);
	}
}
