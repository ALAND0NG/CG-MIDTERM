#include <AssetLoader.h>
#include <ObjLoader.h>
#include <RenderingManager.h>
#include <Texture2D.h>
std::vector<std::string> AssetLoader::RendererNames;
std::vector<RendererComponent> AssetLoader::Renderers;
void AssetLoader::Init() //doing it manually because, actually I don't know why
{
	//basic floor tile
	VertexArrayObject::sptr plane = ObjLoader::LoadFromFile("model/plane.obj");
	Texture2D::sptr floor = Texture2D::LoadFromFile("image/floor.png");
	//Texture2D::sptr wall = Texture2D::LoadFromFile("image/wall.png"); broken I have no ide why
	Texture2D::sptr noSpec = Texture2D::LoadFromFile("image/grassSpec.png");
	ShaderMaterial::sptr Floor_Mat = ShaderMaterial::Create();
	Floor_Mat->Shader = RenderingManager::NoOutline;
	Floor_Mat->Set("s_Diffuse", floor);
	Floor_Mat->Set("s_Specular", noSpec);
	Floor_Mat->Set("u_Shininess", 2.0f);
	Floor_Mat->Set("u_TextureMix", 0.0f);
	RendererComponent FloorTile;
	FloorTile.SetMaterial(Floor_Mat).SetMesh(plane);
	Renderers.push_back(FloorTile);
	RendererNames.push_back("Floor");

	

	Texture2D::sptr WallSpec = Texture2D::LoadFromFile("image/grassSpec.png");
	
	ShaderMaterial::sptr Wall_Mat = ShaderMaterial::Create();
	Wall_Mat->Shader = RenderingManager::NoOutline;
	Wall_Mat->Set("s_Diffuse", floor);
	Wall_Mat->Set("s_Specular", WallSpec);
	Wall_Mat->Set("u_Shininess", 2.0f);
	Wall_Mat->Set("u_TextureMix", 0.0f);
	RendererComponent Wall_Tile;
	Wall_Tile.SetMaterial(Wall_Mat).SetMesh(plane);
	Renderers.push_back(Wall_Tile);
	RendererNames.push_back("Wall");

	//Fire Enemy
	/*
	VertexArrayObject::sptr FE_Mesh = ObjLoader::LoadFromFile("model/Fire_Enemy.obj");
	Texture2D::sptr FE_Tex = Texture2D::LoadFromFile("image/FE_TEXTURE.png");
//	Texture2D::sptr noSpec = Texture2D::LoadFromFile("image/grassSpec.png");
	ShaderMaterial::sptr FE_MAT = ShaderMaterial::Create();
	FE_MAT->Shader = RenderingManager::BaseShader;
	FE_MAT->Set("s_Diffuse", FE_Tex);
	FE_MAT->Set("s_Specular", noSpec);
	FE_MAT->Set("u_Shininess", 2.0f);
	FE_MAT->Set("u_TextureMix", 0.0f);
	RendererComponent Fire_Enemy;
	Fire_Enemy.SetMaterial(FE_MAT).SetMesh(FE_Mesh);
	Renderers.push_back(Fire_Enemy);
	RendererNames.push_back("Fire Enemy");
	*/

	//Fire Enemy
	VertexArrayObject::sptr Ice_Mesh = ObjLoader::LoadFromFile("model/Ice projectile.obj");
	Texture2D::sptr Ice_Tex = Texture2D::LoadFromFile("image/icetexture.png");
	//	Texture2D::sptr noSpec = Texture2D::LoadFromFile("image/grassSpec.png");
	ShaderMaterial::sptr Ice_Mat = ShaderMaterial::Create();
	Ice_Mat->Shader = RenderingManager::BaseShader;
	Ice_Mat->Set("s_Diffuse", Ice_Tex);
	Ice_Mat->Set("s_Specular", noSpec);
	Ice_Mat->Set("u_Shininess", 2.0f);
	Ice_Mat->Set("u_TextureMix", 0.0f);
	RendererComponent Ice_Proj;
	Ice_Proj.SetMaterial(Ice_Mat).SetMesh(Ice_Mesh);
	Renderers.push_back(Ice_Proj);
	RendererNames.push_back("Water_Proj");


}
RendererComponent& AssetLoader::GetRendererFromStr(std::string name)
{
	for (int i = 0; i < Renderers.size(); i++)
	{
		if (name == RendererNames[i])
		{
			return Renderers[i];
		}
	}
	return Renderers[0]; //backup
}
/*
Mesh& AssetLoader::GetMeshFromStr(std::string name)
{
	// TODO: insert return statement here
	for (int i = 0; i < m_Meshes.size(); i++)
	{
		if (name == m_MeshNames[i])
		{
			return m_Meshes[i];
		}
	}
	return m_Meshes[0];

}

Material& AssetLoader::GetMatFromStr(std::string name)
{
	// TODO: insert return statement here

	for (int i = 0; i < m_Materials.size(); i++)
	{
		if (name == m_MaterialNames[i])
		{
			return m_Materials[i];
		}
	}
	return m_Materials[0];
}
*/