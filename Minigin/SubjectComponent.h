#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <vector>


class GameObject;


class SubjectComponent final :
    public BaseComponent
{
public:
    SubjectComponent(std::weak_ptr<GameObject> pGameObject);
    ~SubjectComponent() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;
    void Notify(Event event) const;
    void Notify(Event event, int num) const;
    void Notify(Event event, const std::string& str) const;
    void AddObserver(std::shared_ptr<Observer> observer);
    std::weak_ptr<GameObject> GetOwner() const override { return m_pGameObject; }

    SubjectComponent(const SubjectComponent& other) = delete;
    SubjectComponent(SubjectComponent&& other) = delete;
    SubjectComponent& operator=(const SubjectComponent& other) = delete;
    SubjectComponent& operator=(SubjectComponent&& other) = delete;

private:
    std::weak_ptr<GameObject> m_pGameObject;
    std::vector<std::shared_ptr<Observer>> m_ObserverVector;

};

