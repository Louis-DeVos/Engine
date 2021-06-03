#pragma once
#include "../Minigin/Minigin.h"
class Game :
    public dae::Minigin
{
public:
    void LoadGame() const;
    void Cleanup();
};

