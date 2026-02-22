#pragma once

#include <functional>
#include <string>
#include <sstream>
#include <iostream>

namespace Core {
    #ifndef BIT
    #define BIT(x) (1 << (x))
    #endif


	// this is based on Hazel from the Cherno
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseMoved, MouseScrolled,
        MouseButtonPressed, MouseButtonReleased
    };

    enum EventCategory : int
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };


    #define EVENT_CLASS_TYPE(type) \
                static EventType GetStaticType() { return EventType::type; } \
                EventType GetEventType() const override { return GetStaticType(); } \
                const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(categoryFlags) \
                int GetCategoryFlags() const override { return categoryFlags; }

    class Event {
        friend class EventDispatcher;
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

        virtual std::string ToString() const { return GetName(); }
        bool IsInCategory(EventCategory category) const {
            //  return the bitwise and of the category flag and its category
            return GetCategoryFlags() & category;
        }
    protected:
        bool m_Handled = false;
    };
    

    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : m_Event(event) 
        {
        }
        template<typename T>
        bool Dispatch(EventFn<T> func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.m_Handled = func(*(T*)&m_Event);
                return true;
            }
        }
    private: 
        Event& m_Event;
    };
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

}
