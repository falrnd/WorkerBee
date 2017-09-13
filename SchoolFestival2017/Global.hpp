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
	const int seedslimit=3;
	int score;
	Array<Object>seeds,flowers;
};
using MySceneManager=SceneManager<Scene,GlobalData>;

namespace Name{
	const String font	=L"font";
	constexpr int fontsize	=20;
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
