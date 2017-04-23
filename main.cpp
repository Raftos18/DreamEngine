#pragma once
#define RENDERER_TYPE 1

#if RENDERER_TYPE
#include "Math\maths.h"
#include "Input\input.h"

#include "System\window.h"
#include "Graphics\Layers\layers.h"
#include "Graphics\Layers\group.h"
#include "Graphics\Shaders\shader.h"

#include "Graphics\sprite.h"
#include "Graphics\texture.h"
#include "Graphics\label.h"
#include "Graphics\textRenderer.h"

#include "Graphics/textureManager.h"
#include "Audio\soundManager.h"

#include "Utils\dreamUtils.h"

using namespace dream;
using namespace system;
using namespace graphics;
using namespace maths;
using namespace input;
using namespace audio;

int main()
{
	Window window("dream!", 1980, 1080);	
	Input input(window.GetWindowHandle());		
	window.SetVSync(true);

	//SoundManager::Instance().Init();	
	//SoundManager::Instance().Add(new Sound("TestSong", "./Audio/blip.wav"));

	Shader* sh = new Shader("./Graphics/Shaders/basic.vert", "./Graphics/Shaders/basic.frag");	
	TileLayer layer(sh);
	
	utilities::Timer GTimer;
	GTimer.Init();		

	int frames = 0;		

	for (float i = -9.0f; i < 9.0f; i += .1f)
	{
		for (float j = -16.0f; j < 16.0f; j += .1f) 
		{			
			if(rand() % 3 == 0)
				layer.Add(new Sprite(j, i, .1f, .1f, 0xffffffff));
			else
				layer.Add(new Sprite(j, i, .1f, .1f, 0xff000000));								
		}
	}		
		
	float t = 0.0f;
	float updateStep = 1.0f / 60.0f;
	bool vsync = false;
	float ti = 0.0f;
	float ut = 0.0f;

	utilities::Timer UTimer;
	UTimer.Init();

	float terbulance = 1.0f;
	float color = 1.0f;
	while (!window.Closed())
	{	
		window.Clear();
		if (ti < 1.0f)
		{					
			t += 0.1f * (1.0f / GTimer.GetTime());

			const std::vector<IRenderable2D*>& rs = layer.GetRenderables();
			for (size_t i = 0; i < rs.size(); i++)
			{												
				if (i % 2 == 0) {					
					terbulance += GTimer.GetElapsedSeconds() * .2f;
					color -= 0.2 * GTimer.GetElapsedSeconds();
					rs[i]->SetColor(Vector4(0.0f, 0.8, 0.5f, 1));									
				}
				else
				{
					rs[i]->SetColor(Vector4(0.0, 0.0, terbulance, 1));															
				}
				rs[i]->m_Position = Mat4x4::Rotate(cos(terbulance), Vector3(0.0f, 0.0f, -1.0f)) * rs[i]->m_Position;
			}				

			if (terbulance > 2000000)
				terbulance = 1.0f;

			UTimer.Update();		

			// Happens every frame
			float x, y;			
			input.GetMousePosition(x, y);
			sh->SetUniform2f("lightPos", Vector2((float)(x * 32.0f / window.GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.GetHeight())));

			if (input.IsKeyUp(KeyboardKeys::P))
			{
				std::cout << "Play button pressed\n";
				window.MakeFullscreen();			
				window.SetVSync(true);
			}

			ti += GTimer.GetElapsedSeconds();			
			
			layer.Render();
			GTimer.Update();
			window.Update();
		}	

		// Happens once a sec.
		if(ti > 1.0f)		
		{
			ti = 0.0f;
			ut = 0.0f;			
			printf("%f fps\n", GTimer.GetFPS());					
		}		

	}	
	return 0;
}
#else

#include "System\window.h"
#include "Input\input.h"

#include "Audio\soundManager.h"

using namespace dream;
using namespace system;
using namespace input;
using namespace audio;

	Window window("dream!", 800, 600);
	Input minput(window.GetWindowHandle());	

	float volume = 1.0f;
	int main() 
	{
		SoundManager::Instance().Init();
		SoundManager::Instance().Add(new Sound("TestSong", "./Audio/test.ogg"));
		
		Sound* sound = SoundManager::Instance().Get("TestSong");

		while (!window.Closed())
		{
			window.Clear();		
			if (minput.IsKeyUp(KeyboardKeys::P))
			{								

				if (!sound->isPlaying())
					sound->Resume();
				else {
					std::cout << "P pressed\n";
					sound->Play();
				}				
			}			
			if (minput.IsKeyUp(KeyboardKeys::S))
			{
				std::cout << "P pressed\n";
				sound->Pause();
			}
			if (minput.IsKeyUp(KeyboardKeys::UP))
			{
				volume += 0.1f;
				std::cout << "Down Arrow pressed volume = " << volume << "\n";
				sound->SetVolume(volume);
			}
			if (minput.IsKeyUp(KeyboardKeys::DOWN))
			{
				volume -= 0.1f;
				std::cout << "Down Arrow pressed volume = " << volume << "\n";
				sound->SetVolume(volume);
			}
			if (minput.IsKeyUp(KeyboardKeys::ESC))
			{
				window.Close();
			}

			SoundManager::Instance().Update();

			window.Update();
		}
	}

#endif
