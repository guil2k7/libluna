// Copyright 2024 Maicol Castro (maicolcastro.abc@gmail.com).

#pragma once

#include <vector>
#include <cassert>

namespace Luna::Game {

class IGuiWidget {
public:
    virtual void Render() = 0;
};

class CGui {
public:
    static inline CGui& Instance() {
        assert(m_Instance != nullptr);
        return *m_Instance;
    }

    static void Initialize();
    void Render();

    inline void Subscribe(IGuiWidget* handler) {
        m_Subscribers.push_back(handler);
    }

private:
    static CGui* m_Instance;

    std::vector<IGuiWidget*> m_Subscribers;
};

} // namespce Luna::Game
