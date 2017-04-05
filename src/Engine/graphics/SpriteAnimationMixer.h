#pragma once

#include "SpriteAnimation.h"
#include <map>

namespace engine { namespace graphics {

	enum class MixerState {
		Stopped = 0,
		Playing = 1,
		Paused  = 2
	};

	class SpriteAnimationMixer {
	public:
		SpriteAnimationMixer(const std::vector<SpriteAnimation>& animations);
		SpriteAnimationMixer(const std::initializer_list<SpriteAnimation>& animations);
		~SpriteAnimationMixer();

		void play(const std::string& animationName); // Stop all animations and play this one
		void update(float deltaTime); // Update current animation
		void pause(); // Pause current animation
		void stop(); // Stop current animation
		void reset(); // Stop all animations

		void addAnimation(const SpriteAnimation& animation);
		void removeAnimation(const std::string& animationName);

		std::string getCurrentAnimationName() const { return m_CurrentAnimation; }
	private:
		std::map<std::string, SpriteAnimation> m_Animations;
		std::string m_CurrentAnimation;
		MixerState m_MixerState;
	};

} }