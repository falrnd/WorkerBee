#pragma once
#include"Global.hpp"
class RankScene:public MySceneManager::Scene{
public:
	Array<String> strs;
	void init() override{
		TextReader reader(Name::File::highscore);
		for(int i=0;i<10;++i){
			auto o=reader.readLine();
			if(!o.has_value()){
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
		if(strs.size()==0){
			FontAsset(Name::font)(L"読み込めませんでした……")
				.drawCenter(Window::Center());
		}else{
			for(size_t i=0;i<strs.size();i+=2){
				FontAsset(Name::font)(strs[i]+L"さん")
					.draw(100,(double)(i*35+150));
				FontAsset(Name::font)(strs[i+1])
					.draw(700,(double)(i*35+150));
			}
		}
	}
};