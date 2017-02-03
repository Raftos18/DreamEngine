#pragma once

#include "window.h"
#include "Shader.h"
#include "maths.h"
#include "sprite.h"

#include "layers.h"
#include "group.h"

#include "timer.h"
#include "texture.h"

#define RENDERER_TYPE 1

#if 1
int main()
{
	using namespace dream;
	using namespace graphics;
	using namespace maths;

	Window window("dream!", 960, 540);
	Shader* sh = new Shader("basic.vert", "basic.frag");
	TileLayer layer(sh);

	Timer time;
	float timer = 0.0f;
	int frames = 0;


	for (float i = -9.0f; i < 9.0f; i++)
	{
		for (float j = -16.0f; j < 16.0f; j++)
		{
			layer.Add(new Sprite(j, i, 0.9f, 0.9f, Vector4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}

	sh->Enable();

	glActiveTexture(GL_TEXTURE0);
	Texture texture("C:/Users/nraft/Desktop/test.png");
	texture.Bind();	

	sh->SetUniform1i("tex", 0);	
	sh->SetUniformMat4("pr_matrix", Mat4x4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	while (!window.Closed())
	{
		window.Clear();

		float x, y;
		window.GetMousePosition(x, y);
		sh->SetUniform2f("lightPos", Vector2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		layer.Render();

		frames++;
		if (time.Elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d\n", frames);
			frames = 0;
		}

		window.Update();
	}

	return 0;
}
#else

#endif
