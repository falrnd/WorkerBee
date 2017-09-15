#pragma once
#include"Global.hpp"

#include<Siv3D/String.hpp>

class TitleScene:public MySceneManager::Scene{
public:
	const RoundRect
		start{260,400,270,70,40},//start{180,400,270,70,40},
		rule {510,400,270,70,40},
		rank {430,480,270,70,40};//rank {510,480,270,70,40};
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
		FontAsset(Name::font_large)(L"ハタラキバチ")
			.drawCenter({Window::Center().x,150});
		FontAsset(Name::font      )(L"- Worker Bee -")
			.draw({470,180});

		Rect(440,285,700,60)
			.draw     ({255,255,255,100})
			.drawFrame(1,1,GColor::darkblack);
		FontAsset(Name::font)(L"おなまえは？："+m_data->playername)
			.draw(150,280);


		FontAsset(Name::font_small)(L"(ランクインするとのこります)")
			.draw(150,350);

		start.draw(start.mouseOver?GColor::lightbrown:GColor::darkbrown);
		//rule.draw(rule .mouseOver?GColor::lightbrown:GColor::darkbrown);
		rank.draw(rank .mouseOver?GColor::lightbrown:GColor::darkbrown);

		FontAsset(Name::font)(L"はじめる")
			.drawCenter(start.center);
		//FontAsset(Name::font)(L"あそびかた")
		//	.drawCenter(rule.center);
		FontAsset(Name::font)(L"ランキング")
			.drawCenter(rank.center);
	}
};