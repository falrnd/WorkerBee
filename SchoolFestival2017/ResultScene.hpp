#pragma once
#include"Global.hpp"

#include<algorithm>

class ResultScene:public MySceneManager::Scene{
public:
	RoundRect totitle{550,450,300,100,40};
	bool rankin=false;
	void init(){
		m_data->playername=
			Regex::ReplaceAll(
				m_data->playername,
				L"\\s",
				L""
			);

		Array<std::pair<int,String>>a;
		{
			TextReader reader(Name::File::highscore);
			for(int i=0;i<5;++i){
				auto name=reader.readLine();
				auto score=reader.readLine();
				if(name.has_value()&&score.has_value()){
					a.push_back(std::make_pair(Parse<int>(*score),*name));
				}
			}
			reader.close();
		}
		{
			if(a.size()<5||a[4].first<m_data->score){
				rankin=true;

				a.push_back(std::make_pair(m_data->score,m_data->playername));
				std::sort(a.rbegin(),a.rend());
				if(a.size()>5)
					a.pop_back();

				TextWriter writer(Name::File::highscore);
				writer.clear();
				for(auto& o:a){
					writer.writeln(o.second);
					writer.writeln(o.first);
				}
				writer.close();
			}
		}
	}
	void update() override{
		if(totitle.leftClicked){
			changeScene(Scene::Title);
		}
	}
	void draw() const override{
		FontAsset(Name::font)(
			m_data->playername
			+L"さんの\nあつめたたねは……　　"
			+ToString(m_data->score)
			+L"こ！"
			)
			.draw(150,150);
		totitle
			.draw(totitle.mouseOver?GColor::lightblack:GColor::darkblack);
		
		if(rankin){
			FontAsset(Name::font)(L"ランクイン！")
				.draw(150,380);
		}

		FontAsset(Name::font)(L"もどる")
			.drawCenter(totitle.center);
	}
};