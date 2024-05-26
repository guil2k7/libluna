// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <vector>
#include <cassert>

namespace Luna::Game {
    /* <NOTSA> */

    class IGuiWidget {
    public:
        virtual void Render() = 0;
    };

    class CGui {
    public:
        static CGui& Create();

        static inline CGui& Instance() {
            assert(s_Instance != nullptr);
            return *s_Instance;
        }

        void Initialise();
        void Render();

        inline void Subscribe(IGuiWidget* handler) {
            m_Subscribers.push_back(handler);
        }

    private:
        static CGui* s_Instance;

        std::vector<IGuiWidget*> m_Subscribers;
    };

    /* </NOTSA> */
}
