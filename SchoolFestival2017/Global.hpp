#pragma once
#include<Siv3D.hpp>
#include<HamFramework.hpp>
enum class Scene{
	Title,
	Game,
	Result,
	Ranking,
	Rule
};
struct Object{
	Point pos;
	size_t id;
	int time;
};
class GlobalData{
public:
	int score;
	Array<Object>seeds,flowers;
	String playername=L"‚Í‚¿";
};
using MySceneManager=SceneManager<Scene,GlobalData>;

namespace Name{

	const String font		=L"font";
	const String font_large	=L"font_l";
	const String font_small	=L"font_s";
	const String fontname	=L"Rounded-X Mgen+ 1pp regular";
	namespace File{
		const String highscore=L"highscore.fal";
		const String font	=L"resources/font/rounded-x-mgenplus-1pp-regular.ttf";
		const String BG		=L"resources/background.png";
		const String nuts	=L"resources/nuts_himawari_single_small.png";
		const String kyuukon=L"resources/flower_tulip_kyuukon_single.png";
		const String bee	=L"resources/mitsubachi_new.png";
	}
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
		const String sky	=L"flower_skyblue";
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

namespace GColor{
	const Color darkblack={0,0,0,150};
	const Color lightblack={0,0,0,100};
}

inline bool _registerflower(const String& v){
	return TextureAsset::Register(v,L"resources/small_"+v+L".png");
}
bool registerAssets(){
	bool error=false;

	error|=!FontManager::Register(Name::File::font);
	error|=!FontAsset::Register(Name::font		,35,Name::fontname);
	error|=!FontAsset::Register(Name::font_large,50,Name::fontname);
	error|=!FontAsset::Register(Name::font_small,15,Name::fontname);
	for(auto c:Name::Flower::colors)
		error|=!_registerflower(c);
	error|=!TextureAsset::Register(Name::BG				,Name::File::BG);
	error|=!TextureAsset::Register(Name::bee			,Name::File::bee);
	error|=!TextureAsset::Register(Name::Seed::kyuukon	,Name::File::kyuukon);
	error|=!TextureAsset::Register(Name::Seed::nuts		,Name::File::nuts);

	return !error;
}
