#pragma once
#include"Global.hpp"
class RankScene:public MySceneManager::Scene{
public:
	Array<String> strs;
	bool loadfailed=true;
	void init() override{
		TextReader reader(L"highscore.txt");
		for(int i=0;i<10;++i){
			auto o=reader.readLine();
			if(!o.has_value()){
				loadfailed=true;
				return;
			}
			strs.push_back(*o);
		}
	}
	void update() override{
		if(Input::MouseL.clicked){
			changeScene(Scene::Title,0);
		}
	}
	void draw() const override{
		FontAsset(Name::font_large)(L"ランキング")
			.drawCenter(Window::Center().x,120);
		FontAsset(Name::font)(L"クリックで戻る")
			.drawCenter(Window::Center().x,540);
		if(loadfailed){
			FontAsset(Name::font)(L"読み込めませんでした……")
				.drawCenter(Window::Center());
		}else{
			for(int i=0;i<10;i+=2){
				FontAsset(Name::font)(strs[i])
					.draw(100,i*35+150);
				FontAsset(Name::font)(strs[i+1])
					.draw(700,i*35+150);
			}
		}
	}
};