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

	// TODO: ...
	SpriteAnimation::SpriteAnimation(const std::string& name, const std::initializer_list<int>& frames)
	{
		if (frames.size() % 4 != 0) return; // Each frame contains 4 elements (x, y, width, height)
		for (auto it = frames.begin(); it != frames.end(); it += 4)
		{
			m_Frames.emplace_back(*it, *std::next(it), *std::next(it, 2), *std::next(it, 3));
		}
	}

	void SpriteAnimation::play()
	{
		//if (!m_Running)
		//{
			m_CurrentFrame = m_OriginFrame;
			m_Time = 0.0f;
			m_Running = true;
		//}
	}

	void SpriteAnimation::update(float deltaTime)
	{
		if (m_Running)
		{
			m_Time += deltaTime;
			while (m_Time >= m_Interval)
			{
				m_Sprite->setTextureRect(m_Frames[m_CurrentFrame].x, m_Frames[m_CurrentFrame].y, m_Frames[m_CurrentFrame].width, m_Frames[m_CurrentFrame].height);
				if (++m_CurrentFrame >= m_Frames.size())
					m_CurrentFrame = m_OriginFrame;

				m_Time -= m_Interval;
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