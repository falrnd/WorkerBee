#pragma once
#include"Global.hpp"
class TitleScene:public MySceneManager::Scene{
public:
	const RoundRect
		start{110,400,350,120,40},
		rank {500,400,350,120,40};
	void update() override{
		if(start.leftClicked){
			changeScene(Scene::Game);
		}
		if(rank.leftClicked){
			changeScene(Scene::Ranking,0);
		}

		Input::GetCharsHelper(m_data->playername);
	}
	void draw() const override{
		FontAsset(Name::font_large)(L"ここに素晴らしいタイトル")
			.drawCenter({Window::Center().x,200});

		FontAsset(Name::font)(L"おなまえは？："+m_data->playername)
			.draw(150,280);
		FontAsset(Name::font_small)(L"(ランクインするとのこります)")
			.draw(150,350);

		start
			.draw(start.mouseOver?GColor::lightblack:GColor::darkblack);
		rank 
			.draw(rank .mouseOver?GColor::lightblack:GColor::darkblack);

		FontAsset(Name::font_large)(L"はじめる")
			.drawCenter(start.center);
		FontAsset(Name::font_large)(L"ランキング")
			.drawCenter(rank.center);
	}
};