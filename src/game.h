#define FRAMES_PER_SECONDS 60
#define SECONDS_PER_FRAME (1.0f/FRAMES_PER_SECONDS)

#define PLAYBACK_FREQ 44100

#define isButtonPressed(input, btn) (input->buttons[btn].pressed)
#define wasButtonPressed(input, btn) (input->buttons[btn].wasPressed)
#define isKeyPressed(input, key) (input->keys[key].pressed)
#define wasKeyPressed(input, key) (input->keys[key].wasPressed)

#define getScaledSpeed(context, t) ((t) * (context)->globalSpeed)
#define getScaledTime(context, t) ((t) / (context)->globalSpeed)

void setGlobalScale(GameContext* context, f32 scale);
void changeGlobalScale(GameContext* context, f32 deltaScale);

void setGlobalSpeed(GameContext* context, f32 speed);
void changeGlobalSpeed(GameContext* context, f32 deltaSpeed);
