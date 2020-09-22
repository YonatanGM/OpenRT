#include "openrt.h"
#include "core/timer.h"

using namespace rt;

int main() 
{
	const Vec3f	bgColor = RGB(255, 255, 255);
	const Size	resolution = Size(800, 600);
	const float intensity = 1000;

	// Scene
	CScene scene(bgColor);
	
	// Shaders
	auto pShaderFloor = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40.0f);
	auto pShaderDragon = std::make_shared<CShaderPhong>(scene, RGB(1, 1, 1), 0.1f, 0.9f, 0.0f, 40.0f);

	// Floor
	float s = 50;
	scene.add(CSolidQuad(pShaderFloor, Vec3f(-s, 0, -s), Vec3f(-s, 0, s), Vec3f(s, 0, s), Vec3f(s, 0, -s)));
#ifndef ENABLE_BSP
	RT_WARNING("BSP is not enabled");
#endif // !ENABLE_BSP
	// Stanford Dragon
	CSolid dragon(pShaderDragon, dataPath + "Stanford Dragon.obj");
	CTransform t;
	dragon.transform(t.scale(2.51f).rotate(Vec3f(0, 1, 0), 45).get());
	scene.add(dragon);
	

	// Camera
	float r = 35;
	auto pCamera	= std::make_shared<CCameraPerspectiveTarget>(resolution, Vec3f::all(r), Vec3f(0, 5, 0), Vec3f(0, 1, 0), 45.0f);
	auto pLight		= std::make_shared<CLightOmni>(Vec3f::all(intensity), Vec3f(0, 2 * r, 0));
	auto pLightSky	= std::make_shared<CLightSky>(Vec3f::all(1.0f), 50.0f, std::make_shared<CSamplerStratified>(4, true, true));
	
	
	scene.add(pCamera);
//	scene.add(pLight);
	scene.add(pLightSky);

	
	scene.buildAccelStructure();
	
	Timer::start("Rendering... ");
	Mat img = scene.render(std::make_shared<CSamplerStratified>(1));
	//Mat depth = scene.renderDepth(std::make_shared<CSamplerStratified>(4, true, true));
	//depth.convertTo(img, CV_8UC1);
	Timer::stop();

	imshow("image", img);
	imwrite("D:\\renders\\res.jpg", img);
	waitKey();
	return 0;
}