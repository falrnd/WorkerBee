#pragma once

#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Global.hpp"

#include"GameScene.hpp"
#include"ResultScene.hpp"
#include"TitleScene.hpp"
#include"RankScene.hpp"
#include"RuleScene.hpp"

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
	mng.init(Scene::Title);

	Window::SetTitle(L"Worker Bee ver 1.1");

	while (System::Update()){
		TextureAsset(Name::BG).draw();

		if(!mng.updateAndDraw())
			break;
	}
}
