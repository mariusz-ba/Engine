#include "SpriteAnimation.h"

namespace engine { namespace graphics {

	SpriteAnimation::SpriteAnimation() :
		m_Name("unnamed")
	{
	}

	SpriteAnimation::SpriteAnimation(const std::string& name, const std::vector<Rect<int>>& frames) :
		m_Name(name), m_Frames(frames)
	{

	}

	SpriteAnimation::SpriteAnimation(const std::string& name, const std::initializer_list<int>& frames)
	{

	}

	void SpriteAnimation::play()
	{
		if (!m_Running)
		{
			m_CurrentFrame = m_OriginFrame;
			m_LastUpdate = steady_clock::now();
			m_Running = true;
		}
	}

	void SpriteAnimation::update()
	{
		if (m_Running)
		{
			steady_clock::time_point current = steady_clock::now();
			float duration = duration_cast<milliseconds>(current - m_LastUpdate).count() / 1000.f;
			while (duration >= m_Interval)
			{
				m_Sprite->setTextureRect(m_Frames[m_CurrentFrame].x, m_Frames[m_CurrentFrame].y, m_Frames[m_CurrentFrame].width, m_Frames[m_CurrentFrame].height);
				if (++m_CurrentFrame >= m_Frames.size())
					m_CurrentFrame = m_OriginFrame;

				duration -= m_Interval;
				m_LastUpdate = current;
			}
		}
	}

	void SpriteAnimation::pause()
	{
		m_Running = false;
	}

	void SpriteAnimation::stop()
	{
		pause();
		reset();
	}

	void SpriteAnimation::reset()
	{
		m_CurrentFrame = m_OriginFrame;
	}

} }