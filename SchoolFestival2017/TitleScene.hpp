#pragma once
#include"Global.hpp"
class TitleScene:public MySceneManager::Scene{
public:
	const RoundRect
		start{110,320,350,200,40},
		rank{500,320,350,200,40};
	void update() override{
		if(start.leftClicked){
			changeScene(Scene::Game);
		}
		if(rank.leftClicked){
			changeScene(Scene::Ranking);
		}
	}
	void draw() const override{
		FontAsset(Name::font_large)(L"ここに素晴らしいタイトル")
			.drawCenter({Window::Center().x,200});

		const Color df={0,0,0,150};
		const Color mo={0,0,0,100};

		start.draw(start.mouseOver?mo:df);
		rank.draw(rank.mouseOver?mo:df);

		FontAsset(Name::font_large)(L"はじめる")
			.drawCenter(start.center);
		FontAsset(Name::font_large)(L"ランキング")
			.drawCenter(rank.center);
	}
};