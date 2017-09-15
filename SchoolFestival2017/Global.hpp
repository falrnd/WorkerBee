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
	const String
		font		=L"font",
		font_large	=L"font_l",
		font_small	=L"font_s",
		fontname	=L"Rounded-X Mgen+ 1pp regular";
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
		const String
			blue	=L"flower_blue"  ,
			brown	=L"flower_brown" ,
			green	=L"flower_green" ,
			orange	=L"flower_orange",
			pink	=L"flower_pink"  ,
			purple	=L"flower_purple",
			red		=L"flower_red"   ,
			sky		=L"flower_skyblue",
			yellow	=L"flower_yellow";
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
	const Color darkbrown={165,42,42,150};
	const Color lightbrown={165,42,42,100};
	const Color brown=Palette::Brown;
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
