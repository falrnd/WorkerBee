#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
enum class Scene{
	Title,
	Game,
	Result,
	Ranking
};
struct Object{
	Point pos;
	int id;
};
class GlobalData{
	const int seedslimit=3;
	int score;
	Array<Object>seeds,flowers;
};
using MySceneManager=SceneManager<Scene,GlobalData>;

namespace Name{
	const String BG		=L"BG";
	const String bee	=L"bee";
	namespace Seed{
		const String nuts	=L"nuts";
		const String kyuukon=L"kyuukon";
		const Array<String> colors={
			nuts,
			kyuukon
		};
	}
	namespace Flower{
		const String blue	=L"flower_blue"  ;
		const String brown	=L"flower_brown" ;
		const String green	=L"flower_green" ;
		const String orange	=L"flower_orange";
		const String pink	=L"flower_pink"  ;
		const String purple	=L"flower_purple";
		const String red	=L"flower_red"   ;
		const String sky	=L"flower_sky"   ;
		const String yellow	=L"flower_yellow";
		const Array<String> colors={
			blue,
			brown,
			green,
			orange,
			pink,
			purple,
			red,
			sky,
			yellow
		};
	}
}

inline bool _registerflower(const String& v){
	return TextureAsset::Register(v,L"resources/small_"+v+L".png");
}

bool registerAssets(){
	bool error=false;

	error|=!FontManager::Register(L"resources/nekokaburi.otf");
	error|=!FontAsset::Register(L"font",40,L"‚Ë‚±‚©‚Ô‚è");
	for(auto c:Name::Flower::colors)
		error|=!_registerflower(c);
	error|=!TextureAsset::Register(Name::BG,			L"resources/background.png");
	error|=!TextureAsset::Register(Name::Seed::nuts,	L"resources/nuts_himawari_single.png");
	error|=!TextureAsset::Register(Name::Seed::kyuukon,	L"resources/flower_tulip_kyuukon_single.png");
	error|=!TextureAsset::Register(Name::bee,			L"resources/mitsubachi_new.png");

	return !error;
}