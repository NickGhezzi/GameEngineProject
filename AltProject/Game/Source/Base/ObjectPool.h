#ifndef __ObjectPool_H__
#define __ObjectPool_H__

template <class Type>
class ObjectPool
{
protected:
    std::vector<Type> m_Objects;

public:
    ~ObjectPool()
    {
        for( GameObject* object : m_Objects )
        {
            delete object;
        }
    }

    Type GetObjectFromPool()
    {
        if( m_Objects.empty() )
            return nullptr;

        Type obj = m_Objects.back();
        m_Objects.pop_back();
        return obj;
    }

    void AddObjectToPool(Type object)
    {
        m_Objects.push_back(object);
    }
};

#endif //__ObjectPool_H__

