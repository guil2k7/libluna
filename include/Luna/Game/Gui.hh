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

        static inline CGui& GetInstance() {
            assert(instance != nullptr);
            return *instance;
        }

        void Initialise();
        void Render();
        
        inline void Subscribe(IGuiWidget* handler) {
            subscribers.push_back(handler);
        }

    private:
        static CGui* instance;

        std::vector<IGuiWidget* > subscribers;
    };

    /* </NOTSA> */
}
