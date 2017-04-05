#include "SpriteAnimationMixer.h"

namespace engine { namespace graphics {

	SpriteAnimationMixer::SpriteAnimationMixer(const std::vector<graphics::SpriteAnimation>& animations)
		: m_MixerState(MixerState::Stopped)
	{
		for (auto it = animations.begin(); it != animations.end(); ++it)
		{
			m_Animations[it->getName()] = *it;
		}
	}

	SpriteAnimationMixer::SpriteAnimationMixer(const std::initializer_list<graphics::SpriteAnimation>& animations)
		: m_MixerState(MixerState::Stopped)
	{
		for (auto it = animations.begin(); it != animations.end(); ++it)
		{
			m_Animations[it->getName()] = *it;
		}
	}

	SpriteAnimationMixer::~SpriteAnimationMixer()
	{

	}

	void SpriteAnimationMixer::play(const std::string& animationName)
	{
		// Stop all animations
		reset();

		// Play specified animation
		if (m_Animations.count(animationName))
		{
			m_Animations[animationName].play();
			m_CurrentAnimation = animationName;
			m_MixerState = MixerState::Playing;
		}
	}

	void SpriteAnimationMixer::update(float deltaTime)
	{
		if (m_Animations.count(m_CurrentAnimation))
			m_Animations[m_CurrentAnimation].update(deltaTime);
	}

	void SpriteAnimationMixer::pause()
	{
		if (m_MixerState != MixerState::Playing)
			return;

		if (m_Animations.count(m_CurrentAnimation))
		{
			m_Animations[m_CurrentAnimation].pause();
			m_MixerState = MixerState::Paused;
		}
	}

	void SpriteAnimationMixer::stop()
	{
		if (m_Animations.count(m_CurrentAnimation))
		{
			m_Animations[m_CurrentAnimation].stop();
			m_MixerState = MixerState::Stopped;
		}
	}

	void SpriteAnimationMixer::reset()
	{
		// Stop all animations
		for (auto it = m_Animations.begin(); it != m_Animations.end(); ++it)
			it->second.stop();

		m_MixerState = MixerState::Stopped;
	}

	void SpriteAnimationMixer::addAnimation(const SpriteAnimation& animation)
	{
		m_Animations[animation.getName()] = animation;
	}

	void SpriteAnimationMixer::removeAnimation(const std::string& animationName)
	{
		m_Animations.erase(animationName);
	}

} }