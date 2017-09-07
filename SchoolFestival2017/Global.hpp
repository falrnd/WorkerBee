#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
enum class Scene{
	Title,
	Game,
	Result,
	Ranking
};
struct GlobalData{

};
using MySceneManager=SceneManager<Scene,GlobalData>;

namespace Name{
	const String BG		=L"BG";
	const String nuts	=L"nuts";
	const String kyuukon=L"kyuukon";
	const String bee	=L"bee";
	namespace Flower{
		const String blue	=L"flower_blue";
		const String brown	=L"flower_brown";
		const String green	=L"flower_green";
		const String orange	=L"flower_orange";
		const String pink	=L"flower_pink";
		const String purple	=L"flower_purple";
		const String red	=L"flower_red";
		const String sky	=L"flower_sky";
		const String yellow	=L"flower_yellow";
	}
}

const String root=L"resources/";
inline bool _register(const String& v){
	return TextureAsset::Register(v,root+L"small_"+v+L".png");
}

bool registerAssets(){
	bool error=false;

	error|=!FontManager::Register(root+L"nekokaburi.otf");
	error|=!FontAsset::Register(L"font",40,L"‚Ë‚±‚©‚Ô‚è");
	error|=!_register(Name::Flower::blue);
	error|=!_register(Name::Flower::brown);
	error|=!_register(Name::Flower::green);
	error|=!_register(Name::Flower::orange);
	error|=!_register(Name::Flower::pink);
	error|=!_register(Name::Flower::purple);
	error|=!_register(Name::Flower::red);
	error|=!_register(Name::Flower::sky);
	error|=!_register(Name::Flower::yellow);
	error|=!TextureAsset::Register(Name::BG,		root+L"background.png");
	error|=!TextureAsset::Register(Name::nuts,		root+L"nuts_himawari_single.png");
	error|=!TextureAsset::Register(Name::kyuukon,	root+L"flower_tulip_kyuukon_single.png");
	error|=!TextureAsset::Register(Name::bee,		root+L"mitsubachi_new.png");

	return !error;
}