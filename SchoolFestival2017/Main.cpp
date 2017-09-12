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

	mng.setFadeColor({0,0,0,100});
	mng.init(Scene::Game);

	while (System::Update()){
		TextureAsset(L"BG").draw();

		if(!mng.updateAndDraw())
			break;
	}
}
