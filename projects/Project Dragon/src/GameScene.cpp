#include "GameScene.h"
#include <IBehaviour.h>
#include <CameraControlBehaviour.h>
#include <PhysicsBody.h>
#include <GreyscaleEffect.h>
#include <ColorCorrection.h>
#include <InstantiatingSystem.h>
#include <AssetLoader.h>
#include <Player.h>
#include <WorldBuilderV2.h>
#include "Enemy.h"


void MainGameScene::InitGameScene()
{
	GameScene::RegisterComponentType<Camera>();
	GameScene::RegisterComponentType<RendererComponent>();
	GameScene::RegisterComponentType<BehaviourBinding>();
	GameScene::RegisterComponentType<PhysicsBody>();

	scene = GameScene::Create("GameScene");
	Application::Instance().ActiveScene = scene;
	RenderingManager::activeScene = scene;

	Texture2D::sptr grass = Texture2D::LoadFromFile("image/grass.png");
	Texture2D::sptr noSpec = Texture2D::LoadFromFile("image/grassSpec.png");
	Texture2D::sptr wp = Texture2D::LoadFromFile("image/WOODPLANK.png");
	Texture2D::sptr torch = Texture2D::LoadFromFile("image/TORCH.png");
	TextureCubeMap::sptr environmentMap = TextureCubeMap::LoadFromImages("image/skybox/ToonSky.jpg");

	Texture2D::sptr hand = Texture2D::LoadFromFile("image/handtexture.png");

	// Creating an empty texture
	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	// Clear it with a white colour
	texture2->Clear();

	ShaderMaterial::sptr Floor_Mat = ShaderMaterial::Create();
	Floor_Mat->Shader = RenderingManager::NoOutline;
	Floor_Mat->Set("s_Diffuse", grass);
	Floor_Mat->Set("s_Specular", noSpec);
	Floor_Mat->Set("u_Shininess", 2.0f);
	Floor_Mat->Set("u_TextureMix", 0.0f);

	ShaderMaterial::sptr handMat = ShaderMaterial::Create();
	handMat->Shader = RenderingManager::BaseShader;
	handMat->Set("s_Diffuse", hand);
	handMat->Set("s_Specular", noSpec);
	handMat->Set("u_Shininess", 1.0f);
	handMat->Set("u_TextureMix", 0.0f);

	ShaderMaterial::sptr WP_MAT = ShaderMaterial::Create();
	WP_MAT->Shader = RenderingManager::NoOutline;
	WP_MAT->Set("s_Diffuse", wp);
	WP_MAT->Set("s_Specular", noSpec);
	WP_MAT->Set("u_Shininess", 3.0f);
	WP_MAT->Set("u_TextureMix", 0.0f);


	ShaderMaterial::sptr torchMat = ShaderMaterial::Create();
	torchMat->Shader = RenderingManager::NoOutline;
	torchMat->Set("s_Diffuse", torch);
	torchMat->Set("s_Specular", noSpec);
	torchMat->Set("u_Shininess", 3.0f);
	torchMat->Set("u_TextureMix", 0.0f);

	// Create an object to be our camera
	GameObject cameraObject = scene->CreateEntity("Camera");
	{
		cameraObject.get<Transform>().SetLocalPosition(0, 0, 0).LookAt(glm::vec3(0, 1, 5));
		//cameraObject.get<Transform>().setForward(glm::vec3(0, 0, -1));
		// We'll make our camera a component of the camera object
		Camera& camera = cameraObject.emplace<Camera>();// Camera::Create();
		Player& player = cameraObject.emplace<Player>();
		camera.SetPosition(glm::vec3(0, 3, 3));
		camera.SetUp(glm::vec3(0, 0, 1));
		camera.LookAt(glm::vec3(0));
		camera.SetFovDegrees(90.0f); // Set an initial FOV
		camera.SetOrthoHeight(3.0f);

		cameraObject.emplace<PhysicsBody>();
		cameraObject.get<PhysicsBody>().AddBody(1.f, btVector3(0, 0, 5), btVector3(1, 1, 2));

		BehaviourBinding::Bind<CameraControlBehaviour>(cameraObject);
	}
	//

	GameObject obj3 = scene->CreateEntity("torch");
	{
		obj3.get<Transform>().SetLocalRotation(90, 0, 0);

		RendererComponent& RC = obj3.emplace<RendererComponent>();
		VertexArrayObject::sptr vao = ObjLoader::LoadFromFile("model/torch.obj");
		RC.SetMesh(vao);
		RC.SetMaterial(torchMat);



		PhysicsBody& p = obj3.emplace<PhysicsBody>();
		//Enemy& e = obj4.emplace<Enemy>();
		p.AddBody(0.f, btVector3(2.f, 3.f, 3.f), btVector3(2.f, 2.f, 2.f));
		//p.GetBody()->setUserIndex(5);
		//p.GetBody()->setUserPointer((void*)&e);

	}



	GameObject obj4 = scene->CreateEntity("wp");
	{
		obj4.get<Transform>().SetLocalRotation(90, 0, 0);

		RendererComponent& RC = obj4.emplace<RendererComponent>();
		VertexArrayObject::sptr vao = ObjLoader::LoadFromFile("model/wood platform.obj");
		RC.SetMesh(vao);
		RC.SetMaterial(WP_MAT);



		PhysicsBody& p = obj4.emplace<PhysicsBody>();
		//Enemy& e = obj4.emplace<Enemy>();
		p.AddBody(0.f, btVector3(2.f, 3.f,2.f), btVector3(2.f, 2.f, 2.f));
		//p.GetBody()->setUserIndex(5);
		//p.GetBody()->setUserPointer((void*)&e);

	}

	GameObject obj5 = scene->CreateEntity("plane");
	{
		obj5.get<Transform>().SetLocalRotation(90, 0, 0).SetLocalScale(10,10,10);

		RendererComponent& RC = obj5.emplace<RendererComponent>();
		VertexArrayObject::sptr vao = ObjLoader::LoadFromFile("model/plane.obj");
		RC.SetMesh(vao);
		RC.SetMaterial(Floor_Mat);

		PhysicsBody& p = obj5.emplace<PhysicsBody>();
		//Enemy& e = obj4.emplace<Enemy>();
		p.AddBody(0.f, btVector3(0.f, 0.f, 0.f), btVector3(10.f, 10.f, 1.f));
		//p.GetBody()->setUserIndex(5);
		//p.GetBody()->setUserPointer((void*)&e);

	}

	//skybox
	{
		ShaderMaterial::sptr skyboxMat = ShaderMaterial::Create();
		skyboxMat->Shader = RenderingManager::SkyBox;
		skyboxMat->Set("s_Environment", environmentMap);
		skyboxMat->Set("u_EnvironmentRotation", glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1, 0, 0))));
		skyboxMat->RenderLayer = 100;
		MeshBuilder<VertexPosNormTexCol> mesh;
		MeshFactory::AddIcoSphere(mesh, glm::vec3(0.0f), 1.0f);
		MeshFactory::InvertFaces(mesh);
		VertexArrayObject::sptr meshVao = mesh.Bake();

		GameObject skyboxObj = scene->CreateEntity("skybox");
		skyboxObj.get<Transform>().SetLocalPosition(0.0f, 0.0f, 0.0f);
		skyboxObj.get_or_emplace<RendererComponent>().SetMesh(meshVao).SetMaterial(skyboxMat);
	}

	//Blank post processing effect
	PostEffect* basicEffect;
	GameObject framebufferObject = scene->CreateEntity("Basic Effect");
	{
		int width, height;
		glfwGetWindowSize(BackendHandler::window, &width, &height);

		basicEffect = &framebufferObject.emplace<PostEffect>();
		basicEffect->Init(width, height);
	}

	//greyscale effect
	GreyscaleEffect* greyscaleEffect;
	GameObject greyScaleEffectObject = scene->CreateEntity("Greyscale Effect");
	{
		int width, height;
		glfwGetWindowSize(BackendHandler::window, &width, &height);
		greyscaleEffect = &greyScaleEffectObject.emplace<GreyscaleEffect>();
		greyscaleEffect->Init(width, height);
		greyscaleEffect->SetIntensity(0.f);
	}

	//color grading effect
	ColorCorrectionEffect* colorEffect;
	GameObject colorEffectObject = scene->CreateEntity("ColorGrading Effect");
	{
		int width, height;
		glfwGetWindowSize(BackendHandler::window, &width, &height);

		colorEffect = &colorEffectObject.emplace<ColorCorrectionEffect>();
		colorEffect->Init(width, height);

		//number here doesn't matter
		colorEffect->LoadLUT("cube/Neutral-512.cube", 0);
		//colorEffect->LoadLUT("cube/BrightenedCorrectionwarm.cube", 0);
		//colorEffect->LoadLUT("cube/colourcorrectcool.cube", 0);
		//colorEffect->LoadLUT("cube/test.cube",0);
		colorEffect->_LUT = colorEffect->_LUTS[0];
	}


	//WorldBuilderV2 builder;
	//builder.BuildNewWorld();
	


	
}