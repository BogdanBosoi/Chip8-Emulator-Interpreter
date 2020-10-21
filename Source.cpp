#include "Chip8.hpp"
#include "SDL.h"
#include "SDL_audio.h"
#include <chrono>
#include <iostream>
#include <thread>

Chip8 chip8;

int scale = 10;

int display_width = scale * Chip8::CHIP_WIDTH;
int display_height = scale * Chip8::CHIP_HEIGHT;

constexpr int loop_fps = 6.6666;
constexpr int timer_fps = 16.6666;


// variable declarations
static Uint8* audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

#define BEEP_PATH "beep.wav"

// prototype for our audio callback
// see the implementation for more information
void my_audio_callback(void* userdata, Uint8* stream, int len)
{

	if (audio_len == 0)
		return;

	len = (len > audio_len ? audio_len : len);
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}




static void SDLAudioCallback(void *UserData, Uint8* AudioData, int Length)
{
	memset(AudioData, 0, Length);
}

void Play_Audio()
{
	static Uint32 wav_length; // length of our sample
	static Uint8* wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music


	/* Load the WAV */
	// the specs, length and buffer of our wav are filled
	if (SDL_LoadWAV(BEEP_PATH, &wav_spec, &wav_buffer, &wav_length) == NULL) {
		return ;
	}
	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length

	/* Open the audio device */
	if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}

	/* Start playing */
	SDL_PauseAudio(0);

	// wait until we're don't playing
	while (audio_len > 0) {
		SDL_Delay(100);
	}

	// shut everything down
	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);

}

int main(int argc, char** argv)
{

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_CreateWindowAndRenderer(display_width, display_height, 0, &window, &renderer);

	//Probably on a loop
	SDL_RenderSetScale(renderer, scale, scale);
	SDL_RenderDrawPoint(renderer, 4, 3); //Renders on middle of screen.
	SDL_RenderPresent(renderer);
	chip8.initialize();
	chip8.loadGame("astro.ch8");
	auto loop_start_tick = SDL_GetTicks();
	auto timer_loop_start_tick = SDL_GetTicks();
	while (1)
	{
		auto curr_tick = SDL_GetTicks();
		auto timer_curr_tick = SDL_GetTicks();
		auto delta = curr_tick - loop_start_tick;
		auto delta_timer = timer_curr_tick - timer_loop_start_tick;
		if (delta > loop_fps)
		{
			chip8.emulateCycle();


			if (chip8.render)
			{
				for (int i = 0; i < 32; i++)
					for (int j = 0; j < 64; j++)
					{
						SDL_SetRenderDrawColor(renderer, 255 * chip8.gfx[i * 64 + j], 255 * chip8.gfx[i * 64 + j], 255 * chip8.gfx[i * 64 + j], 255);
						SDL_RenderDrawPoint(renderer, j, i);
					}
				SDL_RenderPresent(renderer);
				chip8.render = false;
			}
			const Uint8* keys = SDL_GetKeyboardState(NULL);
			while (SDL_PollEvent(&event))
			{
				switch (event.type) {
				case SDL_QUIT:
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						break;
					case SDLK_x:
						chip8.key[0] = 1;
						break;
					case SDLK_1:
						chip8.key[1] = 1;
						break;
					case SDLK_2:
						chip8.key[2] = 1;
						break;
					case SDLK_3:
						chip8.key[3] = 1;
						break;
					case SDLK_q:
						chip8.key[4] = 1;
						break;
					case SDLK_w:
						chip8.key[5] = 1;
						break;
					case SDLK_e:
						chip8.key[6] = 1;
						break;
					case SDLK_a:
						chip8.key[7] = 1;
						break;
					case SDLK_s:
						chip8.key[8] = 1;
						break;
					case SDLK_d:
						chip8.key[9] = 1;
						break;
					case SDLK_z:
						chip8.key[0xA] = 1;
						break;
					case SDLK_c:
						chip8.key[0xB] = 1;
						break;
					case SDLK_4:
						chip8.key[0xC] = 1;
						break;
					case SDLK_r:
						chip8.key[0xD] = 1;
						break;
					case SDLK_f:
						chip8.key[0xE] = 1;
						break;
					case SDLK_v:
						chip8.key[0xF] = 1;
						break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
					case SDLK_x:
						chip8.key[0] = 0;
						break;
					case SDLK_1:
						chip8.key[1] = 0;
						break;
					case SDLK_2:
						chip8.key[2] = 0;
						break;
					case SDLK_3:
						chip8.key[3] = 0;
						break;
					case SDLK_q:
						chip8.key[4] = 0;
						break;
					case SDLK_w:
						chip8.key[5] = 0;
						break;
					case SDLK_e:
						chip8.key[6] = 0;
						break;
					case SDLK_a:
						chip8.key[7] = 0;
						break;
					case SDLK_s:
						chip8.key[8] = 0;
						break;
					case SDLK_d:
						chip8.key[9] = 0;
						break;
					case SDLK_z:
						chip8.key[0xA] = 0;
						break;
					case SDLK_c:
						chip8.key[0xB] = 0;
						break;
					case SDLK_4:
						chip8.key[0xC] = 0;
						break;
					case SDLK_r:
						chip8.key[0xD] = 0;
						break;
					case SDLK_f:
						chip8.key[0xE] = 0;
						break;
					case SDLK_v:
						chip8.key[0xF] = 0;
						break;
					}
					break;
				}
			}
			loop_start_tick = curr_tick;
		}
		if (delta_timer > timer_fps)
		{
			if (chip8.delay_timer > 0)
				--chip8.delay_timer;

			if (chip8.sound_timer > 0)
			{
				if (chip8.sound_timer == 1)
				{
					printf("BEEP\n");
					Play_Audio();
				}
				--chip8.sound_timer;
			}
			timer_loop_start_tick = timer_curr_tick;
		}

	}

	return 0;
}






