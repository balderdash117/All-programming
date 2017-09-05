
#include "AnimatedSprite.h"
#include <Renderer2D.h>
#include <Texture.h>

AnimatedSprite::AnimatedSprite(aie::Texture *texture, int fWidth, int fHeight, int framesPerRow, int maxFrames) :
	m_texture(texture),
	m_frameWidth(fWidth),
	m_frameHeight(fHeight),
	m_framesPerRow(framesPerRow),
	m_maxFrames(maxFrames),
	m_currentFrame(0),
	m_animFps(1.0f),
	m_frameTime(0.0f)
{
	
}
AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::Update(float deltaTime)
{
	m_frameTime += deltaTime;
	if (m_frameTime > 1.0f / m_animFps)
	{
		m_currentFrame += 1;
		m_currentFrame = m_currentFrame % m_maxFrames;
		m_frameTime = 0.0f;
	}
}
void AnimatedSprite::Draw(aie::Renderer2D *renderer, float xPos, float yPos, float width, float height, float rot, float depth, float xO, float yO)
{
	renderer->setUVRect(
		(m_currentFrame % m_framesPerRow) * (m_frameWidth / m_texture->getWidth()),
		(int)(m_currentFrame / m_framesPerRow) * (m_frameHeight / m_texture->getHeight()),
		m_frameWidth / m_texture->getWidth(),
		m_frameHeight / m_texture->getHeight());

	renderer->drawSprite(m_texture, xPos, yPos, width, height, rot, depth, xO, yO);

	renderer->setUVRect(0.0f, 0.0f, 1.0f, 1.0f);
}


void AnimatedSprite::SetFrameSize(float width, float height)
{
	m_frameWidth = width;
	m_frameHeight = height;
}
void AnimatedSprite::SetAnimationFPS(float fps)
{
	m_animFps = fps;
}
void AnimatedSprite::SetFramesPerRow(int fpr)
{
	m_framesPerRow = fpr;
}
void AnimatedSprite::SetMaxFrames(int maxFrames)
{
	m_maxFrames = maxFrames;
}
void AnimatedSprite::SetCurrentFrame(int frameId)
{
	m_currentFrame = frameId % m_maxFrames;
}