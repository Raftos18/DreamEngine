#pragma once

#include "Graphics\window.h"
#include "Utils\timer.h"
#include "Graphics\Shaders\Shader.h"
#include "Math\maths.h"
#include "Graphics\sprite.h"

#include "Graphics\Layers\layers.h"
#include "Graphics\Layers\group.h"
#include "Graphics\texture.h"

#define RENDERER_TYPE 1

#if 1
int main()
{
	using namespace dream;
	using namespace graphics;
	using namespace maths;

	Window window("dream!", 960, 540);
	Shader* sh = new Shader("./Graphics/Shaders/basic.vert", "./Graphics/Shaders/basic.frag");
	TileLayer layer(sh);

	Timer time;
	float timer = 0.0f;
	int frames = 0;

	Texture* ta = new Texture("C:/Users/nraft/Desktop/test.png");	
	Texture* tb = new Texture("C:/Users/nraft/Desktop/test2.png");

	for (float i = -9.0f; i < 9.0f; i++)
	{
		for (float j = -16.0f; j < 16.0f; j++) 
		{			
			//layer.Add(new Sprite(j, i, 0.9f, 0.9f, Vector4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			layer.Add(new Sprite(j, i, 1.0f, 1.0f, rand() % 2 == 0 ? ta : tb));
		}
	}

	sh->Enable();
	
	GLint texIDs[] = {
		0,1,2,3,4,5,6,7,8,9
	};


	sh->SetUniform1iv("textures", 10, texIDs);
	
	sh->SetUniformMat4("pr_matrix", Mat4x4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	while (!window.Closed())
	{
		window.Clear();

		float x, y;
		window.GetMousePosition(x, y);
		sh->SetUniform2f("lightPos", Vector2((float)(x * 32.0f / window.GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.GetHeight())));
		layer.Render();

		frames++;
		if (time.Elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}

		window.Update();
	}
	delete ta;
	delete tb;

	return 0;
}
#else

#endif
