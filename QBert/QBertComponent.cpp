#include "MiniginPCH.h"
#include "QBertComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "DiskComponent.h"

QBertComponent::QBertComponent(std::weak_ptr<dae::GameObject> pGameObject)
	:m_pGameObject(pGameObject)
	, m_Lives{ 3 }
{
}

QBertComponent::~QBertComponent()
= default;

void QBertComponent::Update(float dt)
{
	m_MoveTimer += dt;
	if (m_OnDisk)
	{
		m_DiskTimer += dt;
		if (m_DiskTimer >= m_DiskDelay)
		{
			if (!m_pStartLocation.expired())
			{
				SetLocation(m_pStartLocation);
				m_DiskTimer = 0.f;
				m_OnDisk = false;
				m_pDisk.lock()->GetOwner().lock()->SetToBeDestroyed();
				m_pDisk = std::shared_ptr<DiskComponent>(nullptr);
			}
		}
	}
}

void QBertComponent::FixedUpdate(float)
{
}

void QBertComponent::Render(const glm::vec3&) const
{
}

void QBertComponent::GainScore(int score) const
{
	m_pGameObject.lock()->getComponent<SubjectComponent>().lock()->Notify(Event::ChangeScoreEvent, score);
}

void QBertComponent::Die()
{
	ServiceLocator::GetSoundSystem()->Play(1, false);


	--m_Lives;
	m_pGameObject.lock()->getComponent<SubjectComponent>().lock()->Notify(Event::KillEvent);
	if (m_Lives == 0)
	{
		m_pGameObject.lock()->SetToBeDestroyed();
	}
}

int QBertComponent::GetLives() const
{
	return m_Lives;
}

void QBertComponent::SetLocation(std::weak_ptr<GridNodeComponent> gridLocation)
{
	m_pGridLocation = gridLocation;
	m_pGameObject.lock()->SetPosition(m_pGridLocation.lock()->GetWorldPosition().x+8, m_pGridLocation.lock()->GetWorldPosition().y-8);
	if (m_pGridLocation.lock()->ChangeState(1))
	{
		GainScore(25);
	}
}

void QBertComponent::SetStartLocation(std::weak_ptr<GridNodeComponent> gridLocation)
{
	m_pGridLocation = gridLocation;
	m_pGameObject.lock()->SetPosition(m_pGridLocation.lock()->GetWorldPosition().x + 8, m_pGridLocation.lock()->GetWorldPosition().y - 8);
	m_pStartLocation = gridLocation;
}

void QBertComponent::Move(Direction pos)
{
	if (!m_OnDisk && m_MoveTimer >= m_MoveDelay)
	{


		std::weak_ptr<GridNodeComponent> node = m_pGridLocation.lock()->GetConnection(pos);
		if (!node.expired())
		{
			SetLocation(node);
		}
		else
		{
			auto disk = m_pGridLocation.lock()->GetDisk(pos);
			if (!disk.expired())
			{
				MoveOnDisk(disk);
			}
		}
		m_MoveTimer = 0;

	}
}

void QBertComponent::MoveOnDisk(std::weak_ptr<DiskComponent> disk)
{
	m_pGameObject.lock()->SetPosition(disk.lock()->GetWorldPosition().x+8, disk.lock()->GetWorldPosition().y-8);
	m_OnDisk = true;
	m_pGridLocation = std::shared_ptr<GridNodeComponent>(nullptr);
	m_pDisk = disk;
}
