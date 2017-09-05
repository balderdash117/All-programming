#pragma once

namespace aie
{
	class Texture;
	class Renderer2D;
};

class AnimatedSprite
{
public:

	AnimatedSprite(aie::Texture *texture, int fWidth, int fHeight, int framesPerRow, int maxFrames );
	~AnimatedSprite();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D *renderer, float xPos, float yPos, float width, float height, float rot = 0.0f, float depth = 0.0f, float xO = 0.5f, float yO = 0.5f);

	void SetFrameSize(float width, float height);
	void SetAnimationFPS(float fps);
	void SetFramesPerRow(int fpr);
	void SetMaxFrames(int maxFrames);
	void SetCurrentFrame(int frameId);


protected:



	float m_frameWidth = 128.0f;
	float m_frameHeight = 128.0f;
	int m_framesPerRow = 8;
	int m_currentFrame = 0;
	int m_maxFrames = 64;
	float m_animFps = 6.0f;
	float m_frameTime = 0.0f;
	aie::Texture * m_texture = nullptr;

private:
};