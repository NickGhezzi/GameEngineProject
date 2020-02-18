#pragma once

template <class Type>
class ObjectPool
{
protected:
    std::vector<Type> m_Objects;

public:

    ~ObjectPool()
    {
        for (GameObject* obj : m_Objects)
        {
            delete obj;
        }
    }

    void AddObjectToPool(Type obj)
    {
        m_Objects.push_back(obj);
    }

    Type GetObjectFromPool()
    {
        if (m_Objects.size() == 0)
        {
            return nullptr;
        }

        Type obj = m_Objects.back();
        
        m_Objects.pop_back();
        
        return obj;
    }

};