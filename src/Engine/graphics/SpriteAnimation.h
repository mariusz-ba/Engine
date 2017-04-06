#pragma once

#include <string>
#include <vector>
#include <chrono>
#include "Sprite.h"

using namespace std::chrono;

namespace engine { namespace graphics {

	template <typename T>
	struct Rect {
		Rect(T _x, T _y, T _width, T _height) :
			x(_x), y(_y), width(_width), height(_height)
		{}

		T x;
		T y;
		T width;
		T height;
	};

	class SpriteAnimation {
	public:
		SpriteAnimation();
		SpriteAnimation(const std::string& name, const std::vector<Rect<int>>& frames);
		SpriteAnimation(const std::string& name, const std::initializer_list<int>& frames); // no implementation

		inline void setSprite(Sprite* sprite) { m_Sprite = sprite; }
		inline const Sprite* getSprite() const { return m_Sprite; }

		void play();
		void update(float deltaTime);
		void pause();
		void stop();
		void reset();

		inline void setName(const std::string& name) { m_Name = name; }
		inline void setFrames(const std::vector<Rect<int>>& frames) { m_Frames = frames; }
		inline void setCurrentFrame(unsigned int index) { m_CurrentFrame = index; }
		inline void setOriginFrame(unsigned int index) { m_OriginFrame = index; }
		inline void setInterval(float interval) { m_Interval = interval; }

		inline std::string getName() const { return m_Name; }
		inline const std::vector<Rect<int>>& getFrames() const { return m_Frames; }
		inline int getCurrentFrame() const { return m_CurrentFrame; }
		inline int getOriginFrame() const { return m_OriginFrame; }
		inline float getInterval() const { return m_Interval; }
		inline bool isRunning() const { return m_Running; }

	private:
		std::string m_Name;
		std::vector<Rect<int>> m_Frames;
		unsigned int m_CurrentFrame = 0;
		unsigned int m_OriginFrame = 0;
		float m_Interval = 1.0f;
		Sprite* m_Sprite = nullptr;
		bool m_Running = false;
		//steady_clock::time_point m_LastUpdate;
		float m_Time;
	};

} }