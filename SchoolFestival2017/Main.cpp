#pragma once

#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Global.hpp"

#include"GameScene.hpp"
#include"ResultScene.hpp"
#include"TitleScene.hpp"
#include"RankScene.hpp"
#include"RuleScene.hpp"

inline bool _registerflower(const String& v){
	return TextureAsset::Register(v,L"resources/small_"+v+L".png");
}
bool registerAssets(){
	bool error=false;

	error|=!FontManager::Register(Name::File::font);
	error|=!FontAsset::Register(Name::font,Name::fontsize,Name::fontname);
	for(auto c:Name::Flower::colors)
		error|=!_registerflower(c);
	error|=!TextureAsset::Register(Name::BG				,Name::File::BG);
	error|=!TextureAsset::Register(Name::bee			,Name::File::bee);
	error|=!TextureAsset::Register(Name::Seed::kyuukon	,Name::File::kyuukon);
	error|=!TextureAsset::Register(Name::Seed::nuts		,Name::File::nuts);

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

	mng.setFadeColor({0,0,0,100});
	mng.init(Scene::Game);

	while (System::Update()){
		TextureAsset(Name::BG).draw();

		if(!mng.updateAndDraw())
			break;
	}
}
