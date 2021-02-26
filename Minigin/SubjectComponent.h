#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
    class GameObject;
}

class SubjectComponent final :
    public BaseComponent
{
public:
    SubjectComponent(dae::GameObject* pGameObject);
    ~SubjectComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;
    void Notify(Event event) const;
    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observer);

    SubjectComponent(const SubjectComponent& other) = delete;
    SubjectComponent(SubjectComponent&& other) = delete;
    SubjectComponent& operator=(const SubjectComponent& other) = delete;
    SubjectComponent& operator=(SubjectComponent&& other) = delete;

private:
    dae::GameObject* m_pGameObject;
    std::vector<Observer*> m_ObserverVector;

};

