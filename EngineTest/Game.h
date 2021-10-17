#pragma once
#include "../Minigin/Minigin.h"
class Game :
    public Minigin
{
public:
    void LoadGame() const override;
    void Cleanup() override;
};

