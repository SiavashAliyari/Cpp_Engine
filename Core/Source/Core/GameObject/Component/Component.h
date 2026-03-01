#pragma once
#include "string"

namespace Core {
	class Component {
	public:
		virtual ~Component() = default;
		virtual void OnUpdate(float ts)=0;
		virtual void OnRender()=0;
		std::string GetName(){return m_name;}
	private:
		std::string m_name;
	};
}